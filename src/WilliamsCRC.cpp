/* /////////////////////////////////////////////////////////////////////////
 * File:        WilliamsCRC.cpp
 *
 * Purpose:     Implementation of WilliamsCRC API.
 *
 * Created:     1st March 2010
 * Updated:     31st December 2023
 *
 * Author:      Matthew Wilson
 *
 * Copyright (c) 2019-2023, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2010-2019, Matthew Wilson and Synesis Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Information Systems
 *   nor the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes - 1
 */

#include <WilliamsCRC/WilliamsCRC.h>

#include <stlsoft/internal/safestr.h>
#include <stlsoft/smartptr/scoped_handle.hpp>

#define false                                               false
#define true                                                true
#include <crcmodel.h>
#undef false
#undef true

#include <assert.h>
#include <errno.h>

/* /////////////////////////////////////////////////////////////////////////
 * typedefs
 */

struct WilliamsCRC_info_t
{
    cm_t        cm;
};

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

int
WilliamsCRC_cm_init_(
    cm_t*           cm
,   int             crc_bits
,   crc_poly_t      polynomial
);

void
WilliamsCRC_cm_destroy_(
    cm_t*           cm
);

void
WilliamsCRC_Add_(
    cm_t&           cm
,   void const*     pv
,   size_t          cb
);

void
WilliamsCRC_GetCRC_(
    cm_t&           cm
,   crc_result_t*   result
);

int
WilliamsCRC_CalculateBlockCrc_(
    void const*     pv
,   size_t          cb
,   int             crc_bits
,   crc_poly_t      polynomial
,   crc_result_t*   result
);

int
WilliamsCRC_CalculateFileCrc_(
    /* [in] */  char const*     path
,   /* [in] */  size_t          cbMaxToRead
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
);

int
WilliamsCRC_CalculateFileHandleCrc_(
    /* [in] */  FILE*           h
,   /* [in] */  size_t          cbMaxToRead
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
);

} /* anonymous namespace */

/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace
{

static int WilliamsCRC_fopen_(
    FILE**          pf
,   char const*     path
,   char const*     mode
)
{
    STLSOFT_ASSERT(NULL != pf);

#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS) && \
    defined(STLSOFT_COMPILER_IS_MSVC)

    return ::fopen_s(pf, path, mode);

#else
    *pf = ::fopen(path, mode);

    return (NULL != *pf) ? 0 : (0 != errno) ? errno : EMFILE;
#endif
}

} /* anonymous namespace */

/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

namespace {

int
WilliamsCRC_cm_init_(
    cm_t*           cm
,   int             crc_bits
,   crc_poly_t      polynomial
)
{
    crc_poly_t default_poly = 0;

    assert(NULL != cm);

    /*
    see:
    - http://techref.massmind.org/techref/method/math/crcguide.html
    - http://users.ece.cmu.edu/~koopman/crc/index.html
    - https://en.wikipedia.org/wiki/Cyclic_redundancy_check#Polynomial_representations
    */

    if (0 == polynomial)
    {
        switch (crc_bits)
        {
        case 4:

            default_poly    =   0x00000009; /* CRC-4-ITU ( Reciprocal) */
            break;
        case 5:

            default_poly    =   0x00000012; /* CRC-5-USB (Reversed Reciprocal) */
            break;
        case 6:

            default_poly    =   0x00000026; /* CRC-6-DARC (Reversed) */
            break;
        case 7:

            default_poly    =   0x00000011; /* CRC-7 (Reciprocal) */
            break;
        case 8:

            default_poly    =   0x00000057; /* CRC-8 (Reciprocal) */
            break;
        case 10:

            default_poly    =   0x000002BA; /* CRC-10-GSM (Reversed Reciprocal) */
            break;
        case 11:

            default_poly    =   0x00000385; /* CRC-11 (Normal) */
            break;
        case 12:

            default_poly    =   0x00000C07; /* CRC-12 (Reversed Reciprocal) */
            break;
        case 14:

            default_poly    =   0x00000805; /* CRC-14-DARC (Normal) */
            break;
        case 15:

            default_poly    =   0x00004CD1; /* CRC-15-CAN (Reversed) */
            break;
        case 16:

            default_poly    =   0x0000CC27; /* CRC-16 (Reciprocal) */
            break;
        case 24:

            default_poly    =   0x005D6DCB; /* CRC-24 (Normal) */
            break;
        case 30:

            default_poly    =   0x38E74301; /* CRC-30 (Reversed) */
            break;
        case 32:

            default_poly    =   0x82F63B78; /* CRC-32C (Reversed) */
            break;
#if 0
        case 40:

            default_poly    =   0x0000000004820009; /* CRC-40-GSM (Normal) */
            break;
#endif
#if 0
        case 64:

            default_poly    =   0x92D8AF2BAF0E1E85; /* CRC-64-ECMA (Reciprocal) */
            break;
#endif
        default:

            return EINVAL;
        }
    }

    cm->cm_width    =   crc_bits;
    if (0 != polynomial)
    {

        assert(0 != polynomial);

        cm->cm_poly =   polynomial;
    }
    else
    {

        assert(0 != default_poly);

        cm->cm_poly =   default_poly;
    }
    cm->cm_init     =   0L;
    cm->cm_refin    =   true;
    cm->cm_refot    =   true;
    cm->cm_xorot    =   0L;

    cm_ini(cm);

    return 0;
}

void
WilliamsCRC_cm_destroy_(
    cm_t*        /* cm */
)
{
}

void
WilliamsCRC_Add_(
    cm_t&           cm
,   void const*     pv
,   size_t          cb
)
{
    cm_blk(&cm, static_cast<p_ubyte_>(const_cast<void*>(pv)), (ulong)cb);
}

void
WilliamsCRC_GetCRC_(
    cm_t&           cm
,   crc_result_t*   result
)
{
    *result = cm_crc(&cm);
}

int
WilliamsCRC_CalculateBlockCrc_(
    void const*     pv
,   size_t          cb
,   int             crc_bits
,   crc_poly_t      polynomial
,   crc_result_t*   result
)
{
    cm_t    cm;
    int     r   =   WilliamsCRC_cm_init_(&cm, crc_bits, polynomial);

    if (0 == r)
    {
        stlsoft::scoped_handle<cm_t*>  scoper(&cm, WilliamsCRC_cm_destroy_);

        WilliamsCRC_Add_(cm, pv, cb);

        WilliamsCRC_GetCRC_(cm, result);
    }

    return r;
}

int
WilliamsCRC_CalculateFileCrc_(
    /* [in] */  char const*     path
,   /* [in] */  size_t          cbMaxToRead
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
)
{
    FILE* f;
    int   e = WilliamsCRC_fopen_(&f, path, "rb");

    if (0 != e)
    {
        return e;
    }
    else
    {
        stlsoft::scoped_handle<FILE*> scoper2(f, ::fclose);

        return WilliamsCRC_CalculateFileHandleCrc_(
                f
            ,   cbMaxToRead
            ,   crc_bits
            ,   polynomial
            ,   result
            ,   pcbRead
            );
    }
}

int
WilliamsCRC_CalculateFileHandleCrc_(
    /* [in] */  FILE*           f
,   /* [in] */  size_t          cbMaxToRead
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
)
{
    cm_t    cm;
    int     r   =   WilliamsCRC_cm_init_(&cm, crc_bits, polynomial);

    assert(NULL != pcbRead);

    *pcbRead = 0;

    if (0 == r)
    {
        stlsoft::scoped_handle<cm_t*>   scoper(&cm, WilliamsCRC_cm_destroy_);

        unsigned char                   bytes[2048];
        size_t                          numToRead   =   (0 == cbMaxToRead) ? sizeof(bytes) : (cbMaxToRead < sizeof(bytes)) ? cbMaxToRead : sizeof(bytes);

        assert(numToRead <= sizeof(bytes));

        { for(size_t n; 0 != numToRead && 0 != (n = ::fread(&bytes[0], 1, numToRead, f)); )
        {
            *pcbRead += n;

            WilliamsCRC_Add_(cm, bytes, n);

            if (0 != cbMaxToRead)
            {
                size_t remaining;

                assert(*pcbRead <= cbMaxToRead);

                remaining = cbMaxToRead - *pcbRead;

                if (remaining > sizeof(bytes))
                {
                    numToRead = sizeof(bytes);
                }
                else
                {
                    numToRead = remaining;
                }

                assert(numToRead <= sizeof(bytes));
            }
        }}

        WilliamsCRC_GetCRC_(cm, result);
    }

    return r;
}

} /* anonymous namespace */

/* /////////////////////////////////////////////////////////////////////////
 * API Functions
 */

#ifdef __cplusplus
extern "C" {
#endif

int
WilliamsCRC_Init(void)
{
    return 0;
}

void
WilliamsCRC_Uninit(void)
{
}

int
WilliamsCRC_Create(
    int             crc_bits
,   crc_poly_t      polynomial
,   WilliamsCRC_t*  pwcrc
)
{
    assert(NULL != pwcrc);

    *pwcrc = new WilliamsCRC_info_t();

    if (NULL == *pwcrc)
    {
        return ENOMEM;
    }
    else
    {
        return WilliamsCRC_cm_init_(
                &(*pwcrc)->cm
            ,   crc_bits
            ,   polynomial
            );
    }
}

void
WilliamsCRC_Destroy(
    WilliamsCRC_t wcrc
)
{
    if (NULL != wcrc)
    {
        WilliamsCRC_cm_destroy_(&wcrc->cm);

        delete wcrc;
    }
}

void
WilliamsCRC_Add(
    WilliamsCRC_t wcrc
,   void const*   pv
,   size_t        cb
)
{
    WilliamsCRC_Add_(
        wcrc->cm
    ,   pv
    ,   cb
    );
}

void
WilliamsCRC_GetCRC(
    WilliamsCRC_t wcrc
,   crc_result_t* result
)
{
    WilliamsCRC_GetCRC_(
        wcrc->cm
    ,   result
    );
}

int
WilliamsCRC_CalculateBlockCrc(
    void const*     pv
,   size_t          cb
,   int             crc_bits
,   crc_poly_t      polynomial
,   crc_result_t*   result
)
{
    return WilliamsCRC_CalculateBlockCrc_(
            pv
        ,   cb
        ,   crc_bits
        ,   polynomial
        ,   result
        );
}

int
WilliamsCRC_CalculateFileCrc(
    char const*     path
,   int             crc_bits
,   crc_poly_t      polynomial
,   crc_result_t*   result
)
{
    size_t  dummy;

    return WilliamsCRC_CalculateFileCrc_(
            path
        ,   0
        ,   crc_bits
        ,   polynomial
        ,   result
        ,   &dummy
        );
}

int
WilliamsCRC_CalculateFileCrcMax(
    /* [in] */  char const*     path
,   /* [in] */  size_t          cbMaxToRead
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
)
{
    size_t  dummy;

    if (NULL == pcbRead)
    {
        pcbRead = &dummy;
    }

    return WilliamsCRC_CalculateFileCrc_(
            path
        ,   cbMaxToRead
        ,   crc_bits
        ,   polynomial
        ,   result
        ,   pcbRead
        );
}

int
WilliamsCRC_CalculateFileHandleCrc(
    FILE*           f
,   int             crc_bits
,   crc_poly_t      polynomial
,   crc_result_t*   result
)
{
    return WilliamsCRC_CalculateFileHandleCrc_(
            f
        ,   0
        ,   crc_bits
        ,   polynomial
        ,   result
        ,   NULL
        );
}

int
WilliamsCRC_CalculateFileHandleCrcMax(
    /* [in] */  FILE*           f
,   /* [in] */  size_t          cbMaxToRead
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
)
{
    size_t  dummy;

    if (NULL == pcbRead)
    {
        pcbRead = &dummy;
    }

    return WilliamsCRC_CalculateFileHandleCrc_(
            f
        ,   cbMaxToRead
        ,   crc_bits
        ,   polynomial
        ,   result
        ,   pcbRead
        );
}

#ifdef __cplusplus
} /* extern "C" */
#endif

/* /////////////////////////////////////////////////////////////////////////
 * includes - 2
 */

#define false                                               false
#define true                                                true
#include <crcmodel.c>
#undef false
#undef true

/* ///////////////////////////// end of file //////////////////////////// */

