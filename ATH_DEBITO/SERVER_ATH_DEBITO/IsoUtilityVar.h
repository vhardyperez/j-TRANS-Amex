// IsoUtilityVar.h: interface for the IsoUtilityVar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISOUTILITYVAR_H__3850DB08_DBE3_4605_9B1C_07F9D93E96B3__INCLUDED_)
#define AFX_ISOUTILITYVAR_H__3850DB08_DBE3_4605_9B1C_07F9D93E96B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <rw/toolpro/sockaddr.h>
#include <rw/toolpro/sockport.h>
#include <rw/toolpro/inetaddr.h>
#include <rw/toolpro/winsock.h>
#include <rw/toolpro/portstrm.h>
#include <rw/toolpro/socket.h>

#include <rw/cstring.h>
#include <rw/rwdate.h>
#include <rw/rwtime.h>
#include <rw/ctoken.h>
#include <rw/thr/thrfunc.h>
#include <rw/toolpro/neterr.h>
#include <imqi.hpp> // MQSeries MQI

#define MSG_FIELD 5


class IsoUtilityVar  
{
public:
	IsoUtilityVar();
	virtual ~IsoUtilityVar();

//	RWCString SetB24Header0200Pos(RWCString incoming_header); // No se usa
//	RWCString SetField( int input_field ,RWCString field_value); //No se usa 
	RWCString SetMsgField( int input_field); //No se uas
	RWCString SetMsgField( int input_field ,RWCString field_value, RWCString pre_field) ; //Nos e usa
	RWCString setIsoMsg8583(RWCString message, RWCString input);
	RWCString setBitMap( RWCString input_four_bit);
	RWCString SetMsgField8583( int input_field ); //No se usa
	RWCString SetTcpHeader( RWCString incoming_tcp_header ) ;
	RWCString setIsoMsg8583All(RWCString message, RWCString input);
	RWCString setMapIsoBase24FromGeneric( RWCString incoming, char *application, int debug);//No se usa
	RWCString setMapIsoPosTermFromGeneric( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString setBitMapFromChar( RWCString input_four_bit);
    RWCString setMapIsoPosTermFromGeneric100( RWCString incoming, char *application, 
		      char *header_msg ,int debug);//No se usa
		
	RWCString getIsoMsg8583(RWCString type);
	RWCString Get_Msg_From_SendQueue( char *send_queue,char *queue_mgr);//No se usa
	RWCString GetTheIniFileInformation();
	RWCString Get_Msg_From_Queue(   char *send_queue,char *queue_mgr);
	RWCString getTrack2FromGenericVar( RWCString incoming);
	RWCString getGeneric0210FromVar( RWCString incoming, RWCString error_value);

	int SendMessageToQueueNoTimeout(RWCString incoming, char *recv_queue,char *queue_mgr); //No se usa
	int SendMessageToQueueSql(RWCString incoming, char *sql_queue, char *queue_mgr);
	int Send_Message_0210(char *input_msg );//No se usa
	RWCString SendMessageToQueue(RWCString incoming, char *recv_queue,char *queue_mgr);

	void ShowFieldIso8583B24(RWCString incoming , char *msg_type, int debug, RWCString application);
	void showFieldFromGenericVar( RWCString incoming,int debug);

	int  VerifyNumericField(char *incoming_field, const int length_field, RWCString validated_field);
	int  VerifyHexField(char *incoming, const int length_field,RWCString validated_field);
	BOOL VerifyIsoField( RWCString input_msg, int input_field) ;

	void ReturnDumpIsoGeneric( char *msg_type, int debugSB, RWCString peerAddress, int server_port);
	char RetornoHexa( RWCString hex_input);
	RWCString RetornoHexadecimalComplete( RWCString ascii_input, int input);
	char RetornoHexadecimal(RWCString hex_input);
	RWCString  RetornoASCII(char hex_input);
	RWCString  RetornoAsciiComplete( RWCString ascii_input, int input);
	void ReturnIso8583FieldValue(char *msg_type, int field_value, RWCString field_name);

	void MessageErrorLength(RWCString incoming_name, int wrong_field_length, int correct_field_length); 
	RWCString  GetTheIniFileInformationATHDebito();

	RWCString IsoUtilityVar::getGeneric0210FromVarForDebito( RWCString incoming, RWCString error_value);
private:
		RWCString bit_map1 ;
	RWCString bit_map2 ;
	RWCString bit_map_iso  ;
	RWCString complete_iso8583_msg;
	RWCString complete_0800_iso8583_msg;
	RWCString complete_iso_msg_generic;
	RWCString retornoasciicomplete;
	RWCString retornohexadecimalcomplete;
	RWCString response_0210_generic_from_iso;
	RWCString delimiter_comma;
	RWCString message_type;
	RWCString msg_type;
	RWCString header;
	RWCString tpdu_header;
	RWCString card_number;
	RWCString converted_iso_posterm;
	RWCString isomsg8583;
	RWCString isomsg8583complete;
	RWCString bit_map_ascii;
	RWCString bit_map;
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
	RWCString merchant_type;
	RWCString pos_entry_mode;
	RWCString date_settlement;
	RWCString for_athd;						/*024  L04 */ 					
	RWCString pos_condition_code;
	RWCString acquiring_institution_id_code;
	RWCString track_2;
	RWCString retrieval_reference_number;
	RWCString card_acceptor_terminal_id;
	RWCString card_acceptor_id_code;
	RWCString card_acceptor_name_location;
	RWCString track1;
	RWCString additional_data;
	RWCString pos_retailer_data;
	RWCString currency_code_transaction;
	RWCString pin_data;
	RWCString pos_terminal_data;
	RWCString pos_issuer_data;
	RWCString field_63;
	RWCString CVV2;
	RWCString original_data_elements;
	RWCString pos_terminal_address_branch;
	RWCString echo_data;
	RWCString network_managment_info_code;
	RWCString pos_invoice_data;
	RWCString pos_settlement_data;
	RWCString switch_key;
	RWCString 	F1,  F2 ,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20	,			
				F21, F22 , F23, F24, F25, F26, F27, F28, F29, F30, F31, F32, F33, F34, F35, F36, F37, F38, F39, F40	,			
				F41, F42 , F43, F44, F45, F46, F47, F48, F49, F50, F51, F52, F53, F54, F55, F56, F57, F58, F59, F60	,
				F61, F62 , F63, F64, F65, F66, F67, F68, F69, F70, F71, F72, F73, F74, F75, F76, F77, F78, F79, F80 ,	
				F81, F82 , F83, F84, F85, F86, F87, F88, F89, F90, F91, F92, F93, F94, F95, F96, F97, F98, F99, F100 ,	
				F101,F102 ,F103,F104,F105,F106,F107,F108,F109,F110,F111,F112,F113,F114,F115,F116,F117,F118,F119,F120 ,
				F121,F122 ,F123,F124,F125,F126,F127,F128 ;

	RWCString lllvar;					;
	RWCString llvar	;

	char InClient[15]		;
	char IPAddr[15]			;
	char APPName[20]		;
	char send_queue[20]		;
	char send_queue_eps[25] ;
	char send_queue_amex[25] ;
	char recv_queue[20]		;
	char sql_queue[20]		;
	char send_queue_saf[20]		;
	char queue_mgr[20]		;
	char header_ini[18]		;
	char application[10]	;
	int debugSB ;
	char send_queue_string[20];	
	char recv_queue_string[20];	
	char sql_queue_string[20];	
	char queue_mgr_string[20];	
	char header_string[20]	;	
	char send_queue_eps_string[25] ;
	char send_queue_amex_string[25] ;
	char application_string[20];
	int count;




};

#endif // !defined(AFX_ISOUTILITYVAR_H__3850DB08_DBE3_4605_9B1C_07F9D93E96B3__INCLUDED_)
