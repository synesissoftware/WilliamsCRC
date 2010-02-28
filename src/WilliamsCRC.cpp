/* /////////////////////////////////////////////////////////////////////////
 * File:        WilliamsCRC.cpp
 *
 * Purpose:     Implementation of WilliamsCRC API.
 *
 * Created:     1st March 2010
 * Updated:     1st March 2010
 *
 * Author:      Matthew Wilson
 *
 * Copyright:   Synesis Software Pty Ltd, (c) 2010. All rights reserved.
 *
 * Home:        www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <WilliamsCRC/WilliamsCRC.h>

#include <stlsoft/internal/safestr.h>
#include <stlsoft/smartptr/scoped_handle.hpp>

#include <crcmodel.h>

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
    char const*     path
,   crc_result_t*   result
);

int
WilliamsCRC_CalculateFileHandleCrc_(
    FILE*           h
,   crc_result_t*   result
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

    if(0 == r)
    {
        stlsoft::scoped_handle<cm_t*>  scoper(&cm, WilliamsCRC_cm_destroy_);

        r = WilliamsCRC_Add_(cm, pv, cb);

        if(0 == r)
        {
            r = WilliamsCRC_GetCRC_(cm, result);
        }
    }

    return r;
}

int
WilliamsCRC_CalculateFileCrc_(
    char const*     path
,   crc_result_t*   result
)
{
    FILE* f;
    int   e = WilliamsCRC_fopen_(&f, path, "rb");

    if(0 != e)
    {
        return e;
    }
    else
    {
        stlsoft::scoped_handle<FILE*> scoper2(f, ::fclose);

        return WilliamsCRC_CalculateFileHandleCrc_(f, result);
    }
}

int
WilliamsCRC_CalculateFileHandleCrc_(
    FILE*           f
,   crc_result_t*   result
)
{
    cm_t    cm;
    int     r   =   WilliamsCRC_cm_init_(&cm);

    if(0 == r)
    {
        stlsoft::scoped_handle<cm_t*>   scoper(&cm, WilliamsCRC_cm_destroy_);

        unsigned char                   bytes[2048];

        { for(size_t n; 0 != (n = ::fread(&bytes[0], 1, sizeof(bytes), f)); )
        {
            r = WilliamsCRC_Add_(cm, bytes, n);

            if(0 != r)
            {
                break;
            }
        }}

        if(0 == r)
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

    if(NULL == *pwcrc)
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
    if(NULL != wcrc)
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
    return WilliamsCRC_CalculateFileCrc_(path, result);
}

int
WilliamsCRC_CalculateFileHandleCrc(
    FILE*         f
,   crc_result_t* result
)
{
    return WilliamsCRC_CalculateFileHandleCrc_(f, result);
}

/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#include <crcmodel.cpp>

/* ///////////////////////////// end of file //////////////////////////// */
