// IsoBitMap.cpp: implementation of the IsoBitMap class.
//
//////////////////////////////////////////////////////////////////////

#include "IsoBitMap.h"
#include "Iso8583Msg.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IsoBitMap::IsoBitMap()
{

	processing_code_03					= "";
	transaction_amount_04				= "";
	transmition_date_time_07			= "";
	system_trace_011					= "";
	convertion_rate_010					= "";
	time_local_transaction_012			= "";
	date_local_transaction_013			= "";		
	expiration_date_014					= "";					
	date_settlement_015					= "";
	capture_date_017					= "";
	merchant_type_018					= "";
	pos_entry_mode_022					= "";
	for_athd_024						= "";
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
	pos_invoice_data_0123				= "";
	batch_record2_0124					= "";
	pos_settlement_data_125				= "";
	preauthorization_data_0126			= "";
	
	response_0210_generic_from_iso		= "";
	lllvar								= "";
	llvar								= "";
	bit_map_first_part					= "";
	bit_map_second_part					= "";


}

RWCString IsoBitMap::Retorno_Msg_Generic_PostermB24(RWCString incoming , char *msg_type, 
											          int debug, RWCString application)
{


	RWCString  hex_bit = "";
	RWCString  field45	;
	RWCString  bit_map_from_msg   ;
	RWCString  msg_for_processing ;
	RWCString  msg_processing_053 ;
	RWCString  bit_set_fiedl;
	RWCString  ascii_bit;
	RWCString  delimiter = ",";
	RWCString  msg_type_from_incming ;
	int next_field_last = 0;
	int next_field = 0;
	int var_field = 0;
	char msg_input[5] = {""};

	//Se crea los fields con valores fijos
    RWTValVector<int> iso_field_length(129,0);
	      
	iso_field_length[3]  = 6; 	iso_field_length[4]  = 12; 	iso_field_length[5]  = 12;
	iso_field_length[7]  = 10;	iso_field_length[11] = 6; 	iso_field_length[12] = 6; 	
	iso_field_length[13] = 4;	iso_field_length[14] = 4;  	iso_field_length[15] = 4; 
	iso_field_length[16] = 4;   iso_field_length[17] = 4;   iso_field_length[18] = 4;	
	iso_field_length[22] = 3;	iso_field_length[25] = 2;   iso_field_length[26] = 2;
	iso_field_length[28] = 9;   iso_field_length[30] = 9; 	iso_field_length[37] = 12; 
	iso_field_length[38] = 6;   iso_field_length[39] = 2; 	iso_field_length[42] = 15;  
	iso_field_length[43] = 40;  iso_field_length[49] = 3; 	iso_field_length[52] = 16;
	iso_field_length[53] = 48;	iso_field_length[54] = 120; iso_field_length[70] = 3;
	iso_field_length[95] = 42;  iso_field_length[66] = 1;   iso_field_length[74] = 10;
	iso_field_length[75] = 10;  iso_field_length[76] = 10;  iso_field_length[77] = 10;
	iso_field_length[78] = 10;  iso_field_length[79] = 10;  iso_field_length[80] = 10;
	iso_field_length[81] = 10;  iso_field_length[82] = 12;  iso_field_length[83] = 12;
	iso_field_length[84] = 12;  iso_field_length[85] = 12;  iso_field_length[86] = 16;
	iso_field_length[87] = 16;  iso_field_length[88] = 16;  iso_field_length[89] = 16;
	iso_field_length[97] = 17;  iso_field_length[90] = 42;

	
	if(application == "base24")
	{
		iso_field_length[41] = 16;
	}

	if(application == "posterm")
	{
		iso_field_length[41] = 8;
	}

	Iso8583Msg test_iso_new;
	Iso8583Msg get_bit_map_ascii;
	IsoBitMap field_length;

	if(application == "posterm")
	{

		msg_type_from_incming = incoming(7,4);

		response_0210_generic_from_iso += incoming(7,4);
		
		if(debug == 1)
		ReturnIso8583FieldValue(strcpy(msg_input,msg_type_from_incming), 0  , incoming(7,4));
		response_0210_generic_from_iso +=delimiter;

		ascii_bit = get_bit_map_ascii.RetornoAsciiComplete(incoming(11,1),1);

		if (ascii_bit(0,1) == "7")
		{
			 hex_bit = get_bit_map_ascii.RetornoAsciiComplete(incoming(11,8),8);
			 hex_bit += "0000000000000000";
			 if(debug == 1)
				cout << "Valor de BitMap #1 > :" << hex_bit << endl;
			 bit_map_from_msg   = hex_bit;
			 msg_for_processing = incoming(19,incoming.length()-19);
			 

		}

		else
		{
			hex_bit = get_bit_map_ascii.RetornoAsciiComplete(incoming(11,16),16);
		 
			if(debug == 1)
		 
				 cout << "Valor de BitMap  #2 > :" << hex_bit << endl;
			bit_map_from_msg   = hex_bit;
			msg_for_processing = incoming(27,incoming.length()-27);

		}
	}

	if(application == "base24")
	{

	    msg_type_from_incming = incoming(14,4);
		bit_map_from_msg   = incoming(18,32);
		msg_for_processing = incoming(50,incoming.length()-50);
		response_0210_generic_from_iso += incoming(14,4);
		if(debug == 1)
		ReturnIso8583FieldValue(strcpy(msg_input,msg_type_from_incming), 0  , incoming(14,4));
		response_0210_generic_from_iso +=delimiter;

	}




	bit_set_fiedl = test_iso_new.setBitMapFromChar(bit_map_from_msg);

	//Se saca el message type de retorno para enviarse
	int j = 0;

	for(j = 0; j < 128; j++)
	{
		if(bit_set_fiedl(j,1) == "1")
		{
	
			switch (field_length.RetornoFieldNumber(j+1))
			{
			case LLLVAR:
			
				lllvar	= msg_for_processing(next_field,LLLVAR);
				var_field = atoi(lllvar);
				next_field = next_field+LLLVAR;
				if(debug == 1)
					ReturnIso8583FieldValue(msg_input, j+1  , msg_for_processing(next_field,var_field));
				response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+msg_for_processing(next_field,var_field);
				response_0210_generic_from_iso +=delimiter;
				next_field = next_field+var_field;
				break;
		
			case LLVAR:
				
				llvar	= msg_for_processing(next_field,LLVAR);
				var_field = atoi(llvar);
				next_field = next_field+LLVAR;
				if(debug == 1)
					ReturnIso8583FieldValue(msg_input, j+1  , msg_for_processing(next_field,var_field));
				response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+msg_for_processing(next_field,var_field);
				response_0210_generic_from_iso +=delimiter;
				next_field = next_field+var_field;
				break;
			
			case FIXED:
				
				
				next_field = next_field+iso_field_length[j+1];
				if((j+1 != 0) && (j+1 != 1))
				{
					
					
					if(j+1 == 53)
					{
						msg_processing_053 = msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]);
						if(debug == 1)

							ReturnIso8583FieldValue(msg_input, j+1  ,test_iso_new.RetornoAsciiComplete(msg_processing_053(0,8),8));	
						
						response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+test_iso_new.RetornoAsciiComplete(msg_processing_053(0,8),8) ;
						response_0210_generic_from_iso +=delimiter;
					}
					else
					{
						if(debug == 1)
							ReturnIso8583FieldValue(msg_input, j+1  , msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]));
					
						response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]);
						response_0210_generic_from_iso +=delimiter;
					}
				}
			
			}
		}
		
	}


	return response_0210_generic_from_iso;

}
RWCString IsoBitMap::Retorno_210_B24(RWCString incoming , char *msg_type,int debug)
{
	int next_field_last = 0;		
	RWCString hex_bit = incoming(18,32);
	bit_map_first_part = incoming(18,16);
	bit_map_second_part = incoming(34,16);
	RWCString delimiter = ",";
	RWCString msg_type_0200 = "0200";
	response_0210_generic_from_iso +="0210";
	response_0210_generic_from_iso +=delimiter;
	RWCString test_bit_map = "";
	RWCString test_bit_map_2 = "";
	test_bit_map = incoming(18,16);
	test_bit_map_2 = incoming(34,16);
		
	if((strncmp(msg_type, "0210", 4) == 0))
	{
		if(hex_bit(0,1) == "B")// bit 1,2,3,4
		{
			processing_code_03					= incoming(50,6);   //03   
			next_field_last					= 56;
			transaction_amount_04				= incoming(next_field_last,12);	//04
			next_field_last					= next_field_last+12;
			response_0210_generic_from_iso +="00003"+processing_code_03;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +="00004"+transaction_amount_04;
			response_0210_generic_from_iso +=delimiter;

		}
	
		if(hex_bit(1,1) == "2")// bit 5,6,7,8
		{
			transmition_date_time_07			= incoming(next_field_last,10);	//07     		
			next_field_last					= next_field_last+10;
			response_0210_generic_from_iso +="00007"+transmition_date_time_07;
			response_0210_generic_from_iso +=delimiter;
			
		}

		if(hex_bit(2,1) == "3")// bit 9,10,11,12
		{
			system_trace_011					= incoming(next_field_last,6);	//011     		
			time_local_transaction_012			= incoming((next_field_last+6),6);	//012     		
			next_field_last						= next_field_last+6+6;
			response_0210_generic_from_iso +="00011"+system_trace_011;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +="00012"+time_local_transaction_012;
			response_0210_generic_from_iso +=delimiter;
		}
	
		if(hex_bit(2,1) == "7")// bit 9,10,11,12
		{
			convertion_rate_010					= incoming(next_field_last,8);		//010
			system_trace_011					= incoming((next_field_last,8),6);	//011     		
			time_local_transaction_012			= incoming((next_field_last+8+6),6);//012     		
			next_field_last						= next_field_last+8+6+6;
			response_0210_generic_from_iso +="00011"+system_trace_011;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +="00012"+time_local_transaction_012;
			response_0210_generic_from_iso +=delimiter;

		}
	

		if(hex_bit(3,1) == "E")// bit 13,14,15,16
		{
			date_local_transaction_013			= incoming(next_field_last,4);	//013 
			expiration_date_014					= incoming((next_field_last+4),4);	//014 
			date_settlement_015					= incoming((next_field_last+4+4),4);	//015 
			next_field_last						= next_field_last+4+4+4;
			
			response_0210_generic_from_iso +="00013"+date_local_transaction_013;
			response_0210_generic_from_iso +=delimiter;
		
		}
		

		if(hex_bit(3,1) == "8")// bit 13,14,15,16
		{
			date_local_transaction_013			= incoming(next_field_last,4);	//013 
			next_field_last						= next_field_last+4;
			response_0210_generic_from_iso +="00013"+date_local_transaction_013;
			response_0210_generic_from_iso +=delimiter;

		}
	
		if(hex_bit(3,1) == "C")// bit 13,14,15,16
		{
			date_local_transaction_013			= incoming(next_field_last,4);	//013 
			expiration_date_014					= incoming((next_field_last+4),4);	//014 
			next_field_last						= next_field_last+4+4;	
			response_0210_generic_from_iso +="00013"+date_local_transaction_013;
			response_0210_generic_from_iso +=delimiter;


		
		}

		if(hex_bit(4,1) == "8")// bit 17,18,19,20
		{
			capture_date_017					= incoming(next_field_last,4);	//017 
			next_field_last						= next_field_last+4;

		
		}

		if(hex_bit(4,1) == "C")// bit 17,18,19,20
		{
			capture_date_017					= incoming(next_field_last,4);	//017 
			merchant_type_018					= incoming((next_field_last+4),4);
			next_field_last						= next_field_last+4+4;


		}


		if(hex_bit(5,1) == "4")// bit 21,22,23,24
		{
			pos_entry_mode_022					= incoming(next_field_last,3);	//022 
			next_field_last						= next_field_last+3;

		}
	
		if(hex_bit(5,1) == "5")// bit 21,22,23,24
		{
			pos_entry_mode_022					= incoming(next_field_last,3);	//022 
			for_athd_024						= incoming((next_field_last+3),3);	//024 
			next_field_last						= next_field_last+3+3;

		}
	

		if(hex_bit(6,1) == "8")// bit 25,26,27,28
		{
			pos_condition_code_025				= incoming(next_field_last,2);	//025 
			next_field_last					= next_field_last+2;
				
		}
	

		int field32 = 0;
		if(hex_bit(7,1) == "1")// bit 29,30,31,32
		{
			llvar		= incoming(next_field_last,2);	//032 
			field32 = atoi(llvar);
			acquiring_institution_id_code_032		 = incoming((next_field_last+2),field32);	//032 
			next_field_last							 = next_field_last+2+field32;

		}
	
		int field35 = 0;
		if(hex_bit(8,1) == "2")// bit 33,34,35,36
		{
			llvar								= incoming(next_field_last,2);	//035 
			field35 = atoi(llvar);
			track_2_035 = incoming((next_field_last+2),field35);
			next_field_last = next_field_last+2+field35;

		}

		
		if(hex_bit(9,1) == "A")// bit 37,38,39,40
		{
			
			retrieval_reference_number_037 = incoming(next_field_last,12);
			responde_code_039			   = incoming((next_field_last+12),2);
			next_field_last				   = next_field_last+12+2;
			response_0210_generic_from_iso +="00037"+retrieval_reference_number_037;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +="00039"+responde_code_039;
			response_0210_generic_from_iso +=delimiter;
	
		
	
		}


		if(hex_bit(9,1) == "8")// bit 37,38,39,40
		{
			
			retrieval_reference_number_037 = incoming(next_field_last,12);
			next_field_last				   = next_field_last+12;
			response_0210_generic_from_iso +="00037"+retrieval_reference_number_037;
			response_0210_generic_from_iso +=delimiter;
		
	
		}
		if(hex_bit(9,1) == "E")// bit 37,38,39,40
		{
			
			retrieval_reference_number_037 = incoming(next_field_last,12);
			responde_id_response_038       = incoming((next_field_last+12),6);
			responde_code_039			   = incoming((next_field_last+12+6),2);
			next_field_last				   = next_field_last+12+6+2;
			response_0210_generic_from_iso +="00037"+retrieval_reference_number_037;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +="00038"+responde_id_response_038;
			response_0210_generic_from_iso +=delimiter;
			response_0210_generic_from_iso +="00039"+responde_code_039;

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
			

		}
	
		int next_field_052 = 0;
	
		if(hex_bit(12,1) == "8")// bit 49,50,51,52
		{
		
			currency_code_transaction_049	= incoming(next_field_last,3);
			next_field_last					= next_field_last+3;
	
		}
		if(hex_bit(12,1) == "9")// bit 49,50,51,52
		{
		
			currency_code_transaction_049	= incoming(next_field_last,3);
			pin_data_052					= incoming((next_field_last+3),16);
			next_field_last					= next_field_last+3+16;
	
		}
	
		if(hex_bit(13,1) == "0")// bit 53,54,55,56
		{
		
	
		}
		if(hex_bit(13,1) == "4")// bit 53,54,55,56
		{

		}
	
		int field60 = 0;
		int next_field_060 = 0;
		if(hex_bit(14,1) == "1")// bit 57,58,59,60
		{
		
			lllvar							= incoming(next_field_last,3);
			field60							= atoi(lllvar);
			pos_terminal_data_060				= incoming((next_field_last+3),field60);
			next_field_last					= next_field_last+3+field60;
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
	
		}
		
		
		if(hex_bit(15,1) == "8")// bit 61,62,63,64
		{
		
			lllvar							= incoming(next_field_last,3);
			field61							= atoi(lllvar);
			card_issuer_response_data_061	= incoming((next_field_last+3),field61);
			next_field_last					= next_field_last+3+field61;	

			
		}		
	
		if(hex_bit(16,1) == "0")// bit 65,66,67,68
		{
		
			
	
		}
		if(hex_bit(17,1) == "0")// bit 69,70,71,72
		{
		
			
	
		}
		if(hex_bit(18,1) == "0")// bit 73,74,75,76
		{
		
			
	
		}
		
		if(hex_bit(19,1) == "0")// bit 77,78,79,80
		{
		
			

		}
		
		if(hex_bit(20,1) == "0")// bit 81,82,83,84
		{
		
			
	
		}
		
		if(hex_bit(21,1) == "0")// bit 85,86,87,88
		{
		
			
	
		}
		
		if(hex_bit(22,1) == "0")// bit 89,90,91,92
		{
		
			
	
		}
		
		if(hex_bit(23,1) == "0")// bit 93,94,95,96
		{
		
			

		}
		int field100 = 0;
		if(hex_bit(24,1) == "1")// bit 97,98,99,100
		{
		
			llvar = incoming(next_field_last,2);
			field100 = atoi(llvar);
			receiving_institution_id_code_0100 = incoming((next_field_last+2),field100);
			
			next_field_last = next_field_last+2+field100;
	
		}

		if(hex_bit(25,1) == "0")// bit 101,102,103,104
		{
		
	
		}

		if(hex_bit(26,1) == "0")// bit 105,106,107,108
		{
		
			
	
		}
		
		if(hex_bit(27,1) == "0")// bit 109,110,111,112
		{
		
			
	
		}
		
		if(hex_bit(28,1) == "0")// bit 113,114,115,116
		{
		
	
		}
		
		if(hex_bit(29,1) == "0")// bit 117,118,119,120
		{
		
			
	
		
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
		int field123 = 0;
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
	
		
		}
		if(hex_bit(30,1) == "1")// bit 121,122,123,124
		{
			
			lllvar							= incoming(next_field_last,3);
			field124						= atoi(lllvar);
			batch_record2_0124				= incoming((next_field_last+3),field124);
			next_field_last					= next_field_last+3+field124;
			
	
		
		}

		if(hex_bit(30,1) == "2")// bit 121,122,123,124
		{
			
			lllvar							= incoming(next_field_last,3);
			field123						= atoi(lllvar);
			pos_invoice_data_0123			= incoming((next_field_last+3),field123);
			next_field_last					= next_field_last+3+field123;
			
			
		
		
		}
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
			
	
		
		}
		if(hex_bit(31,1) == "4")// bit 125,126,127,128
		{
			
			
			lllvar							= incoming(next_field_last,3);
			field126						= atoi(lllvar);
			preauthorization_data_0126		= incoming((next_field_last+3),field126);
			next_field_last					= next_field_last+3+field126;
			
	
		
		}
		if(hex_bit(31,1) == "0")// bit 125,126,127,128
		{
			
			
	
		
		}
		if(hex_bit(31,1) == "8")// bit 125,126,127,128
		{
			
			lllvar							= incoming(next_field_last,3);
			field125						= atoi(lllvar);
			pos_settlement_data_125		    = incoming((next_field_last+3),field125);
			next_field_last					= next_field_last+3+field125;
	
		}


	}
	

	return response_0210_generic_from_iso;

}
RWCString IsoBitMap::Retorno_Msg_Iso8583_Field125(RWCString incoming , char *msg_type, 
										          int debug, RWCString application)
{


	RWCString  hex_bit = "";
	RWCString  field45	;
	RWCString  bit_map_from_msg   ;
	RWCString  msg_for_processing ;
	RWCString  msg_processing_053 ;
	RWCString  bit_set_fiedl;
	RWCString  ascii_bit;
	RWCString  delimiter = ",";
	RWCString  retorno_125 = "";
	RWCString  msg_type_from_incming ;
	int next_field_last = 0;
	int next_field = 0;
	int var_field = 0;
	char msg_input[5] = {""};

	//Se crea los fields con valores fijos
    RWTValVector<int> iso_field_length(129,0);
	      
	iso_field_length[3]  = 6; 	iso_field_length[4]  = 12; 	iso_field_length[5]  = 12;
	iso_field_length[7]  = 10;	iso_field_length[11] = 6; 	iso_field_length[12] = 6; 	
	iso_field_length[13] = 4;	iso_field_length[14] = 4;  	iso_field_length[15] = 4; 
	iso_field_length[16] = 4;   iso_field_length[17] = 4;   iso_field_length[18] = 4;	
	iso_field_length[22] = 3;	iso_field_length[25] = 2;   iso_field_length[26] = 2;
	iso_field_length[28] = 9;   iso_field_length[30] = 9; 	iso_field_length[37] = 12; 
	iso_field_length[38] = 6;   iso_field_length[39] = 2; 	iso_field_length[42] = 15;  
	iso_field_length[43] = 40;  iso_field_length[49] = 3; 	iso_field_length[52] = 16;
	iso_field_length[53] = 48;	iso_field_length[54] = 120; iso_field_length[70] = 3;
	iso_field_length[95] = 42;  iso_field_length[66] = 1;   iso_field_length[74] = 10;
	iso_field_length[75] = 10;  iso_field_length[76] = 10;  iso_field_length[77] = 10;
	iso_field_length[78] = 10;  iso_field_length[79] = 10;  iso_field_length[80] = 10;
	iso_field_length[81] = 10;  iso_field_length[82] = 12;  iso_field_length[83] = 12;
	iso_field_length[84] = 12;  iso_field_length[85] = 12;  iso_field_length[86] = 16;
	iso_field_length[87] = 16;  iso_field_length[88] = 16;  iso_field_length[89] = 16;
	iso_field_length[97] = 17;  iso_field_length[90] = 42;

	
	if(application == "base24")
	{
		iso_field_length[41] = 16;
	}

	if(application == "posterm")
	{
		iso_field_length[41] = 8;
	}

	Iso8583Msg test_iso_new;
	Iso8583Msg get_bit_map_ascii;
	IsoBitMap field_length;

	if(application == "posterm")
	{

		msg_type_from_incming = incoming(7,4);

		response_0210_generic_from_iso += incoming(7,4);
		
		if(debug == 1)
		ReturnIso8583FieldValue(strcpy(msg_input,msg_type_from_incming), 0  , incoming(7,4));
		response_0210_generic_from_iso +=delimiter;

		ascii_bit = get_bit_map_ascii.RetornoAsciiComplete(incoming(11,1),1);

		if (ascii_bit(0,1) == "7")
		{
			 hex_bit = get_bit_map_ascii.RetornoAsciiComplete(incoming(11,8),8);
			 hex_bit += "0000000000000000";
			 if(debug == 1)
				cout << "Valor de BitMap #1 > :" << hex_bit << endl;
			 bit_map_from_msg   = hex_bit;
			 msg_for_processing = incoming(19,incoming.length()-19);
			 

		}

		else
		{
			hex_bit = get_bit_map_ascii.RetornoAsciiComplete(incoming(11,16),16);
		 
			if(debug == 1)
		 
				 cout << "Valor de BitMap  #2 > :" << hex_bit << endl;
			bit_map_from_msg   = hex_bit;
			msg_for_processing = incoming(27,incoming.length()-27);

		}
	}

	if(application == "base24")
	{

	    msg_type_from_incming = incoming(14,4);
		bit_map_from_msg   = incoming(18,32);
		msg_for_processing = incoming(50,incoming.length()-50);
		response_0210_generic_from_iso += incoming(14,4);
		if(debug == 1)
		ReturnIso8583FieldValue(strcpy(msg_input,msg_type_from_incming), 0  , incoming(14,4));
		response_0210_generic_from_iso +=delimiter;

	}




	bit_set_fiedl = test_iso_new.setBitMapFromChar(bit_map_from_msg);

	//Se saca el message type de retorno para enviarse
	int j = 0;

	for(j = 0; j < 128; j++)
	{
		if(bit_set_fiedl(j,1) == "1")
		{
	
			switch (field_length.RetornoFieldNumber(j+1))
			{
			case LLLVAR:
			
				lllvar	= msg_for_processing(next_field,LLLVAR);
				var_field = atoi(lllvar);
				next_field = next_field+LLLVAR;
				if(debug == 1)
					ReturnIso8583FieldValue(msg_input, j+1  , msg_for_processing(next_field,var_field));
				response_0210_generic_from_iso +=msg_for_processing(next_field,var_field);
				

				
				if((j+1) == 125)
				{
					retorno_125 += msg_for_processing(next_field,var_field);
					retorno_125 +=delimiter;
				
				}
				response_0210_generic_from_iso +=delimiter;
				next_field = next_field+var_field;
				

				break;
		
			case LLVAR:
				
				llvar	= msg_for_processing(next_field,LLVAR);
				var_field = atoi(llvar);
				next_field = next_field+LLVAR;
				if(debug == 1)
					ReturnIso8583FieldValue(msg_input, j+1  , msg_for_processing(next_field,var_field));
				response_0210_generic_from_iso +=msg_for_processing(next_field,var_field);
				response_0210_generic_from_iso +=delimiter;
				next_field = next_field+var_field;
				break;
			
			case FIXED:
				
				
				next_field = next_field+iso_field_length[j+1];
				if((j+1 != 0) && (j+1 != 1))
				{
					if((j+1) == 11)
					{
						retorno_125 += msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]);
						retorno_125 +=delimiter;
					}
					if((j+1) == 37)
					{
						retorno_125 += msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]);
						retorno_125 +=delimiter;
					}
					
					if(j+1 == 53)
					{
						msg_processing_053 = msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]);
						if(debug == 1)

							ReturnIso8583FieldValue(msg_input, j+1  ,test_iso_new.RetornoAsciiComplete(msg_processing_053(0,8),8));	
						
						response_0210_generic_from_iso +=test_iso_new.RetornoAsciiComplete(msg_processing_053(0,8),8) ;
						response_0210_generic_from_iso +=delimiter;
					}
					else
					{
						if(debug == 1)
							ReturnIso8583FieldValue(msg_input, j+1  , msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]));
					
						response_0210_generic_from_iso +=msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]);
						response_0210_generic_from_iso +=delimiter;
					}
				}
			
			}
		}
		
	}

  	return retorno_125;

}

int IsoBitMap::RetornoFieldNumber(int incoming_field )
{

	int length_field = 0;

	if ((incoming_field == 2) || (incoming_field == 32) || (incoming_field == 33) || (incoming_field == 35)
		                      || (incoming_field == 44) || (incoming_field == 45) || (incoming_field == 100)
							  || (incoming_field == 101) || (incoming_field == 102) || (incoming_field == 103))
	{
		length_field = 2;

	}
	else
	if ((incoming_field == 48) || (incoming_field == 54) || (incoming_field == 56) || (incoming_field == 57)
		                       || (incoming_field == 58) || (incoming_field == 59) || (incoming_field == 60)
							   || (incoming_field == 61) || (incoming_field == 63) || (incoming_field == 118)
							   || (incoming_field == 119) || (incoming_field == 120)|| (incoming_field == 123)
							   || (incoming_field == 125))
	{
		length_field = 3;
	}
	else
	{
		length_field = 0;
	}

	return length_field;

	
}

RWCString Iso8583Msg::getIsoGenericTerminalIdITBIS( RWCString incoming) 
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

	  return	pos_settlement_data+","+transaction_amount+","+card_acceptor_id_code+","+card_acceptor_terminal_id;
		
}



RWCString IsoBitMap::RetornoPreZeroes(int incoming_field )
{

	 
	RWCString test_pre;	

	char pre_test = '\x30';
	char buffer[3] = {""};
	_itoa( incoming_field, buffer, 10 );
	test_pre = buffer ;
	size_t test = 5-test_pre.length();
	test_pre.prepend(pre_test , test);

	return test_pre;
	
}

void IsoBitMap::ReturnIso8583FieldValue(char *msg_type, int field_value, RWCString field_name)
{
	
	cout << "    <field id=*" << field_value  << "* value=<"   << field_name	<< ">" << endl;  
	

}

IsoBitMap::~IsoBitMap()
{

}
