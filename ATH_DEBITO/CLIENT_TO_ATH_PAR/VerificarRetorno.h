#if defined(VRETORNO_H)
#else

#define VRETORNO_H

#include <rw/ctoken.h>

#define F2LENGTH								19
#define F3LENGTH								6


RWCString message_type_0200;	
RWCString message_type_0800;	
RWCString bit_map_b24				;				
RWCString header_msg			;			/*     L06 */
RWCString msg_type_identifier   ;			/*     L04 */
RWCString account_number_header;			/*002  L19 */
RWCString processing_code_03;				/*003  L6  */
RWCString transaction_amount_04;			/*004  L12 */ 
RWCString transmition_date_time_07;			/*007  L10 */
RWCString convertion_rate_010;				/*010  NL8  */
RWCString system_trace_011;					/*011  L6  */
RWCString time_local_transaction_012;		/*012  L6  */
RWCString date_local_transaction_013;		/*013  L4  */
RWCString expiration_date_014;				/*014  L4  */
RWCString date_settlement_015;				/*015  L4  */
RWCString capture_date_017;					/*017  L4  */
RWCString merchant_type_018	;				/*018  L4  */
RWCString pos_entry_mode_022;				/*022  NL3  */
RWCString for_athd_024;						/*024  NL3  */
RWCString pos_condition_code_025;			/*025  L2  */
RWCString acquiring_institution_id_code_032;/*032  L11 */
RWCString track_2_035					;	/*035  L37 */
RWCString retrieval_reference_number_037;	/*037  L12 */
RWCString responde_id_response_038		;   /*038  L06 */ 
RWCString responde_code_039		;			/*039  L02 */ 
RWCString card_acceptor_terminal_id_041	;	/*041  L08 */
RWCString card_acceptor_id_code_042		;	/*042  L15 */
RWCString card_acceptor_name_location_043;	/*043  L40 */
RWCString track_1_045					;	/*045  L76 */
RWCString addditional_data_048;				/*048  L120 para Postilion L30 para B24 */
RWCString pos_retailer_data_48;				/*048  L30 para B24 */
RWCString currency_code_transaction_049	;	/*049  L03 */
RWCString pin_data_052					;	/*052  L16An*/
RWCString additional_amount_54				;	/*054  L120*/
RWCString pos_terminal_data_060			;   /*060  L19 para B24 ATH */
RWCString pos_issuer_data_061			;   /*061  L22 para B24 ATH*/
RWCString card_issuer_response_data_061 ;   /*061  lllvar*/
RWCString additional_data_063 ;				/*063  lllvar*/
RWCString original_data_elements_090;
RWCString receiving_institution_id_code_0100	;	/*100  L11 */
RWCString pos_terminal_address_branch_120;	/*120  L32 para ATH B24 */
RWCString authorization_indicators_0121	;	/*121  LLLvar */
RWCString pos_invoice_data_123			;	/*123  L23 para B24 ATH*/
RWCString batch_record2_0124			;	/*124  LLLvar */
RWCString pos_settlement_data_125		;	/*125  L15 para B24 ATH */

//RWCString settlemente_record2_0125		;	/*125  LLLvar */

RWCString preauthorization_data_0126	;	/*126  LLLvar */








RWCString processing_code;					/*003  L6  */
RWCString transaction_amount;				/*004  L12 */ 
RWCString settlement_amount ;				/*005  L12 */
RWCString transmition_date_time;			/*007  L10 */
RWCString conversion_rate_settlement;		/*009  L8  */
RWCString system_trace;						/*011  L6  */
RWCString time_local_transaction;			/*012  L6  */
RWCString date_local_transaction;			/*013  L4  */
RWCString expiration_date;					/*014  L4  */
RWCString date_settlement;					/*015  L4  */
RWCString capture_date;						/*015  L4  */
RWCString date_convertion;					/*016  L4  */
RWCString merchant_type	;					/*018  L4  */
RWCString pos_entry_mode;					/*022  L3  */
RWCString card_sequence_number;				/*023  L2  */
RWCString pos_condition_code;				/*025  L2  */
RWCString pos_pin_capture_code;				/*026  L1  */
RWCString auto_id_reponse_code;				/*027  L9  */
RWCString amount_trans_fee;					/*028  L9  */
RWCString amount_settlement_fee;			/*029  L9  */
RWCString amount_trans_proce_fee;			/*030  L9  */
RWCString amount_settle_proecessing_fee;	/*031  L11 */
RWCString acquiring_institution_id_code	;	/*032  L11 */
RWCString forwarding_institution_id_code;	/*033  L11 */
RWCString track_2						;	/*035  L37 */
RWCString retrieval_reference_number	;	/*037  L12 */
RWCString authorization_id_response		;	/*038  L06 */ //0420
RWCString service_resytricion_code		;	/*040  L03 */
RWCString card_acceptor_terminal_id		;	/*041  L08 */
RWCString card_acceptor_id_code			;	/*042  L15 */
RWCString card_acceptor_name_location	;	/*043  L40 */
RWCString additional_reponse_data		;	/*044  L25 */ //0420
RWCString track_1						;	/*045  L76 */
RWCString pos_retailer_data;				/*048  L30 para B24 */
RWCString addditional_data				;	/*048  L120 */
RWCString currency_code_transaction		;	/*049  L03 */
RWCString currency_code_settlement		;	/*050  L03 */
RWCString pin_data						;	/*052  L08B*/
RWCString security_control_information	;	/*053  L48 */
RWCString additional_amount				;	/*054  L120*/
RWCString message_reason_code			;	/*056  L04 */
RWCString authorization_cycle			;	/*057  L03 */
RWCString authorization_agent_id_code	;	/*058  L11 */ //0420
RWCString echo_data						;	/*059  L255*/
RWCString pos_terminal_data				;   /*060  L19 para B24 ATH */
RWCString pos_issuer_data				;   /*061  L22 para B24 ATH*/
RWCString extended_payment_code			;	/*067  L02 */
RWCString network_mng_info_code			;   /*070  L03 */
RWCString original_data_elements		;	/*090  L42 */ //0420
RWCString replacement_amounts			;   /*095  L42 */
RWCString payee							;	/*098  L25 */
RWCString receiving_institution_id_code	;	/*100  L11 */
RWCString account_identification1		;	/*102  L28 */
RWCString account_identification2		;	/*103  L28 */
RWCString pos_terminal_address_branch	;	/*120  L32 para ATH B24 */
RWCString pos_data_code					;	/*123  L15 */
RWCString pos_invoice_data				;	/*123  L23 para B24 ATH*/
RWCString pos_settlement_data			;	/*125  L15 para B24 ATH */



RWCString switch_key_127				;	/*127.4 L22 */
RWCString pos_data						;	/*127.4 L22 */
RWCString service_satation_data			;	/*127.5 L73 */
RWCString authorization_profile			;	/*127.6 L02 */ //0420
RWCString check_data					;	/*127.7 L50 */
RWCString cvv2							;	/*127.10 L3 */
RWCString terminal_owner				;	/*127.12 L25 */
RWCString pos_geographic_data			;	/*127.13 L17 */
RWCString sponsor_bank					;	/*127.14 L8 */
RWCString addres_verification_data		;	/*127.15 L29 */
RWCString validation_data				;	/*127.18 L50 */
RWCString payee_bank_account			;	/*127.19 L31 */
RWCString payer_account_identification	;	/*127.24 L28 */
RWCString original_node					;	/*127.26 L20 */
RWCString card_verification_result		;	/*127.27 L1 */
RWCString american_express_identifier	;	/*127.28 L4 */
RWCString secure_data					;	/*127.29 L40 */
RWCString response_0110	= "";
RWCString response_0210	= "";
RWCString response_0810 = "";
RWCString response_0430 = "";
RWCString response_0210_generic_from_iso = "";
RWCString delimiter = ",";
RWCString msg_reponse_with_tcp_header = "";
char tpdu_header[15]						= {""};
char header[18]								= {""};
char processing_code_F3[7]					= {""};
char transaction_amount_F4[13]				= {""};
char transmission_date_time_F7[11]			= {""};
char system_trace_audit_number_F11[7]		= {""};
char local_transaction_time_F12[7]			= {""};
char local_transaction_date_F13[5]			= {""};
char expiration_date_14[5]					= {""};
char capture_date_F17[5]					= {""};
char merchant_type_F18[5]					= {""};
char point_service_entry_mode_F22[4]		= {""};
char point_service_condition_code_F25[3]	= {""};
char acquiring_institution_id_code_F32[12]	= {""};
char forwarding_institution_id_code_F33[12] = {""};
char track2_F35[38]							= {""};        
char retrieval_reference_number_F37[13]		= {""};
char card_acceptor_terminal_id_F41[17]		= {""};    
char card_acceptor_id_code_F42[16]			= {""};           
char card_acceptor_name_location_F43[41]    = {""};
//char pos_retailer_data_48[28]				= {""};
char transaction_currency_code_F49[4]		= {""};
char personal_id_number_F52[17]				= {""};
char echo_data_F59[11]						= {""};
char pos_terminal_data_60[17]				= {""};
char pos_issuer_data_61[20]					= {""};
char field_63[27]							= {""};
char network_managment_info_code_F70[4]		= {""};
char receiving_institution_id_code_F100[12] = {""};
//char pos_terminal_address_branch_120[30]	= {""};
////char pos_invoice_data_123[21]				= {""};
//char pos_settlement_data_125[13]			= {""};
int F3 = 1;
RWCString delimiter_comma = ",";
RWCString message_0200_generic = "";
RWCString message_0800_generic = "";
RWCString server_address = "";

char InClient[15]			= {""};
char IPAddr[15]				= {""};
char APPName[20]			= {""};
char SB1ADD[15];
char input_msg[512]			= {""};
char sent_0800[512]			= {""};
char send_queue[20]			= {""};
char recv_queue[20]			= {""};
char sql_queue[20]			= {""};
char monitor_queue[20]			= {""};

char queue_mgr[20]			= {""};
char bsources[20]			= {""};
char file_name[100]			= {""};
char file_name_trace[100]	= {""};
char directorio_archivo[120]= {""};
RWCString argumentofortrace = "";
RWCString debug_from_queue  = "DEBUG_OFF";

char application[20]		= {""};
int client_flag = 0;

int debugSB =0 ;
int debugtrace =0 ;
int time_out_0800 = 0;
int port = 0;
RWCString VretornoBit(RWCString incoming)
{
	cout << "Valor de Bitmap > " << endl;//hex_bit << endl;
	
	
	return 'n';
}





char VretornoHex(RWCString hex_input)
{
	
	
	if (hex_input == "1")
		return '\x1';
	if (hex_input == "2")
		return '\x2';
	if (hex_input == "3")
		return '\x3';
	if (hex_input == "4")
		return '\x4';
	if (hex_input == "5")
		return '\x5';
	if (hex_input == "6")
		return '\x6';
	if (hex_input == "7")
		return '\x7';
	if (hex_input == "8")
		return '\x8';
	if (hex_input == "9")
		return '\x9';
	if (hex_input == "0a")
		return '\x0a';
	if (hex_input == "0b")
		return '\x0b';
	if (hex_input == "0c")
		return '\x0c';
	if (hex_input == "0d")
		return '\x0d';
	if (hex_input == "0e")
		return '\x0e';
	if (hex_input == "0f")
		return '\x0f';

	if (hex_input == "10")
		return '\x10';
	if (hex_input == "11")
		return '\x11';
	if (hex_input == "12")
		return '\x13';
	if (hex_input == "14")
		return '\x14';
	if (hex_input == "15")
		return '\x15';
	if (hex_input == "16")
		return '\x16';
	if (hex_input == "17")
		return '\x17';
	if (hex_input == "18")
		return '\x18';
	if (hex_input == "19")
		return '\x19';
	if (hex_input == "1a")
		return '\x1a';
	if (hex_input == "1b")
		return '\x1b';
	if (hex_input == "1c")
		return '\x1c';
	if (hex_input == "1d")
		return '\x1d';
	if (hex_input == "1e")
		return '\x1e';
	if (hex_input == "1f")
		return '\x1f';

	if (hex_input == "20")
		return '\x20';
	if (hex_input == "21")
		return '\x21';
	if (hex_input == "22")
		return '\x22';
	if (hex_input == "23")
		return '\x23';
	if (hex_input == "24")
		return '\x24';
	if (hex_input == "25")
		return '\x25';
	if (hex_input == "26")
		return '\x26';
	if (hex_input == "27")
		return '\x27';
	if (hex_input == "28")
		return '\x28';
	if (hex_input == "29")
		return '\x29';
	if (hex_input == "2a")
		return '\x2a';
	if (hex_input == "2b")
		return '\x2b';
	if (hex_input == "2c")
		return '\x2c';
	if (hex_input == "2d")
		return '\x2d';
	if (hex_input == "2e")
		return '\x2e';
	if (hex_input == "2f")
		return '\x2f';


	if (hex_input == "30")
		return '\x30';
	if (hex_input == "31")
		return '\x31';
	if (hex_input == "32")
		return '\x32';
	if (hex_input == "33")
		return '\x33';
	if (hex_input == "34")
		return '\x34';
	if (hex_input == "35")
		return '\x35';
	if (hex_input == "36")
		return '\x36';
	if (hex_input == "37")
		return '\x37';
	if (hex_input == "38")
		return '\x38';
	if (hex_input == "39")
		return '\x39';
	if (hex_input == "3a")
		return '\x3a';
	if (hex_input == "3b")
		return '\x3b';
	if (hex_input == "3c")
		return '\x3c';
	if (hex_input == "3d")
		return '\x3d';
	if (hex_input == "3e")
		return '\x3e';
	if (hex_input == "3f")
		return '\x3f';

	if (hex_input == "40")
		return '\x40';
	if (hex_input == "41")
		return '\x41';
	if (hex_input == "42")
		return '\x42';
	if (hex_input == "43")
		return '\x43';
	if (hex_input == "44")
		return '\x44';
	if (hex_input == "45")
		return '\x45';
	if (hex_input == "46")
		return '\x46';
	if (hex_input == "47")
		return '\x47';
	if (hex_input == "48")
		return '\x48';
	if (hex_input == "49")
		return '\x49';
	if (hex_input == "4a")
		return '\x4a';
	if (hex_input == "4b")
		return '\x4b';
	if (hex_input == "4c")
		return '\x4c';
	if (hex_input == "4d")
		return '\x4d';
	if (hex_input == "4e")
		return '\x4e';
	if (hex_input == "4f")
		return '\x4f';


	if (hex_input == "50")
		return '\x50';
	if (hex_input == "51")
		return '\x51';
	if (hex_input == "52")
		return '\x52';
	if (hex_input == "53")
		return '\x53';
	if (hex_input == "54")
		return '\x54';
	if (hex_input == "55")
		return '\x55';
	if (hex_input == "56")
		return '\x56';
	if (hex_input == "57")
		return '\x57';
	if (hex_input == "58")
		return '\x58';
	if (hex_input == "59")
		return '\x59';
	if (hex_input == "5a")
		return '\x5a';
	if (hex_input == "5b")
		return '\x5b';
	if (hex_input == "5c")
		return '\x5c';
	if (hex_input == "5d")
		return '\x5d';
	if (hex_input == "5e")
		return '\x5e';
	if (hex_input == "5f")
		return '\x5f';

	if (hex_input == "60")
		return '\x60';
	if (hex_input == "61")
		return '\x61';
	if (hex_input == "62")
		return '\x62';
	if (hex_input == "63")
		return '\x63';
	if (hex_input == "64")
		return '\x64';
	if (hex_input == "65")
		return '\x65';
	if (hex_input == "66")
		return '\x66';
	if (hex_input == "67")
		return '\x67';
	if (hex_input == "68")
		return '\x68';
	if (hex_input == "69")
		return '\x69';
	if (hex_input == "6a")
		return '\x6a';
	if (hex_input == "6b")
		return '\x6b';
	if (hex_input == "6c")
		return '\x6c';
	if (hex_input == "6d")
		return '\x6d';
	if (hex_input == "6e")
		return '\x6e';
	if (hex_input == "6f")
		return '\x6f';

	if (hex_input == "70")
		return '\x70';
	if (hex_input == "71")
		return '\x71';
	if (hex_input == "72")
		return '\x72';
	if (hex_input == "73")
		return '\x73';
	if (hex_input == "74")
		return '\x74';
	if (hex_input == "75")
		return '\x75';
	if (hex_input == "76")
		return '\x76';
	if (hex_input == "77")
		return '\x77';
	if (hex_input == "78")
		return '\x78';
	if (hex_input == "79")
		return '\x79';
	if (hex_input == "7a")
		return '\x7a';
	if (hex_input == "7b")
		return '\x7b';
	if (hex_input == "7c")
		return '\x7c';
	if (hex_input == "7d")
		return '\x7d';
	if (hex_input == "7e")
		return '\x7e';
	if (hex_input == "7f")
		return '\x7f';

	
	if (hex_input == "80")
		return '\x80';
	if (hex_input == "81")
		return '\x81';
	if (hex_input == "82")
		return '\x82';
	if (hex_input == "83")
		return '\x83';
	if (hex_input == "84")
		return '\x84';
	if (hex_input == "85")
		return '\x85';
	if (hex_input == "86")
		return '\x86';
	if (hex_input == "87")
		return '\x87';
	if (hex_input == "88")
		return '\x88';
	if (hex_input == "89")
		return '\x89';
	if (hex_input == "8a")
		return '\x8a';
	if (hex_input == "8b")
		return '\x8b';
	if (hex_input == "8c")
		return '\x8c';
	if (hex_input == "8d")
		return '\x8d';
	if (hex_input == "8e")
		return '\x8e';
	if (hex_input == "8f")
		return '\x8f';

	if (hex_input == "90")
		return '\x90';
	if (hex_input == "91")
		return '\x91';
	if (hex_input == "92")
		return '\x92';
	if (hex_input == "93")
		return '\x93';
	if (hex_input == "94")
		return '\x94';
	if (hex_input == "95")
		return '\x95';
	if (hex_input == "96")
		return '\x96';
	if (hex_input == "97")
		return '\x97';
	if (hex_input == "98")
		return '\x98';
	if (hex_input == "99")
		return '\x99';
	if (hex_input == "9a")
		return '\x9a';
	if (hex_input == "9b")
		return '\x9b';
	if (hex_input == "9c")
		return '\x9c';
	if (hex_input == "9d")
		return '\x9d';
	if (hex_input == "9e")
		return '\x9e';
	if (hex_input == "9f")
		return '\x9f';

	if (hex_input == "a0")
		return '\xa0';
	if (hex_input == "a1")
		return '\xa1';
	if (hex_input == "a2")
		return '\xa2';
	if (hex_input == "a3")
		return '\xa3';
	if (hex_input == "a4")
		return '\xa4';
	if (hex_input == "a5")
		return '\xa5';
	if (hex_input == "a6")
		return '\xa6';
	if (hex_input == "a7")
		return '\xa7';
	if (hex_input == "a8")
		return '\xa8';
	if (hex_input == "a9")
		return '\xa9';
	if (hex_input == "aa")
		return '\xaa';
	if (hex_input == "ab")
		return '\xab';
	if (hex_input == "ac")
		return '\xac';
	if (hex_input == "ad")
		return '\xad';
	if (hex_input == "ae")
		return '\xae';
	if (hex_input == "af")
		return '\xaf';

	if (hex_input == "b0")
		return '\xb0';
	if (hex_input == "b1")
		return '\xb1';
	if (hex_input == "b2")
		return '\xb2';
	if (hex_input == "b3")
		return '\xb3';
	if (hex_input == "b4")
		return '\xb4';
	if (hex_input == "b5")
		return '\xb5';
	if (hex_input == "b6")
		return '\xb6';
	if (hex_input == "b7")
		return '\xb7';
	if (hex_input == "b8")
		return '\xb8';
	if (hex_input == "b9")
		return '\xb9';
	if (hex_input == "ba")
		return '\xba';
	if (hex_input == "bb")
		return '\xbb';
	if (hex_input == "bc")
		return '\xbc';
	if (hex_input == "bd")
		return '\xbd';
	if (hex_input == "be")
		return '\xbe';
	if (hex_input == "bf")
		return '\xbf';


	if (hex_input == "c0")
		return '\xc0';
	if (hex_input == "c1")
		return '\xc1';
	if (hex_input == "c2")
		return '\xc2';
	if (hex_input == "c3")
		return '\xc3';
	if (hex_input == "c4")
		return '\xc4';
	if (hex_input == "c5")
		return '\xc5';
	if (hex_input == "c6")
		return '\xc6';
	if (hex_input == "c7")
		return '\xc7';
	if (hex_input == "c8")
		return '\xc8';
	if (hex_input == "c9")
		return '\xc9';
	if (hex_input == "ca")
		return '\xca';
	if (hex_input == "cb")
		return '\xcb';
	if (hex_input == "cc")
		return '\xcc';
	if (hex_input == "cd")
		return '\xcd';
	if (hex_input == "ce")
		return '\xce';
	if (hex_input == "cf")
		return '\xcf';

	if (hex_input == "d0")
		return '\xd0';
	if (hex_input == "d1")
		return '\xd1';
	if (hex_input == "d2")
		return '\xd2';
	if (hex_input == "d3")
		return '\xd3';
	if (hex_input == "d4")
		return '\xd4';
	if (hex_input == "d5")
		return '\xd5';
	if (hex_input == "d6")
		return '\xd6';
	if (hex_input == "d7")
		return '\xd7';
	if (hex_input == "d8")
		return '\xd8';
	if (hex_input == "d9")
		return '\xd9';
	if (hex_input == "da")
		return '\xda';
	if (hex_input == "db")
		return '\xdb';
	if (hex_input == "dc")
		return '\xdc';
	if (hex_input == "dd")
		return '\xdd';
	if (hex_input == "de")
		return '\xde';
	if (hex_input == "df")
		return '\xdf';


	if (hex_input == "e0")
		return '\xe0';
	if (hex_input == "e1")
		return '\xe1';
	if (hex_input == "e2")
		return '\xe2';
	if (hex_input == "e3")
		return '\xe3';
	if (hex_input == "e4")
		return '\xe4';
	if (hex_input == "e5")
		return '\xe5';
	if (hex_input == "e6")
		return '\xe6';
	if (hex_input == "e7")
		return '\xe7';
	if (hex_input == "e8")
		return '\xe8';
	if (hex_input == "e9")
		return '\xe9';
	if (hex_input == "ea")
		return '\xea';
	if (hex_input == "eb")
		return '\xeb';
	if (hex_input == "ec")
		return '\xec';
	if (hex_input == "ed")
		return '\xed';
	if (hex_input == "ee")
		return '\xee';
	if (hex_input == "ef")
		return '\xef';

	if (hex_input == "f0")
		return '\xf0';
	if (hex_input == "f1")
		return '\xf1';
	if (hex_input == "f2")
		return '\xf2';
	if (hex_input == "f3")
		return '\xf3';
	if (hex_input == "f4")
		return '\xf4';
	if (hex_input == "f5")
		return '\xf5';
	if (hex_input == "f6")
		return '\xf6';
	if (hex_input == "f7")
		return '\xf7';
	if (hex_input == "f8")
		return '\xf8';
	if (hex_input == "f9")
		return '\xf9';
	if (hex_input == "fa")
		return '\xfa';
	if (hex_input == "fb")
		return '\xfb';
	if (hex_input == "fc")
		return '\xfc';
	if (hex_input == "fd")
		return '\xfd';
	if (hex_input == "fe")
		return '\xfe';
	if (hex_input == "ff")
		return '\xff';

	return 'n';
}




RWCString Retorno_100_200(RWCString incoming , char *msg_type)
{

	
	if((strncmp(msg_type, "0800", 4) == 0))
	{
		header_msg						= incoming(2,6);  //02
		msg_type_identifier				= incoming(8,4);  //02
		transmition_date_time			= incoming(12,10);	//07     		
		system_trace					= incoming(23,6);	//11				
		time_local_transaction			= incoming(30,6);	//12				
		date_local_transaction			= incoming(37,4);	//13
		network_mng_info_code			= incoming(42,3);	//70
		
	}
	
	
	
	if(((strncmp(msg_type, "0100", 4)) == 0) || ((strncmp(msg_type, "0200", 4)) == 0))
	{
		account_number_header			= incoming(12,19);  //02
		processing_code					= incoming(32,6);   //03   
		transaction_amount				= incoming(39,12);	//04		
		settlement_amount				= incoming(52,12);	//05		
		transmition_date_time			= incoming(65,10);	//07     		
		conversion_rate_settlement		= incoming(76,8);	//09			
		system_trace					= incoming(85,6);	//11				
		time_local_transaction			= incoming(92,6);	//12				
		date_local_transaction			= incoming(99,4);	//13		
		expiration_date					= incoming(104,4);	//14			
		date_settlement					= incoming(109,4);	//15
		date_convertion					= incoming(114,4);	//16
		merchant_type					= incoming(119,4);	//18	
		pos_entry_mode					= incoming(124,3);	//22	
		card_sequence_number			= incoming(128,3);	//23
		pos_condition_code				= incoming(132,2);	//25
		pos_pin_capture_code			= incoming(135,2);	//26
		auto_id_reponse_code			= incoming(138,1);	//27
		amount_trans_fee				= incoming(140,9);	//28
		amount_settlement_fee			= incoming(150,9);	//29
		amount_trans_proce_fee			= incoming(160,9);	//30	
		amount_settle_proecessing_fee	= incoming(170,9);	//31
		acquiring_institution_id_code	= incoming(180,11);	//32
		forwarding_institution_id_code	= incoming(192,11);	//33
		track_2							= incoming(204,37);	//35
		retrieval_reference_number		= incoming(242,12);	//37
		service_resytricion_code		= incoming(255,3);	//40
		card_acceptor_terminal_id		= incoming(259,8);	//41
		card_acceptor_id_code			= incoming(268,15);	//42
		card_acceptor_name_location		= incoming(284,40);	//43
		track_1							= incoming(325,76);	//45
		currency_code_transaction		= incoming(402,3);	//49
		currency_code_settlement		= incoming(406,3);	//50
		pin_data						= incoming(410,8);	//52
		security_control_information	= incoming(419,48);	//53
		additional_amount				= incoming(468,120);//54
		message_reason_code				= incoming(589,4);	//56
	}
	if((strncmp(msg_type, "0100", 4)) == 0)
	{
		authorization_cycle				= incoming(594,3);	//57
		//authorization_agent_id_code
		echo_data						= incoming(598,255);//59
		extended_payment_code			= incoming(854,2) ;	//67
		//network_mng_info_code			=	
		//original_data_elements		=	
		//replacement_amounts			=
		payee							= incoming(857,25);	//98
		receiving_institution_id_code	= incoming(883,11);	//100
		account_identification1			= incoming(895,28);	//102
		account_identification2			= incoming(924,28);	//103
		pos_data_code					= incoming(953,15);	//123
		pos_data						= incoming(969,22);	//127.4
		service_satation_data			= incoming(992,73);	//127.5
		//authorization_profile			= 	
		check_data						= incoming(1066,50);//127.7
		cvv2							= incoming(1117,3);	//127.10
		terminal_owner					= incoming(1121,25);//127.12
		pos_geographic_data				= incoming(1147,17);//127.13
		sponsor_bank					= incoming(1165,8);	//127.14
		addres_verification_data		= incoming(1174,29);//125.15
		validation_data					= incoming(1204,50);//127.18
		payee_bank_account				= incoming(1255,31);//127.19
		payer_account_identification	= incoming(1287,28);//127.24
		original_node					= incoming(1316,20);//127.26
		card_verification_result		= incoming(1337,1);	//127.27
		american_express_identifier		= incoming(1339,4);	//127.28
		secure_data						= incoming(1344,40);//127.29
	
	}													
	if((strncmp(msg_type, "0200", 4)) == 0)
	{
		echo_data						= incoming(594,255);//59
		extended_payment_code			= incoming(850,2) ;	//67
		payee							= incoming(853,25);	//98
		account_identification1			= incoming(879,28);	//102
		account_identification2			= incoming(908,28);	//103
		pos_data_code					= incoming(937,15);	//123
		pos_data						= incoming(953,22);	//127.4
		service_satation_data			= incoming(976,73);	//127.5
		check_data						= incoming(1050,50);//127.7
		cvv2							= incoming(1101,3);	//127.10
		terminal_owner					= incoming(1105,25);//127.12
		pos_geographic_data				= incoming(1131,17);//127.13
		sponsor_bank					= incoming(1149,8);	//127.14
		addres_verification_data		= incoming(1158,29);//125.15
		validation_data					= incoming(1188,50);//127.18
		payee_bank_account				= incoming(1239,31);//127.19
		payer_account_identification	= incoming(1271,28);//127.24
		original_node					= incoming(1300,20);//127.26
		card_verification_result		= incoming(1321,1);	//127.27
		american_express_identifier		= incoming(1323,4);	//127.28
		secure_data						= incoming(1328,40);//127.29
	
	}																			
		

		char hex1c_2 = 0x1C;
		RWCString delimiter = hex1c_2;
		RWCString autorization_id_response = "000000";						//038//
		RWCString response_code = "00";										//039//
		RWCString additional_response_data = "Esto es el campo 44      " ;	//044//
/*048*/	RWCString additional_data = "1239999999999                                                                                                                                                                                                                                                                                                                                                           ";
		RWCString authorizing_agent_id_code = "00000000000";				//058//
		RWCString authorization_profile = "00";								/*127.6*/
/*127.8*/RWCString retention_data = "                                                                                                                                ";
		RWCString address_verificaction_result = " ";						/*127.16*/
/*127.17*/RWCString cardholder_information = "                                                  ";
		RWCString authorizaer_date_settlement = "        ";					/*127.20*/	
    	RWCString secure_retail = " ";										/*127.30*/
		RWCString security_control_information = "                                                "; //048//
		
		if((strncmp(msg_type, "0800", 4)) == 0)
		{
		response_0810 =header_msg+"0810"+transmition_date_time+delimiter+system_trace
			+delimiter+time_local_transaction+delimiter+date_local_transaction
			+delimiter+response_code+delimiter+security_control_information
			+delimiter+network_mng_info_code;

			return response_0810;

		}
		
		if((strncmp(msg_type, "0100", 4)) == 0)
		{	
		response_0110 ="EB90410110"+processing_code+delimiter+transaction_amount
			+delimiter+settlement_amount+delimiter+conversion_rate_settlement+delimiter
			+date_convertion+delimiter+amount_trans_fee+delimiter+amount_settlement_fee	
			+delimiter+amount_trans_proce_fee+delimiter+amount_settle_proecessing_fee
			+delimiter+autorization_id_response+delimiter+response_code+delimiter
			+additional_response_data+delimiter+track_1+delimiter+additional_data+delimiter
			+additional_amount+delimiter+authorizing_agent_id_code+delimiter+echo_data 
			+delimiter+account_identification1+delimiter+account_identification2+delimiter
			+authorization_profile+delimiter+retention_data+delimiter+address_verificaction_result
			+delimiter+cardholder_information+delimiter+authorizaer_date_settlement+delimiter
			+card_verification_result+delimiter+secure_retail;

			return response_0110;
	
		}
			if((strncmp(msg_type, "0200", 4)) == 0)
		{	
		response_0210 ="EB90410210"+processing_code+delimiter+transaction_amount
			+delimiter+settlement_amount+delimiter+conversion_rate_settlement+delimiter
			+date_convertion+delimiter+amount_trans_fee+delimiter+amount_settlement_fee	
			+delimiter+amount_trans_proce_fee+delimiter+amount_settle_proecessing_fee
			+delimiter+autorization_id_response+delimiter+response_code+delimiter
			+additional_response_data+delimiter+track_1+delimiter+additional_data+delimiter
			+additional_amount+delimiter+authorizing_agent_id_code+delimiter+echo_data 
			+delimiter+account_identification1+delimiter+account_identification2+delimiter
			+authorization_profile+delimiter+retention_data+delimiter+address_verificaction_result
			+delimiter+cardholder_information+delimiter+authorizaer_date_settlement+delimiter
			+card_verification_result+delimiter+secure_retail;

			return response_0210;
		}
		
		if((strncmp(msg_type, "0420", 4)) == 0)
		{	
		response_0430 ="EB90410430"+processing_code+delimiter+transaction_amount
			+delimiter+settlement_amount+delimiter+conversion_rate_settlement+delimiter
			+date_convertion+delimiter+amount_trans_fee+delimiter+amount_settlement_fee	
			+delimiter+amount_trans_proce_fee+delimiter+amount_settle_proecessing_fee
			+delimiter+autorization_id_response+delimiter+response_code+delimiter
			+additional_response_data+delimiter+track_1+delimiter+additional_data+delimiter
			+additional_amount+delimiter+authorizing_agent_id_code+delimiter+echo_data 
			+delimiter+account_identification1+delimiter+account_identification2+delimiter
			+authorization_profile+delimiter+retention_data+delimiter+address_verificaction_result
			+delimiter+cardholder_information+delimiter+authorizaer_date_settlement+delimiter
			+card_verification_result+delimiter+secure_retail;

			return response_0430;
		}
		return RWCString("n");


}
		
RWCString Retorno_100_200_B24(RWCString incoming , char *msg_type)
{
	processing_code						= "";
//	additional_data_063					= "";
	transaction_amount					= "";
	transmition_date_time				= "";
	system_trace_011					= "";
	time_local_transaction_012			= "";
	date_local_transaction_013			= "";		
	expiration_date_014					= "";					
	date_settlement_015					= "";
	capture_date_017					= "";
	pos_entry_mode_022					= "";
	pos_condition_code_025				= "";
	acquiring_institution_id_code_032	= "";
	track_2_035							= "";
	retrieval_reference_number_037		= "";
	responde_code_039					= "";
	card_acceptor_terminal_id_041		= "";	
	card_acceptor_id_code_042			= "";		
	card_acceptor_name_location_043		= "";
	track_1_045							= "";
	addditional_data_048				= "";
	pin_data_052						= "";
	pos_terminal_data_060				= "";
	card_issuer_response_data_061		= "";
	additional_data_063					= "";
	receiving_institution_id_code_0100	= "";
	authorization_indicators_0121		= "";
	batch_record2_0124					= "";
	pos_settlement_data_125			= "";
	preauthorization_data_0126			= "";
	RWCString lllvar					= "";
	RWCString llvar						= "";
	int next_field_last = 0;		
	RWCString hex_bit = incoming(18,32);
//	cout << "Valor de bitmap > " << incoming(18,32) << endl;
	
	if((strncmp(msg_type, "0200", 4) == 0))
	{
		if(hex_bit(0,1) == "B")// bit 1,2,3,4
		{
			//cout << "el valor de caracter #00 >" << hex_bit(0,1) << endl; 
			processing_code					= incoming(50,6);   //03   
			next_field_last					= 56;
			transaction_amount				= incoming(next_field_last,12);	//04
			next_field_last					= next_field_last+12;
		}
	
		if(hex_bit(1,1) == "2")// bit 5,6,7,8
		{
			//cout << "el valor de caracter #01 >" << hex_bit(1,1) << endl; 
			transmition_date_time			= incoming(next_field_last,10);	//07     		
			next_field_last					= next_field_last+10;
		}

		if(hex_bit(2,1) == "3")// bit 9,10,11,12
		{
			//cout << "el valor de caracter #02 >" << hex_bit(2,1) << endl; 
			system_trace_011					= incoming(next_field_last,6);	//011     		
			time_local_transaction_012			= incoming((next_field_last+6),6);	//012     		
			next_field_last						= next_field_last+6+6;
		}
		
		if(hex_bit(3,1) == "E")// bit 13,14,15,16
		{
			//cout << "el valor de caracter #03 >" << hex_bit(3,1) << endl; 
			date_local_transaction_013			= incoming(next_field_last,4);	//013 
			expiration_date_014					= incoming((next_field_last+4),4);	//014 
			date_settlement_015					= incoming((next_field_last+4+4),4);	//015 
			next_field_last						= next_field_last+4+4+4;	
		}
		
		if(hex_bit(3,1) == "8")// bit 13,14,15,16
		{
			//cout << "el valor de caracter #03 >" << hex_bit(3,1) << endl; 
			date_local_transaction_013			= incoming(next_field_last,4);	//013 
			next_field_last						= next_field_last+4;
		}
	
		if(hex_bit(4,1) == "8")// bit 17,18,19,20
		{
			//cout << "el valor de caracter #04 >" << hex_bit(4,1) << endl; 
			capture_date_017					= incoming(next_field_last,4);	//017 
			next_field_last						= next_field_last+4;
		}

	
		if(hex_bit(5,1) == "4")// bit 21,22,23,24
		{
			//cout << "el valor de caracter #05 >" << hex_bit(5,1) << endl; 
			pos_entry_mode_022					= incoming(next_field_last,3);	//022 
			next_field_last						= next_field_last+3;
		}
		
	
		
		if(hex_bit(6,1) == "0")// bit 25,26,27,28
		{
			//cout << "el valor de caracter #06 >" << hex_bit(6,1) << endl; 
			//pos_entry_mode_022					= incoming(106,3);	 
			
		}
	
		int field32 = 0;
		if(hex_bit(7,1) == "1")// bit 29,30,31,32
		{
			//cout << "el valor de caracter #07 >" << hex_bit(7,1) << endl; 
			llvar		= incoming(next_field_last,2);	//032 
			field32 = atoi(llvar);
			acquiring_institution_id_code_032		 = incoming((next_field_last+2),field32);	//032 
			next_field_last							 = next_field_last+2+field32;
		}
	
		int field35 = 0;
		if(hex_bit(8,1) == "2")// bit 33,34,35,36
		{
			//cout << "el valor de caracter #08 >" << hex_bit(8,1) << endl; 
			llvar								= incoming(next_field_last,2);	//035 
			field35 = atoi(llvar);
			track_2_035 = incoming((next_field_last+2),field35);
			next_field_last = next_field_last+2+field35;
		}

		int next_field_039 = 0;
		
		if(hex_bit(9,1) == "A")// bit 37,38,39,40
		{
			
			retrieval_reference_number_037 = incoming(next_field_last,12);
			responde_code_039			   = incoming((next_field_last+12),2);
			next_field_last				   = next_field_last+12+2;
			

			//cout << "el valor de caracter #09 >" << hex_bit(9,1) << endl; 
	
		}
		if(hex_bit(9,1) == "8")// bit 37,38,39,40
		{
			
			retrieval_reference_number_037 = incoming(next_field_last,12);
			next_field_last				   = next_field_last+12;
			

			//cout << "el valor de caracter #09 >" << hex_bit(9,1) << endl; 
	
		}
	


		int next_field_043 = 0;
		if(hex_bit(10,1) == "E")// bit 41,42,43,44
		{
			
			card_acceptor_terminal_id_041	= incoming(next_field_last,16);
			card_acceptor_id_code_042		= incoming((next_field_last+16),15);
			card_acceptor_name_location_043	= incoming((next_field_last+16+15),40);
			next_field_last					= next_field_last+16+15+40;
			

			//cout << "el valor de caracter #10 >" << hex_bit(10,1) << endl; 
	
			}
	
		int field45= 0;
		int field48 = 0;
		
		int next_field_048 = 0;
		
		if(hex_bit(11,1) == "1")// bit 45,46,47,48
		{
		
			lllvar							= incoming(next_field_last,3);
			field48							= atoi(lllvar);
			addditional_data_048			= incoming((next_field_last+3),field48);
			next_field_last					= next_field_last+3+field48;
			

			//cout << "el valor de caracter #11 >" << hex_bit(11,1) << endl; 
	
			//cout << "el valor de next_field_043 > " << next_field_043 << endl;
		}
	
		if(hex_bit(11,1) == "9")// bit 45,46,47,48
		{
		
			llvar							= incoming(next_field_last,2);
			field45							= atoi(llvar);
			track_1_045						= incoming((next_field_last+2),field45);
			next_field_last					= next_field_last+2+field45;
			
			lllvar							= incoming(next_field_last,3);
			field48							= atoi(lllvar);
			addditional_data_048			= incoming((next_field_last+3),field48);
			next_field_last					= next_field_last+3+field48;
			

			//cout << "el valor de caracter #11 >" << hex_bit(11,1) << endl; 
	
			//cout << "el valor de next_field_043 > " << next_field_043 << endl;
		}
	
		int next_field_052 = 0;
		if(hex_bit(12,1) == "9")// bit 49,50,51,52
		{
		
			currency_code_transaction_049	= incoming(next_field_last,3);
			pin_data_052					= incoming((next_field_last+3),16);
			next_field_last					= next_field_last+3+16;
			

			//cout << "el valor de caracter #12 >" << hex_bit(12,1) << endl; 
	
		}
	
		if(hex_bit(13,1) == "0")// bit 53,54,55,56
		{
		
		
			//cout << "el valor de caracter #13 >" << hex_bit(13,1) << endl; 
	
		}
		if(hex_bit(13,1) == "4")// bit 53,54,55,56
		{
		
			

			//cout << "el valor de caracter #13 >" << hex_bit(13,1) << endl; 
		}
	
		int field60 = 0;
		int next_field_060 = 0;
		if(hex_bit(14,1) == "1")// bit 57,58,59,60
		{
		
			lllvar							= incoming(next_field_last,3);
			field60							= atoi(lllvar);
			pos_terminal_data_060				= incoming((next_field_last+3),field60);
			next_field_last					= next_field_last+3+field60;
			//cout << "el valor de caracter #14 >" << hex_bit(14,1) << endl; 
		}
		
		int field61 = 0;
		int field63 = 0;
		if(hex_bit(15,1) == "A")// bit 61,62,63,64
		{
		
			lllvar							= incoming(next_field_last,3);
			field61							= atoi(lllvar);
			card_issuer_response_data_061	= incoming((next_field_last+3),field61);
		
			lllvar							= incoming((next_field_last+3+field61),3);
			field63							= atoi(lllvar);
			additional_data_063				= incoming((next_field_last+3+field61+3),field63);
			
			next_field_last					= next_field_last+3+field61+3+field63;
			
			//cout << "el valor del caracter #15 >" << hex_bit(15,1) << endl; 
	
		}
		
		
		if(hex_bit(15,1) == "8")// bit 61,62,63,64
		{
		
			lllvar							= incoming(next_field_last,3);
			field61							= atoi(lllvar);
			card_issuer_response_data_061	= incoming((next_field_last+3),field61);
			next_field_last					= next_field_last+3+field61;	

			//cout << "el valor de caracter #15 >" << hex_bit(15,1) << endl; 
			
		}		
		
		if(hex_bit(16,1) == "0")// bit 65,66,67,68
		{
		
			

			//cout << "el valor de caracter #16 >" << hex_bit(16,1) << endl; 
	
		}
		if(hex_bit(17,1) == "0")// bit 69,70,71,72
		{
		
			

			//cout << "el valor de caracter #17 >" << hex_bit(17,1) << endl; 
	
		}
		if(hex_bit(18,1) == "0")// bit 73,74,75,76
		{
		
			

			//cout << "el valor de caracter #18 >" << hex_bit(18,1) << endl; 
	
		}
		
		if(hex_bit(19,1) == "0")// bit 77,78,79,80
		{
		
			

			//cout << "el valor de caracter #19 >" << hex_bit(19,1) << endl; 
	
		}
		
		if(hex_bit(20,1) == "0")// bit 81,82,83,84
		{
		
			

			//cout << "el valor de caracter #20 >" << hex_bit(20,1) << endl; 
	
		}
		
		if(hex_bit(21,1) == "0")// bit 85,86,87,88
		{
		
			

			//cout << "el valor de caracter #21 >" << hex_bit(21,1) << endl; 
	
		}
		
		if(hex_bit(22,1) == "0")// bit 89,90,91,92
		{
		
			

			//cout << "el valor de caracter #22 >" << hex_bit(22,1) << endl; 
	
		}
		
		if(hex_bit(23,1) == "0")// bit 93,94,95,96
		{
		
			

			//cout << "el valor de caracter #23 >" << hex_bit(23,1) << endl; 
	
		}
		int field100 = 0;
		if(hex_bit(24,1) == "1")// bit 97,98,99,100
		{
		
			llvar = incoming(next_field_last,2);
			field100 = atoi(llvar);
			receiving_institution_id_code_0100 = incoming((next_field_last+2),field100);
			
			next_field_last = next_field_last+2+field100;
		
			//cout << "el valor de caracter #24 >" << hex_bit(24,1) << endl; 
	
		}

		if(hex_bit(25,1) == "0")// bit 101,102,103,104
		{
		
			//cout << "el valor de caracter #25 >" << hex_bit(25,1) << endl; 
	
		}

		if(hex_bit(26,1) == "0")// bit 105,106,107,108
		{
		
			

			//cout << "el valor de caracter #26 >" << hex_bit(26,1) << endl; 
	
		}
		
		if(hex_bit(27,1) == "0")// bit 109,110,111,112
		{
		
			

			//cout << "el valor de caracter #27 >" << hex_bit(27,1) << endl; 
	
		}
		
		if(hex_bit(28,1) == "0")// bit 113,114,115,116
		{
		
			

			//cout << "el valor de caracter #28 >" << hex_bit(28,1) << endl; 
	
		}
		
		if(hex_bit(29,1) == "0")// bit 117,118,119,120
		{
		
			

			//cout << "el valor de caracter #29 >" << hex_bit(29,1) << endl; 
	
		
		}
		
		
		int field121 = 0;
		int field124 = 0;
		if(hex_bit(30,1) == "9")// bit 121,122,123,124
		{
			
			lllvar							= incoming(next_field_last,3);
			field121						= atoi(lllvar);
			authorization_indicators_0121	= incoming((next_field_last+3),field121);
			
			lllvar							= incoming((next_field_last+3+field121),3);
			field124						= atoi(lllvar);
			batch_record2_0124				= incoming((next_field_last+3+field121+3),field124);
			next_field_last					= next_field_last+3+field121+3+field124;
			
			
			//cout << "el valor de caracter #30 >" << hex_bit(30,1) << endl; 
	
		
		}
		if(hex_bit(30,1) == "1")// bit 121,122,123,124
		{
			
			lllvar							= incoming(next_field_last,3);
			field124						= atoi(lllvar);
			batch_record2_0124				= incoming((next_field_last+3),field124);
			next_field_last					= next_field_last+3+field124;
			
			
			
			//cout << "el valor de caracter #30 >" << hex_bit(30,1) << endl; 
	
		
		}
		int field125 = 0;
		int field126 = 0;
		
		if(hex_bit(31,1) == "C")// bit 125,126,127,128
		{
			
			lllvar							= incoming(next_field_last,3);
			field125						= atoi(lllvar);
			pos_settlement_data_125		= incoming((next_field_last+3),field125);
			
			lllvar							= incoming((next_field_last+3+field125),3);
			field126						= atoi(lllvar);
			preauthorization_data_0126		= incoming((next_field_last+3+field125+3),field126);
			next_field_last					= next_field_last+3+field125+3+field126;
			
			
			//cout << "el valor de caracter #31 >" << hex_bit(31,1) << endl; 
	
		
		}
		if(hex_bit(31,1) == "4")// bit 125,126,127,128
		{
			
			
			lllvar							= incoming(next_field_last,3);
			field126						= atoi(lllvar);
			preauthorization_data_0126		= incoming((next_field_last+3),field126);
			next_field_last					= next_field_last+3+field126;
			
			
			//cout << "el valor de caracter #31 >" << hex_bit(31,1) << endl; 
	
		
		}
		if(hex_bit(31,1) == "0")// bit 125,126,127,128
		{
			
			
			
			//cout << "el valor de caracter #31 >" << hex_bit(31,1) << endl; 
	
		
		}

		
		/*	
		cout << "<*ISO* value       =<"	 << incoming(2,3)			<< ">" << endl;  
		cout << "<*Product* value   =<"	 << incoming(5,2)			<< ">" << endl;  
		cout << "<*Release* value   =<"	 << incoming(7,2)			<< ">" << endl;  
		cout << "<*Status* value    =<"	 << incoming(9,3)			<< ">" << endl;  
		cout << "<*Originator* value=<" << incoming(12,1)			<< ">" << endl;  
		cout << "<*Responder* value =<"	 << incoming(13,1)			<< ">" << endl;  
		
		
		cout << "<field id=*3* value=<"   << processing_code				<< ">" << endl;  
		cout << "<field id=*4* value=<"   << transaction_amount				<< ">" << endl; 
		cout << "<field id=*7* value=<"   << transmition_date_time			<< ">" << endl;
		cout << "<field id=*11* value=<"  << system_trace_011				<< ">" << endl; 
	
		cout << "<field id=*12* value=<"  << time_local_transaction_012		<< ">" << endl; 
		cout << "<field id=*13* value=<"  << date_local_transaction_013			<< ">" << endl;
		cout << "<field id=*14* value=<"  << expiration_date_014			<< ">" << endl; 
		cout << "<field id=*15* value=<"  << date_settlement_015			<< ">" << endl; 
	
		cout << "<field id=*17* value=<"  << capture_date_017				<< ">" << endl; 
		cout << "<field id=*22* value=<"  << pos_entry_mode_022					<< ">" << endl; 
		cout << "<field id=*32* value=<"   << acquiring_institution_id_code_032 	<< ">" << endl;  
		cout << "<field id=*35* value=<"   << track_2_035 	<< ">" << endl;  
		cout << "<field id=*37* value=<"   << retrieval_reference_number_037 	<< ">" << endl;  
		cout << "<field id=*39* value=<"   <<	responde_code_039		<< ">" << endl;  
		//cout << "<field id=*40* value=<"   << service_resytricion_code 	<< ">" << endl;  
		cout << "<field id=*41* value=<"   << card_acceptor_terminal_id_041 	<< ">" << endl;  
                                    
		cout << "<field id=*42* value=<"   << card_acceptor_id_code_042 	<< ">" << endl;  
		cout << "<field id=*43* value=<"   << card_acceptor_name_location_043 	<< ">" << endl;  
		cout << "<field id=*45* value=<"   << track_1_045 	<< ">" << endl;  
		cout << "<field id=*48* value=<"   << addditional_data_048 	<< ">" << endl;  
		cout << "<field id=*49* value=<"   << currency_code_transaction_049 	<< ">" << endl;  
        cout << "<field id=*52* value=<"   << pin_data_052 	<< ">" << endl;  
        cout << "<field id=*60* value=<"   << terminal_data_060 	<< ">" << endl;  
		cout << "<field id=*61* value=<"   << card_issuer_response_data_061 	<< ">" << endl;  
        cout << "<field id=*63* value=<"   << additional_data_063 	<< ">" << endl;  
        cout << "<field id=*100* value=<"   << receiving_institution_id_code_0100 	<< ">" << endl;  
        cout << "<field id=*121* value=<"   << authorization_indicators_0121 	<< ">" << endl;  
	    cout << "<field id=*124* value=<"   << batch_record2_0124 	<< ">" << endl;  
		cout << "<field id=*125* value=<"   << settlemente_record2_0125 	<< ">" << endl;  
        cout << "<field id=*126* value=<"   << preauthorization_data_0126 	<< ">" << endl;  
              
		*/	
			
		//With this routine we calculated the var field to be sent in the response/////////////////
		////////////////////////////////////////////////////////////////

		int llvar_032		 = acquiring_institution_id_code_032.length();	
		int llvar_035	     = track_2_035.length();
		int llvar_045	     = track_1_045.length();
		
		int lllvar_048		 = addditional_data_048.length();
		int lllvar_060		 = pos_terminal_data_060.length();
		int lllvar_061		 = card_issuer_response_data_061.length();
		int lllvar_063		 = additional_data_063.length();
		int llvar_0100		 = receiving_institution_id_code_0100.length();
		int lllvar_0121		 = authorization_indicators_0121.length();
		int lllvar_0124		 = batch_record2_0124.length();
		int lllvar_0125		 = pos_settlement_data_125.length();
		int lllvar_0126		 = preauthorization_data_0126.length();

	
		char buffer_032[200] = {""};
		char buffer_035[200] = {""};
		char buffer_045[200] = {""};
		char buffer_048[200] = {""};
		char buffer_060[200] = {""};
		char buffer_061[200] = {""};
		char buffer_063[200] = {""};
		char buffer_0100[200] = {""};
		char buffer_0121[200] = {""};
		char buffer_0124[200] = {""};
		char buffer_0125[200] = {""};
		char buffer_0126[200] = {""};
		

		itoa(llvar_032,buffer_032,10);
		itoa(llvar_035,buffer_035,10);
		itoa(llvar_045,buffer_045,10);
		itoa(lllvar_048,buffer_048,10);
		itoa(lllvar_060,buffer_060,10);
		itoa(lllvar_061,buffer_061,10);
		itoa(lllvar_063,buffer_063,10);
		itoa(llvar_0100,buffer_0100,10);
		itoa(lllvar_0121,buffer_0121,10);
		itoa(lllvar_0124,buffer_0124,10);
		itoa(lllvar_0125,buffer_0125,10);
		itoa(lllvar_0126,buffer_0126,10);
			

		RWCString buffer_032_llvar2 = "0";
		RWCString buffer_048_lllvar2 = "0";
		RWCString buffer_cero = "0";
	


		RWCString buffer_032_llvar		= "";
		RWCString buffer_045_llvar		= "";
		RWCString buffer_048_lllvar		= "";
		RWCString buffer_060_lllvar		= "";
		RWCString buffer_061_lllvar		= "";
		RWCString buffer_063_lllvar		= "";
		RWCString buffer_0100_llvar		= "";
		RWCString buffer_0121_lllvar	= "";
		RWCString buffer_0124_lllvar	= "";
		RWCString buffer_0125_lllvar	= "";
		RWCString buffer_0126_lllvar	= "";
		
		////////////////////////////////////////////////////////////////////////
		if(llvar_032 <= 9)
		{
			buffer_032_llvar = buffer_032_llvar2+buffer_032;
		}
		else
		{
			buffer_032_llvar = buffer_032;
		}
		

		////////////////////////////////////////////////////////////////////////
		if(llvar_045 <= 9)
		{
			buffer_045_llvar = buffer_cero+buffer_045;
		}
		else
		{
			buffer_045_llvar = buffer_045;
		}

		///////////////////////////////////////////////////////////////////////
		if(lllvar_048 <= 9)
		{
			buffer_048_lllvar = buffer_cero+buffer_cero+buffer_048;
		}
				
		if(lllvar_048 <= 99)
		{
			buffer_048_lllvar = buffer_048_lllvar2+buffer_048;
		}
		else
		{
				buffer_048_lllvar = buffer_048;
		}
		
		
		///////////////////////////////////////////////////////////////////////
		if(lllvar_060 <= 9)
		{
			buffer_060_lllvar = buffer_cero+buffer_cero+buffer_060;
		}
	
		if(lllvar_060 <= 99)
		{
			buffer_060_lllvar = buffer_cero+buffer_060;
		}
		else
		{
				buffer_060_lllvar = buffer_060;
		}
		
		/////////////////////////////////////////////////////////////////////////
		if(lllvar_061 <= 9)
		{
			buffer_061_lllvar = buffer_cero+buffer_cero+buffer_061;
		}
		
		if(lllvar_061 <= 99)
		{
			buffer_061_lllvar = buffer_cero+buffer_061;
		}
		else
		{
				buffer_061_lllvar = buffer_061;
		}
		
		/////////////////////////////////////////////////////////////////////////
		if(lllvar_063 <= 9)
		{
			buffer_063_lllvar = buffer_cero+buffer_cero+buffer_063;
		}		

		if(lllvar_063 <= 99)
		{
			buffer_063_lllvar = buffer_cero+buffer_063;
		}
		else
		{
				buffer_063_lllvar = buffer_063;
		}
		
		/////////////////////////////////////////////////////////////////////////
		if(llvar_0100 <= 9)
		{
				buffer_0100_llvar = buffer_cero+buffer_0100;
		}
		else
		{
				buffer_0100_llvar = buffer_0100;
		}
	
		//////////////////////////////////////////////////////////////////////////		
		if(lllvar_0121 <= 9)
		{
				buffer_0121_lllvar = buffer_cero+buffer_cero+buffer_0121;
		}
		
		if(lllvar_0121 <= 99)
		{
				buffer_0121_lllvar = buffer_cero+buffer_0121;
		}
		else
		{
				buffer_0121_lllvar = buffer_0121;
		}
		///////////////////////////////////////////////////////////////////////////
		if(lllvar_0124 <= 9)
		{
				buffer_0124_lllvar = buffer_cero+buffer_cero+buffer_0124;
				
				//cout << "Valor de buffer_0124_lllvar 1> " << buffer_0124_lllvar << endl;
		
		}
		
		else if((lllvar_0124 > 9) &&  (lllvar_0124 <= 99))
		{
				buffer_0124_lllvar = buffer_cero+buffer_0124;
				//cout << "Valor de buffer_0124_lllvar> " << buffer_0124_lllvar << endl;
		
		
		}
		
		
		else 
		{
				buffer_0124_lllvar = buffer_0124;
			//	cout << "Valor de buffer_0124_lllvar 2> " << buffer_0124_lllvar << endl;
		
		
		
		}
		
			///////////////////////////////////////////////////////////////////////////
		if(lllvar_0125 <= 9)
		{
				buffer_0125_lllvar = buffer_cero+buffer_cero+buffer_0125;
				
				//cout << "Valor de buffer_0125_lllvar 1> " << buffer_0125_lllvar << endl;
		
		}
		
		else if((lllvar_0125 > 9) &&  (lllvar_0125 <= 99))
		{
				buffer_0125_lllvar = buffer_cero+buffer_0125;
				//cout << "Valor de buffer_0125_lllvar> " << buffer_0125_lllvar << endl;
		
		
		}
		
		
		else 
		{
				buffer_0125_lllvar = buffer_0125;
				//cout << "Valor de buffer_0125_lllvar 2> " << buffer_0125_lllvar << endl;
		
		
		
		}

		///////////////////////////////////////////////////////////////////////////
		if(lllvar_0126 <= 9)
		{
				buffer_0126_lllvar = buffer_cero+buffer_cero+buffer_0126;
				
				//cout << "Valor de buffer_0126_lllvar 1> " << buffer_0126_lllvar << endl;
		
		}
		
		else if((lllvar_0126 > 9) &&  (lllvar_0126 <= 99))
		{
				buffer_0126_lllvar = buffer_cero+buffer_0126;
				//cout << "Valor de buffer_0126_lllvar> " << buffer_0126_lllvar << endl;
		
		
		}
		
		
		else 
		{
				buffer_0126_lllvar = buffer_0126;
				//cout << "Valor de buffer_0126_lllvar 2> " << buffer_0126_lllvar << endl;
		
		
		
		}
		////////////////////////////////////////////////////////////////////////////		
		////////////////////////////////////////////////////////////////////////////
		response_0210 = "";
		
			
		if (incoming(5,2) == "02")
		{
				
			RWCString bit_map_0210 = "B23884012AE1901A000000001000009C";
		
			response_0210 = incoming(2,3)+incoming(5,2)+incoming(7,2)+incoming(9,3)+incoming(12,1)
						+incoming(13,1)+"0210"+bit_map_0210+processing_code+transaction_amount
						+transmition_date_time+system_trace_011+time_local_transaction_012+date_local_transaction_013
						+capture_date_017+pos_entry_mode_022+RWCString(buffer_032_llvar)
						+acquiring_institution_id_code_032+RWCString(buffer_035)+track_2_035
						+retrieval_reference_number_037+responde_code_039+card_acceptor_terminal_id_041
						+card_acceptor_id_code_042+card_acceptor_name_location_043+buffer_048_lllvar
						+addditional_data_048+currency_code_transaction_049+pin_data_052+buffer_060_lllvar
						+pos_terminal_data_060+buffer_061_lllvar+card_issuer_response_data_061
						+buffer_063_lllvar+additional_data_063+buffer_0100_llvar+receiving_institution_id_code_0100
						+buffer_0121_lllvar+authorization_indicators_0121+buffer_0124_lllvar
						+batch_record2_0124+buffer_0125_lllvar+pos_settlement_data_125
						+buffer_0126_lllvar+preauthorization_data_0126;
		
						return response_0210;
		}
		if (incoming(5,2) == "01")
		{
				
			responde_code_039 = "00";
			RWCString bit_map_0210 = "B23880012EE190180000000010000010";
			
			response_0210 = incoming(2,3)+incoming(5,2)+incoming(7,2)+incoming(9,3)+incoming(12,1)
						+incoming(13,1)+"0210"+bit_map_0210+processing_code+transaction_amount
						+transmition_date_time+system_trace_011+time_local_transaction_012+date_local_transaction_013
						+capture_date_017+pos_entry_mode_022+RWCString(buffer_032_llvar)
						+acquiring_institution_id_code_032+RWCString(buffer_035)+track_2_035
						+retrieval_reference_number_037+"000000"+responde_code_039+card_acceptor_terminal_id_041
					
						+card_acceptor_id_code_042+card_acceptor_name_location_043+buffer_048_lllvar
						+addditional_data_048+currency_code_transaction_049+pin_data_052+buffer_060_lllvar
						+pos_terminal_data_060+buffer_061_lllvar+card_issuer_response_data_061
						+buffer_0100_llvar+receiving_institution_id_code_0100
						+buffer_0124_lllvar+batch_record2_0124+buffer_0126_lllvar+preauthorization_data_0126;
		
						return response_0210;
		}


	}
	response_0810 = "";

	if((strncmp(msg_type, "0800", 4) == 0))
	{
		header_msg						= incoming(2,12);   //02
		msg_type_identifier				= incoming(14,4);   //02
		bit_map_b24						= incoming(18,32);  //02
		transmition_date_time			= incoming(50,10);	//07     		
		system_trace					= incoming(60,6);	//11				
		network_mng_info_code			= incoming(66,3);	//70
		
	}
	

		char hex1c_2 = 0x1C;
		RWCString delimiter = hex1c_2;
		RWCString autorization_id_response = "000000";						//038//
		RWCString response_code = "00";										//039//
		RWCString additional_response_data = "Esto es el campo 44      " ;	//044//


/*048*/ RWCString additional_data = "1239999999999                                                                                                                                                                                                                                                                                                                                                           ";
		RWCString authorizing_agent_id_code = "00000000000";				//058//
		RWCString authorization_profile = "00";								/*127.6*/
/*127.8*/RWCString retention_data = "                                                                                                                                ";
		RWCString address_verificaction_result = " ";						/*127.16*/
/*127.17*/RWCString cardholder_information = "                                                  ";
		RWCString authorizaer_date_settlement = "        ";					/*127.20*/	
    	RWCString secure_retail = " ";										/*127.30*/
		RWCString security_control_information = "                                                "; //048//
		
		RWCString bit_map_810 = "82200000020000000400000000000000";
		RWCString end_of_type = '\x03';
		if((strncmp(msg_type, "0800", 4)) == 0)
		{
		response_0810 =header_msg+"0810"+bit_map_810+transmition_date_time+system_trace
			+"00"+network_mng_info_code+end_of_type;
			
			return response_0810;

		}
		
	
		return RWCString("n");


}

/*
RWCString Retorno_110_210_B24(RWCString incoming , char *msg_type)
{
	processing_code_03						= "";
	additional_data_063						= "";
	transaction_amount_04					= "";
	transmition_date_time_07				= "";
	system_trace_011					= "";
	time_local_transaction_012			= "";
	date_local_transaction_013			= "";		
	expiration_date_014					= "";					
	date_settlement_015					= "";
	capture_date_017					= "";
	merchant_type_018					= "";
	pos_entry_mode_022					= "";

	pos_condition_code_025				= "";
	acquiring_institution_id_code_032	= "";
	track_2_035							= "";
	retrieval_reference_number_037		= "";
	responde_id_response_038            = "";
	responde_code_039					= "";
	card_acceptor_terminal_id_041		= "";	
	card_acceptor_id_code_042			= "";		
	card_acceptor_name_location_043		= "";
	track_1_045							= "";
	addditional_data_048				= "";
	currency_code_transaction_049       = "";
	pin_data_052						= "";
	pos_terminal_data_060				= "";
	card_issuer_response_data_061		= "";
	additional_data_063					= "";
	receiving_institution_id_code_0100	= "";
	pos_terminal_address_branch_120		= "";
	authorization_indicators_0121		= "";
	batch_record2_0124					= "";
	pos_settlement_data_125				= "";
	preauthorization_data_0126			= "";
	switch_key_127						= "";
	RWCString lllvar					= "";
	RWCString llvar						= "";
	int next_field_last = 0;		
	RWCString hex_bit = incoming(18,32);
//	cout << "Valor de bitmap > " << incoming(18,32) << endl;
	
	if((strncmp(msg_type, "0210", 4) == 0))
	{
		if(hex_bit(0,1) == "B")// bit 1,2,3,4
		{
			//cout << "el valor de caracter #00 >" << hex_bit(0,1) << endl; 
			processing_code_03					= incoming(50,6);   //03   
			next_field_last					= 56;
			transaction_amount_04				= incoming(next_field_last,12);	//04
			next_field_last					= next_field_last+12;
		}
	
		if(hex_bit(1,1) == "2")// bit 5,6,7,8
		{
			//cout << "el valor de caracter #01 >" << hex_bit(1,1) << endl; 
			transmition_date_time_07			= incoming(next_field_last,10);	//07     		
			next_field_last					= next_field_last+10;
		}

		if(hex_bit(2,1) == "3")// bit 9,10,11,12
		{
			//cout << "el valor de caracter #02 >" << hex_bit(2,1) << endl; 
			system_trace_011					= incoming(next_field_last,6);	//011     		
			time_local_transaction_012			= incoming((next_field_last+6),6);	//012     		
			next_field_last						= next_field_last+6+6;
		}
	
		if(hex_bit(2,1) == "7")// bit 9,10,11,12
		{
			//cout << "el valor de caracter #02 >" << hex_bit(2,1) << endl; 
		
			convertion_rate_010					= incoming(next_field_last,8);		//010
			system_trace_011					= incoming((next_field_last,8),6);	//011     		
			time_local_transaction_012			= incoming((next_field_last+8+6),6);//012     		
			next_field_last						= next_field_last+8+6+6;
		}
	

		if(hex_bit(3,1) == "E")// bit 13,14,15,16
		{
			//cout << "el valor de caracter #03 >" << hex_bit(3,1) << endl; 
			date_local_transaction_013			= incoming(next_field_last,4);	//013 
			expiration_date_014					= incoming((next_field_last+4),4);	//014 
			date_settlement_015					= incoming((next_field_last+4+4),4);	//015 
			next_field_last						= next_field_last+4+4+4;	
		}
		
		if(hex_bit(3,1) == "8")// bit 13,14,15,16
		{
			//cout << "el valor de caracter #03 >" << hex_bit(3,1) << endl; 
			date_local_transaction_013			= incoming(next_field_last,4);	//013 
			next_field_last						= next_field_last+4;
		}
	
		if(hex_bit(3,1) == "C")// bit 13,14,15,16
		{
			//cout << "el valor de caracter #03 >" << hex_bit(3,1) << endl; 
			date_local_transaction_013			= incoming(next_field_last,4);	//013 
			expiration_date_014					= incoming((next_field_last+4),4);	//014 
			//date_settlement_015					= incoming((next_field_last+4+4),4);	//015 
			next_field_last						= next_field_last+4+4;	
		}

		if(hex_bit(4,1) == "8")// bit 17,18,19,20
		{
			//cout << "el valor de caracter #04 >" << hex_bit(4,1) << endl; 
			capture_date_017					= incoming(next_field_last,4);	//017 
			next_field_last						= next_field_last+4;
		}

		if(hex_bit(4,1) == "C")// bit 17,18,19,20
		{
			//cout << "el valor de caracter #04 >" << hex_bit(4,1) << endl; 
			capture_date_017					= incoming(next_field_last,4);	//017 
			merchant_type_018					= incoming((next_field_last+4),4);
			next_field_last						= next_field_last+4+4;


		}


		if(hex_bit(5,1) == "4")// bit 21,22,23,24
		{
			//cout << "el valor de caracter #05 >" << hex_bit(5,1) << endl; 
			pos_entry_mode_022					= incoming(next_field_last,3);	//022 
			next_field_last						= next_field_last+3;
		}
	
		if(hex_bit(5,1) == "5")// bit 21,22,23,24
		{
			//cout << "el valor de caracter #05 >" << hex_bit(5,1) << endl; 
			pos_entry_mode_022					= incoming(next_field_last,3);	//022 
			for_athd_024						= incoming((next_field_last+3),3);	//024 
			next_field_last						= next_field_last+3+3;
		}
	

		if(hex_bit(6,1) == "8")// bit 25,26,27,28
		{
			//cout << "el valor de caracter #06 >" << hex_bit(6,1) << endl; 
			 pos_condition_code_025				= incoming(next_field_last,2);	//025 
			 next_field_last					= next_field_last+2;
			 //pos_entry_mode_022					= incoming(106,3);	 
			
		}
	
		int field32 = 0;
		if(hex_bit(7,1) == "1")// bit 29,30,31,32
		{
			//cout << "el valor de caracter #07 >" << hex_bit(7,1) << endl; 
			llvar		= incoming(next_field_last,2);	//032 
			field32 = atoi(llvar);
			acquiring_institution_id_code_032		 = incoming((next_field_last+2),field32);	//032 
			next_field_last							 = next_field_last+2+field32;
		}
	
		int field35 = 0;
		if(hex_bit(8,1) == "2")// bit 33,34,35,36
		{
			//cout << "el valor de caracter #08 >" << hex_bit(8,1) << endl; 
			llvar								= incoming(next_field_last,2);	//035 
			field35 = atoi(llvar);
			track_2_035 = incoming((next_field_last+2),field35);
			next_field_last = next_field_last+2+field35;
		}

	//	int next_field_039 = 0;
		
		if(hex_bit(9,1) == "A")// bit 37,38,39,40
		{
			
			retrieval_reference_number_037 = incoming(next_field_last,12);
			responde_code_039			   = incoming((next_field_last+12),2);
			next_field_last				   = next_field_last+12+2;
			

			//cout << "el valor de caracter #09 >" << hex_bit(9,1) << endl; 
	
		}
		if(hex_bit(9,1) == "8")// bit 37,38,39,40
		{
			
			retrieval_reference_number_037 = incoming(next_field_last,12);
			next_field_last				   = next_field_last+12;
	
		}
		if(hex_bit(9,1) == "E")// bit 37,38,39,40
		{
			
			retrieval_reference_number_037 = incoming(next_field_last,12);
			responde_id_response_038       = incoming((next_field_last+12),6);
			responde_code_039			   = incoming((next_field_last+12+6),2);
			next_field_last				   = next_field_last+12+6+2;
	
		}
	
		int next_field_043 = 0;
		if(hex_bit(10,1) == "E")// bit 41,42,43,44
		{
			
			card_acceptor_terminal_id_041	= incoming(next_field_last,16);
			card_acceptor_id_code_042		= incoming((next_field_last+16),15);
			card_acceptor_name_location_043	= incoming((next_field_last+16+15),40);
			next_field_last					= next_field_last+16+15+40;
	
		}
	
		if(hex_bit(10,1) == "C")// bit 41,42,43,44
		{
			
			card_acceptor_terminal_id_041	= incoming(next_field_last,16);
			card_acceptor_id_code_042		= incoming((next_field_last+16),15);
			//card_acceptor_name_location_043	= incoming((next_field_last+16+15),40);
			next_field_last					= next_field_last+16+15;
			
		}

		if(hex_bit(10,1) == "8")// bit 41,42,43,44
		{
			
			card_acceptor_terminal_id_041	= incoming(next_field_last,16);
			next_field_last					= next_field_last+16;
			
		}


		int field45= 0;
		int field48 = 0;
		
		int next_field_048 = 0;
		
		if(hex_bit(11,1) == "1")// bit 45,46,47,48
		{
		
			lllvar							= incoming(next_field_last,3);
			field48							= atoi(lllvar);
			addditional_data_048			= incoming((next_field_last+3),field48);
			next_field_last					= next_field_last+3+field48;
			

			//cout << "el valor de caracter #11 >" << hex_bit(11,1) << endl; 
	
			//cout << "el valor de next_field_043 > " << next_field_043 << endl;
		}
	
		if(hex_bit(11,1) == "9")// bit 45,46,47,48
		{
		
			llvar							= incoming(next_field_last,2);
			field45							= atoi(llvar);
			track_1_045						= incoming((next_field_last+2),field45);
			next_field_last					= next_field_last+2+field45;
			
			lllvar							= incoming(next_field_last,3);
			field48							= atoi(lllvar);
			addditional_data_048			= incoming((next_field_last+3),field48);
			next_field_last					= next_field_last+3+field48;
			

			//cout << "el valor de caracter #11 >" << hex_bit(11,1) << endl; 
	
			//cout << "el valor de next_field_043 > " << next_field_043 << endl;
		}
	
		int next_field_052 = 0;
	
		if(hex_bit(12,1) == "8")// bit 49,50,51,52
		{
		
			currency_code_transaction_049	= incoming(next_field_last,3);
			//pin_data_052					= incoming((next_field_last+3),16);
			next_field_last					= next_field_last+3;
			

			//cout << "el valor de caracter #12 >" << hex_bit(12,1) << endl; 
	
		}
		if(hex_bit(12,1) == "9")// bit 49,50,51,52
		{
		
			currency_code_transaction_049	= incoming(next_field_last,3);
			pin_data_052					= incoming((next_field_last+3),16);
			next_field_last					= next_field_last+3+16;
			

			//cout << "el valor de caracter #12 >" << hex_bit(12,1) << endl; 
	
		}
	
		if(hex_bit(13,1) == "0")// bit 53,54,55,56
		{
		
		
			//cout << "el valor de caracter #13 >" << hex_bit(13,1) << endl; 
	
		}
		if(hex_bit(13,1) == "4")// bit 53,54,55,56
		{
		
			

			//cout << "el valor de caracter #13 >" << hex_bit(13,1) << endl; 
		}
	
		int field60 = 0;
		int next_field_060 = 0;
		if(hex_bit(14,1) == "1")// bit 57,58,59,60
		{
		
			lllvar							= incoming(next_field_last,3);
			field60							= atoi(lllvar);
			pos_terminal_data_060				= incoming((next_field_last+3),field60);
			next_field_last					= next_field_last+3+field60;
			//cout << "el valor de caracter #14 >" << hex_bit(14,1) << endl; 
		}
		
		int field61 = 0;
		int field63 = 0;
		if(hex_bit(15,1) == "A")// bit 61,62,63,64
		{
		
			lllvar							= incoming(next_field_last,3);
			field61							= atoi(lllvar);
			card_issuer_response_data_061	= incoming((next_field_last+3),field61);
		
			lllvar							= incoming((next_field_last+3+field61),3);
			field63							= atoi(lllvar);
			additional_data_063				= incoming((next_field_last+3+field61+3),field63);
			
			next_field_last					= next_field_last+3+field61+3+field63;
			
			//cout << "el valor del caracter #15 >" << hex_bit(15,1) << endl; 
	
		}
		
		
		if(hex_bit(15,1) == "8")// bit 61,62,63,64
		{
		
			lllvar							= incoming(next_field_last,3);
			field61							= atoi(lllvar);
			card_issuer_response_data_061	= incoming((next_field_last+3),field61);
			next_field_last					= next_field_last+3+field61;	

			//cout << "el valor de caracter #15 >" << hex_bit(15,1) << endl; 
			
		}		
		
		if(hex_bit(16,1) == "0")// bit 65,66,67,68
		{
		
			

			//cout << "el valor de caracter #16 >" << hex_bit(16,1) << endl; 
	
		}
		if(hex_bit(17,1) == "0")// bit 69,70,71,72
		{
		
			

			//cout << "el valor de caracter #17 >" << hex_bit(17,1) << endl; 
	
		}
		if(hex_bit(18,1) == "0")// bit 73,74,75,76
		{
		
			

			//cout << "el valor de caracter #18 >" << hex_bit(18,1) << endl; 
	
		}
		
		if(hex_bit(19,1) == "0")// bit 77,78,79,80
		{
		
			

			//cout << "el valor de caracter #19 >" << hex_bit(19,1) << endl; 
	
		}
		
		if(hex_bit(20,1) == "0")// bit 81,82,83,84
		{
		
			

			//cout << "el valor de caracter #20 >" << hex_bit(20,1) << endl; 
	
		}
		
		if(hex_bit(21,1) == "0")// bit 85,86,87,88
		{
		
			

			//cout << "el valor de caracter #21 >" << hex_bit(21,1) << endl; 
	
		}
		
		if(hex_bit(22,1) == "0")// bit 89,90,91,92
		{
		
			

			//cout << "el valor de caracter #22 >" << hex_bit(22,1) << endl; 
	
		}
		
		if(hex_bit(23,1) == "0")// bit 93,94,95,96
		{
		
			

			//cout << "el valor de caracter #23 >" << hex_bit(23,1) << endl; 
	
		}
		int field100 = 0;
		if(hex_bit(24,1) == "1")// bit 97,98,99,100
		{
		
			llvar = incoming(next_field_last,2);
			field100 = atoi(llvar);
			receiving_institution_id_code_0100 = incoming((next_field_last+2),field100);
			
			next_field_last = next_field_last+2+field100;
		
			//cout << "el valor de caracter #24 >" << hex_bit(24,1) << endl; 
	
		}

		if(hex_bit(25,1) == "0")// bit 101,102,103,104
		{
		
			//cout << "el valor de caracter #25 >" << hex_bit(25,1) << endl; 
	
		}

		if(hex_bit(26,1) == "0")// bit 105,106,107,108
		{
		
			

			//cout << "el valor de caracter #26 >" << hex_bit(26,1) << endl; 
	
		}
		
		if(hex_bit(27,1) == "0")// bit 109,110,111,112
		{
		
			

			//cout << "el valor de caracter #27 >" << hex_bit(27,1) << endl; 
	
		}
		
		if(hex_bit(28,1) == "0")// bit 113,114,115,116
		{
		
			

			//cout << "el valor de caracter #28 >" << hex_bit(28,1) << endl; 
	
		}
		
		if(hex_bit(29,1) == "0")// bit 117,118,119,120
		{
		
			

			//cout << "el valor de caracter #29 >" << hex_bit(29,1) << endl; 
	
		
		}
		int field120 = 0;
		if(hex_bit(29,1) == "1")// bit 117,118,119,120
		{
		
			lllvar = incoming(next_field_last,3);
			field120 = atoi(lllvar);
			pos_terminal_address_branch_120	= incoming((next_field_last+3),field120);
			next_field_last					= next_field_last+3+field120;
				
		}
		
		int field121 = 0;
		int field124 = 0;
		if(hex_bit(30,1) == "9")// bit 121,122,123,124
		{
			
			lllvar							= incoming(next_field_last,3);
			field121						= atoi(lllvar);
			authorization_indicators_0121	= incoming((next_field_last+3),field121);
			
			lllvar							= incoming((next_field_last+3+field121),3);
			field124						= atoi(lllvar);
			batch_record2_0124				= incoming((next_field_last+3+field121+3),field124);
			next_field_last					= next_field_last+3+field121+3+field124;
			
			
			//cout << "el valor de caracter #30 >" << hex_bit(30,1) << endl; 
	
		
		}
		if(hex_bit(30,1) == "1")// bit 121,122,123,124
		{
			
			lllvar							= incoming(next_field_last,3);
			field124						= atoi(lllvar);
			batch_record2_0124				= incoming((next_field_last+3),field124);
			next_field_last					= next_field_last+3+field124;
			
			
			
			//cout << "el valor de caracter #30 >" << hex_bit(30,1) << endl; 
	
		
		}
	
		//////////Bit 31//////////////////
		int field125 = 0;
		int field126 = 0;
		
		if(hex_bit(31,1) == "C")// bit 125,126,127,128
		{
			
			lllvar							= incoming(next_field_last,3);
			field125						= atoi(lllvar);
			pos_settlement_data_125			= incoming((next_field_last+3),field125);
			
			lllvar							= incoming((next_field_last+3+field125),3);
			field126						= atoi(lllvar);
			preauthorization_data_0126		= incoming((next_field_last+3+field125+3),field126);
			next_field_last					= next_field_last+3+field125+3+field126;
			
			
			//cout << "el valor de caracter #31 >" << hex_bit(31,1) << endl; 
	
		
		}
		if(hex_bit(31,1) == "4")// bit 125,126,127,128
		{
			
			
			lllvar							= incoming(next_field_last,3);
			field126						= atoi(lllvar);
			preauthorization_data_0126		= incoming((next_field_last+3),field126);
			next_field_last					= next_field_last+3+field126;
			
			
			//cout << "el valor de caracter #31 >" << hex_bit(31,1) << endl; 
	
		
		}
		if(hex_bit(31,1) == "0")// bit 125,126,127,128
		{
			
			
			
			//cout << "el valor de caracter #31 >" << hex_bit(31,1) << endl; 
	
		
		}
		if(hex_bit(31,1) == "8")// bit 125,126,127,128
		{
			
			lllvar							= incoming(next_field_last,3);
			field125						= atoi(lllvar);
			pos_settlement_data_125		    = incoming((next_field_last+3),field125);
			next_field_last					= next_field_last+3+field125;
	
		}

		
		response_0210_generic_from_iso = "";
		RWCString delimiter = ",";
		RWCString msg_type_0200 = "0200";
		response_0210_generic_from_iso +="0210";
		response_0210_generic_from_iso +=delimiter;
		RWCString test_bit_map = "";
		RWCString test_bit_map_2 = "";
		test_bit_map = incoming(18,16);
		test_bit_map_2 = incoming(34,16);
		if(test_bit_map == "B23CC4812E818018") //Base 24 Tandem GM
		{
			
			response_0210_generic_from_iso +=processing_code_03;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=transaction_amount_04;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=transmition_date_time_07;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=system_trace_011;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=time_local_transaction_012;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=date_local_transaction_013;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=expiration_date_014;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=capture_date_017;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=merchant_type_018;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_entry_mode_022;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_condition_code_025;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=acquiring_institution_id_code_032;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=track_2_035;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=retrieval_reference_number_037;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=responde_id_response_038;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=responde_code_039;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=card_acceptor_terminal_id_041;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=addditional_data_048;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=currency_code_transaction_049;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_terminal_data_060;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=card_issuer_response_data_061;
			response_0210_generic_from_iso +=delimiter;

		}
		                    
		if(test_bit_map == "B23CC4812E81801A") //Base 24 Tandem GM con campo 63
		{
			
			response_0210_generic_from_iso +=processing_code_03;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=transaction_amount_04;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=transmition_date_time_07;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=system_trace_011;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=time_local_transaction_012;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=date_local_transaction_013;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=expiration_date_014;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=capture_date_017;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=merchant_type_018;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_entry_mode_022;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_condition_code_025;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=acquiring_institution_id_code_032;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=track_2_035;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=retrieval_reference_number_037;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=responde_id_response_038;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=responde_code_039;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=card_acceptor_terminal_id_041;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=addditional_data_048;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=currency_code_transaction_049;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_terminal_data_060;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=card_issuer_response_data_061;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=additional_data_063;
			response_0210_generic_from_iso +=delimiter;
		
		}
	
		if(test_bit_map == "B23E84812EC18018") //Postilion
		{
			response_0210_generic_from_iso +=processing_code_03;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=transaction_amount_04;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=transmition_date_time_07;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=system_trace_011;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=time_local_transaction_012;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=date_local_transaction_013;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=expiration_date_014;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=date_settlement_015;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=capture_date_017;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=merchant_type_018;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_entry_mode_022;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_condition_code_025;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=acquiring_institution_id_code_032;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=track_2_035;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=retrieval_reference_number_037;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=responde_id_response_038;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=responde_code_039;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=card_acceptor_terminal_id_041;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=card_acceptor_id_code_042;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=addditional_data_048;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=currency_code_transaction_049;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_terminal_data_060;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=card_issuer_response_data_061;
			response_0210_generic_from_iso +=delimiter;
		}
		
		if (test_bit_map_2 == "0000000000000008") //B24 Postilion
		{
			response_0210_generic_from_iso +=pos_settlement_data_125;
			switch_key_127=date_local_transaction_013+":"+time_local_transaction_012+
		           ":"+msg_type_0200+":"+retrieval_reference_number_037;

			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=switch_key_127;
	
		}
		if (test_bit_map_2 == "0000000000000108") //B24 Tandem GM
		{
			response_0210_generic_from_iso +=pos_terminal_address_branch_120;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_settlement_data_125;
	
			switch_key_127=date_local_transaction_013+":"+time_local_transaction_012+
			           ":"+msg_type_0200+":"+retrieval_reference_number_037;

			response_0210_generic_from_iso +=delimiter;

			response_0210_generic_from_iso +=switch_key_127;
	
		}
		if (test_bit_map_2 == "0000000010000108") //B24 ATHPR
		{
			response_0210_generic_from_iso +=receiving_institution_id_code_0100;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_terminal_address_branch_120;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +=pos_settlement_data_125;

			response_0210_generic_from_iso +=delimiter;
	
			original_data_elements_090="0200"+retrieval_reference_number_037+date_local_transaction_013+
						time_local_transaction_012+"00"+capture_date_017+"0000000000";
			
			response_0210_generic_from_iso +=original_data_elements_090;



	
		}
	}
	return response_0210_generic_from_iso;

}
*/
#endif