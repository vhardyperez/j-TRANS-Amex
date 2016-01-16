// FDumpHex.h: interface for the FDumpHex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FDUMPHEX_H__914630A2_9367_4FF2_B892_9A9ED9273D90__INCLUDED_)
#define AFX_FDUMPHEX_H__914630A2_9367_4FF2_B892_9A9ED9273D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define LINELEN                     16
//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <iomanip.h>
#include <rw/cstring.h>
#include <rw/rwdate.h>
#include <rw/rwtime.h>
#include <rw/ctoken.h>
#include <fstream.h>
//#include "diCryptoSys.h"
#include <assert.h>

#define     TEST            1   /* compile in test driver */
#define     USE_FLOAT       0   /* use floating point */ 


#if USE_FLOAT == 1
#define TEMP long double
#else
#define TEMP unsigned long
#endif



#define     BYTE                        unsigned char
#define     WORD                        unsigned int
//#define     NO_ERROR                    0
//#define     ERROR                       !NO_ERROR
#define     INVALID_SOURCE_BASE         1
#define     INVALID_DESTINATION_BASE    2
#define     INVALID_CHAR_FOR_BASE       3
#define     INVALID_TOO_LARGE           4

#define     MAX_LENGTH_OUTPUT           80

/* RANGE OF BASES THE ROUTINE HANDLES */
#define		LOWER_LIMIT					2
#define 	UPPER_LIMIT					36


class FDumpHex  
{
public:
	FDumpHex();
	virtual ~FDumpHex();
	void HexDump(RWCString incoming,int nLen);
	void HexDumpFile(RWCString test_append);
	RWCString RetornoASCII(char  hex_input);
	void    ASCII_to_EBCDIC ( long, unsigned char *) ;
	void    EBCDIC_to_ASCII ( long, unsigned char *) ;
	int nBaseConvert(
	char    *pcNumberToConvert,
	int     nSourceBase,
	int     nDestinationBase,
	char    *pcResult,
	int     nSeparateOutput,
	int     cSeparationCharacter,
	int     nPadToLeft,
	int     *pnError);

	int     GetMesageLength( RWCString incoming_msg )  ;
	RWCString DES_Hex_Decrypt(char sHexKey[],char sCorrect[] );
	RWCString DES_Hex_Encrypt(char sHexKey[],char sCorrect[] );
	




private:
	//RWCString RetornoASCII(char  hex_input);

};

#endif // !defined(AFX_FDUMPHEX_H__914630A2_9367_4FF2_B892_9A9ED9273D90__INCLUDED_)
