/* /////////////////////////////////////////////////////////////////////////
 * File:        WilliamsCRC/WilliamsCRC.h
 *
 * Purpose:     WilliamsCRC API
 *
 * Created:     1st March 2010
 * Updated:     6th January 2021
 *
 * Copyright (c) 2019-2021, Matthew Wilson and Synesis Information Systems
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


#ifndef SYNSOFT_INCL_WILLIAMSCRC_H_WILLIAMSCRC
#define SYNSOFT_INCL_WILLIAMSCRC_H_WILLIAMSCRC

#ifndef SYNSOFT_DOCUMENTATION_SKIP_SECTION
# define SYNSOFT_VER_WILLIAMSCRC_H_WILLIAMSCRC_MAJOR    1
# define SYNSOFT_VER_WILLIAMSCRC_H_WILLIAMSCRC_MINOR    1
# define SYNSOFT_VER_WILLIAMSCRC_H_WILLIAMSCRC_REVISION 1
# define SYNSOFT_VER_WILLIAMSCRC_H_WILLIAMSCRC_EDIT     8
#endif /* !SYNSOFT_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stddef.h>
#include <stdio.h>

/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

/** \def SYNSOFT_WILLIAMSCRC_VER_MAJOR
 * The major version number of Synesis Information Systems' WilliamsCRC
 */

/** \def SYNSOFT_WILLIAMSCRC_VER_MINOR
 * The minor version number of Synesis Information Systems' WilliamsCRC
 */

/** \def SYNSOFT_WILLIAMSCRC_VER_REVISION
 * The revision version number of Synesis Information Systems' WilliamsCRC
 */

/** \def SYNSOFT_WILLIAMSCRC_VER
 * The current composite version number of Synesis Information Systems' WilliamsCRC
 */

#define SYNSOFT_WILLIAMSCRC_VER_MAJOR       1
#define SYNSOFT_WILLIAMSCRC_VER_MINOR       1
#define SYNSOFT_WILLIAMSCRC_VER_REVISION    1
#define SYNSOFT_WILLIAMSCRC_VER             0x01010100

/* /////////////////////////////////////////////////////////////////////////
 * typedefs
 */

typedef unsigned int                                        crc_result_t;

struct                                                      WilliamsCRC_info_t;
typedef struct WilliamsCRC_info_t*                          WilliamsCRC_t;

/* /////////////////////////////////////////////////////////////////////////
 * API
 */

#ifdef __cplusplus
extern "C" {
#endif

/** Initialises the library */
int
WilliamsCRC_Init(void);

/** Uninitialises the library */
void WilliamsCRC_Uninit(void);

/** Creates a CRC processing context */
int
WilliamsCRC_Create(
    WilliamsCRC_t* pwcrc
);

/** Destroys a CRC processing context */
void
WilliamsCRC_Destroy(
    WilliamsCRC_t   wcrc
);

/** Adds a block to a CRC processing context */
int
WilliamsCRC_Add(
    WilliamsCRC_t   wcrc
,   void const*     pv
,   size_t          cb
);

/** Retrieves the current CRC result from a CRC processing context */
int
WilliamsCRC_GetCRC(
    WilliamsCRC_t   wcrc
,   crc_result_t*   result
);

/** Calculates the CRC of a block of memory */
int
WilliamsCRC_CalculateBlockCrc(
    void const*     pv
,   size_t          cb
,   crc_result_t*   result
);

/** Calculates the CRC of a file */
int
WilliamsCRC_CalculateFileCrc(
    char const*     path
,   crc_result_t*   result
);

/** Calculates the CRC of the contents, up to a maximum number of bytes, of a file identified by its path
 *
 * @param path The path of the file. May not be \c null
 * @param cbMaxToRead The maximum number of bytes to read. If 0, all bytes are read
 * @param result Pointer to variable to receive the result. May not be \c null
 * @param pcbRead Pointer to variable to receive the number of bytes read. May be \c null
 *
 * @pre nullptr != path
 * @pre nullptr != results
 */
int
WilliamsCRC_CalculateFileCrcMax(
    /* [in] */  char const*     path
,   /* [in] */  size_t          cbMaxToRead
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
);

/** Calculates the CRC of a file identified by the given file handle */
int
WilliamsCRC_CalculateFileHandleCrc(
    FILE*           h
,   crc_result_t*   result
);

/** Calculates the CRC of the contents, up to a maximum number of bytes, of a file identified by its file-handle
 *
 * @param path The path of the file. May not be \c null
 * @param cbMaxToRead The maximum number of bytes to read. If 0, all bytes are read
 * @param result Pointer to variable to receive the result. May not be \c null
 * @param pcbRead Pointer to variable to receive the number of bytes read. May be \c null
 *
 * @pre nullptr != path
 * @pre nullptr != results
 */
int
WilliamsCRC_CalculateFileHandleCrcMax(
    /* [in] */  FILE*           h
,   /* [in] */  size_t          cbMaxToRead
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* SYNSOFT_INCL_WILLIAMSCRC_H_WILLIAMSCRC */

/* ///////////////////////////// end of file //////////////////////////// */

