// MQUtility.h: interface for the MQUtility class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MQUTILITY_H__B0B02072_D02E_4F2F_8E96_25CF3A64A4AB__INCLUDED_)
#define AFX_MQUTILITY_H__B0B02072_D02E_4F2F_8E96_25CF3A64A4AB__INCLUDED_

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
#include <rw/rwtime.h>
#include <sys/types.h>
#include <sys/timeb.h>


#define MSG_FIELD 5
#define LLVAR	2
#define LLLVAR	3
#define FIXED	0

class MQUtility  
{
public:
	MQUtility();
	virtual ~MQUtility();
	RWCString Get_Msg_From_SendQueueNew( RWCString key_message,  char *send_queue,char *queue_mgr);
	RWCString SendMessageToQueueNew(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	void ReturnIso8583FieldValue(char *msg_type, int field_value, RWCString field_name);
	RWCString Retorno_Msg_Generic_PostermB24(RWCString incoming , char *msg_type, int debug,RWCString application);
	int       RetornoFieldNumber(int incoming_field);
	RWCString RetornoPreZeroes(int incoming_field );
	RWCString Retorno_210_B24(RWCString incoming , char *msg_type,int debug);
	RWCString Retorno_Msg_Iso8583_Field125(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString GetTheIniFileInformation();
	int SendMessageToQueueSql(RWCString incoming, char *sql_queue, char *queue_mgr);
	RWCString setMapIsoPosTermFromGeneric( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString SetB24Header0200Pos(RWCString incoming_header); // No se usa
	RWCString SetField( int input_field ,RWCString field_value); //No se usa 
	RWCString SetMsgField( int input_field); //No se uas
	RWCString SetMsgField( int input_field ,RWCString field_value, RWCString pre_field) ; //Nos e usa
	RWCString setIsoMsg8583(RWCString message, RWCString input);
	RWCString setBitMap( RWCString input_four_bit);
	RWCString SetMsgField8583( int input_field ); //No se usa
	RWCString SetTcpHeader( RWCString incoming_tcp_header ) ;
	RWCString setIsoMsg8583All(RWCString message, RWCString input);
	RWCString setMapIsoBase24FromGeneric( RWCString incoming, char *application, int debug);//No se usa
	RWCString setBitMapFromChar( RWCString input_four_bit);
    RWCString setMapIsoPosTermFromGeneric100( RWCString incoming, char *application,char *header_msg ,int debug);//No se usa
	RWCString setGenericFromGenericVar( RWCString incoming);

	RWCString getIsoGenericTerminalIdITBIS( RWCString incoming) ;
	RWCString getIsoMsg8583(RWCString type);
	RWCString Get_Msg_From_SendQueue( char *send_queue,char *queue_mgr);//No se usa
	RWCString Get_Msg_From_Queue(   char *send_queue,char *queue_mgr);
	RWCString getTrack2FromGenericVar( RWCString incoming);
	RWCString GetFieldFromBtransFormat( RWCString incoming, int value_field);

	int SendMessageToQueueNoTimeout(RWCString incoming, char *recv_queue,char *queue_mgr); //No se usa
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

	void MessageErrorLength(RWCString incoming_name, int wrong_field_length, int correct_field_length); 
	void SendMessageToQueueHeader(RWCString incoming, char *recv_queue_input, char *queue_mgr_input);
	int  VerifyGenericVar( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString SendMessageToQueueNewVisa(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString GetMsgFromSendQueuePagos( RWCString key_message,  char *send_queue,char *queue_mgr);
	RWCString SendMessageToQueueNewPagos(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString GetTheIniFileInformationPagos();
	void SendMessageToQueueHeaderPagos(RWCString incoming, char *recv_queue_input, char *queue_mgr_input);
	RWCString SendMessageToQueueAth(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString GetTheIniFileInformationAth();
	RWCString GetTheIniFileInformationPosVirtual();
	RWCString setMapIsoPosTermFromGenericWKP( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString SendMessageToQueuePosVSD(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	void SendMessageToQueueHeaderWithModuleName(RWCString incoming, char *recv_queue_input, char *queue_mgr_input);
	RWCString GetMsgFromSendQueueHeader( RWCString key_message,  char *send_queue,char *queue_mgr);
	RWCString GetMsgFromRecvQueueHeader( char *send_queue,char *queue_mgr);
    RWCString GetTheIniFileInformationPosVirtualVen();
	RWCString SendMessageToQueuePosVen(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString SendMessageToQueueNewCallCenterVen(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString GetMsgFromSendQueueCallCenterVen( RWCString key_message,  char *send_queue,char *queue_mgr);
    void      SendMessageToQueueHeaderVisa(RWCString incoming, char *recv_queue_input, char *queue_mgr_input);
	RWCString GetTheIniFileInformationVisa();
//	RWCString SetIso8583B24FromBanPais(RWCString incoming , char *msg_type, 
//										          int debug, RWCString application);
	RWCString SendMessageToQueueNewPagosPlata(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString GetTheIniFileInformationPagosPlata();
	RWCString SetIso8583B24FromTransPlata0200Retiro(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString SetIso8583B24FromTransPlata0200Pago(RWCString incoming , char *msg_type, 
										          int debug, RWCString application, RWCString field_42);

	RWCString SetIso8583B24FromTransPlata0210(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);

	RWCString Retorno_Msg_Iso8583_Field39(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString Retorno_Msg_Iso8583_Field42(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString Retorno_Msg_Iso8583_Field11_38_39_41_Amex(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	void SendMessageToQueueNewPagosPlataOnly(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	void SendMessageToQueueNewPagosPlataOnlyPagos(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	void Proccess_Message_Postilion( RWCString incoming_msg, char *sql_queue, char *queue_mgr);
	RWCString Retorno_Msg_Generic_Field125(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString SendMessageToQueueNewPagosPlataTebca(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString SetIso8583B24FromTransPlata0420Pago(RWCString incoming , char *msg_type, 
										          int debug, RWCString application, RWCString field_125 );
	void SendMessageToQueueNewPagosPlataOnlyPagos0420(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	void SendMessageToQueueNewPagosPlataOnlyPagos0420NoTimeout(RWCString incoming, char *send_queue_input, char *queue_mgr_input);

    RWCString SendMessageToQueueNewOrange(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
    RWCString SendMessageToQueueNewPosVirtualSD(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
    RWCString SendMessageToQueueNewVisaThreeMsgId(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	void SendMessageToQueueHeaderNewThreeParameters(RWCString incoming, char *recv_queue_input, char *queue_mgr_input);
	void Proccess_Message_PostilionTwoMsId( RWCString incoming_msg, char *sql_queue, char *queue_mgr);
	int SendMessageToQueueWithTimeout(RWCString incoming, char *recv_queue,char *queue_mgr);

	RWCString SetIsoGenericFromB24ForMonitor(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString SendMessageToQueueNewPagosLotes(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString  GetTheIniFileInformationPagosLotes();

	RWCString SetSqlFieldFrom0420(RWCString incoming , char *msg_type, RWCString application );

	RWCString SetBtransFormatFromB24Format(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString SetIso8583B24FromBtransFormat( RWCString incoming, char *application, char *header_msg ,int debug);

    RWCString SetMapIso8583B24FromGenericVar0420( RWCString incoming, char *application, char *header_msg ,int debug);
	BOOL VerifyIsoFieldAVS0420( RWCString input_msg, int input_field) ;
	int VerifyGenericVar0420( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString SendMessageToQueueNewATHDebito(RWCString incoming, char *send_queue_input,char *recv_queue_string , char *sql_queue_input, char *queue_mgr_input);
	RWCString GetTheIniFileInformationATHDebito();

	void Proccess_Message_ATH( RWCString incoming_msg, char *sql_queue,char *recv_queue, char *queue_mgr);

    RWCString Retorno_210_B24_ATH(RWCString incoming , char *msg_type,int debug);
	int VerifyGenericVar0420ATH( RWCString incoming, char *application, char *header_msg ,int debug);
	BOOL VerifyIsoFieldAVS0420ATHDebito( RWCString input_msg, int input_field);
	RWCString SetMapIso8583B24FromGenericVar0420ATHDebito( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString Set0810Iso8583B24FromBtransFormat( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString Set0800Iso8583B24FromBtransFormat( RWCString incoming, char *application, char *header_msg ,int debug);
    void SendMessageToQueueNewATHDebito0430(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString SendMessageToQueueNewAVS(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
    RWCString GetTheIniFileInformationAVS();
	RWCString SetBtransFormatFromB24FormatNOPB(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);

	RWCString SetIso8583B24FromBanPaisB24(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString SetIso8583B24FromVicanaToB24(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
    RWCString SendMessageToQueueNewATHVicana(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString GetTheIniFileInformationATHVicana();
	RWCString SetIso8583VicanaFromBtransFormat( RWCString incoming, char *application, char *header_msg ,int debug);

	RWCString getTrack2FromGenericVarAndAcc( RWCString incoming);

	RWCString SetSqlFieldFrom0420ATH(RWCString incoming , char *msg_type, 
										           RWCString application );
    RWCString SetIso8583DiscoverFromB24Format(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString SetIso8583B24Msg0210FromIso8583B24Msg0200(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString SetIso8583DiscoverMsg0110FromIso8583DiscoverMsg0100(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString SetMapIsoDiscoverFromGeneric( RWCString incoming, char *application, char *header_msg ,int debug);

	void ShowFieldIso8583B24Discover(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);

	RWCString SetIso8583DiscoverFromB24FormatWithParameters(RWCString incoming , char *msg_type, 
										          int debug, RWCString application,RWCString field_19_rw , RWCString field_24_rw ,
												  RWCString field_61_rw, RWCString field_62_rw, RWCString field_127_rw);

	BOOL VerifyIsoFieldReplica( RWCString input_msg, int input_field); 
	RWCString SetIso8583B24FromBtransFormatReplica( RWCString incoming, char *application, char *header_msg ,int debug);

	RWCString SetIso8583B24Msg0210FromIso8583B24Msg0200(RWCString incoming , char *msg_type, 
										          int debug, RWCString application,RWCString answer);

	RWCString GetMsgFromRecvQueueHeaderUsingTimeOutParameters(  char *send_queue,char *queue_mgr,int time_out);

	RWCString GetTheIniFileInformationPagosPlata2();
	RWCString SendMessageToQueueNewPagosPlata2(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString SetIso85830800DiscoverFromB24Format(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString SetIso8583B24Msg0200FromIso8583B24Msg0200VBV(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);

	RWCString SetIso8583B24FromBtransFormatVBV( RWCString incoming, char *application, char *header_msg ,int debug);


	RWCString GetIso8583FieldB24(RWCString incoming , char *msg_type, 
										          int debug, RWCString application,int input_field);



	RWCString GetIso8583FieldB24(RWCString incoming , char *msg_type, 
										          int debug, RWCString application,int input_field,int input_field2,int input_field3);

	RWCString SetIso8583Msg0421FromB24Format(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString setMapIsoPosTermFromDelimiter1C( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString SetMapIsoDiscoverFrom1C( RWCString incoming, char *application, char *header_msg ,int debug);

	RWCString SetIso8583DiscoverFromB24FormatWithParameters1C(RWCString incoming , char *msg_type, 
										          int debug, RWCString application,RWCString field_19_rw , RWCString field_24_rw,
												  RWCString field_61_rw, RWCString field_62_rw, RWCString field_127_rw);

	void LogTrans(RWCString incoming);
	RWCString SetSqlFieldFrom0420Vicana(RWCString incoming , char *msg_type, 
										           RWCString application );
	RWCString SetFieldFromBtransFormat( RWCString incoming, int value_field,RWCString input_value);
	
	//void SendMessageToQueueNewATHDebito0230(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString SendMessageToQueueNewATHVicana230(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	
	void Proccess_Message_ATH230( RWCString incoming_msg, char *sql_queue,char *recv_queue, char *queue_mgr);
  
	void SendMessageToQueueHeader230(RWCString incoming, char *recv_queue_input, char *queue_mgr_input);

	void Retorno_200_B24(RWCString incoming , char *msg_type, char *name_user);
	void Retorno_200_B24Vbv(RWCString incoming , char *msg_type);
	void Retorno_210_B24(RWCString incoming , char *msg_type, char *name_user);
	void Retorno_210_B24Vbv(RWCString incoming , char *msg_type);


	RWCString SetBtransFormatFromB24FormaVbv(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString SendMessageToQueueNewVbv(RWCString incoming, char *send_queue_input, char *queue_mgr_input);


	RWCString SendMessageToQueueNewVbv430(RWCString incoming, char *send_queue_input, char *queue_mgr_input);

    RWCString GetTheIniFileInformationVbv();
	RWCString Set0420BtransFormatFromIso8583(RWCString incoming , char *msg_type, 
										          int debug, RWCString application, RWCString field_125 );
    void SendMessageToQueueNewVbv0420(RWCString incoming, char *send_queue_input, char *queue_mgr_input);

	int VerifyGenericVar1C( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString getTrack2FromGenericVar1C( RWCString incoming);
    RWCString SendMessageToQueueRetornoMsgBtransVarDelimiter1C(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString Retorno_210_B24_1C(RWCString incoming , char *msg_type,int debug);
	int VerifyGenericVar04201C( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString GetFieldFromBtransFormat1C( RWCString incoming, int value_field);
	RWCString SetMapIso8583B24FromGenericVar04201C( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString SendMessageToQueueNewAVS1C(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	RWCString SetBtransFormatFromB24Format1C(RWCString incoming , char *msg_type, 
									          int debug, RWCString application);
	RWCString Set0800Iso8583B24FromBtransFormat1C( RWCString incoming, char *application, char *header_msg ,int debug);

	RWCString SetBtransFormatFromB24FormatNOPB1C(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	void SendMessageToQueueNewPagosPlataOnlyPagos0420NoTimeoutAvs(RWCString incoming, char *send_queue_input, char *queue_mgr_input);
	void SendMessageToQueueNewAvs0420(RWCString incoming, char *send_queue_input, char *queue_mgr_input);

	RWCString SetIso8583B24Msg0200FromIso8583B24Msg0200VBV1C(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
    RWCString SetIso8583B24FromBtransFormatVBV1C( RWCString incoming, char *application, char *header_msg ,int debug);
	RWCString SendMessageToQueueNewVBV1C(RWCString incoming, char *send_queue_input, char *queue_mgr_input);

	RWCString SendMessageToQueueNewAVSAndVBV(RWCString incoming, char *send_queue_input, char *queue_mgr_input);

	RWCString MQUtility::SetIso8583CapitalGMsg1210FromIso8583CapitalGMsg1200(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString MQUtility::SendMessageToQueueNewATHDebito(RWCString incoming, char *send_queue_input, char *queue_mgr_input);

	RWCString MQUtility::SetIso8583CapitalGMsg1210FromIso8583CapitalGMsg12001993(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);

	RWCString MQUtility::SetIso8583B24FromBtransFormat1993( RWCString incoming, char *application, char *header_msg ,int debug);

	void MQUtility::ShowFieldIso8583B241993(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	RWCString MQUtility::setIsoMsg8583All1Version1993(RWCString message, RWCString input);

	int MQUtility::RetornoFieldNumberVersion1993(int incoming_field );
	RWCString MQUtility::setMapIsoPosTermFromGeneric1C( RWCString incoming, char *application, char *header_msg ,int debug);

	void MQUtility::ShowFieldIso8583B24ForPostBridge(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);

	RWCString MQUtility::SetIso8583B24FromBanPais(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);

	RWCString MQUtility::SendMessageToQueueapitalGWithParameters(RWCString incoming, char *send_queue_input, char *queue_mgr_input ,char *recv_queue_input, char *sql_queue_input);

	RWCString MQUtility::GetIso8583FieldB24ForKioscos(RWCString incoming , char *msg_type, 
										          int debug, RWCString application,int input_field);

	void MQUtility::ShowFieldIso8583B24Format(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);

	RWCString MQUtility::SendMessageToQueueNewATHDebito(RWCString incoming, char *send_queue_input, char *recv_queue, char *sql_queue, char *queue_mgr_input, int debugSB);

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
	RWCString account_information_102;
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

	RWCString processing_code_03;	
	RWCString transaction_amount_04;
	RWCString transmition_date_time_07;
	RWCString convertion_rate_010;	
	RWCString system_trace_011;
	RWCString time_local_transaction_012;
	RWCString date_local_transaction_013;		
	RWCString expiration_date_014;					
	RWCString date_settlement_015;
	RWCString capture_date_017;
	RWCString merchant_type_018;
	RWCString pos_entry_mode_022;
	RWCString for_athd_024;
	RWCString pos_condition_code_025;
	RWCString original_amounts_F30;
	RWCString acquiring_institution_id_code_032	;
	RWCString track_2_035						;
	RWCString retrieval_reference_number_037	;
	RWCString responde_id_response_038          ;
	RWCString responde_code_039					;
	RWCString card_acceptor_terminal_id_041		;	
	RWCString card_acceptor_id_code_042			;		
	RWCString card_acceptor_name_location_043	;
	RWCString track_1_045						;
	RWCString addditional_data_048				;
	RWCString currency_code_transaction_049     ;
	RWCString pin_data_052						;
	RWCString additional_data_054						;

	RWCString pos_terminal_data_060				;
	RWCString card_issuer_response_data_061		;
	RWCString additional_data_063				;
	RWCString receiving_institution_id_code_0100;
	RWCString pos_terminal_address_branch_120	;
	RWCString authorization_indicators_0121		;
	RWCString pos_invoice_data_0123             ;
	RWCString batch_record2_0124				;
	RWCString pos_settlement_data_125			;
	RWCString preauthorization_data_0126		;
	RWCString switch_key_127					;


	RWCString acq_country_code;
	RWCString function_code;
	RWCString geographic_data;
	RWCString card_identifier;
	RWCString ebt_bit_127;


	RWCString lllvar;					;
	RWCString llvar	;
//	RWCString response_0210_generic_from_iso;
	RWCString bit_map_first_part;
	RWCString bit_map_second_part;
	char InClient[15]		;
	char IPAddr[15]			;
	char APPName[20]		;
	char send_queue[20]		;
	char send_queue_alterno[20]		;
	char send_queue_eps[25] ;
	char send_queue_amex[25] ;
	char recv_queue[20]		;
	char sql_queue[20]		;
	char queue_mgr[20]		;
	char header_ini[18]		;
	char application[10]	;
	int debugSB ;
	char send_queue_string[20];	
	char send_queue_alterno_string[20];	
	char recv_queue_string[20];	
	char sql_queue_string[20];	
	char queue_mgr_string[20];	
	char header_string[20]	;	
	char send_queue_eps_string[25] ;
	char send_queue_amex_string[25] ;
	char application_string[20];
	int count;


};

#endif // !defined(AFX_MQUTILITY_H__B0B02072_D02E_4F2F_8E96_25CF3A64A4AB__INCLUDED_)
