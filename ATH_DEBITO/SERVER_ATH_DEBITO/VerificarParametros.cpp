// VerificarParametros.cpp: implementation of the VerificarParametros class.
//
//////////////////////////////////////////////////////////////////////

#include "VerificarParametros.h"
#include <SQLAPI.h> // main SQLAPI++ header
#include "Iso8583Msg.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VerificarParametros::VerificarParametros()
{
//	pan_number						= "";
	complete_visaF_msg				= "";
	complete_iso8583_msg			= "";
	bit_map							= "B23CC48128E1901A0000000000000128";
	bit_map_no_63                   = "B23CC48128E190180000000000000128";
	bit_map_itbis					= "BA3CC48128E1901A0000000000000128";
	bit_map_itbis_0210				= "B23E84812EC180180000000000000008";
	bit_map_itbis_0210_visaf        = "B23E04802EC180000000000000000008";
	message_type					= "";
	processing_code					= "";			/*003  L6  */
	transaction_amount				= "";			/*004  L12 */ 
	transaction_amount_itbis        = "";			/*005  L12 */ 
	transmition_date_time			= "";			/*007  L10 */ 
	convertion_rate					= "";			/*009  L08 */ 			
	system_trace					= "";
	time_local_transaction			= "";
	date_local_transaction			= "";
	expiration_date					= "";
	capture_date					= "";
	date_settlement					= "";
	merchant_type					= "";
	pos_entry_mode					= "";
	for_athd						= "";
	pos_condition_code				= "";
	acquiring_institution_id_code	= "";
	track_2							= "";
	retrieval_reference_number		= "";
	autirization_id_response		= "000000";
	response_code					= "";
	card_acceptor_terminal_id		= "";
	card_acceptor_id_code			= "";
	card_acceptor_name_location		= "";
	pos_retailer_data				= "";
	currency_code_transaction		= "";
	pin_data						= "";
	pos_terminal_data				= "";
	pos_issuer_data					= "";
	CVV2							= "";
	original_data_elements			= "",
	pos_terminal_address_branch		= "";
	pos_invoice_data				= "";
	pos_settlement_data				= "";
	switch_key						= "";

	begin_of_text					= "";
	end_of_text						= "";
	msg_type_visa					= "";
	acquirer_bin					= "";
	merchant_number					= "";
	terminal_id_1					= "";
	category_code					= "";
	country_code					= "";
	city_code						= "";
	timing_zone						= "";
	auth_trans_code					= "";
	terminal_id_2					= "";
	trans_seq_number				= "";
	track2_from_visa_msg			= "";
	amount_from_visa_msg			= "";
	visa_response_code				= "";
	visa_trans_date					= "";
	recv_queue_rw					= "";
	field_35_01						= "";
	field_35_02						= "";
	resultado_rw					= "";		
	connection_status_rw			= "";
	connection_bin_rw				= "";
	pre_zero = '\x30';

}





int VerificarParametros::nBaseConvert(
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

			if( unTempValue2 >= nSourceBase )
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



void VerificarParametros::Proccess_Message( RWCString incoming_msg )
{
	RWCString output_to_b24 ;
	RWCString incoming_visaf;
			
//	incoming_visaf += begingoftext;
	incoming_visaf = incoming_msg(4,(incoming_msg.length()-4));
//	incoming_visaf += endoftext;
//	output_to_b24 = ConvertSendQueueVisaf(incoming_visaf) ;
//	cout << "Valor de mensaje completo > " <<output_to_b24 << endl;
	Iso8583Msg send_generic_0200;
	send_generic_0200.SendMessageToQueueSql(incoming_visaf,
	//    sql_queue,	queue_mgr);
	"eeeeeee",	"eeeeeeeee");
//	send_generic_0200.SendMessageToQueue(output_to_b24,send_queue,queue_mgr);



}

int VerificarParametros::GetMesageLength( char *incoming_msg ) 
{
	
	char message_length[6] = {""}; 
	memcpy(message_length, incoming_msg,4);
	unsigned char buf2[6];
	for (int i=0;i<=3;i++)
	{
			buf2[i]= message_length[i] ;
	}
	
	RWCString tcp_header;
    char buffer_tcp_header[80] = {""};
	char    acResult[80]; 
	int     nErrorCode; 
	
 	VerificarParametros retorno_length;
	for (  i=0;i<=3;i++)
	{
		tcp_header+=retorno_length.RetornoASCII(buf2[i] ) ;

	}
  
	strcpy(buffer_tcp_header,tcp_header);
	retorno_length.nBaseConvert( buffer_tcp_header, 16, 10, acResult, '\x30', '\x30', ' ' , &nErrorCode) ;

	return atoi(acResult);
				
}

RWCString  VerificarParametros::RetornoASCII(char  hex_input)
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
	
	
	
	return "n";

}


int VerificarParametros::ResultOfParametros(RWCString incoming)
{
	
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 


		}

		if (count == 3)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 4)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 5) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 6)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 7)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 8)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 9)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 10)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 11)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 12)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 14)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	

		if (count == 15)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

	
		if (count == 16)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
	
		if (count == 17)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 18)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 19)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			

		if (count == 20)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
	
		if (count == 21)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 22)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 23)
		{
			CVV2 = token; 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
		}
		
		
		if (count == 24)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				salida_result = 0;
				break;
			}
		
		}			


		if (count == 25)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 26)
		{
			pos_settlement_data = token; 
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
		
		}			

		count++;
	}
	
		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			if (connection_bin_rw == "1")
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "B24_Tandem_CC";
			}
			else
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "Visa_Eps_CC";
			}
		

			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( connection_status, cmd.Field("Status_Connection").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
			else
				connection_status_rw = connection_status;
			//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de Connection_Status #1 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();

		//////////////////////////////////////////////////////////////////////////////////////
		
	if(connection_status_rw == "Connected")
	{
		//connection_status_rw = connection_status;
	}
	else
	{
		salida_result = 0;
		salida = 5;
	}




    if ( salida_result == 1)
	{

		RWCTokenizer next(track_2);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
	////////////////////////////Verificar sql////////////////////////////

		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC pro_verify_parameter  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
		//	cout << "Valor de card_acceptor_id_code > " << card_acceptor_id_code << endl;
		//	cout << "Valor de pan_number > " << pan_number << endl;
		//	cout << "Valor de card_acceptor_terminal_id > " << card_acceptor_terminal_id << endl;
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
				strcpy ( maximo, cmd.Field("Maximo").asString());
			}
			
			maximo_pre = maximo ;
			size_t cantidad_ceros = 12-maximo_pre.length();
			maximo_pre.prepend(pre_zero , cantidad_ceros);
		
			resultado_rw = resultado;
		
			if(resultado_rw > "1")
			{
				salida = 3;	
			}
			else
			if( (transaction_amount > maximo_pre) && (maximo_pre != "000000000000" ))
			{
				salida = 2;
			}
			else
				salida = -1;
	
				
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}

			con.Disconnect();
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de Exec Merchant number #1 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();
	}
	//else
	//{
	//	salida = 0;
	//}



	return salida;
}

int VerificarParametros::ResultOfParametrosAVS(RWCString incoming)
{
	
	//cout << "Dentro de avs > " << endl;
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 


		}

		if (count == 3)
		{
			transaction_amount_itbis = token; 


		}

		if (count == 4)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 5)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 6) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 7)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 8)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 9)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 10)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 11)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 12)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 14)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 15)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	

		if (count == 16)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

	
		if (count == 17)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
	
		if (count == 18)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 19)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 20)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			

		if (count == 21)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
	
		if (count == 22)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 23)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 24)
		{
			CVV2 = token; 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
		}
		
		
		if (count == 25)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				salida_result = 0;
				break;
			}
		
		}			


		if (count == 26)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 27)
		{
			pos_settlement_data = token; 
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
		
		}			

		count++;
	}
/* se usa sin los paramtros
	if(	salida_result == 0)
		salida = 0;
	else
		salida = -1;

*/
/// Perte nueva para lo de los parametros...

	SAConnection con; // create connection object

	SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			if (connection_bin_rw == "1")
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "B24_Tandem_CC";
			}
			else
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "Visa_Eps_CC";
			}
		

			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( connection_status, cmd.Field("Status_Connection").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
			else
				connection_status_rw = connection_status;
			//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error Connection_Status #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();

		//////////////////////////////////////////////////////////////////////////////////////
		
	//cout << "Valor de connection_status_rw > " << connection_status_rw << endl;
	if(connection_status_rw == "Connected")
	{
	
	}
	else
	{
		salida_result = 0;
		salida = 5;
	}




    if ( salida_result == 1)
	{

		RWCTokenizer next(track_2);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
	////////////////////////////Verificar sql////////////////////////////

		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

		//cout << "Valor de varios elementos > " << card_acceptor_id_code << " " 
		//	<< pan_number << " " << card_acceptor_terminal_id << endl;
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC pro_verify_parameter  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			//cout << "valor de card_acceptor_id_code > " << card_acceptor_id_code << endl;
		//	cout << "valor de pan_number > " << pan_number << endl;
		//	cout << "valor de card_acceptor_terminal_id > " << card_acceptor_terminal_id << endl;
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
				strcpy ( maximo, cmd.Field("Maximo").asString());
			}
		
			maximo_pre = maximo ;
			size_t cantidad_ceros = 12-maximo_pre.length();
			maximo_pre.prepend(pre_zero , cantidad_ceros);
		//	cout << "Valor de resultado > " << resultado << endl;

			resultado_rw = resultado;
		
			if(resultado_rw == "1")
			{
				salida = 1;	
			}
			else
			if(resultado_rw > "1")
			{
				salida = 3;	
			}
			else
			if( (transaction_amount > maximo_pre) && (maximo_pre != "000000000000" ))
			{
				salida = 2;
			}
			else
				salida = -1;
				
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}

			//con.Disconnect();
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error EXEC pro_verify_parameter #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();


		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC Pro_verify_Int_Upd  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
				//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error de crear 0210  > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();
	
		/////////////////////////////////////////////////////////////////////

	}



///////////////////////////////////////////


	return salida;
}



int VerificarParametros::ResultOfParametrosAVS1C(RWCString incoming)
{
	
	//cout << "Dentro de avs > " << endl;
//	cout << "Valor de incoming " << incoming <<endl;
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	while(!(token=next(RWCString('\x1C'))).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 

			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token(5,token.length()-5); 
//			cout << "Valor de processing_code " << processing_code << endl;
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token(5,token.length()-5); 


		}

		if (count == 3)
		{
			transaction_amount_itbis = token(5,token.length()-5); 


		}

		if (count == 4)
		{
			transmition_date_time = token(5,token.length()-5); 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 5)
		{
		
			system_trace = token(5,token.length()-5); 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 6) 
		{				
					
			time_local_transaction = token(5,token.length()-5);
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 7)
		{
				
			date_local_transaction = token(5,token.length()-5); 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 8)
		{
				
			expiration_date = token(5,token.length()-5); 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 9)
		{
				
			capture_date = token(5,token.length()-5); 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 10)
		{
				
			merchant_type = token(5,token.length()-5); 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 11)
		{
				
			pos_entry_mode = token(5,token.length()-5); 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 12)
		{
			pos_condition_code = token(5,token.length()-5); 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token(5,token.length()-5); 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 14)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token(5,token.length()-5); 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 15)
		{
			retrieval_reference_number = token(5,token.length()-5); 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	

		if (count == 16)
		{
			card_acceptor_terminal_id = token(5,token.length()-5); 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

	
		if (count == 17)
		{
			card_acceptor_id_code = token(5,token.length()-5); 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
	
		if (count == 18)
		{
			card_acceptor_name_location = token(5,token.length()-5); 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 19)
		{
			pos_retailer_data = token(5,token.length()-5); 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 20)
		{
			currency_code_transaction = token(5,token.length()-5); 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			

		if (count == 21)
		{
			pin_data = token(5,token.length()-5); 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
	
		if (count == 22)
		{
			pos_terminal_data = token(5,token.length()-5); 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 23)
		{
			pos_issuer_data = token(5,token.length()-5); 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 24)
		{
			CVV2 = token(5,token.length()-5); 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
		}
		
		
		if (count == 25)
		{
			pos_terminal_address_branch = token(5,token.length()-5); 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				salida_result = 0;
				break;
			}
		
		}			


		if (count == 26)
		{
			pos_invoice_data = token(5,token.length()-5); 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 27)
		{
			pos_settlement_data = token(5,token.length()-5); 
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
		
		}			

		count++;
	}
/* se usa sin los paramtros
	if(	salida_result == 0)
		salida = 0;
	else
		salida = -1;

*/
/// Perte nueva para lo de los parametros...
//cout << "Dentro de avs > " << endl;
	SAConnection con; // create connection object

	SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			if (connection_bin_rw == "1")
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "B24_Tandem_CC";
			}
			else
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "Visa_Eps_CC";
			}
		

			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( connection_status, cmd.Field("Status_Connection").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
			else
				connection_status_rw = connection_status;
			//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error Connection_Status #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();

		//////////////////////////////////////////////////////////////////////////////////////
		
	//cout << "Valor de connection_status_rw > " << connection_status_rw << endl;
	if(connection_status_rw == "Connected")
	{
	
	}
	else
	{
		salida_result = 0;
		salida = 5;
	}




    if ( salida_result == 1)
	{

		RWCTokenizer next(track_2);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
	////////////////////////////Verificar sql////////////////////////////

		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

		//cout << "Valor de varios elementos > " << card_acceptor_id_code << " " 
		//	<< pan_number << " " << card_acceptor_terminal_id << endl;
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC pro_verify_parameter  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			//cout << "valor de card_acceptor_id_code > " << card_acceptor_id_code << endl;
		//	cout << "valor de pan_number > " << pan_number << endl;
		//	cout << "valor de card_acceptor_terminal_id > " << card_acceptor_terminal_id << endl;
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
				strcpy ( maximo, cmd.Field("Maximo").asString());
			}
		
			maximo_pre = maximo ;
			size_t cantidad_ceros = 12-maximo_pre.length();
			maximo_pre.prepend(pre_zero , cantidad_ceros);
		//	cout << "Valor de resultado > " << resultado << endl;

			resultado_rw = resultado;
		
			if(resultado_rw == "1")
			{
				salida = 1;	
			}
			else
			if(resultado_rw > "1")
			{
				salida = 3;	
			}
			else
			if( (transaction_amount > maximo_pre) && (maximo_pre != "000000000000" ))
			{
				salida = 2;
			}
			else
				salida = -1;
				
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}

			//con.Disconnect();
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error EXEC pro_verify_parameter #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();


		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC Pro_verify_Int_Upd  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
				//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error de crear 0210  > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();
	
		/////////////////////////////////////////////////////////////////////

	}



///////////////////////////////////////////


	return salida;
}



int VerificarParametros::ResultOfParametrosITBIS(RWCString incoming)
{
	
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;

	
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	//cout << "Dentro de ITBIS"  << endl;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			//cout << "Dentro de proccessing code"  << endl;
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				//cout << "Valor de salida_result Dentro #1" << salida_result << endl;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				//cout << "Valor de salida_result Dentro #2" << salida_result << endl;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 


		}
		
		if (count == 3)
		{
			transaction_amount_itbis = token; 

		}

		if (count == 4)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 5)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 6) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 7)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 8)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 9)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 10)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 11)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 12)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 14)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 15)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	

		if (count == 16)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

	
		if (count == 17)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
	

		if (count == 18)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 19)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 20)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			

		if (count == 21)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
	
		if (count == 22)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 23)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 24)
		{
			CVV2 = token; 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
		}
		
		
		if (count == 25)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				salida_result = 0;
				break;
			}
		
		}			


		if (count == 26)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 27)
		{
			pos_settlement_data = token;
			
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
			
		
		}			

		count++;
	}

	//salida = -1;
	
		
//	cout << "Valor de salida_result # > " << salida_result << endl;
	SAConnection con; // create connection object

	SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			if (connection_bin_rw == "1")
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "B24_Tandem_CC";
			}
			else
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "Visa_Eps_CC";
			}
		

			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( connection_status, cmd.Field("Status_Connection").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
			else
				connection_status_rw = connection_status;
			//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error Connection_Status #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();

		//////////////////////////////////////////////////////////////////////////////////////
		
	//cout << "Valor de connection_status_rw > " << connection_status_rw << endl;
	if(connection_status_rw == "Connected")
	{
	
	}
	else
	{
		salida_result = 0;
		salida = 5;
	}




    if ( salida_result == 1)
	{

		RWCTokenizer next(track_2);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
	////////////////////////////Verificar sql////////////////////////////

		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC pro_verify_parameter  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
				strcpy ( maximo, cmd.Field("Maximo").asString());
			}
		
			maximo_pre = maximo ;
			size_t cantidad_ceros = 12-maximo_pre.length();
			maximo_pre.prepend(pre_zero , cantidad_ceros);
	
			resultado_rw = resultado;
		
			if(resultado_rw == "1")
			{
				salida = 1;	
			}
			else
			if(resultado_rw > "1")
			{
				salida = 3;	
			}
			else
			if( (transaction_amount > maximo_pre) && (maximo_pre != "000000000000" ))
			{
				salida = 2;
			}
			else
				salida = -1;
				
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}

			//con.Disconnect();
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error EXEC pro_verify_parameter #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();


		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC Pro_verify_Int_Upd  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
				//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error de crear 0210  > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();
	
		/////////////////////////////////////////////////////////////////////

	}
	


	return salida;
}

int VerificarParametros::ResultOfParametrosATHDebito(RWCString incoming)
{
	
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	//cout << "Dentro de ITBIS"  << endl;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			//cout << "Dentro de proccessing code"  << endl;
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				//cout << "Valor de salida_result Dentro #1" << salida_result << endl;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				//cout << "Valor de salida_result Dentro #2" << salida_result << endl;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 


		}
		
	
		if (count == 3)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 4)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 5) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 6)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 7)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 8)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 9)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 10)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 11)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 12)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 14)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	

		if (count == 15)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

/*	
		if (count == 16)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
*/	
		if (count == 16)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 17)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 18)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			

		if (count == 19)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
	
		if (count == 20)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 21)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			
/*
		if (count == 22)
		{
			CVV2 = token; 
			
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			
		}
*/		
		
		if (count == 22)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				salida_result = 0;
				break;
			}
		
		}			


		if (count == 23)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 24)
		{
			pos_settlement_data = token;
			
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
			
		
		}			

		count++;
	}

   if(salida_result == 0)
   {
       salida = 0;
   }
   else
    salida = -1;
	
	
/*
	//salida = -1;
	
		
//	cout << "Valor de salida_result # > " << salida_result << endl;
	SAConnection con; // create connection object

	SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			if (connection_bin_rw == "1")
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "B24_Tandem_CC";
			}
			else
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "Visa_Eps_CC";
			}
		

			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( connection_status, cmd.Field("Status_Connection").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
			else
				connection_status_rw = connection_status;
			//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error Connection_Status #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();

		//////////////////////////////////////////////////////////////////////////////////////
		
	//cout << "Valor de connection_status_rw > " << connection_status_rw << endl;
	if(connection_status_rw == "Connected")
	{
	
	}
	else
	{
		salida_result = 0;
		salida = 5;
	}




    if ( salida_result == 1)
	{

		RWCTokenizer next(track_2);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
	////////////////////////////Verificar sql////////////////////////////

		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

		//cout << "Valor de varios elementos > " << card_acceptor_id_code << " " 
		//	<< pan_number << " " << card_acceptor_terminal_id << endl;
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC pro_verify_parameter  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			//cout << "valor de card_acceptor_id_code > " << card_acceptor_id_code << endl;
		//	cout << "valor de pan_number > " << pan_number << endl;
		//	cout << "valor de card_acceptor_terminal_id > " << card_acceptor_terminal_id << endl;
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
				strcpy ( maximo, cmd.Field("Maximo").asString());
			}
		
			maximo_pre = maximo ;
			size_t cantidad_ceros = 12-maximo_pre.length();
			maximo_pre.prepend(pre_zero , cantidad_ceros);
		//	cout << "Valor de resultado > " << resultado << endl;

			resultado_rw = resultado;
		
			if(resultado_rw == "1")
			{
				salida = 1;	
			}
			else
			if(resultado_rw > "1")
			{
				salida = 3;	
			}
			else
			if( (transaction_amount > maximo_pre) && (maximo_pre != "000000000000" ))
			{
				salida = 2;
			}
			else
				salida = -1;
				
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}

			//con.Disconnect();
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error EXEC pro_verify_parameter #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();


		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC Pro_verify_Int_Upd  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
				//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error de crear 0210  > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();
	
		/////////////////////////////////////////////////////////////////////

	}
*/	

	return salida;
}

int VerificarParametros::ResultOfParametrosATHDebitoITBIS(RWCString incoming)
{
	
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	//cout << "Dentro de ITBIS"  << endl;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			//cout << "Dentro de proccessing code"  << endl;
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				//cout << "Valor de salida_result Dentro #1" << salida_result << endl;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				//cout << "Valor de salida_result Dentro #2" << salida_result << endl;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 


		}
		
	
		if (count == 3)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 4)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 5) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 6)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 7)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 8)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 9)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 10)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 11)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 12)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 14)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	

		if (count == 15)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

/*	
		if (count == 16)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
*/	
		if (count == 16)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 17)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 18)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			

		if (count == 19)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
	
		if (count == 20)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 21)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 22)
		{
			CVV2 = token; 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
			
		}
		
		
		if (count == 23)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				salida_result = 0;
				break;
			}
		
		}			


		if (count == 24)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 25)
		{
			pos_settlement_data = token;
			
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
			
		
		}			

		count++;
	}

   if(salida_result == 0)
   {
       salida = 0;
   }
   else
    salida = -1;
	
	
/*
	//salida = -1;
	
		
//	cout << "Valor de salida_result # > " << salida_result << endl;
	SAConnection con; // create connection object

	SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			if (connection_bin_rw == "1")
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "B24_Tandem_CC";
			}
			else
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "Visa_Eps_CC";
			}
		

			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( connection_status, cmd.Field("Status_Connection").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
			else
				connection_status_rw = connection_status;
			//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error Connection_Status #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();

		//////////////////////////////////////////////////////////////////////////////////////
		
	//cout << "Valor de connection_status_rw > " << connection_status_rw << endl;
	if(connection_status_rw == "Connected")
	{
	
	}
	else
	{
		salida_result = 0;
		salida = 5;
	}




    if ( salida_result == 1)
	{

		RWCTokenizer next(track_2);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
	////////////////////////////Verificar sql////////////////////////////

		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

		//cout << "Valor de varios elementos > " << card_acceptor_id_code << " " 
		//	<< pan_number << " " << card_acceptor_terminal_id << endl;
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC pro_verify_parameter  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			//cout << "valor de card_acceptor_id_code > " << card_acceptor_id_code << endl;
		//	cout << "valor de pan_number > " << pan_number << endl;
		//	cout << "valor de card_acceptor_terminal_id > " << card_acceptor_terminal_id << endl;
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
				strcpy ( maximo, cmd.Field("Maximo").asString());
			}
		
			maximo_pre = maximo ;
			size_t cantidad_ceros = 12-maximo_pre.length();
			maximo_pre.prepend(pre_zero , cantidad_ceros);
		//	cout << "Valor de resultado > " << resultado << endl;

			resultado_rw = resultado;
		
			if(resultado_rw == "1")
			{
				salida = 1;	
			}
			else
			if(resultado_rw > "1")
			{
				salida = 3;	
			}
			else
			if( (transaction_amount > maximo_pre) && (maximo_pre != "000000000000" ))
			{
				salida = 2;
			}
			else
				salida = -1;
				
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}

			//con.Disconnect();
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error EXEC pro_verify_parameter #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();


		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC Pro_verify_Int_Upd  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
				//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error de crear 0210  > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();
	
		/////////////////////////////////////////////////////////////////////

	}
*/	

	return salida;
}



int VerificarParametros::ResultOfParametrosATHCredito(RWCString incoming)
{
	
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	//cout << "Dentro de ITBIS"  << endl;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			//cout << "Dentro de proccessing code"  << endl;
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				//cout << "Valor de salida_result Dentro #1" << salida_result << endl;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				//cout << "Valor de salida_result Dentro #2" << salida_result << endl;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 


		}
		
		if (count == 3)
		{
			transaction_amount_itbis = token; 

		}

		if (count == 4)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 5)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 6) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 7)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 8)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 9)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 10)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 11)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 12)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 14)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 15)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	

		if (count == 16)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

	
		if (count == 17)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
	
		if (count == 18)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 19)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 20)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			

		if (count == 21)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
	
		if (count == 22)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 23)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 24)
		{
			CVV2 = token; 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
		}
		if (count == 25)
		{
			//CVV2 = token; 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
		}
		
		if (count == 26)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				salida_result = 0;
				break;
			}
		
		}			


		if (count == 27)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 28)
		{
			pos_settlement_data = token;
			
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
			
		
		}			

		count++;
	}

   if(salida_result == 0)
   {
       salida = 0;
   }
   else
    salida = -1;
	
	
/*
	//salida = -1;
	
		
//	cout << "Valor de salida_result # > " << salida_result << endl;
	SAConnection con; // create connection object

	SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			if (connection_bin_rw == "1")
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "B24_Tandem_CC";
			}
			else
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "Visa_Eps_CC";
			}
		

			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( connection_status, cmd.Field("Status_Connection").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
			else
				connection_status_rw = connection_status;
			//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error Connection_Status #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();

		//////////////////////////////////////////////////////////////////////////////////////
		
	//cout << "Valor de connection_status_rw > " << connection_status_rw << endl;
	if(connection_status_rw == "Connected")
	{
	
	}
	else
	{
		salida_result = 0;
		salida = 5;
	}




    if ( salida_result == 1)
	{

		RWCTokenizer next(track_2);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
	////////////////////////////Verificar sql////////////////////////////

		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

		//cout << "Valor de varios elementos > " << card_acceptor_id_code << " " 
		//	<< pan_number << " " << card_acceptor_terminal_id << endl;
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC pro_verify_parameter  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			//cout << "valor de card_acceptor_id_code > " << card_acceptor_id_code << endl;
		//	cout << "valor de pan_number > " << pan_number << endl;
		//	cout << "valor de card_acceptor_terminal_id > " << card_acceptor_terminal_id << endl;
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
				strcpy ( maximo, cmd.Field("Maximo").asString());
			}
		
			maximo_pre = maximo ;
			size_t cantidad_ceros = 12-maximo_pre.length();
			maximo_pre.prepend(pre_zero , cantidad_ceros);
		//	cout << "Valor de resultado > " << resultado << endl;

			resultado_rw = resultado;
		
			if(resultado_rw == "1")
			{
				salida = 1;	
			}
			else
			if(resultado_rw > "1")
			{
				salida = 3;	
			}
			else
			if( (transaction_amount > maximo_pre) && (maximo_pre != "000000000000" ))
			{
				salida = 2;
			}
			else
				salida = -1;
				
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}

			//con.Disconnect();
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error EXEC pro_verify_parameter #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();


		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC Pro_verify_Int_Upd  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
				//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error de crear 0210  > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();
	
		/////////////////////////////////////////////////////////////////////

	}
*/	

	return salida;
}

int VerificarParametros::ResultOfParametrosAvs0420(RWCString incoming)
{
	
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	//cout << "Dentro de ITBIS"  << endl;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			//cout << "Dentro de proccessing code"  << endl;
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				//cout << "Valor de salida_result Dentro #1" << salida_result << endl;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				//cout << "Valor de salida_result Dentro #2" << salida_result << endl;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 


		}

		if (count == 3)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 4)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 5) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 6)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 7)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 8)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 9)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 10)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 11)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 12)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 14)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	
		if (count == 15)
		{
			autirization_id_response = token; 
			int autirization_id_response_length = autirization_id_response.length();
			if( autirization_id_response_length != 6)
			{
				MessageErrorLength(RWCString("autirization_id_response"),
				autirization_id_response_length,6);
				salida_result = 0;
				break;
			}
		}
		if (count == 16)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

	
		if (count == 17)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
	
		if (count == 18)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 19)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 20)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			
/*
		if (count == 21)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
*/	
		if (count == 21)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 22)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			
		if (count == 23)
		{
		
		
		}		
		
		if (count == 24)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}				


		if (count == 25)
		{
			pos_settlement_data = token;
			
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
			
		
		}			

		count++;
	}

	if(salida_result == 0)
		salida = 0;
	else
		salida = -1;

	return salida;
}

int VerificarParametros::ResultOfParametrosAvs04201C(RWCString incoming)
{
	
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	//cout << "Dentro de ITBIS"  << endl;
	while(!(token=next(RWCString('\x1C'))).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token(5,token.length()-5); 
			//cout << "Dentro de proccessing code"  << endl;
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				//cout << "Valor de salida_result Dentro #1" << salida_result << endl;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				//cout << "Valor de salida_result Dentro #2" << salida_result << endl;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token(5,token.length()-5); 


		}

		if (count == 3)
		{
			transmition_date_time = token(5,token.length()-5); 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 4)
		{
		
			system_trace = token(5,token.length()-5); 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 5) 
		{				
					
			time_local_transaction = token(5,token.length()-5);
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 6)
		{
				
			date_local_transaction = token(5,token.length()-5); 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 7)
		{
				
			expiration_date = token(5,token.length()-5); 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 8)
		{
				
			capture_date = token(5,token.length()-5); 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 9)
		{
				
			merchant_type = token(5,token.length()-5); 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 10)
		{
				
			pos_entry_mode = token(5,token.length()-5); 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 11)
		{
			pos_condition_code = token(5,token.length()-5); 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 12)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token(5,token.length()-5); 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token(5,token.length()-5); 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 14)
		{
			retrieval_reference_number = token(5,token.length()-5); 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	
		if (count == 15)
		{
			autirization_id_response = token(5,token.length()-5); 
			int autirization_id_response_length = autirization_id_response.length();
			if( autirization_id_response_length != 6)
			{
				MessageErrorLength(RWCString("autirization_id_response"),
				autirization_id_response_length,6);
				salida_result = 0;
				break;
			}
		}
		if (count == 16)
		{
			card_acceptor_terminal_id = token(5,token.length()-5); 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

	
		if (count == 17)
		{
			card_acceptor_id_code = token(5,token.length()-5); 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
	
		if (count == 18)
		{
			card_acceptor_name_location = token(5,token.length()-5); 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 19)
		{
			pos_retailer_data = token(5,token.length()-5); 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 20)
		{
			currency_code_transaction = token(5,token.length()-5); 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			
/*
		if (count == 21)
		{
			pin_data = token(5,token.length()-5); 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
*/	
		if (count == 21)
		{
			pos_terminal_data = token(5,token.length()-5); 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 22)
		{
			pos_issuer_data = token(5,token.length()-5); 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			
		if (count == 23)
		{
		
		
		}		
		
		if (count == 24)
		{
			pos_invoice_data = token(5,token.length()-5); 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}				


		if (count == 25)
		{
			pos_settlement_data = token(5,token.length()-5);
			
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
			
		
		}			

		count++;
	}

	if(salida_result == 0)
		salida = 0;
	else
		salida = -1;

	return salida;
}

int VerificarParametros::ResultOfParametros0420ATHDebito(RWCString incoming)
{
	
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	//cout << "Dentro de ITBIS"  << endl;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			//cout << "Dentro de proccessing code"  << endl;
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				//cout << "Valor de salida_result Dentro #1" << salida_result << endl;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				//cout << "Valor de salida_result Dentro #2" << salida_result << endl;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 


		}

		if (count == 3)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 4)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 5) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 6)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 7)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 8)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 9)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 10)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 11)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 12)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 14)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	


		if (count == 15)
		{
			response_code = token; 
			int response_code_length = response_code.length();
			if( response_code_length != 2)
			{
				MessageErrorLength(RWCString("response_code"),
				response_code_length,2);
				salida_result = 0;
				break;
			}
		}	


		if (count == 16)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

	/*
		if (count == 16)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
	*/
		if (count == 17)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 18)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 19)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			
/*
		if (count == 19)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
*/	
		if (count == 20)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 21)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			
		if (count == 22)
		{
		
		
			original_data_elements = token; 
			int original_data_elements_length = original_data_elements.length();
			if( original_data_elements_length != 42)
			{
				MessageErrorLength(RWCString("original_data_elements"),
				original_data_elements_length,42);
				salida_result = 0;
				break;
			}


		}
		/*
		if (count == 23)
		{
			
			pos_terminal_address_branch = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
			
		
		}				
		*/
		
		if (count == 23)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}				


		if (count == 24)
		{
			pos_settlement_data = token;
			
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
			
		
		}			

		count++;
	}

	if(salida_result == 0)
	{
		salida = 0;
	}
	else
	{
		salida = -1;
	}


	//salida = -1;
	
		
/*
	SAConnection con; // create connection object

	SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			if (connection_bin_rw == "1")
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "B24_Tandem_CC";
			}
			else
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "Visa_Eps_CC";
			}
		

			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( connection_status, cmd.Field("Status_Connection").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
			else
				connection_status_rw = connection_status;
			//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error Connection_Status #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();

		//////////////////////////////////////////////////////////////////////////////////////
		
	//cout << "Valor de connection_status_rw > " << connection_status_rw << endl;
	if(connection_status_rw == "Connected")
	{
	
	}
	else
	{
		salida_result = 0;
		salida = 5;
	}




    if ( salida_result == 1)
	{

		RWCTokenizer next(track_2);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
	////////////////////////////Verificar sql////////////////////////////

		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

		//cout << "Valor de varios elementos > " << card_acceptor_id_code << " " 
		//	<< pan_number << " " << card_acceptor_terminal_id << endl;
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC pro_verify_parameter  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			//cout << "valor de card_acceptor_id_code > " << card_acceptor_id_code << endl;
		//	cout << "valor de pan_number > " << pan_number << endl;
		//	cout << "valor de card_acceptor_terminal_id > " << card_acceptor_terminal_id << endl;
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
				strcpy ( maximo, cmd.Field("Maximo").asString());
			}
		
			maximo_pre = maximo ;
			size_t cantidad_ceros = 12-maximo_pre.length();
			maximo_pre.prepend(pre_zero , cantidad_ceros);
		//	cout << "Valor de resultado > " << resultado << endl;

			resultado_rw = resultado;
		
			if(resultado_rw == "1")
			{
				salida = 1;	
			}
			else
			if(resultado_rw > "1")
			{
				salida = 3;	
			}
			else
			if( (transaction_amount > maximo_pre) && (maximo_pre != "000000000000" ))
			{
				salida = 2;
			}
			else
				salida = -1;
				
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}

			//con.Disconnect();
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error EXEC pro_verify_parameter #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();


		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC Pro_verify_Int_Upd  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
				//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error de crear 0210  > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();
	
		/////////////////////////////////////////////////////////////////////

	}
	*/
	
	/*
		cout << "Valor de varios elementos > " << card_acceptor_id_code << " " 
			<< pan_number << " " << card_acceptor_terminal_id << endl;

		SAConnection con1; // create connection object
		SACommand cmd1(&con1);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

		try
		{
   
			
			con1.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"fr2436",   // password
			SA_SQLServer_Client);
			
			cmd1.setConnection(&con1);

			
			cmd1.setCommandText("EXEC Pro_verify_Int_Upd  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd1.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd1.Param("Pan_Number").setAsString() = pan_number;
			cmd1.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			
			cmd1.Execute();
			while(cmd1.FetchNext())
			{
			 
				strcpy ( resultado, cmd1.Field("resultado").asString());
			}
		
					
			if (cmd1.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd1.RowsAffected());
			}
			//	con1.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con1.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error de crear 0210  > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con1.Disconnect();
	
	
	}
	*/

	return salida;
}



int VerificarParametros::ResultOfParametrosATH(RWCString incoming)
{
	
	connection_bin_rw = "1";
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	//cout << "Dentro de ITBIS"  << endl;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			//cout << "Dentro de proccessing code"  << endl;
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				//cout << "Valor de salida_result Dentro #1" << salida_result << endl;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				//cout << "Valor de salida_result Dentro #2" << salida_result << endl;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 


		}
		
		if (count == 3)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 4)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 5) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 6)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 7)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 8)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 9)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 10)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 11)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 12)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 14)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	

		if (count == 15)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			
	
	
		if (count == 16)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 17)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 18)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			

		if (count == 19)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}

/*
			 RWCString output_descrypt;
			 RWCString output_encrypt;
			 RWCString key				  = "1123456789abcdef";
	         RWCString output_for_descrypt = output_descrypt;


			 char ath_key[20]			  = {""};
	         char output_to_encrypt[20]	  = {""};
			 char output_to_decrypt[20]	  = {""};

		 	 strcpy(output_to_decrypt,pin_data);

	

			 FDumpHex des_descrypt;
			 FDumpHex des_encrypt;


		     output_descrypt=des_descrypt.DES_Hex_Decrypt("0123456789abcdef", output_to_decrypt) ;
	         cout << "Valor de output_descrypt > " << output_descrypt << endl;
	         cout << "Valor de output_descrypt.length() > " << output_descrypt.length() << endl;

	        
	         
	         strcpy(ath_key ,key); 
			 strcpy(output_to_encrypt,output_descrypt);

			 output_encrypt=des_encrypt.DES_Hex_Encrypt(ath_key, output_to_encrypt) ;
	
			 cout << "Valor de output_encrypt > " << output_encrypt << endl;
			 cout << "Valor de output_encrypt.length() > " << output_encrypt.length() << endl;
			 pin_data=output_encrypt;
*/	
		}			
	
		if (count == 20)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 21)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			

			
		
		if (count == 22)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				salida_result = 0;
				break;
			}
		
		}			


		if (count == 23)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 24)
		{
			pos_settlement_data = token;
			/*
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
			*/
		
		}			

		count++;
	}
	


	SAConnection con; // create connection object

	SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			if (connection_bin_rw == "1")
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "B24_Tandem_CC";
			}
			else
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "Visa_Eps_CC";
			}
		

			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( connection_status, cmd.Field("Status_Connection").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
			else
				connection_status_rw = connection_status;
			//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error Connection_Status #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();

		//////////////////////////////////////////////////////////////////////////////////////
		
	//cout << "Valor de connection_status_rw > " << connection_status_rw << endl;
	if(connection_status_rw == "Connected")
	{
	
	}
	else
	{
		salida_result = 0;
		salida = 5;
	}



/*
    if ( salida_result == 1)
	{

	
		RWCTokenizer next(track_2);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
	////////////////////////////Verificar sql////////////////////////////

		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

		//cout << "Valor de varios elementos > " << card_acceptor_id_code << " " 
		//	<< pan_number << " " << card_acceptor_terminal_id << endl;
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"fr2436",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC pro_verify_parameter  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			//cout << "valor de card_acceptor_id_code > " << card_acceptor_id_code << endl;
		//	cout << "valor de pan_number > " << pan_number << endl;
		//	cout << "valor de card_acceptor_terminal_id > " << card_acceptor_terminal_id << endl;
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
				strcpy ( maximo, cmd.Field("Maximo").asString());
			}
		
			maximo_pre = maximo ;
			size_t cantidad_ceros = 12-maximo_pre.length();
			maximo_pre.prepend(pre_zero , cantidad_ceros);
		//	cout << "Valor de resultado > " << resultado << endl;

			resultado_rw = resultado;
		
			if(resultado_rw == "1")
			{
				salida = 1;	
			}
			else
			if(resultado_rw > "1")
			{
				salida = 3;	
			}
			else
			if( (transaction_amount > maximo_pre) && (maximo_pre != "000000000000" ))
			{
				salida = 2;
			}
			else
				salida = -1;
				
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}

			//con.Disconnect();
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error EXEC pro_verify_parameter #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();


		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"sa",   // user name
			"fr2436",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC Pro_verify_Int_Upd  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
				//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error de crear 0210  > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		con.Disconnect();
	
		/////////////////////////////////////////////////////////////////////


	}
	*/


	salida = -1;

	return salida;
}




int VerificarParametros::ResultOfParametrosOnly(RWCString incoming)
{
	
	connection_bin_rw = "1";
	char incoming_field[1024] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int salida_result = 1;
	int salida = 0;
	BOOL flag_salida = TRUE;
/*
	RWCTokenizer next(incoming);
	RWCString token;
	//cout << "Dentro de ITBIS"  << endl;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				salida_result = 0;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			cout << "Dentro de proccessing code"  << endl;
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				//flag_salida = FALSE;
				salida_result = 0;
				//cout << "Valor de salida_result Dentro #1" << salida_result << endl;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				//cout << "Valor de salida_result Dentro #2" << salida_result << endl;
				salida_result = 0;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 


		}
		
		if (count == 3)
		{
			transaction_amount_itbis = token; 

		}

		if (count == 4)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				salida_result = 0;
				break;
			}
			
		}

		if (count == 5)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				salida_result = 0;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}				 
					
		if (count == 6) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
		
		}
	
		if (count == 7)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 

		
		if (count == 8)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				salida_result = 0;
				break;
			}
			

		}				 
		if (count == 9)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}				 
	
		if (count == 10)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				salida_result = 0;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 11)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				salida_result = 0;
				break;
			}

		}		

		if (count == 12)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				salida_result = 0;
				break;
			}


		}		

		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				salida_result = 0;
				break;
			}

		}		
		
		if (count == 14)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				salida_result = 0;
				break;
			}
		}	

		if (count == 15)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				salida_result = 0;
				break;
			}
		}	

		if (count == 16)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				salida_result = 0;
				break;
			}
		}			

	
		if (count == 17)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				salida_result = 0;
				break;
			}
		}
	
		if (count == 18)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				salida_result = 0;
				break;
			}
		}			

		if (count == 19)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				salida_result = 0;
				break;
			}
		}				
		if (count == 20)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				salida_result = 0;
				break;
			}
		}			

		if (count == 21)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				salida_result = 0;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				salida_result = 0;
				break;
			}
	
		}			
	
		if (count == 22)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				salida_result = 0;
				break;
			}
		
		}			
	
		if (count == 23)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 24)
		{
			CVV2 = token; 
			
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			
		}
		
		
		if (count == 25)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				salida_result = 0;
				break;
			}
		
		}			


		if (count == 26)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				salida_result = 0;
				break;
			}
		
		}			

		if (count == 27)
		{
			pos_settlement_data = token;
			
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				salida_result = 0;
				break;
			}
			
		
		}			

		count++;
	}

	*/
	
//	cout << "Valor de salida_result # > " << salida_result << endl;
	SAConnection con; // create connection object

	SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			if (connection_bin_rw == "1")
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "B24_Tandem_CC";
			}
			else
			{
				cmd.setCommandText("Select * from Connection_Status where Connection_Host = :Connection_Host");    // command object
				cmd.Param("Connection_Host").setAsString() = "Visa_Eps_CC";
			}
		

			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( connection_status, cmd.Field("Status_Connection").asString());
			}
		
					
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}
			else
				connection_status_rw = connection_status;
			//con.Disconnect();
			
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error Connection_Status #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();

		//////////////////////////////////////////////////////////////////////////////////////
		
	
	if(connection_status_rw == "Connected")
	{
	
	}
	else
	{
		salida_result = 0;
		salida = 5;
	}




    if ( salida_result == 1)
	{

		RWCTokenizer next(track_2);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
	////////////////////////////Verificar sql////////////////////////////

		SAConnection con; // create connection object

		SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

	
		try
		{
   
			
			con.Connect(
			"Btrans_trans",     // database name
			"btrans",   // user name
			"",   // password
			SA_SQLServer_Client);
			
			cmd.setConnection(&con);

			
			cmd.setCommandText("EXEC pro_verify_parameter  :Merchant_Number,:Pan_Number,:Terminal_Number");    // command object
			cmd.Param("Merchant_Number").setAsString() = card_acceptor_id_code;
			cmd.Param("Pan_Number").setAsString() = pan_number;
			cmd.Param("Terminal_Number").setAsString() = card_acceptor_terminal_id;
			
			
			
			cmd.Execute();
			while(cmd.FetchNext())
			{
			 
				strcpy ( resultado, cmd.Field("resultado").asString());
				strcpy ( maximo, cmd.Field("Maximo").asString());
			}
		
			maximo_pre = maximo ;
			size_t cantidad_ceros = 12-maximo_pre.length();
			maximo_pre.prepend(pre_zero , cantidad_ceros);
	
			resultado_rw = resultado;
		
		
			if(resultado_rw > "1")
			{
				salida = 3;	
			}
			else
			if( (transaction_amount > maximo_pre) && (maximo_pre != "000000000000" ))
			{
				salida = 2;
			}
			else
				salida = -1;
				
			if (cmd.RowsAffected() == 0)
			{
					
				RWCString no_in_DB = "Not in DB >>> ";
				printf("Rows afected: %d\n", cmd.RowsAffected());
			}

			//con.Disconnect();
		}
		catch(SAException &x)
		{
			 // SAConnection::Rollback()
			// can also throw an exception
			// (if a network error for example),
			 // we will be ready
			
			try
			{
				// on error rollback changes
				con.Rollback();
			}
			catch(SAException &)
			{
			
			}
				
			cout << "Dentro de error EXEC pro_verify_parameter #2 > " << endl;
			printf("%s\n", (const char*)x.ErrText());
		}

		//con.Disconnect();
	}
	//else
	//{
	//	salida = 0;
	//}



	return salida;
}


BOOL VerificarParametros::setIso8583B240210( ) 
{
	
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	BOOL flag_salida = TRUE;
	message_type = "0210"; 
	processing_code="000000";
	transaction_amount = "000000000000";
	transmition_date_time = "0000000000";
	system_trace = "051767";
	time_local_transaction = "000000";
	date_local_transaction = "0000";
	expiration_date = "0000"; 
	capture_date = "0000"; 
	merchant_type = "5812"; 
	pos_entry_mode = "901"; 
	pos_condition_code = "00"; 
	acquiring_institution_id_code = "000077185"; 
	track_2 = "0000000000000000=00000000000000000000"; 
	retrieval_reference_number = "000000000000"; 
	card_acceptor_terminal_id = "239387912393    "; 
    card_acceptor_id_code     = "346003538      ";
    card_acceptor_name_location ="                                        "; 
	pos_retailer_data = "111111111111111111122223333"; 
	currency_code_transaction = "214"; 
	pin_data = "D3CED104F9235D44"; 
	pos_terminal_data = "TERMPR04TES40000"; 
	pos_issuer_data = "1111222200000000000"; 
	CVV2 = "& 0000300045!";
	pos_terminal_address_branch = "CCN                          "; 

	pos_invoice_data = "          9397910019"; 
    pos_settlement_data = "RECVQVISA   "; 




	return	flag_salida ;
		
}
//This funtion is for create a message for B24
BOOL VerificarParametros::setIso8583B24( ) 
{
	
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	BOOL flag_salida = TRUE;
	message_type = "0200"; 
	processing_code="000000";
	transaction_amount = "000000000000";
	transmition_date_time = "0000000000";
	system_trace = "051767";
	time_local_transaction = "000000";
	date_local_transaction = "0000";
	expiration_date = "0000"; 
	capture_date = "0000"; 
	merchant_type = "5812"; 
	pos_entry_mode = "901"; 
	pos_condition_code = "00"; 
	acquiring_institution_id_code = "000077185"; 
	track_2 = "0000000000000000=00000000000000000000"; 
	retrieval_reference_number = "000000000000"; 
	card_acceptor_terminal_id = "239387912393    "; 
    card_acceptor_id_code     = "346003538      ";
    card_acceptor_name_location ="                                        "; 
	pos_retailer_data = "111111111111111111122223333"; 
	currency_code_transaction = "214"; 
	pin_data = "D3CED104F9235D44"; 
	pos_terminal_data = "TERMPR04TES40000"; 
	pos_issuer_data = "1111222200000000000"; 
	CVV2 = "& 0000300045!";
	pos_terminal_address_branch = "CCN                          "; 

	pos_invoice_data = "          9397910019"; 
    pos_settlement_data = "RECVQVISA   "; 




	return	flag_salida ;
		
}



BOOL VerificarParametros::VerifyFieldBeginOfText(RWCString incomingS)
{

  if(incomingS.first('\x02') == RW_NPOS )
  {
	 cout << "No tiene caracter de comienzo de mensaje 02 HEX >" << endl;
	  return TRUE;
	  
  }
  else
  return FALSE;


}

BOOL VerificarParametros::VerifyFieldEndOfText(RWCString incomingS)
{

  if(incomingS.first('\x03') == RW_NPOS )
  {
	  cout << "No tiene caracter de fin de mensaje 03 HEX >" << endl;
	  return TRUE;
  }
  else

	  return FALSE;


}

int VerificarParametros::SetVisaField(RWCString incoming) 
{
	
/*	
	RWTValHashDictionary<RWCString, RWCString>     birthdays(RWCString::hash);

	birthdays.insertKeyAndValue(
	"600353850000",
	"CCN-SN NACIONAL LOPE D V           RD RD"
	);

	 RWCString test_input = "111160035385000099999";

	birthdays.insertKeyAndValue("Ivan", "6666666666");

	// Alternative syntax:
	 birthdays["Susan"] = "4444444444";
	birthdays["Gene"] = "55555555555";

	// Print a birthday:
	if( birthdays.contains(test_input(4,12)))
		cout << birthdays[test_input(4,12)] << endl;
 
*/
	
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	int output = 1;
	BOOL flag_salida = TRUE;
	
	
	begin_of_text	=  incoming(0,1);
    msg_type_visa	=  incoming(1,2);
	acquirer_bin	=  incoming(4,6);	
	merchant_number =  incoming(10,12);	 
	terminal_id_1   =  incoming(22,8);
	category_code	=  incoming(30,4);
	country_code	=  incoming(34,3);
	city_code		=  incoming(37,5); 
	timing_zone		=  incoming(42,3); 
	auth_trans_code	=  incoming(45,2);
	terminal_id_2	=  incoming(47,8);
	trans_seq_number=  incoming(56,4); 
	
	
	RWCTokenizer next(incoming);
	
	
	RWCString token;
	
	while(1)
	{	
		VerificarParametros verificacion_mensaje;

		if(verificacion_mensaje.VerifyFieldBeginOfText(incoming) == TRUE)
		{
		
			output = 0;
			break;
		}
		if(verificacion_mensaje.VerifyFieldEndOfText(incoming) == TRUE)
		{
		
			output = 0;
			break;
		}
		else
			end_of_text = '\x03';
			
		strcpy(incoming_field,acquirer_bin);
		
		if ( (VerifyNumericField(incoming_field, 6,
				RWCString("acquirer_bin"))) == 0)
		{
			output = 0;
			break;
		}

		strcpy(incoming_field,merchant_number);
		if ( (VerifyNumericField(incoming_field,12 ,
			RWCString("merchant_number"))) == 0)
		{
				output = 0;
			break;
		}
						
		strcpy(incoming_field,terminal_id_1);
		if ( (VerifyNumericField(incoming_field,8 ,
			RWCString("terminal_id_1"))) == 0)
		{
				output = 0;
			break;
		}
	
					
		strcpy(incoming_field,category_code);
		if ( (VerifyNumericField(incoming_field,4 ,
			RWCString("category_code"))) == 0)
		{
				output = 0;
			break;
		}
		
		strcpy(incoming_field,country_code);
		if ( (VerifyNumericField(incoming_field,3 ,
			RWCString("country_code"))) == 0)
		{
				output = 0;
			break;
		}
			
		strcpy(incoming_field,	city_code);
		if ( (VerifyNumericField(incoming_field,5 ,
			RWCString("	city_code"))) == 0)
		{
				output = 0;
			break;
		}
			
		strcpy(incoming_field,timing_zone);
		if ( (VerifyNumericField(incoming_field,3 ,
			RWCString("timing_zone"))) == 0)
		{
				output = 0;
			break;
		}
				
		strcpy(incoming_field,auth_trans_code);
		if ( (VerifyNumericField(incoming_field,2 ,
			RWCString("auth_trans_code"))) == 0)
		{
				output = 0;
			break;
		}

		strcpy(incoming_field,terminal_id_2);
		if ( (VerifyNumericField(incoming_field,8 ,
			RWCString("pos_entry_mode"))) == 0)
		{
			output = 0;
			break;
		}

		strcpy(incoming_field,trans_seq_number);
		if ( (VerifyNumericField(incoming_field,4 ,
			RWCString("trans_seq_number"))) == 0)
		{
				output = 0;
			break;
		}

/*
		 if( merchant_list.contains(merchant_number))
		 {
			cout << merchant_list[merchant_number] << endl;
		    card_acceptor_name_location = merchant_list[merchant_number];
		 }

*/


		int longitud_incoming = 0;
		int longitud_diferencia = 0;
		longitud_incoming = incoming.length();
			
		RWCString informacion_restante = incoming(62,(longitud_incoming-62)) ;
			
		longitud_diferencia = informacion_restante.length();

		track2_from_visa_msg = 	informacion_restante(0,(longitud_diferencia-12)) ;
		amount_from_visa_msg =  informacion_restante( ((informacion_restante(0,(longitud_diferencia-12)).length() )+2) ,7 );
		//end_of_text			 =  informacion_restante( ((informacion_restante(0,(longitud_diferencia-12)).length() )+10) ,1 );
		system_trace = "00"+trans_seq_number;
		acquiring_institution_id_code = "000"+acquirer_bin;     //F32
		track_2                       = track2_from_visa_msg;
		merchant_type = category_code;

		/////////////////////////////////////////////////////////////////
		/*En esta parte se extrae el Track2 y el amount*/
		
		RWCTokenizer next1(informacion_restante);
		RWCString token1;
		char primera_parte[100]	 = {""};
		char segunda_parte[100]	= {""};
		int counter1 = 0;
		RWCString caracter_delimitador = '\x1C';
		while(!(token1=next1(caracter_delimitador)).isNull())
		{
	
		
			if (counter1 == 0)
			{
		
		
				strcpy(primera_parte , ((LPCTSTR) (RWCString)token1));

			}
		
			if (counter1 == 1)
			{
		
		
				strcpy(segunda_parte, ((LPCTSTR) (RWCString)token1));

			}		
	
			counter1 ++;
		}
		
		//cout << "Valor de primera parte > " << primera_parte << endl;
		//cout << "Valor de segunda parte > " << segunda_parte << endl;

		track_2 = primera_parte;
		/*En esta parte el amount extraido se le pone tantos ceros al frente 
		  hasta llegar a 12*/

		RWCString test_amount;	
		char pre_amount = '\x30';

		test_amount = segunda_parte ;
		size_t test1 = 12-test_amount.length();
		test_amount.prepend(pre_amount , test1);

		transaction_amount = test_amount;

		//////////////////////////////////////////////////////////////////
		/*En esta parte se saca el PAN del resto del TRACK*/

	
		if(!informacion_restante.contains("="))
		{
			cout << "El Track2 no tiene el delimitador de signo de =  > " << endl;
			cout << "Transaccion abortada ............................> " << endl;
			cout << endl;
			output = 0;
			break;
		}



		RWCTokenizer next(primera_parte);
		RWCString token;
		char pan_number[100]	 = {""};
		char resto_track2[100]	= {""};
		int counter = 0;
		RWCString valor_exdate_from_track2;
		while(!(token=next("=")).isNull())
		{
	
		
			if (counter == 0)
			{
		
		
				strcpy(pan_number , ((LPCTSTR) (RWCString)token));

			}
		
			if (counter == 1)
			{
		
		
				strcpy(resto_track2, ((LPCTSTR) (RWCString)token));

			}		
	
			counter ++;
		}
		
		
		valor_exdate_from_track2 = resto_track2;
		expiration_date = valor_exdate_from_track2(0,4);

		card_acceptor_terminal_id	  = terminal_id_1+"0000"+"    "; //F41


		strcpy(incoming_field,transaction_amount);
		if ( (VerifyNumericField(incoming_field,transaction_amount.length() ,
			RWCString("amount_from_visa_msg"))) == 0)
		{
				output = 0;
			break;
		}

		cout << "<field id=*STX..............* value=<"  << begin_of_text			<< ">" << endl;
		cout << "<field id=*Message Delimiter* value=<"  << msg_type_visa			<< ">" << endl;
		cout << "<field id=*Acquirer Bin.....* value=<"  << acquirer_bin			<< ">" << endl;
		cout << "<field id=*Merchant Number..* value=<"  << merchant_number			<< ">" << endl;  
		cout << "<field id=*Terminal ID......* value=<"  << terminal_id_1			<< ">" << endl; 
		cout << "<field id=*Category Code....* value=<"  << category_code			<< ">" << endl; 
		cout << "<field id=*Country Code.....* value=<"  << country_code			<< ">" << endl;
		cout << "<field id=*City Code........* value=<"  << city_code				<< ">" << endl; 
		cout << "<field id=*Timing Zone......* value=<"  << timing_zone				<< ">" << endl; 
		cout << "<field id=*Auth. Trans Code.* value=<"  << auth_trans_code			<< ">" << endl; 
		cout << "<field id=*Terminal ID......* value=<"  << terminal_id_2			<< ">" << endl;
		cout << "<field id=*Trans Seq.Number.* value=<"  << trans_seq_number		<< ">" << endl; 
		cout << "<field id=*Track2...........* value=<"  << primera_parte			<< ">" << endl; 
		cout << "<field id=*Amount...........* value=<"  << segunda_parte		<< ">" << endl; 
		cout << "<field id=*ETX..............* value=<"  << end_of_text				<< ">" << endl; 

		/*En esta parte se le anaden tantos espacios al merchant number hasta 15*/

		RWCString test_pre;	
		char pre_test = '\x20';

		test_pre = merchant_number ;
		size_t test = 15-test_pre.length();
		test_pre.append(pre_test , test);

		card_acceptor_id_code = test_pre;

		break;
		

	

	}
 
	return	output ;
		
}

//This function read the iso-generic message and read each token and put in 
//variable that correspond.

BOOL VerificarParametros::setIsoGeneric( RWCString incoming) 
{
	
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				flag_salida = FALSE;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				flag_salida = FALSE;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 

		}

		if (count == 3)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				break;
			}
			
		}

		if (count == 4)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				flag_salida = FALSE;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				break;
			}
	
		}				 
					
		if (count == 5) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				break;
			}
		
		}
	
		if (count == 6)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				break;
			}
			

		}				 

		
		if (count == 7)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				break;
			}
			

		}				 
		if (count == 8)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				break;
			}

		}				 
	
		if (count == 9)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				break;
			}

		}		
		
		if (count == 10)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				break;
			}

		}		

		if (count == 11)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				break;
			}


		}		

		if (count == 12)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				flag_salida = FALSE;
				break;
			}

		}		
		
		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				flag_salida = FALSE;
				break;
			}
		}	

		if (count == 14)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				flag_salida = FALSE;
				break;
			}
		}	

		if (count == 15)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				flag_salida = FALSE;
				break;
			}
		}			

	
		if (count == 16)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				flag_salida = FALSE;
				break;
			}
		}
	
		if (count == 17)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				flag_salida = FALSE;
				break;
			}
		}			

		if (count == 18)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				flag_salida = FALSE;
				break;
			}
		}				
		if (count == 19)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				flag_salida = FALSE;
				break;
			}
		}			

		if (count == 20)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				break;
			}
	
		}			
	
		if (count == 21)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				flag_salida = FALSE;
				break;
			}
		
		}			
	
		if (count == 22)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				flag_salida = FALSE;
				break;
			}
		
		}			

		if (count == 23)
		{
			CVV2 = token; 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
		}
		
		
		if (count == 24)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				flag_salida = FALSE;
				break;
			}
		
		}			


		if (count == 25)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				flag_salida = FALSE;
				break;
			}
		
		}			

		if (count == 26)
		{
			pos_settlement_data = token; 
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				break;
			}
		
		}			

		count++;
	}
	//cout << "Valor flag_salida > " << flag_salida << endl;
	return	flag_salida ;
		
}

BOOL VerificarParametros::setIsoGeneric0210( RWCString incoming) 
{
	
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				flag_salida = FALSE;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				flag_salida = FALSE;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 

		}

		if (count == 3)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				break;
			}
			
		}

		if (count == 4)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				flag_salida = FALSE;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				break;
			}
	
		}				 
					
		if (count == 5) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				break;
			}
		
		}
	
		if (count == 6)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				break;
			}
			

		}				 

		
		if (count == 7)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				break;
			}
			

		}				 
		if (count == 8)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				break;
			}

		}				 
	
		if (count == 9)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				break;
			}

		}		
		
		if (count == 10)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				break;
			}

		}		

		if (count == 11)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				break;
			}


		}		

		if (count == 12)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				flag_salida = FALSE;
				break;
			}

		}		
		
		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				flag_salida = FALSE;
				break;
			}
		}	

		if (count == 14)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				flag_salida = FALSE;
				break;
			}
		}	

		if (count == 15)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				flag_salida = FALSE;
				break;
			}
		}			

	
		if (count == 16)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				flag_salida = FALSE;
				break;
			}
		}
	
		if (count == 17)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				flag_salida = FALSE;
				break;
			}
		}			

		if (count == 18)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				flag_salida = FALSE;
				break;
			}
		}				
		if (count == 19)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				flag_salida = FALSE;
				break;
			}
		}			

		if (count == 20)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				break;
			}
	
		}			
	
		if (count == 21)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				flag_salida = FALSE;
				break;
			}
		
		}			
	
		if (count == 22)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				flag_salida = FALSE;
				break;
			}
		
		}			

		if (count == 23)
		{
			CVV2 = token; 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
		}
		
		
		if (count == 24)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				flag_salida = FALSE;
				break;
			}
		
		}			


		if (count == 25)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				flag_salida = FALSE;
				break;
			}
		
		}			

		if (count == 26)
		{
			pos_settlement_data = token; 
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				break;
			}
		
		}			

		count++;
	}
	//cout << "Valor flag_salida > " << flag_salida << endl;
	return	flag_salida ;
		
}

BOOL VerificarParametros::setIsoGenericITBIS( RWCString incoming) 
{
	
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				flag_salida = FALSE;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				flag_salida = FALSE;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 

		}

		if (count == 3)
		{
			transaction_amount_itbis = token; 

		}
		if (count == 4)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				break;
			}
			
		}

		if (count == 5)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				flag_salida = FALSE;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				break;
			}
	
		}				 
					
		if (count == 6) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				break;
			}
		
		}
	
		if (count == 7)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				break;
			}
			

		}				 

		
		if (count == 8)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				break;
			}
			

		}				 
		if (count == 9)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				break;
			}

		}				 
	
		if (count == 10)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				break;
			}

		}		
		
		if (count == 11)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				break;
			}

		}		

		if (count == 12)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				break;
			}


		}		

		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				flag_salida = FALSE;
				break;
			}

		}		
		
		if (count == 14)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				flag_salida = FALSE;
				break;
			}
		}	

		if (count == 15)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				flag_salida = FALSE;
				break;
			}
		}	

		if (count == 16)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				flag_salida = FALSE;
				break;
			}
		}			

	
		if (count == 17)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				flag_salida = FALSE;
				break;
			}
		}
	
		if (count == 18)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				flag_salida = FALSE;
				break;
			}
		}			

		if (count == 19)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				flag_salida = FALSE;
				break;
			}
		}				
		if (count == 20)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				flag_salida = FALSE;
				break;
			}
		}			

		if (count == 21)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				break;
			}
	
		}			
	
		if (count == 22)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				flag_salida = FALSE;
				break;
			}
		
		}			
	
		if (count == 23)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				flag_salida = FALSE;
				break;
			}
		
		}			

		if (count == 24)
		{
			CVV2 = token; 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
		}
		
		
		if (count == 25)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				flag_salida = FALSE;
				break;
			}
		
		}			


		if (count == 26)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				flag_salida = FALSE;
				break;
			}
		
		}			

		if (count == 27)
		{
			pos_settlement_data = token; 
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				break;
			}
		
		}			

		count++;
	}
	//cout << "Valor flag_salida > " << flag_salida << endl;
	return	flag_salida ;
		
}

BOOL VerificarParametros::setIsoGenericITBIS0210( RWCString incoming) 
{
	
	char incoming_field[256] = {""};
	RWCString msg_reponse_with_tcp_header = "";
	int count = 0;
	BOOL flag_salida = TRUE;
	RWCTokenizer next(incoming);
	RWCString token;
	while(!(token=next(",")).isNull())
	{	
		if (count == 0)
		{
			message_type = token; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
				
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				flag_salida = FALSE;
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
					RWCString("message_type"))) == 0)
			{
				//flag_salida = FALSE;
				break;
			}

		}
		if (count == 1)
		{
			processing_code= token; 
			int processing_code_length = processing_code.length();
			if( processing_code_length != 6)
			{
				
				MessageErrorLength(RWCString("processing_code"),
					processing_code_length,6);
				flag_salida = FALSE;
				break;
			}
			
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field, 6,
					RWCString("processing_code"))) == 0)
			{
			//	flag_salida = FALSE;
				break;
			}

		}
		
		if (count == 2)
		{
			transaction_amount = token; 

		}

		if (count == 3)
		{
			transaction_amount_itbis = token; 

		}
		if (count == 4)
		{
			transmition_date_time = token; 
			int transmition_date_time_length = transmition_date_time.length();
			if( transmition_date_time_length != 10)
			{
				MessageErrorLength(RWCString("transmition_date_time"),
					transmition_date_time_length,10);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,transmition_date_time);
		
			if ( (VerifyNumericField(incoming_field,10 ,
					RWCString("transmition_date_time"))) == 0)
			{
				break;
			}
			
		}

		if (count == 5)
		{
		
			system_trace = token; 
			int system_trace_length = system_trace.length();
			if( system_trace_length != 6)
			{
				MessageErrorLength(RWCString("system_trace"),
					system_trace_length,6);
				flag_salida = FALSE;
				break;
			}
		
			strcpy(incoming_field,system_trace);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("system_trace"))) == 0)
			{
				break;
			}
	
		}				 
					
		if (count == 6) 
		{				
					
			time_local_transaction = token;
			int time_local_transaction_length = time_local_transaction.length();
			if( time_local_transaction_length != 6)
			{
				MessageErrorLength(RWCString("time_local_transaction"),
					time_local_transaction_length,6);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,time_local_transaction);
			if ( (VerifyNumericField(incoming_field,6 ,
					RWCString("time_local_transaction"))) == 0)
			{
				break;
			}
		
		}
	
		if (count == 7)
		{
				
			date_local_transaction = token; 
			int date_local_transaction_length = date_local_transaction.length();
			if( date_local_transaction_length != 4)
			{
				MessageErrorLength(RWCString("date_local_transaction"),
				date_local_transaction_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,date_local_transaction);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("date_local_transaction"))) == 0)
			{
				break;
			}
			

		}				 

		
		if (count == 8)
		{
				
			expiration_date = token; 
			int expiration_date_length = expiration_date.length();
			if( expiration_date_length != 4)
			{
				MessageErrorLength(RWCString("expiration_date"),
				expiration_date_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,expiration_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("expiration_date"))) == 0)
			{
				break;
			}
			

		}				 
		if (count == 9)
		{
				
			capture_date = token; 
			int capture_date_length = capture_date.length();
			if( capture_date_length != 4)
			{
				MessageErrorLength(RWCString("capture_date"),
				capture_date_length,4);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,capture_date);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("capture_date"))) == 0)
			{
				break;
			}

		}				 
	
		if (count == 10)
		{
				
			merchant_type = token; 
			int merchant_type_length = merchant_type.length();
			if( merchant_type_length != 4)
			{
				MessageErrorLength(RWCString("merchant_type"),
				merchant_type_length,4);
				flag_salida = FALSE;
				break;
			}

			strcpy(incoming_field,merchant_type);
			if ( (VerifyNumericField(incoming_field,4 ,
					RWCString("merchant_type"))) == 0)
			{
				break;
			}

		}		
		
		if (count == 11)
		{
				
			pos_entry_mode = token; 
			int pos_entry_mode_length = pos_entry_mode.length();
			if( pos_entry_mode_length != 3)
			{
				MessageErrorLength(RWCString("pos_entry_mode"),
				pos_entry_mode_length,3);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pos_entry_mode);
			if ( (VerifyNumericField(incoming_field,3 ,
					RWCString("pos_entry_mode"))) == 0)
			{
				break;
			}

		}		

		if (count == 12)
		{
			pos_condition_code = token; 
			int pos_condition_code_length = pos_condition_code.length();
			if( pos_condition_code_length != 2)
			{
				MessageErrorLength(RWCString("pos_condition_code"),
				pos_condition_code_length,2);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pos_condition_code);
			if ( (VerifyNumericField(incoming_field,2 ,
					RWCString("pos_condition_code"))) == 0)
			{
				break;
			}


		}		

		if (count == 13)
		{
			
			//Este campo es variable y debe ser de 9 y delante del campo debe ir un 09
			//RWCString length_fiel_032 = "09"
			acquiring_institution_id_code = token; 
			
			int acquiring_institution_id_code_length = acquiring_institution_id_code.length();
			if( acquiring_institution_id_code_length != 9)
			{
				MessageErrorLength(RWCString("acquiring_institution_id_code"),
				acquiring_institution_id_code_length,9);
				flag_salida = FALSE;
				break;
			}

		}		
		
		if (count == 14)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			track_2 = token; 
			int track_2_length = track_2.length();
			if( track_2_length > 37)
			{
				MessageErrorLength(RWCString("track_2"),
				track_2_length,37);
				flag_salida = FALSE;
				break;
			}
		}	

		if (count == 15)
		{
			retrieval_reference_number = token; 
			int retrieval_reference_number_length = retrieval_reference_number.length();
			if( retrieval_reference_number_length != 12)
			{
				MessageErrorLength(RWCString("retrieval_reference_number"),
				retrieval_reference_number_length,12);
				flag_salida = FALSE;
				break;
			}
		}	

		if (count == 16)
		{
			card_acceptor_terminal_id = token; 
			int card_acceptor_terminal_id_length = card_acceptor_terminal_id.length();
			if( card_acceptor_terminal_id_length != 16)
			{
				MessageErrorLength(RWCString("card_acceptor_terminal_id"),
				card_acceptor_terminal_id_length,16);
				flag_salida = FALSE;
				break;
			}
		}			

	
		if (count == 17)
		{
			card_acceptor_id_code = token; 
			int card_acceptor_id_code_length = card_acceptor_id_code.length();
			if( card_acceptor_id_code_length != 15)
			{
				MessageErrorLength(RWCString("card_acceptor_id_code"),
				card_acceptor_id_code_length,15);
				flag_salida = FALSE;
				break;
			}
		}
	
		if (count == 18)
		{
			card_acceptor_name_location = token; 
			int card_acceptor_name_location_length = card_acceptor_name_location.length();
			if( card_acceptor_name_location_length != 40)
			{
				MessageErrorLength(RWCString("card_acceptor_name_location"),
				card_acceptor_name_location_length,40);
				flag_salida = FALSE;
				break;
			}
		}			

		if (count == 19)
		{
			pos_retailer_data = token; 
			int pos_retailer_data_length = pos_retailer_data.length();
			if( pos_retailer_data_length != 27)
			{
				MessageErrorLength(RWCString("pos_retailer_data"),
				pos_retailer_data_length,27);
				flag_salida = FALSE;
				break;
			}
		}				
		if (count == 20)
		{
			currency_code_transaction = token; 
			int currency_code_transaction_length = currency_code_transaction.length();
			if( currency_code_transaction_length != 3)
			{
				MessageErrorLength(RWCString("currency_code_transaction"),
				currency_code_transaction_length,3);
				flag_salida = FALSE;
				break;
			}
		}			

		if (count == 21)
		{
			pin_data = token; 
			int pin_data_length = pin_data.length();
			if( pin_data_length != 16)
			{
				MessageErrorLength(RWCString("pin_data"),
				pin_data_length,16);
				flag_salida = FALSE;
				break;
			}
			strcpy(incoming_field,pin_data);
			if ( (VerifyHexField(incoming_field,16 ,
					RWCString("pin_data"))) == 0)
			{
				break;
			}
	
		}			
	
		if (count == 22)
		{
			pos_terminal_data = token; 
			int pos_terminal_data_length = pos_terminal_data.length();
			if( pos_terminal_data_length != 16)
			{
				MessageErrorLength(RWCString("pos_terminal_data"),
				pos_terminal_data_length,16);
				flag_salida = FALSE;
				break;
			}
		
		}			
	
		if (count == 23)
		{
			pos_issuer_data = token; 
			int pos_issuer_data_length = pos_issuer_data.length();
			if( pos_issuer_data_length != 19)
			{
				MessageErrorLength(RWCString("pos_issuer_data"),
				pos_issuer_data_length,19);
				flag_salida = FALSE;
				break;
			}
		
		}			

		if (count == 24)
		{
			CVV2 = token; 
			/*
			int CVV2_length = CVV2.length();
			if( CVV2_length != 45)
			{
				MessageErrorLength(RWCString("CVV2"),
				CVV2_length,15);
				flag_salida = FALSE;
				break;
			}
			*/
		}
		
		
		if (count == 25)
		{
			pos_terminal_address_branch = token; 
			int pos_terminal_address_branch_length = pos_terminal_address_branch.length();
			if( pos_terminal_address_branch_length != 29)
			{
				MessageErrorLength(RWCString("pos_terminal_address_branch"),
				pos_terminal_address_branch_length,29);
				flag_salida = FALSE;
				break;
			}
		
		}			


		if (count == 26)
		{
			pos_invoice_data = token; 
			int pos_invoice_data_length = pos_invoice_data.length();
			if( pos_invoice_data_length != 20)
			{
				MessageErrorLength(RWCString("pos_invoice_data"),
				pos_invoice_data_length,20);
				flag_salida = FALSE;
				break;
			}
		
		}			

		if (count == 27)
		{
			pos_settlement_data = token; 
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
				pos_settlement_data_length,12);
				break;
			}
		
		}			

		count++;
	}
	//cout << "Valor flag_salida > " << flag_salida << endl;
	return	flag_salida ;
		
}

RWCString VerificarParametros::SetField( int input_field ,RWCString field_value) 
{
	char incoming_field[256] = {""};
	
	RWCString msg_reponse_with_tcp_header = "";
	

	while(1)
	{
	
		if (input_field == 0)
		{
			message_type = field_value; 
			int message_type_length = message_type.length();
			if( message_type_length != 4)
			{
					
				MessageErrorLength(RWCString("message_type"),
					message_type_length,4);
				break;
			}
			
			strcpy(incoming_field,message_type);
		
			if ( (VerifyNumericField(incoming_field, 4,
				RWCString("message_type"))) == 0)
			{
				break;
			}
	
		}
		if (input_field == 3)
		{
			processing_code = field_value; 
			int processing_code_length_length = processing_code.length();
			if( processing_code_length_length != 6)
			{
			
				MessageErrorLength(RWCString("processing_code"),
				processing_code_length_length,6);
				break;
			}
		
			strcpy(incoming_field,processing_code);
		
			if ( (VerifyNumericField(incoming_field,6 ,
				RWCString("processing_code"))) == 0)
			{
				break;
			}
		
		}
		
		if (input_field == 4)
		{
			transaction_amount = field_value; 
			int transaction_amount_length = transaction_amount.length();
			if( transaction_amount_length != 12)
			{
				MessageErrorLength(RWCString("transaction_amount"),
					transaction_amount_length,12);
				break;
			}
	
			strcpy(incoming_field,transaction_amount);
	
			if ( (VerifyNumericField(incoming_field,12 ,
					RWCString("transaction_amount"))) == 0)
			{
				break;
			}
		
		}

		if (input_field == 125)
		{
		
			pos_settlement_data = field_value; 
			int pos_settlement_data_length = pos_settlement_data.length();
			if( pos_settlement_data_length != 12)
			{
				MessageErrorLength(RWCString("pos_settlement_data"),
					pos_settlement_data_length,12);
				break;
			}
	
			//cout << "Valor de pos_settlement_data > " << pos_settlement_data << endl;
		
		}
	
		break;
	}

	return field_value;
}

//This funtion create the message ISO8583 B24 
RWCString VerificarParametros::setIsoMsg()
{

	complete_iso8583_msg+=message_type;
	complete_iso8583_msg+=bit_map;

	complete_iso8583_msg+=processing_code;
	complete_iso8583_msg+=transaction_amount; 
	complete_iso8583_msg+=transmition_date_time; 
	complete_iso8583_msg+=system_trace;
	complete_iso8583_msg+=time_local_transaction;
	complete_iso8583_msg+=date_local_transaction;
	capture_date = date_local_transaction;
	complete_iso8583_msg+=expiration_date;
	complete_iso8583_msg+=capture_date;
	complete_iso8583_msg+=merchant_type;
	complete_iso8583_msg+=pos_entry_mode;
	complete_iso8583_msg+=pos_condition_code;
	complete_iso8583_msg+=acquiring_institution_id_code;
	complete_iso8583_msg+=track_2;
	complete_iso8583_msg+=retrieval_reference_number;
	complete_iso8583_msg+=card_acceptor_terminal_id;
	complete_iso8583_msg+=card_acceptor_id_code;
	complete_iso8583_msg+=card_acceptor_name_location;
	complete_iso8583_msg+=pos_retailer_data;
	complete_iso8583_msg+=currency_code_transaction;
	complete_iso8583_msg+=pin_data;
	complete_iso8583_msg+=pos_terminal_data;
	complete_iso8583_msg+=pos_issuer_data;
	complete_iso8583_msg+=CVV2;
	complete_iso8583_msg+=pos_terminal_address_branch;
	complete_iso8583_msg+=pos_invoice_data;
	complete_iso8583_msg+=pos_settlement_data;
	complete_iso8583_msg+='\x03';
	return complete_iso8583_msg;

}


RWCString VerificarParametros::setIsoMsg0210()
{

	complete_iso8583_msg+="0210";
	complete_iso8583_msg+=bit_map_itbis_0210;

	complete_iso8583_msg+=processing_code;					//03
	complete_iso8583_msg+=transaction_amount;				//04
	complete_iso8583_msg+=transmition_date_time;			//07 
	complete_iso8583_msg+=system_trace;						//11
	complete_iso8583_msg+=time_local_transaction;			//12
	complete_iso8583_msg+=date_local_transaction;			//13
    capture_date = date_local_transaction;
	complete_iso8583_msg+=expiration_date;					//14
	complete_iso8583_msg+=capture_date;						//15
	complete_iso8583_msg+=capture_date;						//17
	complete_iso8583_msg+=pos_entry_mode;					//22
	complete_iso8583_msg+=pos_condition_code;				//25
	complete_iso8583_msg+=acquiring_institution_id_code;	//32
	complete_iso8583_msg+=track_2;							//35
	complete_iso8583_msg+=retrieval_reference_number;		//37
	complete_iso8583_msg+=autirization_id_response;			//38
	complete_iso8583_msg+=response_code;					//39
	complete_iso8583_msg+=card_acceptor_terminal_id;		//41
	complete_iso8583_msg+=card_acceptor_id_code;			//42
	complete_iso8583_msg+=pos_retailer_data;				//48
	complete_iso8583_msg+=currency_code_transaction;		//49
	complete_iso8583_msg+=pos_terminal_data;				//60
	complete_iso8583_msg+=pos_issuer_data;					//61	
	complete_iso8583_msg+=pos_settlement_data;				//125
	complete_iso8583_msg+='\x03';
	return complete_iso8583_msg;

}
RWCString VerificarParametros::setIsoMsgItbis()
{

	complete_iso8583_msg+=message_type;
	complete_iso8583_msg+=bit_map_itbis;

	complete_iso8583_msg+=processing_code;
	complete_iso8583_msg+=transaction_amount; 
	complete_iso8583_msg+=transaction_amount_itbis; 
	complete_iso8583_msg+=transmition_date_time; 
	complete_iso8583_msg+=system_trace;
	complete_iso8583_msg+=time_local_transaction;
	complete_iso8583_msg+=date_local_transaction;
	capture_date = date_local_transaction;
	complete_iso8583_msg+=expiration_date;
	complete_iso8583_msg+=capture_date;
	complete_iso8583_msg+=merchant_type;
	complete_iso8583_msg+=pos_entry_mode;
	complete_iso8583_msg+=pos_condition_code;
	complete_iso8583_msg+=acquiring_institution_id_code;
	complete_iso8583_msg+=track_2;
	complete_iso8583_msg+=retrieval_reference_number;
	complete_iso8583_msg+=card_acceptor_terminal_id;
	complete_iso8583_msg+=card_acceptor_id_code;
	complete_iso8583_msg+=card_acceptor_name_location;
	complete_iso8583_msg+=pos_retailer_data;
	complete_iso8583_msg+=currency_code_transaction;
	complete_iso8583_msg+=pin_data;
	complete_iso8583_msg+=pos_terminal_data;
	complete_iso8583_msg+=pos_issuer_data;
	complete_iso8583_msg+=CVV2;
	complete_iso8583_msg+=pos_terminal_address_branch;
	complete_iso8583_msg+=pos_invoice_data;
	complete_iso8583_msg+=pos_settlement_data;
	complete_iso8583_msg+='\x03';
	return complete_iso8583_msg;

}



RWCString VerificarParametros::getIsoMsg()
{
				
	return complete_iso8583_msg;
}


RWCString VerificarParametros::getIsoMsgGeneric()
{

   	delimiter_comma = ",";
	complete_iso_msg_generic+=message_type;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=processing_code;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=transaction_amount;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=transmition_date_time;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=system_trace;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=time_local_transaction;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=date_local_transaction;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=expiration_date;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=capture_date;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=merchant_type;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=pos_entry_mode;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=pos_condition_code;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=acquiring_institution_id_code;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=track_2;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=retrieval_reference_number;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=card_acceptor_terminal_id;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=card_acceptor_id_code;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=card_acceptor_name_location;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=pos_retailer_data;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=currency_code_transaction;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=pin_data;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=pos_terminal_data;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=pos_issuer_data;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=pos_terminal_address_branch;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=pos_invoice_data;
	complete_iso_msg_generic+=delimiter_comma;
	complete_iso_msg_generic+=pos_settlement_data;
	complete_iso_msg_generic+=delimiter_comma;
	switch_key=date_local_transaction+":"+time_local_transaction+":"+message_type+":"+retrieval_reference_number;
	complete_iso_msg_generic+=switch_key;
	
	//original_data_elements="0200"+retrieval_reference_number+date_local_transaction+
	//						time_local_transaction+"00"+capture_date+"0000000000";
	//complete_iso_msg_generic+=delimiter_comma;
	//complete_iso_msg_generic+=original_data_elements;
	
	return complete_iso_msg_generic;
}

RWCString VerificarParametros::SetB24Header0200Pos( RWCString incoming_header ) 
{
	RWCString header_base24_0200= incoming_header;
	header_base24_0200+=complete_iso8583_msg;
	return complete_iso8583_msg = header_base24_0200;				
}

void VerificarParametros::MessageErrorLength(RWCString incoming_name, int wrong_field_length, 
						int correct_field_length) 
{

	cout << "El largo de " <<  incoming_name << " es incorrecto > " 
	     << " es de " << wrong_field_length <<" y debe ser "
		 << correct_field_length << endl;
		 cout << "***********Transaccion abortada********** > " << endl;

}

int VerificarParametros::VerifyNumericField(char *incoming_field, const int length_field, 
					   RWCString validated_field)
{
	int i = 0;
	int flag = 1;
	char *test_isdigit = {""};
	for (i = 0 ; i < length_field;i++)
	{
		if(!isdigit(incoming_field[i]))
		{
			cout << "<********Este campo >" << validated_field << "< no es numerico*******>" << endl;
			flag =0;
		}
	
	}
	
	  return flag;

}

int VerificarParametros::VerifyHexField(char *incoming, const int length_field,RWCString validated_field)
{

	int i = 0;
	int flag = 1;
	char *test_isdigit = {""};
	for (i = 0 ; i < length_field;i++)
	{
		if(!isxdigit(incoming[i]))
		{
			cout << "<********Este campo >" << validated_field << "< no es Hexadecimal*******> " << endl;
			flag =0;
		}
	}
 
	  return flag;

}




RWCString VerificarParametros::SetMsgField( int input_field ) 
{

	char buffer[20];
 	RWCString msg_reponse_with_tcp_header = "";
	while(1)
	{
	
		if (input_field == 7)
		{
		
			RWDate d;

			RWTime t;   // Current time
			transmition_date_time = "";
			char buffer[20];
		 	int month_of_year  = d.month();
			int day_of_month   = d.dayOfMonth();
			int hour_of_day    = t.hourGMT(); 
			int minute_of_hour = t.minuteGMT();
			int second_of_hour = t.second(); 

			_itoa( month_of_year, buffer, 10 );
			if(month_of_year < 10)
			transmition_date_time+="0";
			transmition_date_time+=buffer;

			_itoa( day_of_month, buffer, 10 );
			if(day_of_month < 10)
			transmition_date_time+="0";
			transmition_date_time+=buffer;

			_itoa( hour_of_day, buffer, 10 );
			if(hour_of_day < 10)
			transmition_date_time+="0"; 
			transmition_date_time+=buffer;
  
			_itoa( minute_of_hour, buffer, 10 );
			if( minute_of_hour < 10)
			transmition_date_time+="0"; 
			transmition_date_time+=buffer;
  
			_itoa( second_of_hour, buffer, 10 );
			if( second_of_hour < 10)
			transmition_date_time+="0"; 
			transmition_date_time+=buffer;


		}		

		if (input_field == 10)
		{
		
			convertion_rate = "214";


		}		
		
		if (input_field == 12)
		{
		
			RWTime t;   // Current time
			time_local_transaction = "";
			char buffer[20];
			int hour_of_day    = t.hourGMT(); 
			int minute_of_hour = t.minuteGMT();
			int second_of_hour = t.second(); 

			_itoa( hour_of_day, buffer, 10 );
			if(hour_of_day < 10)
			time_local_transaction+="0"; 
			time_local_transaction+=buffer;
  
			_itoa( minute_of_hour, buffer, 10 );
			if( minute_of_hour < 10)
			time_local_transaction+="0"; 
			time_local_transaction+=buffer;
  
			_itoa( second_of_hour, buffer, 10 );
			if( second_of_hour < 10)
			time_local_transaction+="0"; 
			time_local_transaction+=buffer;


		}		

		if (input_field == 13)
		{
		
			RWDate d;
			date_local_transaction = "";
			char buffer[20];
		 	int month_of_year  = d.month();
			int day_of_month   = d.dayOfMonth();

			_itoa( month_of_year, buffer, 10 );
			if(month_of_year < 10)
			date_local_transaction+="0";
			date_local_transaction+=buffer;

			_itoa( day_of_month, buffer, 10 );
			if(day_of_month < 10)
			date_local_transaction+="0";
			date_local_transaction+=buffer;


		}		
		if (input_field == 24)
		{
		
			for_athd = "ATHD";


		}		


		if (input_field == 32)
		{
			//Este campo es el no debe ser mayor de 11 y para B24 debe ser minimo 09
			int input_field_length = acquiring_institution_id_code.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			acquiring_institution_id_code = cero_field + acquiring_institution_id_code;
							
		}		
		
		if (input_field == 35)
		{
			//Este campo no debe ser mayor de 37
			int input_field_length = track_2.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = RWCString(buffer) ;
			track_2 = cero_field + track_2;
		
		}	

		if (input_field == 37)
		{
		    
			 struct _timeb tstruct;
  
			 _ftime( &tstruct );
			 cout << endl;
			int test_time = tstruct.millitm;
			RWCString re_test = "";
			char buffer_mil[20] = {""};
					
			_itoa( test_time, buffer_mil, 10 );
		  	srand( (unsigned)time( NULL ));
			char buffer1[20];
				char buffer2[20];
				char buffer3[20];
				char buffer4[20];
				int valor1 = unsigned(rand());
				int valor2 = unsigned(rand());
				int valor3 = unsigned(rand());
				int valor4 = unsigned(rand());
			
				_itoa( valor1, buffer1, 10 );
				_itoa( valor2, buffer2, 10 );
				_itoa( valor3, buffer3, 10 );
				_itoa( valor4, buffer4, 10 );

				RWCString primero = RWCString(buffer1);
				RWCString segundo = RWCString(buffer2);
				RWCString tercero = RWCString(buffer3);
				RWCString cuarto  = RWCString(buffer4);

				if( ((primero+segundo+tercero).length()) >=12)
				{
					retrieval_reference_number = ((primero+segundo+tercero)(((primero+segundo+tercero).length()-12),12));
				}
				else
				if( ((primero+segundo+tercero).length()) == 11)
				{
					retrieval_reference_number = "1"+primero+segundo+tercero;
				}
				else
				if( ((primero+segundo+tercero).length()) == 10)
				{
					retrieval_reference_number = "13"+primero+segundo+tercero;
				}
		
						
			//	cout << endl;
			//	cout << "valor de retrieval_reference_number > " << retrieval_reference_number << endl;
			  //  cout << endl;
				re_test = retrieval_reference_number;
				int len_buffer_mil = RWCString(buffer_mil).length();
					
				re_test+=buffer_mil;

				//cout << re_test(len_buffer_mil,12) << endl;
				//cout << re_test(len_buffer_mil,12).length() << endl;
				retrieval_reference_number=re_test(len_buffer_mil,12);
		}


		if (input_field == 42)
		{
			//char add_space[4] = "   ";
			RWCString add_space = card_acceptor_id_code+"   ";
			card_acceptor_id_code=add_space; 
		}			

		if (input_field == 48)
		{
			//Este campo no debe ser mayor de 30 y para B24 debe ser 27
			int input_field_length = pos_retailer_data.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			pos_retailer_data = cero_field + pos_retailer_data;
	
		}			
		
		if (input_field == 60)
		{
			//Este campo no debe ser mayor de 19
			int input_field_length = pos_terminal_data.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			pos_terminal_data = cero_field + pos_terminal_data;
		
		}			
			
		if (input_field == 61)
		{
			//Este campo no debe ser mayor de 22
			int input_field_length = pos_issuer_data.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			pos_issuer_data = cero_field + pos_issuer_data;
	
		}			
	
		if (input_field == 63)
		{
			//Este campo no debe ser mayor de 22
			int input_field_length = CVV2.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			CVV2 = cero_field + CVV2;
	
		}			
	
	
	
		if (input_field == 120)
		{
			//Este campo no debe ser mayor de 32
			int input_field_length = pos_terminal_address_branch.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			pos_terminal_address_branch = cero_field + pos_terminal_address_branch;
	
		
		}			

		if (input_field == 123)
		{
//				cout << "Valor de pos_invoice_data > " << pos_invoice_data << endl;
			//Este campo no debe ser mayor de 23
			int input_field_length = pos_invoice_data.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			pos_invoice_data = cero_field + pos_invoice_data;
	
		}			

		if (input_field == 125)
		{
	
			//	cout << "Valor de pos_settlement_data > " << pos_settlement_data << endl;
			
			//Este campo no debe ser mayor de 15
			int input_field_length = pos_settlement_data.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			pos_settlement_data = cero_field + pos_settlement_data;
	
			
		}			
	
		break;
	}

	return msg_reponse_with_tcp_header;

}



RWCString VerificarParametros::SetMsgField( int input_field ,RWCString field_value, RWCString pre_field) 
{
	char incoming_field[256] = {""};
	
	RWCString msg_reponse_with_tcp_header = "";
	RWCString msg_field_to_iso = "";
	while(1)
	{
	
		if (input_field == 32)
		{
			//Este campo debe ser no mayor de 11 numerico y para B24 debe
			//ser 09
			acquiring_institution_id_code = pre_field + field_value;
						
		}		
		
		if (input_field == 48)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			
			pos_retailer_data = pre_field + field_value;
		
		}	
		
	
		if (input_field == 60)
		{
			pos_terminal_data = pre_field + field_value;
			
		}			
	
		if (input_field == 61)
		{
			pos_issuer_data = pre_field + field_value;
		
		}			
		
		if (input_field == 63)
		{
			
			CVV2 = pre_field + field_value;
		
		}			

		if (input_field == 120)
		{
			pos_terminal_address_branch = pre_field + field_value;
		
		}			

		
		if (input_field == 123)
		{
			pos_invoice_data = pre_field + field_value;
		}			

		if (input_field == 125)
		{
			pos_settlement_data = pre_field + field_value;
		
		}			
		
		break;
	}

	return msg_reponse_with_tcp_header;

}

RWCString VerificarParametros::SetMsgField( int input_field ,RWCString field_value) 
{
	char incoming_field[256] = {""};
		char buffer[20];
	
	RWCString msg_reponse_with_tcp_header = "";
	RWCString msg_field_to_iso = "";
	while(1)
	{
	
		if (input_field == 32)
		{
			//Este campo debe ser no mayor de 11 numerico y para B24 debe
			//ser 09
			acquiring_institution_id_code =  field_value;
						
		}	
		if (input_field == 39)
		{
			//Este campo debe ser no mayor de 11 numerico y para B24 debe
			//ser 09
			response_code =  field_value;
						
		}	
		
		if (input_field == 43)
		{
			//Este campo debe ser no mayor de 11 numerico y para B24 debe
			//ser 09
			card_acceptor_name_location =  field_value;
						
		}	
		
		
		if (input_field == 48)
		{
			
			//Este campo es variable y debe ser de 37 y delante del campo debe ir un 37
			
			pos_retailer_data =  field_value;
		
		}	
		
	
		if (input_field == 60)
		{
			pos_terminal_data =  field_value;
			
		}			
	
		if (input_field == 61)
		{
			pos_issuer_data = field_value;
		
		}			
		
		if (input_field == 63)
		{
			
			CVV2 =  field_value;
		
		}			

		if (input_field == 120)
		{
			pos_terminal_address_branch = field_value;
		
		}			

		
		if (input_field == 123)
		{
			pos_invoice_data = field_value;
		}			

		if (input_field == 125)
		{
			pos_settlement_data =  field_value;
			int input_field_length = pos_settlement_data.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			pos_settlement_data = cero_field + pos_settlement_data;
	
		
		}			
		
		break;
	}

	return msg_reponse_with_tcp_header;

}
/*
void VerificarParametros::ReturnDumpIsoGeneric( char *msg_type, int debugSB, RWCString peerAddress, int server_port) 
{
	
	RWTime t;   // Current time
	RWTime d(RWTime::beginDST(1990, RWZone::local()));
	cout << endl;
	cout << "["  << t <<   "] -" << " <" << msg_type << ">" << " Message from b-source " 
		<<  "[" << peerAddress << ":" << server_port << "]"   << endl; 

	if( (debugSB == 1) && ( (strncmp(msg_type, "0200", 4) == 0) || ((strncmp(msg_type, "0210", 4) == 0)  ) || ((strncmp(msg_type, "0100", 4) == 0)  )))

	{
	
		cout << endl;
		cout << msg_type << ":" << endl;
		cout << "    <field id=*3* value=<"   << processing_code				<< ">" << endl;  
		cout << "    <field id=*4* value=<"   << transaction_amount				<< ">" << endl; 
		cout << "    <field id=*7* value=<"   << transmition_date_time			<< ">" << endl;
		cout << "    <field id=*11* value=<"  << system_trace					<< ">" << endl; 
		cout << "    <field id=*12* value=<"  << time_local_transaction			<< ">" << endl; 
		cout << "    <field id=*13* value=<"  << date_local_transaction			<< ">" << endl;
		cout << "    <field id=*14* value=<"  << expiration_date				<< ">" << endl;
		cout << "    <field id=*17* value=<"  << capture_date					<< ">" << endl; 
		cout << "    <field id=*18* value=<"  << merchant_type					<< ">" << endl; 
		cout << "    <field id=*22* value=<"  << pos_entry_mode					<< ">" << endl; 
		cout << "    <field id=*25* value=<"  << pos_condition_code				<< ">" << endl; 
		cout << "    <field id=*32* value=<"   << acquiring_institution_id_code	<< ">" << endl;  
		cout << "    <field id=*35* value=<"   << track_2 						<< ">" << endl;  
		cout << "    <field id=*37* value=<"   << retrieval_reference_number 	<< ">" << endl;  
		cout << "    <field id=*41* value=<"   << card_acceptor_terminal_id 	<< ">" << endl;  
		cout << "    <field id=*42* value=<"   << card_acceptor_id_code 	<< ">" << endl;  
		cout << "    <field id=*43* value=<"   << card_acceptor_name_location 	<< ">" << endl;  
		cout << "    <field id=*48* value=<"   << pos_retailer_data 			<< ">" << endl;  
		cout << "    <field id=*49* value=<"   << currency_code_transaction 	<< ">" << endl;  
		cout << "    <field id=*52* value=<"   << pin_data 	<< ">" << endl;  
		cout << "    <field id=*60* value=<"   << pos_terminal_data 		<< ">" << endl;  
        cout << "    <field id=*61* value=<"   << pos_issuer_data 			<< ">" << endl;  
	    cout << "    <field id=*63* value=<"   << CVV2 			<< ">" << endl;  
		
		cout << "    <field id=*120* value=<"   << pos_terminal_address_branch 			<< ">" << endl;  
		cout << "    <field id=*123* value=<"   << pos_invoice_data 			<< ">" << endl;  
		
		cout << "    <field id=*125* value=<"  << pos_settlement_data 	<< ">" << endl;  
		cout << "    <field id=*127.2* value=<"  << switch_key 	<< ">" << endl;  
		
		cout << endl;
	}
	
	
	

}
*/

VerificarParametros::~VerificarParametros()
{

}
