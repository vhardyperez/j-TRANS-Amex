// Iso8583Msg.h: interface for the Iso8583Msg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISO8583MSG_H__81A8BE17_B2F0_47F7_A732_7693483664D1__INCLUDED_)
#define AFX_ISO8583MSG_H__81A8BE17_B2F0_47F7_A732_7693483664D1__INCLUDED_

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

class Iso8583Msg  
{
public:
	Iso8583Msg();
	virtual ~Iso8583Msg();
	RWCString setIsoMsg();
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
	void ReturnDumpIsoGeneric( char *msg_type, int debugSB, RWCString peerAddress, int server_port);
  	int       SendMessageToQueue(RWCString incoming, char *recv_queue,char *queue_mgr);
	RWCString setIsoMsg8583(RWCString message, RWCString input);
	RWCString getIsoMsg8583(RWCString type);
	RWCString setBitMap( RWCString input_four_bit);
	RWCString SetMsgField8583( int input_field ); 
	char RetornoHexa( RWCString hex_input);
	RWCString  RetornoHexadecimalComplete( RWCString ascii_input, int input);
	int SendMessageToQueueSql(RWCString incoming, char *sql_queue, char *queue_mgr);
	RWCString Get_Msg_From_SendQueue( char *send_queue,char *queue_mgr);
	int Send_Message_0210(char *input_msg );
	RWCString SetTcpHeader( RWCString incoming_tcp_header ) ;
	char RetornoHexadecimal(RWCString hex_input);
	RWCString  RetornoASCII(char hex_input);
	RWCString  RetornoAsciiComplete( RWCString ascii_input, int input);
	int SendMessageToQueueNoTimeout(RWCString incoming, char *recv_queue,char *queue_mgr);
	RWCString  setIsoMsg8583All(RWCString message, RWCString input);
	RWCString  setMapIsoBase24FromGeneric( RWCString incoming, char *application, int debug);
	RWCString  setMapIsoPosTermFromGeneric( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString  setBitMapFromChar( RWCString input_four_bit);
    RWCString  setMapIsoPosTermFromGeneric100( RWCString incoming, char *application, char *header_msg ,int debug);


private:
	

	RWCString bit_map1 ;
	RWCString bit_map2 ;
	RWCString bit_map_iso  ;
	RWCString complete_iso8583_msg;
	RWCString complete_0800_iso8583_msg;
	RWCString complete_iso_msg_generic;
	RWCString retornoasciicomplete;
	RWCString retornohexadecimalcomplete;
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


	int llvar;
	int lllvar;
};

#endif // !defined(AFX_ISO8583MSG_H__81A8BE17_B2F0_47F7_A732_7693483664D1__INCLUDED_)
