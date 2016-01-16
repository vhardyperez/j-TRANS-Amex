// FDumpHex.cpp: implementation of the FDumpHex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FDumpHex.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


FDumpHex::FDumpHex()
{



}

 
void    FDumpHex::EBCDIC_to_ASCII ( long buf_length, unsigned char *buf_addr)
{   
	   static  unsigned char
        EBCDIC_translate_ASCII [ 256 ] =
            {
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
            0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
            0x19, 0x92, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
            0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
            0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
            0x30, 0x2E, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
            0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x2E, 0x3F,
            0x20, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
            0x2E, 0x2E, 0x2E, 0x3C, 0x28, 0x2B, 0x7C,
            0x26, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
            0x2E, 0x21, 0x24, 0x2A, 0x29, 0x3B, 0x5E,
            0x2D, 0x2F, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
            0x2E, 0x7C, 0x2C, 0x25, 0x5F, 0x3E, 0x3F,
            0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
            0x2E, 0x3A, 0x23, 0x40, 0x27, 0x3D, 0x22,
            0x2E, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
            0x69, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
            0x2E, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71,
            0x72, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
            0x2E, 0x7E, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
            0x7A, 0x2E, 0x2E, 0x2E, 0x5B, 0x2E, 0x2E,
            0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
            0x2E, 0x2E, 0x2E, 0x2E, 0x5D, 0x2E, 0x2E,
            0x7B, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
            0x49, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
            0x7D, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,                                             
            0x52, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
            0x5C, 0x2E, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
            0x5A, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
            0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,                 
            0x39, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E } ;

	
	int i;
    unsigned char temp;
    for (i=0; i < buf_length; i++)
    {
        temp = buf_addr[i];
        buf_addr[i] = EBCDIC_translate_ASCII[temp];

    }
};

void    FDumpHex::ASCII_to_EBCDIC ( long buf_length, unsigned char *buf_addr)
{   
	
	
        static unsigned char ASCII_translate_EBCDIC [ 256 ] =
            {
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
            0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
            0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
            0x40, 0x4F, 0x7F, 0x7B, 0x5B, 0x6C, 0x50, 0x7D, 0x4D,
            0x5D, 0x5C, 0x4E, 0x6B, 0x60, 0x4B, 0x61,
            0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
            0xF9, 0x7A, 0x5E, 0x4C, 0x7E, 0x6E, 0x6F,
            0x7C, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8,
            0xC9, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,
            0xD7, 0xD8, 0xD9, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
            0xE8, 0xE9, 0xAD, 0xE0, 0xBD, 0x5F, 0x6D,
            0x7D, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
            0x89, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96,
            0x97, 0x98, 0x99, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
            0xA8, 0xA9, 0xC0, 0x6A, 0xD0, 0xA1, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B,
            0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4B } ;
	int i;
    unsigned char temp;
    for (i=0; i < buf_length; i++)
    {
        temp = buf_addr[i];
        buf_addr[i] = ASCII_translate_EBCDIC[temp];
		
	}
};
/*
RWCString FDumpHex::DES_Hex_Decrypt(char sHexKey[],char sCorrect[] )
{
  
	char *testfn = "DES_Hex()";
   
	char sOutput[20] = {""};
	long lngRet;
    printf("KY=%s\n", sHexKey);
    printf("PT=%s\n", sCorrect);
    lngRet = DES_Hex(sOutput, sCorrect, sHexKey, DECRYPT);
	return RWCString(sOutput);
}
RWCString FDumpHex::DES_Hex_Encrypt(char sHexKey[],char sCorrect[] )
{
  
	char *testfn = "DES_Hex()";
   
	char sOutput[20] = {""};
	long lngRet;
    printf("KY=%s\n", sHexKey);
    printf("PT=%s\n", sCorrect);
    lngRet = DES_Hex(sOutput, sCorrect, sHexKey, ENCRYPT);
			  	 
	return RWCString(sOutput);
}
*/
void FDumpHex::HexDumpFile(RWCString incoming)
{
	

	RWCString   b_number2 = "hex";
	RWCString	fname = "LogTrans."+b_number2;
	RWCString	m_fname = fname;
	ofstream fp;
	RWTime t;   // Current time
	char buf[16],nbuf[64];
	time_t ltime;
	time(&ltime);
	struct tm *today = localtime(&ltime);
	strftime(buf,sizeof(buf),"%m%d%Y",today);
	sprintf(nbuf,"%s_%s",buf,m_fname);
	RWCString newname = nbuf;

	fp.open(newname, ios::app );
	fp << endl;
	fp <<  t ;
	fp << endl;


	int nLen = incoming.length();
	unsigned int x = 0;
	unsigned char test_hex[1024] = {""};
	unsigned char ch = '\x20';
	memcpy(test_hex,incoming,incoming.length());
	int           i, nCount;
    unsigned char Line[LINELEN] = {""};
    ULONG         ulOffset = 0L;
	RWCString Data;
	char buffer_for_input[17] = {""}; 
	char pre_test = '\x20';
	RWCString test_pre;	
	RWCString char_return;
    FDumpHex retorno_ascii;

    while (nLen > 0L) 
	{
        nCount = nLen > LINELEN ? LINELEN : nLen;
   
		Data = incoming(ulOffset,nCount);
		
		memcpy(test_hex,Data,nCount);
        
		//printf("%04lX  ",  ulOffset);
 		for (i = 0; i < nCount; i++) 
			
		{
            x = test_hex[i];
			char_return = retorno_ascii.RetornoASCII(x);
			fp << char_return;
			fp << " ";
        }
        
		fp << " ";
		test_pre = Data ;
		fp << test_pre;
		fp << endl;
        nLen     -= nCount;
        ulOffset += nCount;
    }
	fp.close();	
	return ;
}


void FDumpHex::HexDump(RWCString incoming,int nLen)
{
	//int nLen = incoming.length();
	unsigned int x = 0;
	unsigned char test_hex[1024] = {""};
	unsigned char ch = '\x20';
	memcpy(test_hex,incoming,incoming.length());
	int           i, nCount;
    unsigned char Line[LINELEN] = {""};
    ULONG         ulOffset = 0L;
	RWCString Data;
//	char buffer_for_input[17] = {""}; 
	char pre_test = '\x20';
	RWCString test_pre;	
	RWCString char_return;
    FDumpHex retorno_ascii;

    while (nLen > 0L) 
	{
        nCount = nLen > LINELEN ? LINELEN : nLen;
   
		Data = incoming(ulOffset,nCount);
		
		memcpy(test_hex,Data,nCount);
        
		printf("%04lX  ",  ulOffset);
 		for (i = 0; i < nCount; i++) 
			
		{
            x = test_hex[i];
			char_return = retorno_ascii.RetornoASCII(x);
			cout <<  char_return ; // Outputs 0x2a\n
			cout << " ";
		
        }
        
		cout << " " ;

		test_pre = Data ;

		//cout << test_pre ;
		cout << endl;
        nLen     -= nCount;
        ulOffset += nCount;
    }

	return ;
}

int FDumpHex::nBaseConvert(
	char    *pcNumberToConvert,
	int     nSourceBase,
	int     nDestinationBase,
	char    *pcResult,
	int     nSeparateOutput,
	int     cSeparationCharacter,
	int     nPadToLeft,
	int     *pnError)
{
	TEMP    TempValue1;
	TEMP    TempWidth;
	WORD    unTempValue2;
	WORD    unTemp;
	WORD    unLoop;
	char    acTempArray[2*MAX_LENGTH_OUTPUT + 1];
	char    *pcHolding;
	int     nReturnValue;

#if USE_FLOAT == 1
	WORD    wCounter;
	WORD    wNumberOfPlaces;
#endif

	/* ARRAY THAT DEFINES HOW WE GROUP OUTPUT.  Ex: bBatchArray[2] == 8,    */
	/* SO WE OUTPUT BASE 2 STUFF IN BLOCKS OF 8 DIGITS                      */
	static BYTE    bBatchArray[] =
				   { 0, 0, 8, 0, 0, 0, 0, 0, 3, 0,
			 		 3, 0, 0, 0, 0, 0, 2, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0 };

	/* INITIALIZE THE ERROR FLAGS AND RETURN VALUES */
	*pnError = NO_ERROR;
	nReturnValue = NO_ERROR;
	*pcResult = '\0';

	/* BASES MUST BE BETWEEN LOWER_LIMIT AND UPPER_LIMIT */
	if( (nSourceBase < LOWER_LIMIT) || (nSourceBase > UPPER_LIMIT) )
	{
		*pnError  = INVALID_SOURCE_BASE;
		nReturnValue = ERROR;
	}
	else if( (nDestinationBase < LOWER_LIMIT) || (nDestinationBase > UPPER_LIMIT) )
	{
		*pnError  = INVALID_DESTINATION_BASE;
		nReturnValue = ERROR;
	}
	else
	{
		/* REVERSE ORDER - WE WORK FROM LEAST TO MOST SIGNIFICANT DIGIT */
		strrev( pcNumberToConvert );

		/* PUT BINARY pcNumberToConvert INTO unTempValue1 */
		for( unLoop=0, TempValue1=(TEMP) 0, TempWidth=(TEMP) 1;
			pcNumberToConvert[unLoop];
			unLoop++ )
		{

			/* CONVERT CHARACTER TO NUMERIC EQUIVALENT */
			unTempValue2 = UPPER_LIMIT;
			if (isdigit(pcNumberToConvert[unLoop]))
				unTempValue2 = pcNumberToConvert[unLoop] - '0';
			else if (isalpha(pcNumberToConvert[unLoop]))
				/* 'A' - '7' gives 10 ... */
				unTempValue2 = toupper(pcNumberToConvert[unLoop]) - '7';

			if( unTempValue2 >= (WORD)nSourceBase )
			{
				*pnError  = INVALID_CHAR_FOR_BASE;
				nReturnValue = ERROR;
				break;
			}
			else
			{
				/* UPDATE TEMPORARY VALUE AND WIDTH */
				TempValue1 += ((TEMP) unTempValue2) * TempWidth;
				TempWidth *= (TEMP) nSourceBase;
			}
		} /* end of for loop */

		/* RESTORE TO ORIGINAL ORDER */
		strrev( pcNumberToConvert );

		/* CHECK FOR POSSIBLE CONVERSION ERROR */
		if( *pnError == NO_ERROR )
		{

#if USE_FLOAT == 1
			/* FIND HIGHEST DIVISOR */
			for( TempWidth=(TEMP) 1, wNumberOfPlaces=1;
				(TempWidth * (TEMP)nDestinationBase) <= TempValue1; )
			{
				TempWidth *= (TEMP)nDestinationBase;
				wNumberOfPlaces++;
			}

			/* CONVERT TempValue1 TO DESTINATION BASE & PUT INTO acTempArray */
			for( unLoop=0,wCounter=0; wNumberOfPlaces; unLoop++, wCounter++, wNumberOfPlaces-- )
			{
				unTemp = (WORD) (TempValue1 / TempWidth);
				acTempArray[unLoop] = (char)(unTemp<10 ? unTemp+'0' : unTemp+'7' );
				TempValue1 = TempValue1 - ((TEMP) unTemp * TempWidth );
				TempWidth /= (TEMP) nDestinationBase;
				if( unLoop >= MAX_LENGTH_OUTPUT - 1 )
				{
					*pnError  = INVALID_TOO_LARGE;
					*acTempArray = '\0';
					return( ERROR );
				}
			}
			/* NULL TERMINATE AND REVERSE THE RESULT STRING */
			acTempArray[unLoop] = '\0';
			strrev( acTempArray );

#else
			/* CONVERT TempValue1 TO DESTINATION BASE & PUT INTO acTempArray */
			unLoop=0;
			while(TempValue1 != 0)
			{
				unTemp = (WORD) (TempValue1 % (TEMP) nDestinationBase);
				TempValue1 /= (TEMP) nDestinationBase;
				acTempArray[unLoop++] = (char)(unTemp<10 ?
					unTemp+'0' : unTemp+'7' );
				if( unLoop >= MAX_LENGTH_OUTPUT - 1 )
				{
					*pnError  = INVALID_TOO_LARGE;
					return( ERROR );
				}
			}
			/* NULL TERMINATE THE RESULT STRING */
			acTempArray[unLoop] = '\0';
#endif

			/* DO ANY PADDING IF SPECIFIED */
			if( nPadToLeft && bBatchArray[nDestinationBase] )
			{
				unLoop = (WORD) strlen( acTempArray );
				while( (unLoop % bBatchArray[nDestinationBase]) )
					acTempArray[unLoop++] = '0';
				acTempArray[unLoop] = '\0';
			}

			/* NOW GROUP VALUES IN "acTempArray" IF SPECIFIED */
			if( nSeparateOutput && bBatchArray[nDestinationBase] )
			{
				pcHolding = acTempArray;
				for( unLoop=1; *pcHolding; pcHolding++, unLoop++ )
				{
					if( !(unLoop % bBatchArray[nDestinationBase]) )
					{
						memmove( pcHolding+2, pcHolding+1, strlen( pcHolding+1 ) + 1 );
						*++pcHolding = (char) cSeparationCharacter;
						unLoop = 0;
					}
				}
				if( *--pcHolding == (char) cSeparationCharacter )
					*pcHolding = '\0';
			}
			if( strlen(acTempArray) >= MAX_LENGTH_OUTPUT )
			{
				*pnError  = INVALID_TOO_LARGE;
				nReturnValue = ERROR;
			}
			else
			{
				strcpy( pcResult, acTempArray );
				strrev( pcResult );
			}

		} /* END OF IF NO_ERROR */
	} /* END OF ELSE NO_ERROR */

	return( nReturnValue );
}

int FDumpHex::GetMesageLength( RWCString incoming_msg ) 
{
	
	char message_length[6] = {""}; 
	memcpy(message_length, incoming_msg,2);
	unsigned char buf2[6];
	for (int i=0;i<=1;i++)
	{
			buf2[i]= message_length[i] ;
	}
	
	RWCString tcp_header;
    char buffer_tcp_header[80] = {""};
	char    acResult[80]; 
	int     nErrorCode; 
	
 	FDumpHex retorno_length;
	for (  i=0;i<=1;i++)
	{
		tcp_header+=retorno_length.RetornoASCII(buf2[i] ) ;

	}
  
	strcpy(buffer_tcp_header,tcp_header);
	retorno_length.nBaseConvert( buffer_tcp_header, 16, 10, acResult, '\x30', '\x30', ' ' , &nErrorCode) ;

	return atoi(acResult);
				
}


RWCString FDumpHex::RetornoASCII(char  hex_input)
{
	

	if (hex_input  == '\x00') 
		return "00";
	if (hex_input  == '\x01') 
		return "01";
	if (hex_input  == '\x02') 
		return "02";
	if (hex_input  == '\x03') 
		return "03";
	if (hex_input  == '\x04') 
		return "04";
	if (hex_input  == '\x05') 
		return "05";
	if (hex_input  == '\x06') 
		return "06";
	if (hex_input  == '\x07') 
		return "07";
	if (hex_input  == '\x08') 
		return "08";
	if (hex_input  == '\x09') 
		return "09";
	if (hex_input  == '\x0A') 
		return "0A";
	if (hex_input  == '\x0B') 
		return "0B";
	if (hex_input  == '\x0C') 
		return "0C";
	if (hex_input  == '\x0D') 
		return "0D";
	if (hex_input  == '\x0E') 
		return "0E";
	if (hex_input  == '\x0F') 
		return "0F";

	if (hex_input  == '\x10') 
		return "10";
	if (hex_input  == '\x11') 
		return "11";
	if (hex_input  == '\x12') 
		return "12";
	if (hex_input  == '\x13') 
		return "13";
	if (hex_input  == '\x14') 
		return "14";
	if (hex_input  == '\x15') 
		return "15";
	if (hex_input  == '\x16') 
		return "16";
	if (hex_input  == '\x17') 
		return "17";
	if (hex_input  == '\x18') 
		return "18";
	if (hex_input  == '\x19') 
		return "19";
	if (hex_input  == '\x1A') 
		return "1A";
	if (hex_input  == '\x1B') 
		return "1B";
	if (hex_input  == '\x1C') 
		return "1C";
	if (hex_input  == '\x1D') 
		return "1D";
	if (hex_input  == '\x1E') 
		return "1E";
	if (hex_input  == '\x1F') 
		return "1F";

	if (hex_input  == '\x20') 
		return "20";
	if (hex_input  == '\x21') 
		return "21";
	if (hex_input  == '\x22') 
		return "22";
	if (hex_input  == '\x23') 
		return "23";
	if (hex_input  == '\x24') 
		return "24";
	if (hex_input  == '\x25') 
		return "25";
	if (hex_input  == '\x26') 
		return "26";
	if (hex_input  == '\x27') 
		return "27";
	if (hex_input  == '\x28') 
		return "28";
	if (hex_input  == '\x29') 
		return "29";
	if (hex_input  == '\x2A') 
		return "2A";
	if (hex_input  == '\x2B') 
		return "2B";
	if (hex_input  == '\x2C') 
		return "2C";
	if (hex_input  == '\x2D') 
		return "2D";
	if (hex_input  == '\x2E') 
		return "2E";
	if (hex_input  == '\x2F') 
		return "2F";

	
	if (hex_input  == '\x30') 
		return "30";
	if (hex_input  == '\x31') 
		return "31";
	if (hex_input  == '\x32') 
		return "32";
	if (hex_input  == '\x33') 
		return "33";
	if (hex_input  == '\x34') 
		return "34";
	if (hex_input  == '\x35') 
		return "35";
	if (hex_input  == '\x36') 
		return "36";
	if (hex_input  == '\x37') 
		return "37";
	if (hex_input  == '\x38') 
		return "38";
	if (hex_input  == '\x39') 
		return "39";
	if (hex_input  == '\x3A') 
		return "3A";
	if (hex_input  == '\x3B') 
		return "3B";
	if (hex_input  == '\x3C') 
		return "3C";
	if (hex_input  == '\x3D') 
		return "3D";
	if (hex_input  == '\x3E') 
		return "3E";
	if (hex_input  == '\x3F') 
		return "3F";

	if (hex_input  == '\x40') 
		return "40";
	if (hex_input  == '\x41') 
		return "41";
	if (hex_input  == '\x42') 
		return "42";
	if (hex_input  == '\x43') 
		return "43";
	if (hex_input  == '\x44') 
		return "44";
	if (hex_input  == '\x45') 
		return "45";
	if (hex_input  == '\x46') 
		return "46";
	if (hex_input  == '\x47') 
		return "47";
	if (hex_input  == '\x48') 
		return "48";
	if (hex_input  == '\x49') 
		return "49";
	if (hex_input  == '\x4A') 
		return "4A";
	if (hex_input  == '\x4B') 
		return "4B";
	if (hex_input  == '\x4C') 
		return "4C";
	if (hex_input  == '\x4D') 
		return "4D";
	if (hex_input  == '\x4E') 
		return "4E";
	if (hex_input  == '\x4F') 
		return "4F";
	
	if (hex_input  == '\x50') 
		return "50";
	if (hex_input  == '\x51') 
		return "51";
	if (hex_input  == '\x52') 
		return "52";
	if (hex_input  == '\x53') 
		return "53";
	if (hex_input  == '\x54') 
		return "54";
	if (hex_input  == '\x55') 
		return "55";
	if (hex_input  == '\x56') 
		return "56";
	if (hex_input  == '\x57') 
		return "57";
	if (hex_input  == '\x58') 
		return "58";
	if (hex_input  == '\x59') 
		return "59";
	if (hex_input  == '\x5A') 
		return "5A";
	if (hex_input  == '\x5B') 
		return "5B";
	if (hex_input  == '\x5C') 
		return "5C";
	if (hex_input  == '\x5D') 
		return "5D";
	if (hex_input  == '\x5E') 
		return "5E";
	if (hex_input  == '\x5F') 
		return "5F";
	
	if (hex_input  == '\x60') 
		return "60";
	if (hex_input  == '\x61') 
		return "61";
	if (hex_input  == '\x62') 
		return "62";
	if (hex_input  == '\x63') 
		return "63";
	if (hex_input  == '\x64') 
		return "64";
	if (hex_input  == '\x65') 
		return "65";
	if (hex_input  == '\x66') 
		return "66";
	if (hex_input  == '\x67') 
		return "67";
	if (hex_input  == '\x68') 
		return "68";
	if (hex_input  == '\x69') 
		return "69";
	if (hex_input  == '\x6A') 
		return "6A";
	if (hex_input  == '\x6B') 
		return "6B";
	if (hex_input  == '\x6C') 
		return "6C";
	if (hex_input  == '\x6D') 
		return "6D";
	if (hex_input  == '\x6E') 
		return "6E";
	if (hex_input  == '\x6F') 
		return "6F";

	if (hex_input  == '\x70') 
		return "70";
	if (hex_input  == '\x71') 
		return "71";
	if (hex_input  == '\x72') 
		return "72";
	if (hex_input  == '\x73') 
		return "73";
	if (hex_input  == '\x74') 
		return "74";
	if (hex_input  == '\x75') 
		return "75";
	if (hex_input  == '\x76') 
		return "76";
	if (hex_input  == '\x77') 
		return "77";
	if (hex_input  == '\x78') 
		return "78";
	if (hex_input  == '\x79') 
		return "79";
	if (hex_input  == '\x7A') 
		return "7A";
	if (hex_input  == '\x7B') 
		return "7B";
	if (hex_input  == '\x7C') 
		return "7C";
	if (hex_input  == '\x7D') 
		return "7D";
	if (hex_input  == '\x7E') 
		return "7E";
	if (hex_input  == '\x7F') 
		return "7F";

	if (hex_input  == '\x80') 
		return "80";
	if (hex_input  == '\x81') 
		return "81";
	if (hex_input  == '\x82') 
		return "82";
	if (hex_input  == '\x83') 
		return "83";
	if (hex_input  == '\x84') 
		return "84";
	if (hex_input  == '\x85') 
		return "85";
	if (hex_input  == '\x86') 
		return "86";
	if (hex_input  == '\x87') 
		return "87";
	if (hex_input  == '\x88') 
		return "88";
	if (hex_input  == '\x89') 
		return "89";
	if (hex_input  == '\x8A') 
		return "8A";
	if (hex_input  == '\x8B') 
		return "8B";
	if (hex_input  == '\x8C') 
		return "8C";
	if (hex_input  == '\x8D') 
		return "8D";
	if (hex_input  == '\x8E') 
		return "8E";
	if (hex_input  == '\x8F') 
		return "8F";

	if (hex_input  == '\x90') 
		return "90";
	if (hex_input  == '\x91') 
		return "91";
	if (hex_input  == '\x92') 
		return "92";
	if (hex_input  == '\x93') 
		return "93";
	if (hex_input  == '\x94') 
		return "94";
	if (hex_input  == '\x95') 
		return "95";
	if (hex_input  == '\x96') 
		return "96";
	if (hex_input  == '\x97') 
		return "97";
	if (hex_input  == '\x98') 
		return "98";
	if (hex_input  == '\x99') 
		return "99";
	if (hex_input  == '\x9A') 
		return "9A";
	if (hex_input  == '\x9B') 
		return "9B";
	if (hex_input  == '\x9C') 
		return "9C";
	if (hex_input  == '\x9D') 
		return "9D";
	if (hex_input  == '\x9E') 
		return "9E";
	if (hex_input  == '\x9F') 
		return "9F";

	if (hex_input  == '\xA0') 
		return "A0";
	if (hex_input  == '\xA1') 
		return "A1";
	if (hex_input  == '\xA2') 
		return "A2";
	if (hex_input  == '\xA3') 
		return "A3";
	if (hex_input  == '\xA4') 
		return "A4";
	if (hex_input  == '\xA5') 
		return "A5";
	if (hex_input  == '\xA6') 
		return "A6";
	if (hex_input  == '\xA7') 
		return "A7";
	if (hex_input  == '\xA8') 
		return "A8";
	if (hex_input  == '\xA9') 
		return "A9";
	if (hex_input  == '\xAA') 
		return "AA";
	if (hex_input  == '\xAB') 
		return "AB";
	if (hex_input  == '\xAC') 
		return "AC";
	if (hex_input  == '\xAD') 
		return "AD";
	if (hex_input  == '\xAE') 
		return "AE";
	if (hex_input  == '\xAF') 
		return "AF";

	if (hex_input  == '\xB0') 
		return "B0";
	if (hex_input  == '\xB1') 
		return "B1";
	if (hex_input  == '\xB2') 
		return "B2";
	if (hex_input  == '\xB3') 
		return "B3";
	if (hex_input  == '\xB4') 
		return "B4";
	if (hex_input  == '\xB5') 
		return "B5";
	if (hex_input  == '\xB6') 
		return "B6";
	if (hex_input  == '\xB7') 
		return "B7";
	if (hex_input  == '\xB8') 
		return "B8";
	if (hex_input  == '\xB9') 
		return "B9";
	if (hex_input  == '\xBA') 
		return "BA";
	if (hex_input  == '\xBB') 
		return "BB";
	if (hex_input  == '\xBC') 
		return "BC";
	if (hex_input  == '\xBD') 
		return "BD";
	if (hex_input  == '\xBE') 
		return "BE";
	if (hex_input  == '\xBF') 
		return "BF";
	
	if (hex_input  == '\xC0') 
		return "C0";
	if (hex_input  == '\xC1') 
		return "C1";
	if (hex_input  == '\xC2') 
		return "C2";
	if (hex_input  == '\xC3') 
		return "C3";
	if (hex_input  == '\xC4') 
		return "C4";
	if (hex_input  == '\xC5') 
		return "C5";
	if (hex_input  == '\xC6') 
		return "C6";
	if (hex_input  == '\xC7') 
		return "C7";
	if (hex_input  == '\xC8') 
		return "C8";
	if (hex_input  == '\xC9') 
		return "C9";
	if (hex_input  == '\xCA') 
		return "CA";
	if (hex_input  == '\xCB') 
		return "CB";
	if (hex_input  == '\xCC') 
		return "CC";
	if (hex_input  == '\xCD') 
		return "CD";
	if (hex_input  == '\xCE') 
		return "CE";
	if (hex_input  == '\xCF') 
		return "CF";

	if (hex_input  == '\xD0') 
		return "D0";
	if (hex_input  == '\xD1') 
		return "D1";
	if (hex_input  == '\xD2') 
		return "D2";
	if (hex_input  == '\xD3') 
		return "D3";
	if (hex_input  == '\xD4') 
		return "D4";
	if (hex_input  == '\xD5') 
		return "D5";
	if (hex_input  == '\xD6') 
		return "D6";
	if (hex_input  == '\xD7') 
		return "D7";
	if (hex_input  == '\xD8') 
		return "D8";
	if (hex_input  == '\xD9') 
		return "D9";
	if (hex_input  == '\xDA') 
		return "DA";
	if (hex_input  == '\xDB') 
		return "DB";
	if (hex_input  == '\xDC') 
		return "DC";
	if (hex_input  == '\xDD') 
		return "DD";
	if (hex_input  == '\xDE') 
		return "DE";
	if (hex_input  == '\xDF') 
		return "DF";

	if (hex_input  == '\xE0') 
		return "E0";
	if (hex_input  == '\xE1') 
		return "E1";
	if (hex_input  == '\xE2') 
		return "E2";
	if (hex_input  == '\xE3') 
		return "E3";
	if (hex_input  == '\xE4') 
		return "E4";
	if (hex_input  == '\xE5') 
		return "E5";
	if (hex_input  == '\xE6') 
		return "E6";
	if (hex_input  == '\xE7') 
		return "E7";
	if (hex_input  == '\xE8') 
		return "E8";
	if (hex_input  == '\xE9') 
		return "E9";
	if (hex_input  == '\xEA') 
		return "EA";
	if (hex_input  == '\xEB') 
		return "EB";
	if (hex_input  == '\xEC') 
		return "EC";
	if (hex_input  == '\xED') 
		return "ED";
	if (hex_input  == '\xEE') 
		return "EE";
	if (hex_input  == '\xEF') 
		return "EF";

	if (hex_input  == '\xF0') 
		return "F0";
	if (hex_input  == '\xF1') 
		return "F1";
	if (hex_input  == '\xF2') 
		return "F2";
	if (hex_input  == '\xF3') 
		return "F3";
	if (hex_input  == '\xF4') 
		return "F4";
	if (hex_input  == '\xF5') 
		return "F5";
	if (hex_input  == '\xF6') 
		return "F6";
	if (hex_input  == '\xF7') 
		return "F7";
	if (hex_input  == '\xF8') 
		return "F8";
	if (hex_input  == '\xF9') 
		return "F9";
	if (hex_input  == '\xFA') 
		return "FA";
	if (hex_input  == '\xFB') 
		return "FB";
	if (hex_input  == '\xFC') 
		return "FC";
	if (hex_input  == '\xFD') 
		return "FD";
	if (hex_input  == '\xFE') 
		return "FE";
	if (hex_input  == '\xFF') 
		return "FF";
	
		
	if (hex_input  == '\x0D') 
		return "0D";
 	if (hex_input  == '\x1D') 
		return "1D";
 	if (hex_input  == '\x2D') 
		return "2D";
 	if (hex_input  == '\x3D') 
		return "3D";
 	if (hex_input  == '\x4D') 
		return "4D";
 	if (hex_input  == '\x5D') 
		return "5D";
 	if (hex_input  == '\x6D') 
		return "6D";
 	if (hex_input  == '\x7D') 
		return "7D";
 	if (hex_input  == '\x8D') 
		return "8D";
	if (hex_input  == '\x9D') 
		return "9D";
 
	
	return "n";

}

FDumpHex::~FDumpHex()
{

}
