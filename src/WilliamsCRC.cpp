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
);

void
WilliamsCRC_cm_destroy_(
    cm_t*           cm
);

int
WilliamsCRC_Add_(
    cm_t&           cm
,   void const*     pv
,   size_t          cb
);

int
WilliamsCRC_GetCRC_(
    cm_t&           cm
,   crc_result_t*   result
);

int
WilliamsCRC_CalculateBlockCrc_(
    void const*     pv
,   size_t          cb
,   crc_result_t*   result
);

int
WilliamsCRC_CalculateFileCrc_(
    /* [in] */  char const*     path
,   /* [in] */  size_t          cbMaxToRead
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
);

int
WilliamsCRC_CalculateFileHandleCrc_(
    /* [in] */  FILE*           h
,   /* [in] */  size_t          cbMaxToRead
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
)
{
    assert(NULL != cm);

    cm->cm_width    =   16;
    cm->cm_poly     =   0x8005L;
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

int
WilliamsCRC_Add_(
    cm_t&           cm
,   void const*     pv
,   size_t          cb
)
{
    cm_blk(&cm, static_cast<p_ubyte_>(const_cast<void*>(pv)), (ulong)cb);

    return 0;
}

int
WilliamsCRC_GetCRC_(
    cm_t&           cm
,   crc_result_t*   result
)
{
    *result = cm_crc(&cm);

    return 0;
}

int
WilliamsCRC_CalculateBlockCrc_(
    void const*     pv
,   size_t          cb
,   crc_result_t*   result
)
{
    cm_t    cm;
    int     r   =   WilliamsCRC_cm_init_(&cm);

    if (0 == r)
    {
        stlsoft::scoped_handle<cm_t*>  scoper(&cm, WilliamsCRC_cm_destroy_);

        r = WilliamsCRC_Add_(cm, pv, cb);

        if (0 == r)
        {
            r = WilliamsCRC_GetCRC_(cm, result);
        }
    }

    return r;
}

int
WilliamsCRC_CalculateFileCrc_(
    /* [in] */  char const*     path
,   /* [in] */  size_t          cbMaxToRead
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

        return WilliamsCRC_CalculateFileHandleCrc_(f, cbMaxToRead, result, pcbRead);
    }
}

int
WilliamsCRC_CalculateFileHandleCrc_(
    /* [in] */  FILE*           f
,   /* [in] */  size_t          cbMaxToRead
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
)
{
    cm_t    cm;
    int     r   =   WilliamsCRC_cm_init_(&cm);

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

            r = WilliamsCRC_Add_(cm, bytes, n);

            if (0 != r)
            {
                break;
            }
            else
            {
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
            }
        }}

        if (0 == r)
        {
            r = WilliamsCRC_GetCRC_(cm, result);
        }
    }

    return r;
}

} /* anonymous namespace */

/* /////////////////////////////////////////////////////////////////////////
 * API Functions
 */

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
    WilliamsCRC_t* pwcrc
)
{
    *pwcrc = new WilliamsCRC_info_t();

    if (NULL == *pwcrc)
    {
        return ENOMEM;
    }
    else
    {
        return WilliamsCRC_cm_init_(&(*pwcrc)->cm);
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

int
WilliamsCRC_Add(
    WilliamsCRC_t wcrc
,   void const*   pv
,   size_t        cb
)
{
    return WilliamsCRC_Add_(wcrc->cm, pv, cb);
}

int
WilliamsCRC_GetCRC(
    WilliamsCRC_t wcrc
,   crc_result_t* result
)
{
    return WilliamsCRC_GetCRC_(wcrc->cm, result);
}

int
WilliamsCRC_CalculateBlockCrc(
    void const*   pv
,   size_t        cb
,   crc_result_t* result
)
{
    return WilliamsCRC_CalculateBlockCrc_(pv, cb, result);
}

int
WilliamsCRC_CalculateFileCrc(
    char const*   path
,   crc_result_t* result
)
{
    size_t  dummy;

    return WilliamsCRC_CalculateFileCrc_(path, 0, result, &dummy);
}

int
WilliamsCRC_CalculateFileCrcMax(
    /* [in] */  char const*     path
,   /* [in] */  size_t          cbMaxToRead
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
)
{
    size_t  dummy;

    if (NULL == pcbRead)
    {
        pcbRead = &dummy;
    }

    return WilliamsCRC_CalculateFileCrc_(path, cbMaxToRead, result, pcbRead);
}

int
WilliamsCRC_CalculateFileHandleCrc(
    FILE*         f
,   crc_result_t* result
)
{
    return WilliamsCRC_CalculateFileHandleCrc_(f, 0, result, NULL);
}

int
WilliamsCRC_CalculateFileCrcMax(
    /* [in] */  FILE*           f
,   /* [in] */  size_t          cbMaxToRead
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
)
{
    size_t  dummy;

    if (NULL == pcbRead)
    {
        pcbRead = &dummy;
    }

    return WilliamsCRC_CalculateFileHandleCrc_(f, cbMaxToRead, result, pcbRead);
}

/* /////////////////////////////////////////////////////////////////////////
 * includes - 2
 */

#define false                                               false
#define true                                                true
#include <crcmodel.cpp>
#undef false
#undef true

/* ///////////////////////////// end of file //////////////////////////// */

