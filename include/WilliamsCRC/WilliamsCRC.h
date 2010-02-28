/* /////////////////////////////////////////////////////////////////////////
 * File:        WilliamsCRC/WilliamsCRC.h
 *
 * Purpose:     WilliamsCRC API
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


#ifndef SYNSOFT_INCL_WILLIAMSCRC_H_WILLIAMSCRC
#define SYNSOFT_INCL_WILLIAMSCRC_H_WILLIAMSCRC

#ifndef SYNSOFT_DOCUMENTATION_SKIP_SECTION
# define SYNSOFT_VER_WILLIAMSCRC_H_WILLIAMSCRC_MAJOR    1
# define SYNSOFT_VER_WILLIAMSCRC_H_WILLIAMSCRC_MINOR    0
# define SYNSOFT_VER_WILLIAMSCRC_H_WILLIAMSCRC_REVISION 1
# define SYNSOFT_VER_WILLIAMSCRC_H_WILLIAMSCRC_EDIT     1
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
 * The major version number of Synesis Software WilliamsCRC
 */

/** \def SYNSOFT_WILLIAMSCRC_VER_MINOR
 * The minor version number of Synesis Software WilliamsCRC
 */

/** \def SYNSOFT_WILLIAMSCRC_VER_REVISION
 * The revision version number of Synesis Software WilliamsCRC
 */

/** \def SYNSOFT_WILLIAMSCRC_VER
 * The current composite version number of Synesis Software WilliamsCRC
 */

#define SYNSOFT_WILLIAMSCRC_VER_MAJOR       1
#define SYNSOFT_WILLIAMSCRC_VER_MINOR       0
#define SYNSOFT_WILLIAMSCRC_VER_REVISION    0
#define SYNSOFT_WILLIAMSCRC_VER             0x01000000

/* /////////////////////////////////////////////////////////////////////////
 * typedefs
 */

typedef unsigned int                crc_result_t;

struct                              WilliamsCRC_info_t;
typedef struct WilliamsCRC_info_t*  WilliamsCRC_t;

/* /////////////////////////////////////////////////////////////////////////
 * API
 */

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

/** Retrieves the (
    urrent
 CRC result from a CRC processing context */
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

/** Calculates the CRC of a file identified by the given file handle */
int
WilliamsCRC_CalculateFileHandleCrc(
    FILE*           h
,   crc_result_t*   result
);

/* ////////////////////////////////////////////////////////////////////// */

#endif /* SYNSOFT_INCL_WILLIAMSCRC_H_WILLIAMSCRC */

/* ///////////////////////////// end of file //////////////////////////// */
