/******************************************************************************/
/*                             Start of crctable.c                            */
/******************************************************************************/
/*                                                                            */
/* Author  : Ross Williams (ross@guest.adelaide.edu.au.).                     */
/* Date    : 3 June 1993.                                                     */
/* Version : 1.0.                                                             */
/* Status  : Public domain.                                                   */
/*                                                                            */
/* Description : This program writes a CRC lookup table (suitable for         */
/* inclusion in a C program) to a designated output file. The program can be  */
/* statically configured to produce any table covered by the Rocksoft^tm      */
/* Model CRC Algorithm. For more information on the Rocksoft^tm Model CRC     */
/* Algorithm, see the document titled "A Painless Guide to CRC Error          */
/* Detection Algorithms" by Ross Williams (ross@guest.adelaide.edu.au.). This */
/* document is likely to be in "ftp.adelaide.edu.au/pub/rocksoft".            */
/*                                                                            */
/* Note: Rocksoft is a trademark of Rocksoft Pty Ltd, Adelaide, Australia.    */
/*                                                                            */
/******************************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "crcmodel.h"

/******************************************************************************/

/* TABLE PARAMETERS                                                           */
/* ================                                                           */
/* The following parameters entirely determine the table to be generated. You */
/* should need to modify only the definitions in this section before running  */
/* this program.                                                              */
/*                                                                            */
/*    TB_WIDTH is the table width in bytes (either 2 or 4).                   */
/*    TB_POLY  is the "polynomial", which must be TB_WIDTH bytes wide.        */
/*    TB_REVER indicates whether the table is to be reversed (reflected).     */
/*                                                                            */
/* Example:                                                                   */
/*                                                                            */
/*    #define TB_WIDTH  2                                                     */
/*    #define TB_POLY   0x8005L                                               */
/*    #define TB_REVER  true                                                  */

int TB_WIDTH;// 4
unsigned long TB_POLY;//   0x04C11DB7L
bool TB_REVER;//  true

/******************************************************************************/

/* Miscellaneous definitions. */


/******************************************************************************/

static void chk_err (char *mess)
/* If mess is non-empty, write it out and abort. Otherwise, check the error   */
{
	if (mess[0] != '\0')
		TRACE("ERROR - %s\n",mess);
}

/******************************************************************************/

static void chkparam ()
{
	if ((TB_WIDTH != 2) && (TB_WIDTH != 4))
		chk_err("chkparam: Width parameter is illegal.");
	if ((TB_WIDTH == 2) && (TB_POLY & 0xFFFF0000L))
		chk_err("chkparam: Poly parameter is too wide.");
	if ((TB_REVER != false) && (TB_REVER != true))
		chk_err("chkparam: Reverse parameter is not boolean.");
}

/******************************************************************************/

static void gentable ()
{
	char buff[255];
	OutputDebugString ("\n/*****************************************************************/\n");
	OutputDebugString ("/*                                                               */\n");
	OutputDebugString ("/* CRC LOOKUP TABLE                                              */\n");
	OutputDebugString ("/* ================                                              */\n");
	OutputDebugString ("/*                                                               */\n");
	sprintf(buff, "/*    Width   : %1lu bytes.                                         */\n", (ulong) TB_WIDTH);
	OutputDebugString (buff);
	if (TB_WIDTH == 2)
		sprintf(buff, "/*    Poly    : 0x%04lX                                           */\n", (ulong) TB_POLY);
	else
		sprintf(buff, "/*    Poly    : 0x%08lXL                                      */\n", (ulong) TB_POLY);
	OutputDebugString (buff);

	if (TB_REVER)
		OutputDebugString ("/*    Reverse : true.                                            */\n");
	else
		OutputDebugString ("/*    Reverse : false.                                           */\n");

	OutputDebugString ("/*                                                               */\n");
	OutputDebugString ("/*                                                               */\n");
	OutputDebugString ("/*****************************************************************/\n");
	OutputDebugString ("\n");
	switch (TB_WIDTH)
	{
		case 2:
		case 4:
			break;
		default:
			chk_err("gentable: TB_WIDTH is invalid.");
			break;
	}
	chk_err("");

	{
		int i,j;
		cm_t cm;
		char *form    = (TB_WIDTH==2) ? "%04lx " : "%08lx ";
		int   perline = (TB_WIDTH==2) ? 16 : 8;

		cm.cm_width = TB_WIDTH*8;
		cm.cm_poly  = TB_POLY;
		cm.cm_refin = TB_REVER;

		for (j=0, i=0; i<256; i++)
		{
			j += sprintf (&buff[j], form, (ulong) cm_tab(&cm,i));

			 if (((i+1) % perline) == 0)
			 {
				 buff[j++] = '\n';
				 buff[j++] = '\0';
				 OutputDebugString (buff);
				 j = 0;
			 }

			 chk_err("");
		}

		OutputDebugString ("\n/*****************************************************************/\n");
		OutputDebugString ("/*                   End of CRC Lookup Table                     */\n");
		OutputDebugString ("/*****************************************************************/\n");
		chk_err("");
	}
}

/******************************************************************************/

void TraceVerificationTable
(
	  int width
	, unsigned long poly
	, bool bReverse
)
{
	TB_WIDTH = width;
	TB_POLY = poly;
	TB_REVER = bReverse;
	printf("\n");
	chkparam();
	gentable();
}

/******************************************************************************/
/*                             End of crctable.c                              */
/******************************************************************************/
