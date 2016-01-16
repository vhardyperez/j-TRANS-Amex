// SqlUtil.h: interface for the SqlUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLUTIL_H__D446B1A8_D89C_4A77_A9CD_75770ADDF2BD__INCLUDED_)
#define AFX_SQLUTIL_H__D446B1A8_D89C_4A77_A9CD_75770ADDF2BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <rw/cstring.h>
#include <rw/rwdate.h>
#include <rw/rwtime.h>
#include <rw/ctoken.h>
#include <rw/thr/thrfunc.h>
#include <rw/toolpro/neterr.h>
#include <rw/tvhdict.h>


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


class SqlUtil  
{
public:
	SqlUtil();
	virtual ~SqlUtil();
		int ResultOfParametros(RWCString incoming);
		BOOL setIsoGeneric( RWCString incoming);
	BOOL setIso8583B24();
	BOOL setIso8583B240210( ) ;
	RWCString setIsoMsg();
	RWCString getIsoMsg();
	RWCString SetB24Header0200Pos(RWCString incoming_header); 
	void MessageErrorLength(RWCString incoming_name, int wrong_field_length, 
	int correct_field_length); 
	int VerifyNumericField(char *incoming_field, const int length_field, 
		RWCString validated_field);
	int VerifyHexField(char *incoming, const int length_field,
		RWCString validated_field);
	RWCString SetField( int input_field ,RWCString field_value); 
	RWCString SetMsgField( int input_field); 
	RWCString SetMsgField( int input_field ,RWCString field_value, RWCString pre_field) ;
	RWCString getIsoMsgGeneric();
	int SetVisaField(RWCString incoming);
	BOOL VerifyFieldBeginOfText(RWCString incomingS);
	BOOL VerifyFieldEndOfText(RWCString incomingS);
	RWCString SetMsgField( int input_field ,RWCString field_value);
	BOOL setIsoGenericITBIS( RWCString incoming) ;
	RWCString setIsoMsgItbis();
	BOOL setIsoGeneric0210( RWCString incoming);
	RWCString setIsoMsg0210();
	BOOL setIsoGenericITBIS0210( RWCString incoming) ;
	
	int ResultOfParametrosITBIS(RWCString incoming);
	int nBaseConvert(
	char    *pcNumberToConvert,
	int     nSourceBase,
	int     nDestinationBase,
	char    *pcResult,
	int     nSeparateOutput,
	int     cSeparationCharacter,
	int     nPadToLeft,
	int     *pnError);
	int GetMesageLength( char *incoming_msg ) ;
	RWCString  RetornoASCII(char  hex_input);
//	void Proccess_Message( RWCString incoming_msg );
	RWCString Proccess_Message_Retorno_Visaf( RWCString incoming_msg,
						char *send_queue_string,char  *sql_queue_string, char *queue_mgr_string);

	
private:
	RWCString complete_visaF_msg;
	RWCString complete_iso8583_msg;
	RWCString complete_iso_msg_generic;
	RWCString delimiter_comma;
	RWCString message_type;
	RWCString bit_map;
	RWCString bit_map_no_63;
	RWCString bit_map_itbis;
	RWCString bit_map_itbis_0210;
	RWCString bit_map_itbis_0210_visaf;
	RWCString processing_code;				/*003  L6  */
	RWCString transaction_amount;			/*004  L12 */ 
	RWCString transaction_amount_itbis;
	RWCString transmition_date_time;		/*007  L10 */ 	
	RWCString convertion_rate;				/*010  L03 */ 	
	RWCString system_trace;
	RWCString time_local_transaction;
	RWCString date_local_transaction;
	RWCString expiration_date;
	RWCString capture_date;
	RWCString date_settlement;
	RWCString merchant_type;
	RWCString pos_entry_mode;
	RWCString for_athd;						/*024  L04 */ 					
	RWCString pos_condition_code;
	RWCString acquiring_institution_id_code;
	RWCString track_2;
	RWCString retrieval_reference_number;
	RWCString autirization_id_response;
	RWCString response_code;
	RWCString card_acceptor_terminal_id;
	RWCString card_acceptor_id_code;
	RWCString card_acceptor_name_location;
	RWCString pos_retailer_data;
	RWCString currency_code_transaction;
	RWCString pin_data;
	RWCString pos_terminal_data;
	RWCString pos_issuer_data;
	RWCString CVV2;
	RWCString original_data_elements;
	RWCString pos_terminal_address_branch;
	RWCString pos_invoice_data;
	RWCString pos_settlement_data;
	RWCString switch_key;
	RWCString begin_of_text;
	RWCString end_of_text;
	RWCString msg_type_visa;
	RWCString acquirer_bin;
	RWCString merchant_number;
	RWCString terminal_id_1	;
	RWCString category_code	;
	RWCString country_code;
	RWCString city_code;
	RWCString timing_zone;
	RWCString auth_trans_code;
	RWCString terminal_id_2;
	RWCString trans_seq_number;
	RWCString track2_from_visa_msg;
	RWCString amount_from_visa_msg;
	RWCString visa_response_code;
	RWCString visa_trans_date;
	RWCString recv_queue_rw;
	RWCString field_35_01;
	RWCString field_35_02;
	RWCString resultado_rw;
	RWCString connection_status_rw;
	RWCString connection_bin_rw;
	char queue_bin[20];
	char resultado[20];
	char maximo[20];
	char connection_status[20];
	RWCString maximo_pre;	
	char pre_zero ;


};

#endif // !defined(AFX_SQLUTIL_H__D446B1A8_D89C_4A77_A9CD_75770ADDF2BD__INCLUDED_)
