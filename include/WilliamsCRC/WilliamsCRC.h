/* /////////////////////////////////////////////////////////////////////////
 * File:        WilliamsCRC/WilliamsCRC.h
 *
 * Purpose:     WilliamsCRC API
 *
 * Created:     1st March 2010
 * Updated:     1st January 2024
 *
 * Copyright (c) 2019-2024, Matthew Wilson and Synesis Information Systems
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
# define SYNSOFT_VER_WILLIAMSCRC_H_WILLIAMSCRC_REVISION 5
# define SYNSOFT_VER_WILLIAMSCRC_H_WILLIAMSCRC_EDIT     14
#endif /* !SYNSOFT_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#if defined(__cplusplus) && \
    __cplusplus >= 201103L
# include <stdint.h>
#endif /* C++-11+ */

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
 * The current composite version number of Synesis Information Systems'
 * WilliamsCRC
 */

#define SYNSOFT_WILLIAMSCRC_VER_MAJOR                       2
#define SYNSOFT_WILLIAMSCRC_VER_MINOR                       0
#define SYNSOFT_WILLIAMSCRC_VER_REVISION                    0
#define SYNSOFT_WILLIAMSCRC_VER                             0x02000081

/* /////////////////////////////////////////////////////////////////////////
 * typedefs
 */

/** Result type */
#if defined(__cplusplus) && \
    __cplusplus >= 201103L
typedef uint32_t                                            crc_result_t;
#else /* ? C++-11+ */
typedef unsigned int                                        crc_result_t;
#endif /* C++-11+ */

/** Polynomial type */
#if defined(__cplusplus) && \
    __cplusplus >= 201103L
typedef uint32_t                                            crc_poly_t;
#else /* ? C++-11+ */
typedef int                                                 crc_poly_t;
#endif /* C++-11+ */

/** Internal context structure */
struct                                                      WilliamsCRC_info_t;
/** CRC context structure */
typedef struct WilliamsCRC_info_t*                          WilliamsCRC_t;

/* /////////////////////////////////////////////////////////////////////////
 * API
 */

#ifdef __cplusplus
extern "C" {
#endif

/** Initialises the library.
 *
 * @retval 0 The library has been initialised, and may be used;
 * @retval !0 The library has not been initialised, and may not be used, and
 *   the returned value indicates a standard error (e.g. `ENOMEM`);
 */
int
WilliamsCRC_Init(void);

/** Uninitialises the library.
 */
void WilliamsCRC_Uninit(void);

/** Creates a CRC processing context.
 *
 * @param crc_bits CRC width. Must be one of { 4, 5, 6, 7, 8, 10, 10, 11,
 *   12, 14, 15, 16, 24, 30, 32 };
 * @param polynomial Polynomial for use in the algorithm. Uses an internal
 *   well-known default if 0;
 * @param pwcrc Pointer to a variable to receive the created CRC context
 *   structure. May not be `NULL`;
 *
 * @retval 0 The CRC context has been created, and may be used;
 * @retval !0 The CRC context has not been created, and may not be used, and
 *   the returned value indicates a standard error (e.g. `ENOMEM`);
 */
int
WilliamsCRC_Create(
    /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [out] */ WilliamsCRC_t*  pwcrc
);

/** Destroys a CRC processing context.
 *
 * @param wcrc Instance of the CRC context structure obtained from a
 *   successful call to WilliamsCRC_Create();
 */
void
WilliamsCRC_Destroy(
    /* [in] */ WilliamsCRC_t    wcrc
);

/** Adds a block to a CRC processing context.
 *
 * @param wcrc Instance of the CRC context structure obtained from a
 *   successful call to WilliamsCRC_Create();
 * @param pv Pointer to the first byte in the block. May not be `NULL`
 *   unless `0 == cb`;
 * @param cb Number of bytes in the block;
 *
 * @pre nullptr != wcrc
 * @pre nullptr != pv || 0 == cb
 */
void
WilliamsCRC_Add(
    /* [in] */  WilliamsCRC_t   wcrc
,   /* [in] */  void const*     pv
,   /* [in] */  size_t          cb
);

/** Retrieves the current CRC result from a CRC processing context.
 *
 * @param wcrc Instance of the CRC context structure obtained from a
 *   successful call to WilliamsCRC_Create();
 * @param result Pointer to a variable to receive the CRC result. May not be
 *   `NULL`;
 *
 * @pre nullptr != wcrc
 * @pre nullptr != result
 */
void
WilliamsCRC_GetCRC(
    /* [in] */  WilliamsCRC_t   wcrc
,   /* [out] */ crc_result_t*   result
);

/** Calculates the CRC of a block of memory.
 *
 * @param pv Pointer to the first byte in the block. May not be `NULL`
 *   unless `0 == cb`;
 * @param cb Number of bytes in the block;
 * @param crc_bits CRC width. Must be one of { 4, 5, 6, 7, 8, 10, 10, 11,
 *   12, 14, 15, 16, 24, 30, 32 };
 * @param polynomial Polynomial for use in the algorithm. Uses an internal
 *   well-known default if 0;
 * @param result Pointer to a variable to receive the CRC result. May not be
 *   `NULL`;
 *
 * @retval 0 The CRC calculation has succeeded;
 * @retval !0 The CRC calculation has failed, and the returned value
 *   indicates a standard error (e.g. `ENOMEM`);
 *
 * @pre nullptr != pv || 0 == cb
 * @pre nullptr != result
 */
int
WilliamsCRC_CalculateBlockCrc(
    /* [in] */  void const*     pv
,   /* [in] */  size_t          cb
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [in] */  crc_result_t*   result
);

/** Calculates the CRC of a file.
 *
 * @param path The path of the file. May not be `NULL`
 * @param crc_bits CRC width. Must be one of { 4, 5, 6, 7, 8, 10, 10, 11,
 *   12, 14, 15, 16, 24, 30, 32 };
 * @param polynomial Polynomial for use in the algorithm. Uses an internal
 *   well-known default if 0;
 * @param result Pointer to a variable to receive the CRC result. May not be
 *   `NULL`;
 *
 * @retval 0 The CRC calculation has succeeded;
 * @retval !0 The CRC calculation has failed, and the returned value
 *   indicates a standard error (e.g. `ENOMEM`);
 *
 * @pre nullptr != path
 * @pre nullptr != result
 */
int
WilliamsCRC_CalculateFileCrc(
    /* [in] */  char const*     path
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [out] */ crc_result_t*   result
);

/** Calculates the CRC of the contents, up to a maximum number of bytes, of
 * a file identified by its path.
 *
 * @param path The path of the file. May not be `NULL`
 * @param cbMaxToRead The maximum number of bytes to read. If 0, all bytes
 *   are read
 * @param crc_bits CRC width. Must be one of { 4, 5, 6, 7, 8, 10, 10, 11,
 *   12, 14, 15, 16, 24, 30, 32 };
 * @param polynomial Polynomial for use in the algorithm. Uses an internal
 *   well-known default if 0;
 * @param result Pointer to a variable to receive the CRC result. May not be
 *   `NULL`;
 * @param pcbRead Pointer to variable to receive the number of bytes read.
 *   May be `NULL`
 *
 * @retval 0 The CRC calculation has succeeded;
 * @retval !0 The CRC calculation has failed, and the returned value
 *   indicates a standard error (e.g. `ENOMEM`);
 *
 * @pre nullptr != path
 * @pre nullptr != result
 */
int
WilliamsCRC_CalculateFileCrcMax(
    /* [in] */  char const*     path
,   /* [in] */  size_t          cbMaxToRead
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [out] */ crc_result_t*   result
,   /* [out] */ size_t*         pcbRead
);

/** Calculates the CRC of a file identified by the given file handle.
 *
 * @param h Open handle to the file. May not be `NULL`
 * @param crc_bits CRC width. Must be one of { 4, 5, 6, 7, 8, 10, 10, 11,
 *   12, 14, 15, 16, 24, 30, 32 };
 * @param polynomial Polynomial for use in the algorithm. Uses an internal
 *   well-known default if 0;
 * @param result Pointer to a variable to receive the CRC result. May not be
 *   `NULL`;
 *
 * @retval 0 The CRC calculation has succeeded;
 * @retval !0 The CRC calculation has failed, and the returned value
 *   indicates a standard error (e.g. `ENOMEM`);
 *
 * @pre nullptr != h
 * @pre nullptr != result
 */
int
WilliamsCRC_CalculateFileHandleCrc(
    /* [in] */  FILE*           h
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
,   /* [in] */  crc_result_t*   result
);

/** Calculates the CRC of the contents, up to a maximum number of bytes, of
 * a file identified by its file-handle.
 *
 * @param h Open handle to the file. May not be `NULL`
 * @param cbMaxToRead The maximum number of bytes to read. If 0, all bytes
 *   are to be read
 * @param crc_bits CRC width. Must be one of { 4, 5, 6, 7, 8, 10, 10, 11,
 *   12, 14, 15, 16, 24, 30, 32 };
 * @param polynomial Polynomial for use in the algorithm. Uses an internal
 *   well-known default if 0;
 * @param result Pointer to a variable to receive the CRC result. May not be
 *   `NULL`;
 * @param pcbRead Pointer to variable to receive the number of bytes read.
 *   May be `NULL`
 *
 * @retval 0 The CRC calculation has succeeded;
 * @retval !0 The CRC calculation has failed, and the returned value
 *   indicates a standard error (e.g. `ENOMEM`);
 *
 * @pre nullptr != path
 * @pre nullptr != result
 */
int
WilliamsCRC_CalculateFileHandleCrcMax(
    /* [in] */  FILE*           h
,   /* [in] */  size_t          cbMaxToRead
,   /* [in] */  int             crc_bits
,   /* [in] */  crc_poly_t      polynomial
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

