// Iso8583Msg.cpp: implementation of the Iso8583Msg class.
//
//////////////////////////////////////////////////////////////////////

#include "Iso8583Msg.h"
//#include "messageprocess.h"		// To Save Message

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Iso8583Msg::Iso8583Msg()
{
	bit_map1	= "1000000000000000000000000000000000000000000000000000000000000000";
	bit_map2	= "0000000000000000000000000000000000000000000000000000000000000000";
	bit_map_iso  = bit_map1+bit_map2;
	msg_type						= "";
	header							= "";
	tpdu_header						= "";
	converted_iso_posterm			= "";
	card_number						= "";
	retornoasciicomplete			= "";
	retornohexadecimalcomplete      = "";
	isomsg8583						= "";
	complete_iso8583_msg			= "";
	isomsg8583complete              = "";
	bit_map_ascii                   = "";
	complete_0800_iso8583_msg		= "";
	bit_map							= "B23CC48128E190180000000000000128";
	message_type					= "";
	processing_code					= "";			/*003  L6  */
	transaction_amount				= "";			/*004  L12 */ 
	transmition_date_time			= "";
	convertion_rate					= "";
	system_trace					= "";
	time_local_transaction			= "";
	date_local_transaction			= "";
	expiration_date					= "";
	capture_date					= "";
	merchant_type					= "";
	date_settlement					= "";
	pos_entry_mode					= "";
	for_athd						= "";
	pos_condition_code				= "";
	acquiring_institution_id_code	= "";
	track_2							= "";
	retrieval_reference_number		= "";
	card_acceptor_terminal_id		= "";
	card_acceptor_id_code			= "";
	card_acceptor_name_location		= "";
	track1							= "";
	additional_data					= "";
	pos_retailer_data				= "";
	currency_code_transaction		= "";
	pin_data						= "";
	pos_terminal_data				= "";
	pos_issuer_data					= "";
	field_63						= "";
	original_data_elements			= "",
	pos_terminal_address_branch		= "";
	echo_data						= "";
	network_managment_info_code		= "";
	pos_invoice_data				= "";
	pos_settlement_data				= "";
	switch_key						= "";
	F1,  F2 ,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20	,			
	F21, F22 , F23, F24, F25, F26, F27, F28, F29, F30, F31, F32, F33, F34, F35, F36, F37, F38, F39, F40	,			
	F41, F42 , F43, F44, F45, F46, F47, F48, F49, F50, F51, F52, F53, F54, F55, F56, F57, F58, F59, F60	,
	F61, F62 , F63, F64, F65, F66, F67, F68, F69, F70, F71, F72, F73, F74, F75, F76, F77, F78, F79, F80 ,	
	F81, F82 , F83, F84, F85, F86, F87, F88, F89, F90, F91, F92, F93, F94, F95, F96, F97, F98, F99, F100 ,	
	F101,F102 ,F103,F104,F105,F106,F107,F108,F109,F110,F111,F112,F113,F114,F115,F116,F117,F118,F119,F120 ,
	F121,F122 ,F123,F124,F125,F126,F127,F128 = "";
	llvar = 0;
	lllvar = 0;
}

RWCString Iso8583Msg::setMapIsoPosTermFromGeneric( RWCString incoming, char *application, char *header_msg ,int debug)
{


	RWTValVector<RWCString> iso_field(129,"0");
	RWCString F1;
	RWCString field_number;
	RWCString header_tpdu = header_msg;
	RWCString valor_field;
	RWCString msg_reponse_with_tcp_header = "";
	RWCTokenizer next(incoming);
	RWCTokenizer next2(incoming);
	RWCString token;
	RWCString token2;
	int field = 0;
	int i = 0;
	int count = 0;
	int field_count = 0;
	int counter_token = 0;
	char incoming_field[256] = {""};
	
		
	while(!(token=next(",")).isNull())
	{	
			counter_token++;
	}

	Iso8583Msg testiso200;

	if (strcmp(application,"posterm") == 0)
	{
		testiso200.setIsoMsg8583("TPDU", testiso200.RetornoHexadecimalComplete(header_tpdu,5));
	}
	if (strcmp(application,"base24") == 0)
	{
		 testiso200.setIsoMsg8583("header", header_tpdu);
	}
	
	for (i=0; i<counter_token; i++)
	{
		while(!(token=next2(",")).isNull())
		{	
	
			F1 = token; 
			if( count == 0)
			{

				valor_field = F1;
				testiso200.setIsoMsg8583All("00001", valor_field);

				iso_field [1] = valor_field;
				field_number = "00001";
				count++;
			}	
			else
			{
												
				field_number = F1(0,MSG_FIELD);
				valor_field = F1(MSG_FIELD,F1.length()-MSG_FIELD);
		

				if((atoi(field_number) > 0) && (atoi(field_number) <= 129))
				{
					iso_field[atoi(field_number)] = valor_field;
					field_count = atoi(field_number); 

				}
				else
				{
					cout << "Problemas en uno de los campos recibidos" << endl;
					cout << "El ultimo csmpo recibido bien es : " << field_count <<  endl;
					//cout << "Salir " << endl;
				}

				if ((strcmp(application,"posterm") == 0) && (atoi(field_number) == 52))
				{
					testiso200.setIsoMsg8583All("00052",testiso200.RetornoHexadecimalComplete(valor_field,8));
				}
				
				
				
				
				/*
				if ((strcmp(application,"posterm") == 0) && (atoi(field_number) == 63))
				{
					//testiso200.setIsoMsg8583All("00052",testiso200.RetornoHexadecimalComplete(valor_field,8));
				
					int counter_token = 0;
					RWCString field_63_01;
					RWCString field_63_02;
					RWCString field_63_03;
					RWCTokenizer next1(valor_field);
					RWCString token1;

					while(!(token1=next1("!")).isNull())
					{	
						if (counter_token == 0)
						{
							field_63_01 = token1; 
		
						}			

						if (counter_token == 1)
						{
							field_63_02 = token1; 
		
						}			

						if (counter_token == 2)
						{
							field_63_03 = token1; 
	
		
						}	

						counter_token++;
					}

					int long_token2 = 0;
					long_token2 = field_63_02.length(); 
					int long_token3 = 0;
					long_token3 = field_63_03.length(); 
					RWCString field_048 = "";

					if( (long_token2 > 3) || (long_token3 > 9))
					{
	
					  field_048 = field_63_02((long_token2-3),3)+field_63_03((long_token3-10),10 );
					}
					else
					{
						field_048 = "0000000000000";
					}

					 testiso200.setIsoMsg8583All("00048", field_048);
				
				}
				*/
				if ((strcmp(application,"posterm") == 0) && (atoi(field_number) != 52))
				{
					testiso200.setIsoMsg8583All(field_number, iso_field [atoi(field_number)]);
				}
			
				if (strcmp(application,"base24") == 0)
				{
					testiso200.setIsoMsg8583All(field_number, iso_field [atoi(field_number)]);
				}
			
			}
			if(debug == 1)
				cout << "    <field id=*"<<atoi(field_number)<<"* value=<"   << iso_field[atoi(field_number)]				<< ">" << endl;  
			
		}
	}


	msg_reponse_with_tcp_header += testiso200.getIsoMsg8583(application);
	
	return msg_reponse_with_tcp_header;
}

RWCString Iso8583Msg::setMapIsoPosTermFromGeneric100( RWCString incoming, char *application, char *header_msg ,int debug)
{


	RWTValVector<RWCString> iso_field(129,"0");
	RWCString F1;
	RWCString field_number;
	RWCString header_tpdu = header_msg;
	RWCString valor_field;
	RWCString msg_reponse_with_tcp_header = "";
	RWCTokenizer next(incoming);
	RWCTokenizer next2(incoming);
	RWCString token;
	RWCString token2;
	int field = 0;
	int i = 0;
	int count = 0;
	int field_count = 0;
	int counter_token = 0;
	char incoming_field[256] = {""};
	
		
	while(!(token=next(",")).isNull())
	{	
			counter_token++;
	}

	Iso8583Msg testiso200;

	if (strcmp(application,"posterm") == 0)
	{
		testiso200.setIsoMsg8583("TPDU", testiso200.RetornoHexadecimalComplete(header_tpdu,5));
	}
	if (strcmp(application,"base24") == 0)
	{
		 testiso200.setIsoMsg8583("header", header_tpdu);
	}
	
	for (i=0; i<counter_token; i++)
	{
		while(!(token=next2(",")).isNull())
		{	
	
			F1 = token; 
			if( count == 0)
			{

				valor_field = F1;
				testiso200.setIsoMsg8583All("00001", valor_field);

				iso_field [1] = valor_field;
				field_number = "00001";
				count++;
			}	
			else
			{
												
				field_number = F1(0,MSG_FIELD);
				valor_field = F1(MSG_FIELD,F1.length()-MSG_FIELD);
		

				if((atoi(field_number) > 0) && (atoi(field_number) <= 129))
				{
					iso_field[atoi(field_number)] = valor_field;
					field_count = atoi(field_number); 

				}
				else
				{
					cout << "Problemas en uno de los campos recibidos" << endl;
					cout << "El ultimo csmpo recibido bien es : " << field_count <<  endl;
				}

				if ((strcmp(application,"posterm") == 0) && (atoi(field_number) == 52))
				{
					testiso200.setIsoMsg8583All("00052",testiso200.RetornoHexadecimalComplete(valor_field,8));
				}
				
				
				
				
				/*
				if ((strcmp(application,"posterm") == 0) && (atoi(field_number) == 63))
				{
					//testiso200.setIsoMsg8583All("00052",testiso200.RetornoHexadecimalComplete(valor_field,8));
				
					int counter_token = 0;
					RWCString field_63_01;
					RWCString field_63_02;
					RWCString field_63_03;
					RWCTokenizer next1(valor_field);
					RWCString token1;

					while(!(token1=next1("!")).isNull())
					{	
						if (counter_token == 0)
						{
							field_63_01 = token1; 
		
						}			

						if (counter_token == 1)
						{
							field_63_02 = token1; 
		
						}			

						if (counter_token == 2)
						{
							field_63_03 = token1; 
	
		
						}	

						counter_token++;
					}

					int long_token2 = 0;
					long_token2 = field_63_02.length(); 
					int long_token3 = 0;
					long_token3 = field_63_03.length(); 
					RWCString field_048 = "";

					if( (long_token2 > 3) || (long_token3 > 9))
					{
	
					  field_048 = field_63_02((long_token2-3),3)+field_63_03((long_token3-10),10 );
					}
					else
					{
						field_048 = "0000000000000";
					}

					 testiso200.setIsoMsg8583All("00048", field_048);
				
				}
				*/
				if ((strcmp(application,"posterm") == 0) && (atoi(field_number) != 52))
				{
					testiso200.setIsoMsg8583All(field_number, iso_field [atoi(field_number)]);
				}
			
				if (strcmp(application,"base24") == 0)
				{
					testiso200.setIsoMsg8583All(field_number, iso_field [atoi(field_number)]);
				}
			
			}
			if(debug == 1)
				cout << "    <field id=*"<<atoi(field_number)<<"* value=<"   << iso_field[atoi(field_number)]				<< ">" << endl;  
			
		}
	}

	msg_reponse_with_tcp_header += testiso200.getIsoMsg8583(application);
	
	return msg_reponse_with_tcp_header;
}

RWCString Iso8583Msg::setMapIsoBase24FromGeneric( RWCString incoming, char *application,int debug)
{


	RWTValVector<RWCString> iso_field(129,"0");
	RWCString F1;
	RWCString field_number;
	RWCString valor_field;
	RWCString msg_reponse_with_tcp_header = "";
	RWCTokenizer next(incoming);
	RWCTokenizer next2(incoming);
	RWCString token;
	RWCString token2;
	int test = 0;

	int field = 0;
	int i = 0;
	int counter_token = 0;	
	
	char incoming_field[256] = {""};
	
	int count = 0;
	
		
	while(!(token=next(",")).isNull())
	{	
			counter_token++;
	}

	Iso8583Msg testiso200;
	for (i=0; i<counter_token; i++)
	{
		while(!(token=next2(",")).isNull())
		{	
	
			F1 = token; 

			if( count == 0)
			{

				field_number = F1(0,MSG_FIELD);
				valor_field = F1(MSG_FIELD,F1.length()-MSG_FIELD);
			
				if (strcmp(application,"posterm") == 0)
				{
					iso_field[atoi(field_number)] = testiso200.setIsoMsg8583("TPDU", testiso200.RetornoHexadecimalComplete(valor_field,5));
				}
				if (strcmp(application,"base24") == 0)
				{
					iso_field[atoi(field_number)] = testiso200.setIsoMsg8583("header", valor_field);
				}
				testiso200.setIsoMsg8583All(field_number, iso_field [atoi(field_number)]);
				count++;
			}	
			else
			{
	
				field_number = F1(0,MSG_FIELD);
				valor_field = F1(MSG_FIELD,F1.length()-MSG_FIELD);
		
				iso_field[atoi(field_number)] = valor_field;
				testiso200.setIsoMsg8583All(field_number, iso_field [atoi(field_number)]);
			}
		
			
				if(debug == 1)
		

				cout << "    <field id=*"<<atoi(field_number)<<"* value=<"   << iso_field[atoi(field_number)]				<< ">" << endl;  

			
		}
	}


	msg_reponse_with_tcp_header += testiso200.getIsoMsg8583(application);
	
	return msg_reponse_with_tcp_header;
}

//This funtion is for create a message for B24
//This fiction read the iso-generic message a reade each token a put in 
//variable that correspond.

//This funtion create the message ISO8583 B24 
RWCString Iso8583Msg::setIsoMsg8583(RWCString message, RWCString input)
{

	char buffer[20];

	if(message == "header")
	{
	  
		msg_type = input;
	
	}
	if(message == "TPDU")
	{
	  
		msg_type += input;
	
	}
	if(message == "MTI")
	{
	  
		msg_type += input;
	
	}
	if(message == "F2")
	{
	    
		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input=RWCString(buffer)+input;
		}
		isomsg8583 += input;
		bit_map_iso(1,1) = "1";
	
	}
	if(message == "F3")
	{
	  
		isomsg8583 += input;
		bit_map_iso(2,1) = "1";
	
	}

	if(message == "F4")
	{
	  
		isomsg8583 += input;
		bit_map_iso(3,1) = "1";
	
	}

	if(message == "F7")
	{
	  
		isomsg8583 += input;
		bit_map_iso(6,1) = "1";
	
	}

	if(message == "F11")
	{
	  
		isomsg8583 += input;
		bit_map_iso(10,1) = "1";
	
	}	
	if(message == "F12")
	{
	  
		isomsg8583 += input;
		bit_map_iso(11,1) = "1";
	
	}	
	if(message == "F13")
	{
	  
		isomsg8583 += input;
		bit_map_iso(12,1) = "1";
	
	}
	if(message == "F15")
	{
	  
		isomsg8583 += input;
		bit_map_iso(14,1) = "1";
	
	}

	if(message == "F35")
	{
	  

		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input=RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(34,1) = "1";
	
	}
	if(message == "F37")
	{
	  
	
		isomsg8583 += input;
		bit_map_iso(36,1) = "1";
	
	}
	if(message == "F41")
	{
	  
		isomsg8583 += input;
		bit_map_iso(40,1) = "1";
	
	}

	if(message == "F45")
	{
	  
		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input=RWCString(buffer)+input;
		}
		isomsg8583 += input;
		bit_map_iso(44,1) = "1";
	
	}

	if(message == "F48")
	{
	  	_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(47,1) = "1";
	
	}

	if(message == "F49")
	{
	  
		isomsg8583 += input;
		bit_map_iso(48,1) = "1";
	
	}
	if(message == "F52")
	{
	  
		isomsg8583 += input;
		bit_map_iso(51,1) = "1";
	
	}

	if(message == "F70")
	{
	  
		isomsg8583 += input;
		bit_map_iso(69,1) = "1";
	
	}
	if(message == "F90")
	{
	  
		isomsg8583 += input;
		bit_map_iso(89,1) = "1";
	
	}
	if(message == "F102")
	{
	  
		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input=RWCString(buffer)+input;
		}
		isomsg8583 += input;
		bit_map_iso(101,1) = "1";
	
	}
	if(message == "F123")
	{
	  	_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(122,1) = "1";
	
	}

	if(message == "F125")
	{
	  	_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(124,1) = "1";
	
	}


	isomsg8583complete = isomsg8583;
	return isomsg8583complete;
}

RWCString Iso8583Msg::setIsoMsg8583All(RWCString message, RWCString input)
{

	char buffer[20];

	if(message == "header")
	{
	  
		msg_type = input;
	
	}
	if(message == "TPDU")
	{
	  
		msg_type += input;
	
	}
	if(message == "00001")
	{
	  
		msg_type += input;
	
	}
	if(message == "00002")
	{
	    
		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input=RWCString(buffer)+input;
		}
		isomsg8583 += input;
		bit_map_iso(1,1) = "1";
	
	}
	if(message == "00003")
	{
	  
		isomsg8583 += input;
		bit_map_iso(2,1) = "1";
	
	}

	if(message == "00004")
	{
	  
		isomsg8583 += input;
		bit_map_iso(3,1) = "1";
	
	}

	if(message == "00007")
	{
	  
		isomsg8583 += input;
		bit_map_iso(6,1) = "1";
	
	}

	if(message == "00011")
	{
	  
		isomsg8583 += input;
		bit_map_iso(10,1) = "1";
	
	}	
	if(message == "00012")
	{
	  
		isomsg8583 += input;
		bit_map_iso(11,1) = "1";
	
	}	
	if(message == "00013")
	{
	  
		isomsg8583 += input;
		bit_map_iso(12,1) = "1";
	
	}
	if(message == "00014")
	{
	  
		isomsg8583 += input;
		bit_map_iso(13,1) = "1";
	
	}
	if(message == "00015")
	{
	  
		isomsg8583 += input;
		bit_map_iso(14,1) = "1";
	
	}

	if(message == "00017")
	{
	  
		isomsg8583 += input;
		bit_map_iso(16,1) = "1";
	
	}
	if(message == "00018")
	{
	  
		isomsg8583 += input;
		bit_map_iso(17,1) = "1";
	
	}
	if(message == "00022")
	{
	  
		isomsg8583 += input;
		bit_map_iso(21,1) = "1";
	
	}
	if(message == "00025")
	{
	  
		isomsg8583 += input;
		bit_map_iso(24,1) = "1";
	
	}

	if(message == "00032")
	{
	  
		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input=RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(31,1) = "1";
	
	}

	
	if(message == "00035")
	{
	  

		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input=RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(34,1) = "1";
	
	}

	if(message == "00037")
	{
	  

	
		isomsg8583 += input;
		bit_map_iso(36,1) = "1";
	
	}
	if(message == "00039")
	{
	  

	
		isomsg8583 += input;
		bit_map_iso(38,1) = "1";
	
	}
	if(message == "00041")
	{
	  
		isomsg8583 += input;
		bit_map_iso(40,1) = "1";
	
	}
	if(message == "00042")
	{
	  
		isomsg8583 += input;
		bit_map_iso(41,1) = "1";
	
	}
	if(message == "00043")
	{
	  
		isomsg8583 += input;
		bit_map_iso(42,1) = "1";
	
	}

	if(message == "00045")
	{
	  
		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input=RWCString(buffer)+input;
		}
		isomsg8583 += input;
		bit_map_iso(44,1) = "1";
	
	}

	if(message == "00048")
	{
	  	_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(47,1) = "1";
	
	}

	if(message == "00049")
	{
	  
		isomsg8583 += input;
		bit_map_iso(48,1) = "1";
	
	}
	if(message == "00052")
	{
	  
		isomsg8583 += input;
		bit_map_iso(51,1) = "1";
	
	}

	if(message == "00054")
	{
	  
		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(53,1) = "1";
	
	}
	if(message == "00060")
	{
	  
		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(59,1) = "1";
	
	}
	if(message == "00061")
	{
	  
	  	_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(60,1) = "1";
	}
	if(message == "00063")
	{
	  	_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(62,1) = "1";
	}



	if(message == "00070")
	{
	  
		isomsg8583 += input;
		bit_map_iso(69,1) = "1";
	
	}
	if(message == "00090")
	{
	  
		isomsg8583 += input;
		bit_map_iso(89,1) = "1";
	
	}
	if(message == "00102")
	{
	  
		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input=RWCString(buffer)+input;
		}
		isomsg8583 += input;
		bit_map_iso(101,1) = "1";
	
	}

	if(message == "00103")
	{
	  
		_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input=RWCString(buffer)+input;
		}
		isomsg8583 += input;
		bit_map_iso(102,1) = "1";
	
	}
	if(message == "00120")
	{
	  	_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(119,1) = "1";
	
	}

	if(message == "00123")
	{
	  	_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(122,1) = "1";
	
	}

	if(message == "00125")
	{
	  	_itoa( (input.length()), buffer, 10 );
		if(input.length() < 10)
		{
			input="00"+RWCString(buffer)+input;
		}
		else
		if(  (input.length() > 10) && (input.length() < 99))
		{
			input="0"+RWCString(buffer)+input;
		}
		else
		{
			input="0"+RWCString(buffer)+input;
		}
		
		isomsg8583 += input;
		bit_map_iso(124,1) = "1";
	
	}

	RWCString last_char = '\x03';
	isomsg8583complete = isomsg8583;
	isomsg8583complete=isomsg8583complete+last_char;
	
	return isomsg8583complete;
}


RWCString Iso8583Msg::getIsoMsg8583(RWCString type)
{
	char bit_map_ascii2[33] = {""};
	char bit_map_ascii_to_convert[2] = {""};
	RWCString test_bit;

	RWCString pin_wk_ascii = "";
	RWCString pin_bk_hex = "";
	RWCString pin_bk_hex_sub = "";
	char vic_test[3]   = {""};
	char vic_test2[17] = {""};

	int i;
	for( i = 0; i < 32; i++)
	{
										
		test_bit = setBitMap(bit_map_iso( (i*4),4 ));

		strcpy(bit_map_ascii_to_convert, test_bit);
		strcat(bit_map_ascii2, bit_map_ascii_to_convert);
		
	}


	pin_wk_ascii = bit_map_ascii2;
	
	
	if (type == "posterm")
	{
		for( i = 0; i < 16; i++)
		{
										
			pin_bk_hex_sub=pin_wk_ascii((i*2),2);
								
		
			pin_bk_hex+=RetornoHexa(pin_bk_hex_sub);

		}
		isomsg8583complete = msg_type+pin_bk_hex+isomsg8583complete;
	}

	if (type == "base24")
	{
		for( i = 0; i < 16; i++)
		{
										
			pin_bk_hex_sub=pin_wk_ascii((i*2),2);
								
		
			pin_bk_hex+=pin_bk_hex_sub;

		}
		isomsg8583complete = msg_type+pin_bk_hex+isomsg8583complete;
	}

	return isomsg8583complete;
}

RWCString  Iso8583Msg::RetornoHexadecimalComplete( RWCString ascii_input, int input)
{
	RWCString pin_wk_ascii = ascii_input;
	RWCString pin_bk_hex = "";
	RWCString pin_bk_hex_sub = "";
	int i;
	for( i = 0; i < input; i++)
	{
										
		pin_bk_hex_sub=pin_wk_ascii((i*2),2);
								
		
		pin_bk_hex+=RetornoHexa(pin_bk_hex_sub);
	

	}

	retornohexadecimalcomplete = pin_bk_hex;
	return retornohexadecimalcomplete;
}


RWCString  Iso8583Msg::RetornoAsciiComplete( RWCString ascii_input, int input)
{
	RWCString pin_wk_ascii = ascii_input;

	RWCString pin_bk_hex = "";
	char buffer[32] = {""};
	unsigned char ch2;
	memcpy( buffer, ascii_input ,input);

	int i;
	for( i = 0; i < input; i++)
	{
										
		ch2=buffer[i];
		pin_bk_hex+=RetornoASCII(ch2);

	}

	retornoasciicomplete= pin_bk_hex;
	return retornoasciicomplete;
}



RWCString  Iso8583Msg::RetornoAsciiCompletePB( RWCString ascii_input, int input)
{
	RWCString pin_wk_ascii = ascii_input;

	RWCString pin_bk_hex = "";
	char buffer[32] = {""};
	unsigned char ch2;
	memcpy( buffer, ascii_input ,input);

	int i;
	for( i = 0; i < input; i++)
	{
										
		ch2=buffer[i];
		pin_bk_hex+=RetornoASCIIPB(ch2);

	}

	retornoasciicomplete= pin_bk_hex;
	return retornoasciicomplete;
}

RWCString  Iso8583Msg::RetornoASCII(char  hex_input)
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


RWCString  Iso8583Msg::RetornoASCIIPB(char  hex_input)
{
	

	if (hex_input  == '\x00') 
		return "0";
	if (hex_input  == '\x01') 
		return "1";
	if (hex_input  == '\x02') 
		return "2";
	if (hex_input  == '\x03') 
		return "3";
	if (hex_input  == '\x04') 
		return "4";
	if (hex_input  == '\x05') 
		return "5";
	if (hex_input  == '\x06') 
		return "6";
	if (hex_input  == '\x07') 
		return "7";
	if (hex_input  == '\x08') 
		return "8";
	if (hex_input  == '\x09') 
		return "9";
	if (hex_input  == '\x0A') 
		return "A";
	if (hex_input  == '\x0B') 
		return "B";
	if (hex_input  == '\x0C') 
		return "C";
	if (hex_input  == '\x0D') 
		return "D";
	if (hex_input  == '\x0E') 
		return "E";
	if (hex_input  == '\x0F') 
		return "F";

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
		return "9";
	if (hex_input  == '\x71') 
		return "8";
	if (hex_input  == '\x72') 
		return "B";
	if (hex_input  == '\x73') 
		return "A";
	if (hex_input  == '\x74') 
		return "D";
	if (hex_input  == '\x75') 
		return "C";
	if (hex_input  == '\x76') 
		return "F";
	if (hex_input  == '\x77') 
		return "E";
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
		return "7";
	if (hex_input  == '\x7F') 
		return "6";

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

char  Iso8583Msg::RetornoHexa( RWCString hex_input)
{
	


	if (hex_input  == "00") 
		return '\x00';
	if (hex_input  == "01") 
		return '\x01';
	if (hex_input  == "02") 
		return '\x02';
	if (hex_input  == "03") 
		return '\x03';
	if (hex_input  == "04") 
		return '\x04';
	if (hex_input  == "05") 
		return '\x05';
	if (hex_input  == "06") 
		return '\x06';
	if (hex_input  == "07") 
		return '\x07';
	if (hex_input  == "08") 
		return '\x08';
	if (hex_input  == "09") 
		return '\x09';
	if (hex_input  == "0A") 
		return '\x0A';
	if (hex_input  == "0B") 
		return '\x0B';
	if (hex_input  == "0C") 
		return '\x0C';
	if (hex_input  == "0D") 
		return '\x0D';
	if (hex_input  == "0E") 
		return '\x0E';
	if (hex_input  == "0F") 
		return '\x0F';

	if (hex_input  == "10") 
		return '\x10';
	if (hex_input  == "11") 
		return '\x11';
	if (hex_input  == "12") 
		return '\x12';
	if (hex_input  == "13") 
		return '\x13';
	if (hex_input  == "14") 
		return '\x14';
	if (hex_input  == "15") 
		return '\x15';
	if (hex_input  == "16") 
		return '\x16';
	if (hex_input  == "17") 
		return '\x17';
	if (hex_input  == "18") 
		return '\x18';
	if (hex_input  == "19") 
		return '\x19';
	if (hex_input  == "1A") 
		return '\x1A';
	if (hex_input  == "1B") 
		return '\x1B';
	if (hex_input  == "1C") 
		return '\x1C';
	if (hex_input  == "1D") 
		return '\x1D';
	if (hex_input  == "1E") 
		return '\x1E';
	if (hex_input  == "1F") 
		return '\x1F';

	if (hex_input  == "20") 
		return '\x20';
	if (hex_input  == "21") 
		return '\x21';
	if (hex_input  == "22") 
		return '\x22';
	if (hex_input  == "23") 
		return '\x23';
	if (hex_input  == "24") 
		return '\x24';
	if (hex_input  == "25") 
		return '\x25';
	if (hex_input  == "26") 
		return '\x26';
	if (hex_input  == "27") 
		return '\x27';
	if (hex_input  == "28") 
		return '\x28';
	if (hex_input  == "29") 
		return '\x29';
	if (hex_input  == "2A") 
		return '\x2A';
	if (hex_input  == "2B") 
		return '\x2B';
	if (hex_input  == "2C") 
		return '\x2C';
	if (hex_input  == "2D") 
		return '\x2D';
	if (hex_input  == "2E") 
		return '\x2E';
	if (hex_input  == "2F") 
		return '\x2F';

	
	if (hex_input  == "30") 
		return '\x30';
	if (hex_input  == "31") 
		return '\x31';
	if (hex_input  == "32") 
		return '\x32';
	if (hex_input  == "33") 
		return '\x33';
	if (hex_input  == "34") 
		return '\x34';
	if (hex_input  == "35") 
		return '\x35';
	if (hex_input  == "36") 
		return '\x36';
	if (hex_input  == "37") 
		return '\x37';
	if (hex_input  == "38") 
		return '\x38';
	if (hex_input  == "39") 
		return '\x39';
	if (hex_input  == "3A") 
		return '\x3A';
	if (hex_input  == "3B") 
		return '\x3B';
	if (hex_input  == "3C") 
		return '\x3C';
	if (hex_input  == "3D") 
		return '\x3D';
	if (hex_input  == "3E") 
		return '\x3E';
	if (hex_input  == "3F") 
		return '\x3F';

	if (hex_input  == "40") 
		return '\x40';
	if (hex_input  == "41") 
		return '\x41';
	if (hex_input  == "42") 
		return '\x42';
	if (hex_input  == "43") 
		return '\x43';
	if (hex_input  == "44") 
		return '\x44';
	if (hex_input  == "45") 
		return '\x45';
	if (hex_input  == "46") 
		return '\x46';
	if (hex_input  == "47") 
		return '\x47';
	if (hex_input  == "48") 
		return '\x48';
	if (hex_input  == "49") 
		return '\x49';
	if (hex_input  == "4A") 
		return '\x4A';
	if (hex_input  == "4B") 
		return '\x4B';
	if (hex_input  == "4C") 
		return '\x4C';
	if (hex_input  == "4D") 
		return '\x4D';
	if (hex_input  == "4E") 
		return '\x4E';
	if (hex_input  == "4F") 
		return '\x4F';
	
	if (hex_input  == "50") 
		return '\x50';
	if (hex_input  == "51") 
		return '\x51';
	if (hex_input  == "52") 
		return '\x52';
	if (hex_input  == "53") 
		return '\x53';
	if (hex_input  == "54") 
		return '\x54';
	if (hex_input  == "55") 
		return '\x55';
	if (hex_input  == "56") 
		return '\x56';
	if (hex_input  == "57") 
		return '\x57';
	if (hex_input  == "58") 
		return '\x58';
	if (hex_input  == "59") 
		return '\x59';
	if (hex_input  == "5A") 
		return '\x5A';
	if (hex_input  == "5B") 
		return '\x5B';
	if (hex_input  == "5C") 
		return '\x5C';
	if (hex_input  == "5D") 
		return '\x5D';
	if (hex_input  == "5E") 
		return '\x5E';
	if (hex_input  == "5F") 
		return '\x5F';
	
	if (hex_input  == "60") 
		return '\x60';
	if (hex_input  == "61") 
		return '\x61';
	if (hex_input  == "62") 
		return '\x62';
	if (hex_input  == "63") 
		return '\x63';
	if (hex_input  == "64") 
		return '\x64';
	if (hex_input  == "65") 
		return '\x65';
	if (hex_input  == "66") 
		return '\x66';
	if (hex_input  == "67") 
		return '\x67';
	if (hex_input  == "68") 
		return '\x68';
	if (hex_input  == "69") 
		return '\x69';
	if (hex_input  == "6A") 
		return '\x6A';
	if (hex_input  == "6B") 
		return '\x6B';
	if (hex_input  == "6C") 
		return '\x6C';
	if (hex_input  == "6D") 
		return '\x6D';
	if (hex_input  == "6E") 
		return '\x6E';
	if (hex_input  == "6F") 
		return '\x6F';

	if (hex_input  == "70") 
		return '\x70';
	if (hex_input  == "71") 
		return '\x71';
	if (hex_input  == "72") 
		return '\x72';
	if (hex_input  == "73") 
		return '\x73';
	if (hex_input  == "74") 
		return '\x74';
	if (hex_input  == "75") 
		return '\x75';
	if (hex_input  == "76") 
		return '\x76';
	if (hex_input  == "77") 
		return '\x77';
	if (hex_input  == "78") 
		return '\x78';
	if (hex_input  == "79") 
		return '\x79';
	if (hex_input  == "7A") 
		return '\x7A';
	if (hex_input  == "7B") 
		return '\x7B';
	if (hex_input  == "7C") 
		return '\x7C';
	if (hex_input  == "7D") 
		return '\x7D';
	if (hex_input  == "7E") 
		return '\x7E';
	if (hex_input  == "7F") 
		return '\x7F';

	if (hex_input  == "80") 
		return '\x80';
	if (hex_input  == "81") 
		return '\x81';
	if (hex_input  == "82") 
		return '\x82';
	if (hex_input  == "83") 
		return '\x83';
	if (hex_input  == "84") 
		return '\x84';
	if (hex_input  == "85") 
		return '\x85';
	if (hex_input  == "86") 
		return '\x86';
	if (hex_input  == "87") 
		return '\x87';
	if (hex_input  == "88") 
		return '\x88';
	if (hex_input  == "89") 
		return '\x89';
	if (hex_input  == "8A") 
		return '\x8A';
	if (hex_input  == "8B") 
		return '\x8B';
	if (hex_input  == "8C") 
		return '\x8C';
	if (hex_input  == "8D") 
		return '\x8D';
	if (hex_input  == "8E") 
		return '\x8E';
	if (hex_input  == "8F") 
		return '\x8F';

	if (hex_input  == "90") 
		return '\x90';
	if (hex_input  == "91") 
		return '\x91';
	if (hex_input  == "92") 
		return '\x92';
	if (hex_input  == "93") 
		return '\x93';
	if (hex_input  == "94") 
		return '\x94';
	if (hex_input  == "95") 
		return '\x95';
	if (hex_input  == "96") 
		return '\x96';
	if (hex_input  == "97") 
		return '\x97';
	if (hex_input  == "98") 
		return '\x98';
	if (hex_input  == "99") 
		return '\x99';
	if (hex_input  == "9A") 
		return '\x9A';
	if (hex_input  == "9B") 
		return '\x9B';
	if (hex_input  == "9C") 
		return '\x9C';
	if (hex_input  == "9D") 
		return '\x9D';
	if (hex_input  == "9E") 
		return '\x9E';
	if (hex_input  == "9F") 
		return '\x9F';

	if (hex_input  == "A0") 
		return '\xA0';
	if (hex_input  == "A1") 
		return '\xA1';
	if (hex_input  == "A2") 
		return '\xA2';
	if (hex_input  == "A3") 
		return '\xA3';
	if (hex_input  == "A4") 
		return '\xA4';
	if (hex_input  == "A5") 
		return '\xA5';
	if (hex_input  == "A6") 
		return '\xA6';
	if (hex_input  == "A7") 
		return '\xA7';
	if (hex_input  == "A8") 
		return '\xA8';
	if (hex_input  == "A9") 
		return '\xA9';
	if (hex_input  == "AA") 
		return '\xAA';
	if (hex_input  == "AB") 
		return '\xAB';
	if (hex_input  == "AC") 
		return '\xAC';
	if (hex_input  == "AD") 
		return '\xAD';
	if (hex_input  == "AE") 
		return '\xAE';
	if (hex_input  == "AF") 
		return '\xAF';

	if (hex_input  == "B0") 
		return '\xB0';
	if (hex_input  == "B1") 
		return '\xB1';
	if (hex_input  == "B2") 
		return '\xB2';
	if (hex_input  == "B3") 
		return '\xB3';
	if (hex_input  == "B4") 
		return '\xB4';
	if (hex_input  == "B5") 
		return '\xB5';
	if (hex_input  == "B6") 
		return '\xB6';
	if (hex_input  == "B7") 
		return '\xB7';
	if (hex_input  == "B8") 
		return '\xB8';
	if (hex_input  == "B9") 
		return '\xB9';
	if (hex_input  == "BA") 
		return '\xBA';
	if (hex_input  == "BB") 
		return '\xBB';
	if (hex_input  == "BC") 
		return '\xBC';
	if (hex_input  == "BD") 
		return '\xBD';
	if (hex_input  == "BE") 
		return '\xBE';
	if (hex_input  == "BF") 
		return '\xBF';
	
	if (hex_input  == "C0") 
		return '\xC0';
	if (hex_input  == "C1") 
		return '\xC1';
	if (hex_input  == "C2") 
		return '\xC2';
	if (hex_input  == "C3") 
		return '\xC3';
	if (hex_input  == "C4") 
		return '\xC4';
	if (hex_input  == "C5") 
		return '\xC5';
	if (hex_input  == "C6") 
		return '\xC6';
	if (hex_input  == "C7") 
		return '\xC7';
	if (hex_input  == "C8") 
		return '\xC8';
	if (hex_input  == "C9") 
		return '\xC9';
	if (hex_input  == "CA") 
		return '\xCA';
	if (hex_input  == "CB") 
		return '\xCB';
	if (hex_input  == "CC") 
		return '\xCC';
	if (hex_input  == "CD") 
		return '\xCD';
	if (hex_input  == "CE") 
		return '\xCE';
	if (hex_input  == "CF") 
		return '\xCF';

	if (hex_input  == "D0") 
		return '\xD0';
	if (hex_input  == "D1") 
		return '\xD1';
	if (hex_input  == "D2") 
		return '\xD2';
	if (hex_input  == "D3") 
		return '\xD3';
	if (hex_input  == "D4") 
		return '\xD4';
	if (hex_input  == "D5") 
		return '\xD5';
	if (hex_input  == "D6") 
		return '\xD6';
	if (hex_input  == "D7") 
		return '\xD7';
	if (hex_input  == "D8") 
		return '\xD8';
	if (hex_input  == "D9") 
		return '\xD9';
	if (hex_input  == "DA") 
		return '\xDA';
	if (hex_input  == "DB") 
		return '\xDB';
	if (hex_input  == "DC") 
		return '\xDC';
	if (hex_input  == "DD") 
		return '\xDD';
	if (hex_input  == "DE") 
		return '\xDE';
	if (hex_input  == "DF") 
		return '\xDF';

	if (hex_input  == "E0") 
		return '\xE0';
	if (hex_input  == "E1") 
		return '\xE1';
	if (hex_input  == "E2") 
		return '\xE2';
	if (hex_input  == "E3") 
		return '\xE3';
	if (hex_input  == "E4") 
		return '\xE4';
	if (hex_input  == "E5") 
		return '\xE5';
	if (hex_input  == "E6") 
		return '\xE6';
	if (hex_input  == "E7") 
		return '\xE7';
	if (hex_input  == "E8") 
		return '\xE8';
	if (hex_input  == "E9") 
		return '\xE9';
	if (hex_input  == "EA") 
		return '\xEA';
	if (hex_input  == "EB") 
		return '\xEB';
	if (hex_input  == "EC") 
		return '\xEC';
	if (hex_input  == "ED") 
		return '\xED';
	if (hex_input  == "EE") 
		return '\xEE';
	if (hex_input  == "EF") 
		return '\xEF';

	if (hex_input  == "F0") 
		return '\xF0';
	if (hex_input  == "F1") 
		return '\xF1';

  if (hex_input  == "F2") 
		return '\xF2';

	if (hex_input  == "F3") 
		return '\xF3';
	if (hex_input  == "F4") 
		return '\xF4';
	if (hex_input  == "F5") 
		return '\xF5';
	if (hex_input  == "F6") 
		return '\xF6';
	if (hex_input  == "F7") 
		return '\xF7';
	if (hex_input  == "F8") 
		return '\xF8';
	if (hex_input  == "F9") 
		return '\xF9';
	if (hex_input  == "FA") 
		return '\xFA';
	if (hex_input  == "FB") 
		return '\xFB';
	if (hex_input  == "FC") 
		return '\xFC';
	if (hex_input  == "FD") 
		return '\xFD';
	if (hex_input  == "FE") 
		return '\xFE';
	if (hex_input  == "FF") 
		return '\xFF';
	

	
	return '\x09';

}



RWCString Iso8583Msg::SetMsgField8583( int input_field ) 
{

	char buffer[20];
 	RWCString msg_reponse_with_tcp_header = "";
	
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
			msg_reponse_with_tcp_header=transmition_date_time;
//			cout << transmition_date_time << endl;


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
			msg_reponse_with_tcp_header=time_local_transaction;

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
			msg_reponse_with_tcp_header=date_local_transaction;

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
		    
			//struct  tstruct;

		//	_ftime( &tstruct );
		//	printf( "Plus milliseconds:\t\t\t%u\n", tstruct.millitm );
    
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


			//cout << endl;
			//cout << "<<<<<<<<<<Valor de primero>>>>>>>>>>> " << primero << endl;
			//cout << "<<<<<<<<<<Valor de segundo>>>>>>>>>>>" << segundo << endl;
			//cout << "<<<<<<<<<<Valor de tercero>>>>>>>>>>> " << tercero << endl;
			//cout << "<<<<<<<<<<Valor de cuarto >>>>>>>>>>>" << cuarto<< endl;
			//cout << endl;

			retrieval_reference_number = ((primero+segundo+tercero)(((primero+segundo+tercero).length()-12),12));
			//((primero+segundo+tercero).length()-12)
			pos_invoice_data=retrieval_reference_number(2,10)+retrieval_reference_number(2,10);

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
	/*
		if (input_field == 70)
		{
			//Este campo no debe ser mayor de 22
			int input_field_length = network_managment_info_code.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			network_managment_info_code = cero_field + network_managment_info_code;
	
		}			
	*/
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
	
			//Este campo no debe ser mayor de 23
			int input_field_length = pos_invoice_data.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			pos_invoice_data = cero_field + pos_invoice_data;
	
		}			

		if (input_field == 125)
		{
	
			//Este campo no debe ser mayor de 15
			int input_field_length = pos_settlement_data.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			pos_settlement_data = cero_field + pos_settlement_data;
	
			
		}			
	


	return msg_reponse_with_tcp_header;

}


RWCString Iso8583Msg::setBitMap( RWCString input_four_bit)
{

   	if (input_four_bit == "0000")
		bit_map_ascii = "0";

  	if (input_four_bit == "0001")
		bit_map_ascii = "1";

	if (input_four_bit == "0010")
		bit_map_ascii = "2";

	if (input_four_bit == "0011")
		bit_map_ascii = "3";

  	if (input_four_bit == "0100")
		bit_map_ascii = "4";

	if (input_four_bit == "0101")
		bit_map_ascii = "5";

	if (input_four_bit == "0101")
		bit_map_ascii = "5";

	if (input_four_bit == "0110")
		bit_map_ascii = "6";

	if (input_four_bit == "0111")
		bit_map_ascii = "7";

	if (input_four_bit == "1000")
		bit_map_ascii = "8";

	if (input_four_bit == "1001")
		bit_map_ascii = "9";

	if (input_four_bit == "1010")
		bit_map_ascii = "A";

	if (input_four_bit == "1011")
		bit_map_ascii = "B";

	if (input_four_bit == "1100")
		bit_map_ascii = "C";

	if (input_four_bit == "1101")
		bit_map_ascii = "D";

	if (input_four_bit == "1110")
		bit_map_ascii = "E";

	if (input_four_bit == "1111")
		bit_map_ascii = "F";


	return bit_map_ascii;
}

RWCString Iso8583Msg::setBitMapFromChar( RWCString input_four_bit)
{

   	int i = 0;
	int j = 0;
	RWCString retorno_bit_map;
	RWCString bit_map_field;
	

	for(j = 0; j < 32 ; j++)
	{
		bit_map_field=input_four_bit(j,1);
	
		i = 0;
		for( i = 0; i < 1 ; i++)
		{
			if (bit_map_field == "0")
				retorno_bit_map += "0000";

			if (bit_map_field == "1")
				retorno_bit_map += "0001";

			if (bit_map_field == "2")
				retorno_bit_map += "0010";

			if (bit_map_field == "3")
				retorno_bit_map += "0011";

  			if (bit_map_field == "4")
				retorno_bit_map += "0100";

			if (bit_map_field == "5")
				retorno_bit_map += "0101";

			if (bit_map_field == "6")
				retorno_bit_map += "0110";

			if (bit_map_field == "7")
				retorno_bit_map += "0111";

			if (bit_map_field == "8")
				retorno_bit_map += "1000";

			if (bit_map_field == "9")
				retorno_bit_map += "1001";

			if (bit_map_field == "A")
				retorno_bit_map += "1010";

			if (bit_map_field == "B")
				retorno_bit_map += "1011";

			if (bit_map_field == "C")
				retorno_bit_map += "1100";

			if (bit_map_field == "D")
				retorno_bit_map += "1101";

			if (bit_map_field == "E")
				retorno_bit_map += "1110";

			if (bit_map_field == "F")
				retorno_bit_map +="1111";

		}

	}
	return retorno_bit_map;
}


RWCString Iso8583Msg::SetB24Header0200Pos( RWCString incoming_header ) 
{
	RWCString header_base24_0200= incoming_header;
	header_base24_0200+=complete_iso8583_msg;
	return complete_iso8583_msg = header_base24_0200;				
}

void Iso8583Msg::MessageErrorLength(RWCString incoming_name, int wrong_field_length, 
						int correct_field_length) 
{

	cout << "El largo de " <<  incoming_name << " es incorrecto > " 
	     << " es de " << wrong_field_length <<" y debe ser "
		 << correct_field_length << endl;
		 cout << "***********Transaccion abortada********** > " << endl;

}

int Iso8583Msg::VerifyNumericField(char *incoming_field, const int length_field, 
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

int Iso8583Msg::VerifyHexField(char *incoming, const int length_field,RWCString validated_field)
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


RWCString Iso8583Msg::SetField( int input_field ,RWCString field_value) 
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

	
		break;
	}

	return field_value;
}



RWCString Iso8583Msg::SetMsgField( int input_field ) 
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

//			cout << transmition_date_time << endl;


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
		    
			//struct  tstruct;

		//	_ftime( &tstruct );
		//	printf( "Plus milliseconds:\t\t\t%u\n", tstruct.millitm );
    
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


			//cout << endl;
			//cout << "<<<<<<<<<<Valor de primero>>>>>>>>>>> " << primero << endl;
			//cout << "<<<<<<<<<<Valor de segundo>>>>>>>>>>>" << segundo << endl;
			//cout << "<<<<<<<<<<Valor de tercero>>>>>>>>>>> " << tercero << endl;
			//cout << "<<<<<<<<<<Valor de cuarto >>>>>>>>>>>" << cuarto<< endl;
			//cout << endl;

			retrieval_reference_number = ((primero+segundo+tercero)(((primero+segundo+tercero).length()-12),12));
			//((primero+segundo+tercero).length()-12)
			pos_invoice_data=retrieval_reference_number(2,10)+retrieval_reference_number(2,10);

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
	/*
		if (input_field == 70)
		{
			//Este campo no debe ser mayor de 22
			int input_field_length = network_managment_info_code.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			network_managment_info_code = cero_field + network_managment_info_code;
	
		}			
	*/
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
	
			//Este campo no debe ser mayor de 23
			int input_field_length = pos_invoice_data.length();
			_itoa( input_field_length, buffer, 10 );
			RWCString cero_field = "0" + RWCString(buffer) ;
			pos_invoice_data = cero_field + pos_invoice_data;
	
		}			

		if (input_field == 125)
		{
	
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



RWCString Iso8583Msg::SetMsgField( int input_field ,RWCString field_value, RWCString pre_field) 
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
/*
void Iso8583Msg::ReturnDumpIsoGeneric( char *msg_type, int debugSB, RWCString peerAddress, int server_port) 
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
		//cout << "    <field id=*15* value=<"  << date_settlement_015			<< ">" << endl;
		cout << "    <field id=*17* value=<"  << capture_date					<< ">" << endl; 
		cout << "    <field id=*18* value=<"  << merchant_type					<< ">" << endl; 
		cout << "    <field id=*22* value=<"  << pos_entry_mode					<< ">" << endl; 
		cout << "    <field id=*25* value=<"  << pos_condition_code				<< ">" << endl; 
		cout << "    <field id=*32* value=<"   << acquiring_institution_id_code	<< ">" << endl;  
		cout << "    <field id=*35* value=<"   << track_2 						<< ">" << endl;  
		cout << "    <field id=*37* value=<"   << retrieval_reference_number 	<< ">" << endl;  
		//cout << "    <field id=*38* value=<"   << responde_id_response_038 	<< ">" << endl;  
       // cout << "    <field id=*39* value=<"   << responde_code_039 	<< ">" << endl;  
		cout << "    <field id=*41* value=<"   << card_acceptor_terminal_id 	<< ">" << endl;  
		cout << "    <field id=*42* value=<"   << card_acceptor_id_code 	<< ">" << endl;  
		cout << "    <field id=*43* value=<"   << card_acceptor_name_location 	<< ">" << endl;  
		cout << "    <field id=*48* value=<"   << pos_retailer_data 			<< ">" << endl;  
		cout << "    <field id=*49* value=<"   << currency_code_transaction 	<< ">" << endl;  
		cout << "    <field id=*52* value=<"   << pin_data 	<< ">" << endl;  
		cout << "    <field id=*60* value=<"   << pos_terminal_data 		<< ">" << endl;  
        cout << "    <field id=*61* value=<"   << pos_issuer_data 			<< ">" << endl;  
		
		cout << "    <field id=*120* value=<"   << pos_terminal_address_branch 			<< ">" << endl;  
		cout << "    <field id=*123* value=<"   << pos_invoice_data 			<< ">" << endl;  
		
		cout << "    <field id=*125* value=<"  << pos_settlement_data 	<< ">" << endl;  
		cout << "    <field id=*127.2* value=<"  << switch_key 	<< ">" << endl;  
		
		cout << endl;
	}
	
	
	

}
*/


int Iso8583Msg::SendMessageToQueue(RWCString incoming, char *recv_queue,char *queue_mgr)
{
	
  
   MQOD     od = {MQOD_DEFAULT};    /* Object Descriptor             */
   MQMD     md = {MQMD_DEFAULT};    /* Message Descriptor            */
   MQPMO   pmo = {MQPMO_DEFAULT};   /* put message options           */
      /** note, sample uses defaults where it can **/

   MQHCONN  Hcon;                   /* connection handle             */
   MQHOBJ   Hobj;                   /* object handle                 */
   MQLONG   O_options;              /* MQOPEN options                */
   MQLONG   C_options;              /* MQCLOSE options               */
   MQLONG   CompCode;               /* completion code               */
   MQLONG   OpenCode;               /* MQOPEN completion code        */
   MQLONG   Reason;                 /* reason code                   */
   MQLONG   CReason;                /* reason code for MQCONN        */
   MQLONG   messlen;                /* message length                */
   char     buffer[1024] = {""};    /* message buffer                */
   char     QMName[50];             /* queue manager name            */


   strcpy(buffer,incoming);
   /******************************************************************/
   /*                                                                */
   /*   Connect to queue manager                                     */
   /*                                                                */
   /******************************************************************/
   QMName[0] = 0;    /* default */
   strcpy(QMName, queue_mgr);
  
   
  // printf("Manager code %s\n", QMName);
  
   MQCONN(QMName,                  /* queue manager                  */
          &Hcon,                   /* connection handle              */
          &CompCode,               /* completion code                */
          &CReason);               /* reason code                    */

   /* report reason and stop if it failed     */
   if (CompCode == MQCC_FAILED)
   {
     printf("MQCONN ended with reason code %ld\n", CReason);
     exit( (int)CReason );
   }

   /******************************************************************/
   /*                                                                */
   /*   Use parameter as the name of the target queue                */
   /*                                                                */
   /******************************************************************/
   //strncpy(od.ObjectName, argv[1], (size_t)MQ_Q_NAME_LENGTH);
  strncpy(od.ObjectName, recv_queue, (size_t)MQ_Q_NAME_LENGTH);
  
  
  // printf("target queue is %s\n", od.ObjectName);

   /******************************************************************/
   /*                                                                */
   /*   Open the target message queue for output                     */
   /*                                                                */
   /******************************************************************/
   O_options = MQOO_OUTPUT           /* open queue for output        */
           + MQOO_FAIL_IF_QUIESCING; /* but not if MQM stopping      */
   MQOPEN(Hcon,                      /* connection handle            */
          &od,                       /* object descriptor for queue  */
          O_options,                 /* open options                 */
          &Hobj,                     /* object handle                */
          &OpenCode,                 /* MQOPEN completion code       */
          &Reason);                  /* reason code                  */

   /* report reason, if any; stop if failed      */
   if (Reason != MQRC_NONE)
   {
     printf("MQOPEN ended with reason code %ld\n", Reason);
   }

   if (OpenCode == MQCC_FAILED)
   {
     printf("unable to open queue for output\n");
   }

 
 
   
   
   
   /******************************************************************/
   /*                                                                */
   /*   Read lines from the file and put them to the message queue   */
   /*   Loop until null line or end of file, or there is a failure   */
   /*                                                                */
   /******************************************************************/
   CompCode = OpenCode;        /* use MQOPEN result for initial test */
  // fp = stdin;

   memcpy(md.Format,           /* character string format            */
          MQFMT_STRING, (size_t)MQ_FORMAT_LENGTH);
  
   
  /******************************************************************/
   /* Use these options when connecting to Queue Managers that also  */
   /* support them, see the Application Programming Reference for    */
   /* details.                                                       */
   /* These options cause the MsgId and CorrelId to be replaced, so  */
   /* that there is no need to reset them before each MQPUT          */ 
   /******************************************************************/
   /* pmo.Options |= MQPMO_NEW_MSG_ID;                               */
   /* pmo.Options |= MQPMO_NEW_CORREL_ID;                            */
 
  
       messlen = strlen(buffer);       /* length without null        */
 
     /****************************************************************/
     /*                                                              */
     /*   Put each buffer to the message queue                       */
     /*                                                              */
     /****************************************************************/
     if (messlen > 0)
     {
       /**************************************************************/
       /* The following two statements are not required if the       */
       /* MQPMO_NEW_MSG_ID and MQPMO_NEW _CORREL_ID options are used */
       /**************************************************************/
       memcpy(md.MsgId,           /* reset MsgId to get a new one    */
              MQMI_NONE, sizeof(md.MsgId) );
       md.Expiry=250; /* cambiar msg descr */ 
 		  

	   /* jnivar end */
	   memcpy(md.CorrelId,        /* reset CorrelId to get a new one */
              MQCI_NONE, sizeof(md.CorrelId) );

       MQPUT(Hcon,                /* connection handle               */
             Hobj,                /* object handle                   */
             &md,                 /* message descriptor              */
             &pmo,                /* default options (datagram)      */
             messlen,             /* message length                  */
             buffer,              /* message buffer                  */
             &CompCode,           /* completion code                 */
             &Reason);            /* reason code                     */

       /* report reason, if any */
       if (Reason != MQRC_NONE)
       {
         printf("MQPUT ended with reason code %ld\n", Reason);
       }
     

       /* report reason, if any */
       if (Reason != MQRC_NONE)
       {
         printf("MQPUT ended with reason code %ld\n", Reason);
       }
     
	 
	 
	 
	 }
     else   /* satisfy end condition when empty line is read */
       CompCode = MQCC_FAILED;


   /******************************************************************/
   /*                                                                */
   /*   Close the target queue (if it was opened)                    */
   /*                                                                */
   /******************************************************************/
   if (OpenCode != MQCC_FAILED)
   {
     C_options = 0;                  /* no close options             */
     MQCLOSE(Hcon,                   /* connection handle            */
             &Hobj,                  /* object handle                */
             C_options,
             &CompCode,              /* completion code              */
             &Reason);               /* reason code                  */

     /* report reason, if any     */
     if (Reason != MQRC_NONE)
     {
       printf("MQCLOSE ended with reason code %ld\n", Reason);
     }
   }

   /******************************************************************/
   /*                                                                */
   /*   Disconnect from MQM if not already connected                 */
   /*                                                                */
   /******************************************************************/
   if (CReason != MQRC_ALREADY_CONNECTED)
   {
     MQDISC(&Hcon,                   /* connection handle            */
            &CompCode,               /* completion code              */
            &Reason);                /* reason code                  */

     /* report reason, if any     */
     if (Reason != MQRC_NONE)
     {
       printf("MQDISC ended with reason code %ld\n", Reason);
     }
   }

   /******************************************************************/
   /*                                                                */
   /* END OF AMQSPUT0                                                */
   /*                                                                */
   /******************************************************************/
   //printf("Sample AMQSPUT0 end\n");

 	
	
	return 1;
}

int Iso8583Msg::SendMessageToQueueWithTimeout(RWCString incoming, char *recv_queue,char *queue_mgr)
{
	
  
   MQOD     od = {MQOD_DEFAULT};    /* Object Descriptor             */
   MQMD     md = {MQMD_DEFAULT};    /* Message Descriptor            */
   MQPMO   pmo = {MQPMO_DEFAULT};   /* put message options           */
      /** note, sample uses defaults where it can **/

   MQHCONN  Hcon;                   /* connection handle             */
   MQHOBJ   Hobj;                   /* object handle                 */
   MQLONG   O_options;              /* MQOPEN options                */
   MQLONG   C_options;              /* MQCLOSE options               */
   MQLONG   CompCode;               /* completion code               */
   MQLONG   OpenCode;               /* MQOPEN completion code        */
   MQLONG   Reason;                 /* reason code                   */
   MQLONG   CReason;                /* reason code for MQCONN        */
   MQLONG   messlen;                /* message length                */
   char     buffer[1024] = {""};    /* message buffer                */
   char     QMName[50];             /* queue manager name            */


   strcpy(buffer,incoming);
   /******************************************************************/
   /*                                                                */
   /*   Connect to queue manager                                     */
   /*                                                                */
   /******************************************************************/
   QMName[0] = 0;    /* default */
   strcpy(QMName, queue_mgr);
  
   
  // printf("Manager code %s\n", QMName);
  
   MQCONN(QMName,                  /* queue manager                  */
          &Hcon,                   /* connection handle              */
          &CompCode,               /* completion code                */
          &CReason);               /* reason code                    */

   /* report reason and stop if it failed     */
   if (CompCode == MQCC_FAILED)
   {
     printf("MQCONN ended with reason code %ld\n", CReason);
     exit( (int)CReason );
   }

   /******************************************************************/
   /*                                                                */
   /*   Use parameter as the name of the target queue                */
   /*                                                                */
   /******************************************************************/
   //strncpy(od.ObjectName, argv[1], (size_t)MQ_Q_NAME_LENGTH);
  strncpy(od.ObjectName, recv_queue, (size_t)MQ_Q_NAME_LENGTH);
  
  
  // printf("target queue is %s\n", od.ObjectName);

   /******************************************************************/
   /*                                                                */
   /*   Open the target message queue for output                     */
   /*                                                                */
   /******************************************************************/
   O_options = MQOO_OUTPUT           /* open queue for output        */
           + MQOO_FAIL_IF_QUIESCING; /* but not if MQM stopping      */
   MQOPEN(Hcon,                      /* connection handle            */
          &od,                       /* object descriptor for queue  */
          O_options,                 /* open options                 */
          &Hobj,                     /* object handle                */
          &OpenCode,                 /* MQOPEN completion code       */
          &Reason);                  /* reason code                  */

   /* report reason, if any; stop if failed      */
   if (Reason != MQRC_NONE)
   {
     printf("MQOPEN ended with reason code %ld\n", Reason);
   }

   if (OpenCode == MQCC_FAILED)
   {
     printf("unable to open queue for output\n");
   }

 
 
   
   
   
   /******************************************************************/
   /*                                                                */
   /*   Read lines from the file and put them to the message queue   */
   /*   Loop until null line or end of file, or there is a failure   */
   /*                                                                */
   /******************************************************************/
   CompCode = OpenCode;        /* use MQOPEN result for initial test */
  // fp = stdin;

   memcpy(md.Format,           /* character string format            */
          MQFMT_STRING, (size_t)MQ_FORMAT_LENGTH);
  
   
  /******************************************************************/
   /* Use these options when connecting to Queue Managers that also  */
   /* support them, see the Application Programming Reference for    */
   /* details.                                                       */
   /* These options cause the MsgId and CorrelId to be replaced, so  */
   /* that there is no need to reset them before each MQPUT          */ 
   /******************************************************************/
   /* pmo.Options |= MQPMO_NEW_MSG_ID;                               */
   /* pmo.Options |= MQPMO_NEW_CORREL_ID;                            */
 
  
       messlen = strlen(buffer);       /* length without null        */
 
     /****************************************************************/
     /*                                                              */
     /*   Put each buffer to the message queue                       */
     /*                                                              */
     /****************************************************************/
     if (messlen > 0)
     {
       /**************************************************************/
       /* The following two statements are not required if the       */
       /* MQPMO_NEW_MSG_ID and MQPMO_NEW _CORREL_ID options are used */
       /**************************************************************/
       memcpy(md.MsgId,           /* reset MsgId to get a new one    */
              MQMI_NONE, sizeof(md.MsgId) );
       md.Expiry=250; /* cambiar msg descr */ 
 		  

	   /* jnivar end */
	   memcpy(md.CorrelId,        /* reset CorrelId to get a new one */
              MQCI_NONE, sizeof(md.CorrelId) );

       MQPUT(Hcon,                /* connection handle               */
             Hobj,                /* object handle                   */
             &md,                 /* message descriptor              */
             &pmo,                /* default options (datagram)      */
             messlen,             /* message length                  */
             buffer,              /* message buffer                  */
             &CompCode,           /* completion code                 */
             &Reason);            /* reason code                     */

       /* report reason, if any */
       if (Reason != MQRC_NONE)
       {
         printf("MQPUT ended with reason code %ld\n", Reason);
       }
     

       /* report reason, if any */
       if (Reason != MQRC_NONE)
       {
         printf("MQPUT ended with reason code %ld\n", Reason);
       }
     
	 
	 
	 
	 }
     else   /* satisfy end condition when empty line is read */
       CompCode = MQCC_FAILED;


   /******************************************************************/
   /*                                                                */
   /*   Close the target queue (if it was opened)                    */
   /*                                                                */
   /******************************************************************/
   if (OpenCode != MQCC_FAILED)
   {
     C_options = 0;                  /* no close options             */
     MQCLOSE(Hcon,                   /* connection handle            */
             &Hobj,                  /* object handle                */
             C_options,
             &CompCode,              /* completion code              */
             &Reason);               /* reason code                  */

     /* report reason, if any     */
     if (Reason != MQRC_NONE)
     {
       printf("MQCLOSE ended with reason code %ld\n", Reason);
     }
   }

   /******************************************************************/
   /*                                                                */
   /*   Disconnect from MQM if not already connected                 */
   /*                                                                */
   /******************************************************************/
   if (CReason != MQRC_ALREADY_CONNECTED)
   {
     MQDISC(&Hcon,                   /* connection handle            */
            &CompCode,               /* completion code              */
            &Reason);                /* reason code                  */

     /* report reason, if any     */
     if (Reason != MQRC_NONE)
     {
       printf("MQDISC ended with reason code %ld\n", Reason);
     }
   }

   /******************************************************************/
   /*                                                                */
   /* END OF AMQSPUT0                                                */
   /*                                                                */
   /******************************************************************/
   //printf("Sample AMQSPUT0 end\n");

 	
	
	return 1;
}



int Iso8583Msg::SendMessageToQueueSql(RWCString incoming, char *sql_queue, char *queue_mgr)
{

/*   Declare MQI structures needed                                */
   MQOD     od = {MQOD_DEFAULT};    /* Object Descriptor             */
 

   MQMD     md = {MQMD_DEFAULT};    /* Message Descriptor            */

 
   MQPMO   pmo = {MQPMO_DEFAULT};   /* put message options           */
      /** note, sample uses defaults where it can **/

   MQHCONN  Hcon;                   /* connection handle             */
   MQHOBJ   Hobj;                   /* object handle                 */
   MQLONG   O_options;              /* MQOPEN options                */
   MQLONG   C_options;              /* MQCLOSE options               */
   MQLONG   CompCode;               /* completion code               */
   MQLONG   OpenCode;               /* MQOPEN completion code        */
   MQLONG   Reason;                 /* reason code                   */
   MQLONG   CReason;                /* reason code for MQCONN        */
   MQLONG   messlen;                /* message length                */
   char     buffer[1024];           /* message buffer                */
   char     QMName[50];             /* queue manager name            */


   strcpy(buffer,incoming);
   /******************************************************************/
   /*                                                                */
   /*   Connect to queue manager                                     */
   /*                                                                */
   /******************************************************************/
   QMName[0] = 0;    /* default */
   strcpy(QMName, queue_mgr);
  
   
   //printf("Manager code %s\n", QMName);
  
   MQCONN(QMName,                  /* queue manager                  */
          &Hcon,                   /* connection handle              */
          &CompCode,               /* completion code                */
          &CReason);               /* reason code                    */

   /* report reason and stop if it failed     */
   if (CompCode == MQCC_FAILED)
   {
     printf("MQCONN ended with reason code %ld\n", CReason);
     exit( (int)CReason );
   }

   /******************************************************************/
   /*                                                                */
   /*   Use parameter as the name of the target queue                */
   /*                                                                */
   /******************************************************************/
   //strncpy(od.ObjectName, argv[1], (size_t)MQ_Q_NAME_LENGTH);
  strncpy(od.ObjectName, sql_queue, (size_t)MQ_Q_NAME_LENGTH);
  
  
  // printf("target queue is %s\n", od.ObjectName);

   /******************************************************************/
   /*                                                                */
   /*   Open the target message queue for output                     */
   /*                                                                */
   /******************************************************************/
   O_options = MQOO_OUTPUT           /* open queue for output        */
           + MQOO_FAIL_IF_QUIESCING; /* but not if MQM stopping      */
   MQOPEN(Hcon,                      /* connection handle            */
          &od,                       /* object descriptor for queue  */
          O_options,                 /* open options                 */
          &Hobj,                     /* object handle                */
          &OpenCode,                 /* MQOPEN completion code       */
          &Reason);                  /* reason code                  */

   /* report reason, if any; stop if failed      */
   if (Reason != MQRC_NONE)
   {
     printf("MQOPEN ended with reason code %ld\n", Reason);
   }

   if (OpenCode == MQCC_FAILED)
   {
     printf("unable to open queue for output\n");
   }

 
 
   
   
   
   /******************************************************************/
   /*                                                                */
   /*   Read lines from the file and put them to the message queue   */
   /*   Loop until null line or end of file, or there is a failure   */
   /*                                                                */
   /******************************************************************/
   CompCode = OpenCode;        /* use MQOPEN result for initial test */
  // fp = stdin;

   memcpy(md.Format,           /* character string format            */
          MQFMT_STRING, (size_t)MQ_FORMAT_LENGTH);
  
   
  /******************************************************************/
   /* Use these options when connecting to Queue Managers that also  */
   /* support them, see the Application Programming Reference for    */
   /* details.                                                       */
   /* These options cause the MsgId and CorrelId to be replaced, so  */
   /* that there is no need to reset them before each MQPUT          */ 
   /******************************************************************/
   /* pmo.Options |= MQPMO_NEW_MSG_ID;                               */
   /* pmo.Options |= MQPMO_NEW_CORREL_ID;                            */
 
  
       messlen = strlen(buffer);       /* length without null        */
 
     /****************************************************************/
     /*                                                              */
     /*   Put each buffer to the message queue                       */
     /*                                                              */
     /****************************************************************/
     if (messlen > 0)
     {
       /**************************************************************/
       /* The following two statements are not required if the       */
       /* MQPMO_NEW_MSG_ID and MQPMO_NEW _CORREL_ID options are used */
       /**************************************************************/
       memcpy(md.MsgId,           /* reset MsgId to get a new one    */
              MQMI_NONE, sizeof(md.MsgId) );
//       md.Expiry=500; /* cambiar msg descr */ 
 		  

	   /* jnivar end */
	   memcpy(md.CorrelId,        /* reset CorrelId to get a new one */
              MQCI_NONE, sizeof(md.CorrelId) );

       MQPUT(Hcon,                /* connection handle               */
             Hobj,                /* object handle                   */
             &md,                 /* message descriptor              */
             &pmo,                /* default options (datagram)      */
             messlen,             /* message length                  */
             buffer,              /* message buffer                  */
             &CompCode,           /* completion code                 */
             &Reason);            /* reason code                     */

       /* report reason, if any */
       if (Reason != MQRC_NONE)
       {
         printf("MQPUT ended with reason code %ld\n", Reason);
       }
     

       /* report reason, if any */
       if (Reason != MQRC_NONE)
       {
         printf("MQPUT ended with reason code %ld\n", Reason);
       }
     
	 
	 
	 
	 }
     else   /* satisfy end condition when empty line is read */
       CompCode = MQCC_FAILED;


   /******************************************************************/
   /*                                                                */
   /*   Close the target queue (if it was opened)                    */
   /*                                                                */
   /******************************************************************/
   if (OpenCode != MQCC_FAILED)
   {
     C_options = 0;                  /* no close options             */
     MQCLOSE(Hcon,                   /* connection handle            */
             &Hobj,                  /* object handle                */
             C_options,
             &CompCode,              /* completion code              */
             &Reason);               /* reason code                  */

     /* report reason, if any     */
     if (Reason != MQRC_NONE)
     {
       printf("MQCLOSE ended with reason code %ld\n", Reason);
     }
   }

   /******************************************************************/
   /*                                                                */
   /*   Disconnect from MQM if not already connected                 */
   /*                                                                */
   /******************************************************************/
   if (CReason != MQRC_ALREADY_CONNECTED)
   {
     MQDISC(&Hcon,                   /* connection handle            */
            &CompCode,               /* completion code              */
            &Reason);                /* reason code                  */

     /* report reason, if any     */
     if (Reason != MQRC_NONE)
     {
       printf("MQDISC ended with reason code %ld\n", Reason);
     }
   }

   /******************************************************************/
   /*                                                                */
   /* END OF AMQSPUT0                                                */
   /*                                                                */
   /******************************************************************/
   //printf("Sample AMQSPUT0 end\n");

	
	
	
	return 1;
}

int Iso8583Msg::SendMessageToQueueSqlOld(RWCString incoming, char *sql_queue, char *queue_mgr)
{

  ImqQueueManager mgr;             // Queue manager
  ImqQueue queueA;                  // Queue
  ImqQueue queueB;                  // Queue
  ImqMessage msg;                  // Data message
  ImqMessage msg2;                  // Data message
  
  int      buflen;                 // Buffer length
  char     buffer[ 1024 ] = {""};          // Message buffer
  ImqDistributionList dlist;	   // Distribution List
  ImqChannel * pchannel = 0 ;      // Channel definition

  strcpy(buffer, incoming);

 // printf( "Sample IMQSPUT start\n" );
 	
  char test_input[] = "SYSTEM.DEF.SVRCONN/TCP/127.0.0.1(1414)";
  ImqString strParse( test_input );
 // printf("valor de test > %s\n", test_input);
	  
  ImqString strToken ;

  pchannel = new ImqChannel ;
  pchannel -> setHeartBeatInterval( 1L );

    // Break down the channel definition,
    // which is of the form "channel-name/transport-type/connection-name".
    if ( strParse.cutOut( strToken, '/' ) ) {
      pchannel -> setChannelName( strToken );
      if ( strParse.cutOut( strToken, '/' ) ) {

        // Interpret the transport type.
        if ( strToken.upperCase( ) == (ImqString)"LU62" ) {
          pchannel -> setTransportType( MQXPT_LU62 );
        }
        if ( strToken.upperCase( ) == (ImqString)"NETBIOS" ) {
          pchannel -> setTransportType( MQXPT_NETBIOS );
        }
        if ( strToken.upperCase( ) == (ImqString)"SPX" ) {
          pchannel -> setTransportType( MQXPT_SPX );
        }
        if ( strToken.upperCase( ) == (ImqString)"TCP" ) {
          pchannel -> setTransportType( MQXPT_TCP );
        }

        // Establish the connection name.
        if ( strParse.cutOut( strToken ) ) {
          pchannel -> setConnectionName( strToken );
       
		
		
		}
      }

    
	
	mgr.setChannelReference( pchannel );
	
	 
  }


  
  mgr.setName( queue_mgr );
  
  // Connect to queue manager

  if ( ! mgr.connect( ) ) {

    /* stop if it failed */
    printf( "ImqQueueManager::connect ended with reason code %d\n",
            (int)mgr.reasonCode( ) );
    exit( (int)mgr.reasonCode( ) );
  }

  ImqString strManagerName( mgr.name( ) );
 // printf("Successful connection to queue manager %s\n",
   //                                     (char *)strManagerName );

  queueB.setConnectionReference( mgr );

  queueB.setName( sql_queue );
  
  // Use parameter as the name of the target queue

  queueB.setQueueManagerName( (char *)strManagerName );


 queueB.setOpenOptions( MQOO_OUTPUT /* open queue for output        */
    + MQOO_FAIL_IF_QUIESCING );     /* but not if MQM stopping      */
  queueB.open( );

  
  

  if ( queueB.reasonCode( ) ) {
    printf( "ImqQueue::open ended with reason code %d\n",
            (int)queueB.reasonCode( ) );
  }

  if ( queueB.completionCode( ) == MQCC_FAILED ) {
    printf( "unable to open queue for output\n" );
  }

//  msg.setExpiry( 150 );  
 // msg.useEmptyBuffer( buffer, sizeof( buffer ) );
//  msg.setFormat( MQFMT_STRING );      /* character string format    */

  msg2.useEmptyBuffer( buffer, sizeof( buffer ) );
  msg2.setFormat( MQFMT_STRING );      /* character string format    */


     buflen = (int)strlen( buffer ); /* determine string length    */

     buffer[ buflen ] = '\0' ;            /* add line-end          */
 

   if ( buflen > 0 ) {
//      msg.setMessageLength( buflen );
	   msg2.setMessageLength( buflen );
	 
//      if ( ! queueA.put( msg ) ) {

        /* report reason, if any */
   //     printf( "ImqQueueA::put ended with reason code %d\n",
   //             (int)queueA.reasonCode( ) );
    //  }
	   if ( ! queueB.put( msg2 ) ) {

        /* report reason, if any */
        printf( "ImqQueueB::put ended with reason code %d\n",
                (int)queueB.reasonCode( ) );
      }


    } else {
      /* quit loop when empty line is read */
     // break ;
    }

	// Close the target queue (if it was opened)
//  if ( ! queueA.close( ) ) {

    /* report reason, if any     */
//    printf( "ImqQueue::close ended with reason code %d\n",
//            (int)queueA.reasonCode( ) );
 // }

 if ( ! queueB.close( ) ) {

    /* report reason, if any     */
    printf( "ImqQueue::close ended with reason code %d\n",
            (int)queueB.reasonCode( ) );
  }



  // Disconnect from MQM if not already connected (the
  // ImqQueueManager object handles this situation automatically)
  if ( ! mgr.disconnect( ) ) {

    /* report reason, if any     */
    printf( "ImqQueueManager::disconnect ended with reason code %ld\n",
            (long)mgr.reasonCode( ) );
  }

  // Tidy up the channel object if allocated.
  if ( pchannel ) {
    mgr.setChannelReference( );
    delete pchannel ;
  }

 // printf( "Sample IMQSPUT end\n" );
  //return( 0 );
	
	
	
	return 1;
}



RWCString Iso8583Msg::Get_Msg_From_SendQueue( char *send_queue,char *queue_mgr)
{
	  /*   Declare MQI structures needed                                */
   MQOD     od = {MQOD_DEFAULT};    /* Object Descriptor             */
   MQMD     md = {MQMD_DEFAULT};    /* Message Descriptor            */
   MQGMO   gmo = {MQGMO_DEFAULT};   /* get message options           */
      /** note, sample uses defaults where it can **/

   MQHCONN  Hcon;                   /* connection handle             */
   MQHOBJ   Hobj;                   /* object handle                 */
   MQLONG   O_options;              /* MQOPEN options                */
   MQLONG   C_options;              /* MQCLOSE options               */
   MQLONG   CompCode;               /* completion code               */
   MQLONG   OpenCode;               /* MQOPEN completion code        */
   MQLONG   Reason;                 /* reason code                   */
   MQLONG   CReason;                /* reason code for MQCONN        */
   //MQBYTE   buffer[1024];            /* message buffer                */
   MQLONG   buflen;                 /* buffer length                 */
   MQLONG   messlen;                /* message length received       */
   char     QMName[50];             /* queue manager name            */
   char     buffer[1024] = {""};            /* message buffer                */
   strcpy(buffer,"");

   /******************************************************************/
   /*                                                                */
   /*   Create object descriptor for subject queue                   */
   /*                                                                */
   /******************************************************************/
   strcpy(od.ObjectName, send_queue);
   QMName[0] = 0;   /* default */
   //if (argc > 2)
     strcpy(QMName, queue_mgr);

   /******************************************************************/
   /*                                                                */
   /*   Connect to queue manager                                     */
   /*                                                                */
   /******************************************************************/
   MQCONN(QMName,                  /* queue manager                  */
          &Hcon,                   /* connection handle              */
          &CompCode,               /* completion code                */
          &CReason);               /* reason code                    */

   /* report reason and stop if it failed     */
   if (CompCode == MQCC_FAILED)
   {
     printf("MQCONN ended with reason code %ld\n", CReason);
     exit( (int)CReason );
   }

   /******************************************************************/
   /*                                                                */
   /*   Open the named message queue for input; exclusive or shared  */
   /*   use of the queue is controlled by the queue definition here  */
   /*                                                                */
   /******************************************************************/
   O_options = MQOO_INPUT_AS_Q_DEF   /* open queue for input         */
         + MQOO_FAIL_IF_QUIESCING;   /* but not if MQM stopping      */
   MQOPEN(Hcon,                      /* connection handle            */
          &od,                       /* object descriptor for queue  */
          O_options,                 /* open options                 */
          &Hobj,                     /* object handle                */
          &OpenCode,                 /* completion code              */
          &Reason);                  /* reason code                  */

   /* report reason, if any; stop if failed      */
   if (Reason != MQRC_NONE)
   {
     printf("MQOPEN ended with reason code %ld\n", Reason);
   }

   if (OpenCode == MQCC_FAILED)
   {
     printf("unable to open queue for input\n");
   }

   /******************************************************************/
   /*                                                                */
   /*   Get messages from the message queue                          */
   /*   Loop until there is a failure                                */
   /*                                                                */
   /******************************************************************/
   CompCode = OpenCode;       /* use MQOPEN result for initial test  */
   
   /******************************************************************/
   /* Use these options when connecting to Queue Managers that also  */
   /* support them, see the Application Programming Reference for    */
   /* details.                                                       */
   /* These options cause the MsgId and CorrelId to be replaced, so  */
   /* that there is no need to reset them before each MQGET          */ 
   /******************************************************************/
   /*gmo.Version = MQGMO_VERSION_2;*/ /* Avoid need to reset Message */
   /*gmo.MatchOptions = MQMO_NONE; */ /* ID and Correlation ID after */
                                      /* every MQGET                 */
   gmo.Options = MQGMO_WAIT       /* wait for new messages           */
               + MQGMO_CONVERT;   /* convert if necessary            */
   gmo.WaitInterval = 1500;      /* 15 second limit for waiting     */
   //gmo.MsgId("BTRAN3");
    // strcpy(md.MsgId,"BTRAN3");

   //while (CompCode != MQCC_FAILED)
   //{
     buflen = sizeof(buffer) - 1; /* buffer size available for GET   */

     /****************************************************************/
     /* The following two statements are not required if the MQGMO   */
     /* version is set to MQGMO_VERSION_2 and and gmo.MatchOptions   */
     /* is set to MQGMO_NONE                                         */
     /****************************************************************/
     /*                                                              */
     /*   In order to read the messages in sequence, MsgId and       */
     /*   CorrelID must have the default value.  MQGET sets them     */
     /*   to the values in for message it returns, so re-initialise  */
     /*   them before every call                                     */
     /*                                                              */
     /****************************************************************/
    // memcpy(md.MsgId, MQMI_NONE, sizeof(md.MsgId));
    // cout << "Valor de key_message > " << key_message << endl;
	// memcpy(md.MsgId,key_message,18);
	 
	 //memcpy(md.CorrelId, MQCI_NONE, sizeof(md.CorrelId));

	 memcpy(md.MsgId, MQMI_NONE, sizeof(md.MsgId));
     memcpy(md.CorrelId, MQCI_NONE, sizeof(md.CorrelId));

     /****************************************************************/
     /*                                                              */
     /*   MQGET sets Encoding and CodedCharSetId to the values in    */
     /*   the message returned, so these fields should be reset to   */
     /*   the default values before every call, as MQGMO_CONVERT is  */
     /*   specified.                                                 */
     /*                                                              */
     /****************************************************************/

     md.Encoding       = MQENC_NATIVE;
     md.CodedCharSetId = MQCCSI_Q_MGR;

     MQGET(Hcon,                /* connection handle                 */
           Hobj,                /* object handle                     */
           &md,                 /* message descriptor                */
           &gmo,                /* get message options               */
           buflen,              /* buffer length                     */
           buffer,              /* message buffer                    */
           &messlen,            /* message length                    */
           &CompCode,           /* completion code                   */
           &Reason);            /* reason code                       */

     /* report reason, if any     */
     if (Reason != MQRC_NONE)
     {
       if (Reason == MQRC_NO_MSG_AVAILABLE)
       {                         /* special report for normal end    */
         //printf("no more messages\n");
       }
       else                      /* general report for other reasons */
       {
         printf("MQGET ended with reason code %ld\n", Reason);

         /*   treat truncated message as a failure for this sample   */
         if (Reason == MQRC_TRUNCATED_MSG_FAILED)
         {
           CompCode = MQCC_FAILED;
         }
       }
     }

     /****************************************************************/
     /*   Display each message received                              */
     /****************************************************************/
     if (CompCode != MQCC_FAILED)
     {
       buffer[messlen] = '\0';            /* add terminator          */
       //printf("message <%s>\n", buffer);
     }
   //}

   /******************************************************************/
   /*                                                                */
   /*   Close the source queue (if it was opened)                    */
   /*                                                                */
   /******************************************************************/
   if (OpenCode != MQCC_FAILED)
   {
     C_options = 0;                   /* no close options            */
     MQCLOSE(Hcon,                    /* connection handle           */
             &Hobj,                   /* object handle               */
             C_options,
             &CompCode,               /* completion code             */
             &Reason);                /* reason code                 */

     /* report reason, if any     */
     if (Reason != MQRC_NONE)
     {
       printf("MQCLOSE ended with reason code %ld\n", Reason);
     }
   }

   /******************************************************************/
   /*                                                                */
   /*   Disconnect from MQM if not already connected                 */
   /*                                                                */
   /******************************************************************/
   if (CReason != MQRC_ALREADY_CONNECTED )
   {
     MQDISC(&Hcon,                     /* connection handle          */
            &CompCode,                 /* completion code            */
            &Reason);                  /* reason code                */

     /* report reason, if any     */
     if (Reason != MQRC_NONE)
     {
       printf("MQDISC ended with reason code %ld\n", Reason);
     }
   }

   /******************************************************************/
   /*                                                                */
   /* END OF AMQSGET0                                                */
   /*                                                                */
   /******************************************************************/
   //printf("Sample AMQSGET0 end\n");


   RWCString incoming_0200_sql_queue = buffer;
   /*
   int len = strlen(buffer);
	for(int i = 0; i < len ; i++)
	{

	}
	*/
	return incoming_0200_sql_queue;
}

int Iso8583Msg::SendMessageToQueueOld(RWCString incoming, char *recv_queue,char *queue_mgr)
{
	
   //FILE * fp ;                      // Console


  ImqQueueManager mgr;             // Queue manager
  ImqQueue queueA;                  // Queue
  ImqQueue queueB;                  // Queue
  ImqMessage msg;                  // Data message
  ImqMessage msg2;                  // Data message
  
  int      buflen;                 // Buffer length
  char     buffer[ 1024 ] = {""};          // Message buffer
  ImqDistributionList dlist;	   // Distribution List
  ImqChannel * pchannel = 0 ;      // Channel definition

  strcpy(buffer, incoming);

 // printf( "Sample IMQSPUT start\n" );
 	
  char test_input[] = "SYSTEM.DEF.SVRCONN/TCP/127.0.0.1(1414)";
  ImqString strParse( test_input );
 // printf("valor de test > %s\n", test_input);
	  
  ImqString strToken ;

  pchannel = new ImqChannel ;
  pchannel -> setHeartBeatInterval( 1L );

    // Break down the channel definition,
    // which is of the form "channel-name/transport-type/connection-name".
    if ( strParse.cutOut( strToken, '/' ) ) {
      pchannel -> setChannelName( strToken );
      if ( strParse.cutOut( strToken, '/' ) ) {

        // Interpret the transport type.
        if ( strToken.upperCase( ) == (ImqString)"LU62" ) {
          pchannel -> setTransportType( MQXPT_LU62 );
        }
        if ( strToken.upperCase( ) == (ImqString)"NETBIOS" ) {
          pchannel -> setTransportType( MQXPT_NETBIOS );
        }
        if ( strToken.upperCase( ) == (ImqString)"SPX" ) {
          pchannel -> setTransportType( MQXPT_SPX );
        }
        if ( strToken.upperCase( ) == (ImqString)"TCP" ) {
          pchannel -> setTransportType( MQXPT_TCP );
        }

        // Establish the connection name.
        if ( strParse.cutOut( strToken ) ) {
          pchannel -> setConnectionName( strToken );
       
		
		
		}
      }

    
	
	mgr.setChannelReference( pchannel );
	
	 
  }


  
  mgr.setName( queue_mgr );
  //mgr.setName( "QM_victort8100" );
  
  // Connect to queue manager

  if ( ! mgr.connect( ) ) {

    /* stop if it failed */
    printf( "ImqQueueManager::connect ended with reason code %d\n",
            (int)mgr.reasonCode( ) );
    exit( (int)mgr.reasonCode( ) );
  }

  ImqString strManagerName( mgr.name( ) );
 // printf("Successful connection to queue manager %s\n",
   //                                     (char *)strManagerName );

  // Associate distribution list with queue manager
//  dlist.setConnectionReference( mgr);
  // Associate queue with queue manager.
 // queue.setConnectionReference( mgr );

  queueA.setConnectionReference( mgr );
  //queueB.setConnectionReference( mgr );

  queueA.setName( recv_queue );
//  queueB.setName( sql_queue );
  
  // Use parameter as the name of the target queue

 // printf( "First target queue is %s\n", (char *)queueA.name( ) );
 // printf( "Second target queue is %s\n", (char *)queueB.name( ) );

  queueA.setQueueManagerName( (char *)strManagerName );
//  queueB.setQueueManagerName( (char *)strManagerName );

 queueA.setOpenOptions( MQOO_OUTPUT /* open queue for output        */
    + MQOO_FAIL_IF_QUIESCING );     /* but not if MQM stopping      */
  queueA.open( );

// queueB.setOpenOptions( MQOO_OUTPUT /* open queue for output        */
//    + MQOO_FAIL_IF_QUIESCING );     /* but not if MQM stopping      */
 // queueB.open( );

  
  
  /* report reason, if any; stop if failed      */
  if ( queueA.reasonCode( ) ) {
    printf( "ImqQueue::open ended with reason code %d\n",
            (int)queueA.reasonCode( ) );
  }

  if ( queueA.completionCode( ) == MQCC_FAILED ) {
    printf( "unable to open queue for output\n" );
  }


//  if ( queueB.reasonCode( ) ) {
 //   printf( "ImqQueue::open ended with reason code %d\n",
 //           (int)queueB.reasonCode( ) );
//  }

//  if ( queueB.completionCode( ) == MQCC_FAILED ) {
//    printf( "unable to open queue for output\n" );
//  }

  msg.setExpiry( 150 );  
  msg.useEmptyBuffer( buffer, sizeof( buffer ) );
  msg.setFormat( MQFMT_STRING );      /* character string format    */
//  msg2.useEmptyBuffer( buffer, sizeof( buffer ) );
//  msg2.setFormat( MQFMT_STRING );      /* character string format    */


     buflen = (int)strlen( buffer ); /* determine string length    */

     buffer[ buflen ] = '\0' ;            /* add line-end          */
 

   if ( buflen > 0 ) {
      msg.setMessageLength( buflen );
	   msg2.setMessageLength( buflen );
	 
      if ( ! queueA.put( msg ) ) {

        /* report reason, if any */
        printf( "ImqQueueA::put ended with reason code %d\n",
                (int)queueA.reasonCode( ) );
      }
//	   if ( ! queueB.put( msg2 ) ) {

        /* report reason, if any */
//        printf( "ImqQueueB::put ended with reason code %d\n",
//                (int)queueB.reasonCode( ) );
//      }


    } else {
      /* quit loop when empty line is read */
     // break ;
    }

	// Close the target queue (if it was opened)
  if ( ! queueA.close( ) ) {

    /* report reason, if any     */
    printf( "ImqQueue::close ended with reason code %d\n",
            (int)queueA.reasonCode( ) );
  }

 //if ( ! queueB.close( ) ) {

    /* report reason, if any     */
 //   printf( "ImqQueue::close ended with reason code %d\n",
//            (int)queueB.reasonCode( ) );
//  }



  // Disconnect from MQM if not already connected (the
  // ImqQueueManager object handles this situation automatically)
  if ( ! mgr.disconnect( ) ) {

    /* report reason, if any     */
    printf( "ImqQueueManager::disconnect ended with reason code %ld\n",
            (long)mgr.reasonCode( ) );
  }

  // Tidy up the channel object if allocated.
  if ( pchannel ) {
    mgr.setChannelReference( );
    delete pchannel ;
  }

 // printf( "Sample IMQSPUT end\n" );
  //return( 0 );
	
 	
	
	return 1;
}

int Iso8583Msg::SendMessageToQueueNoTimeout(RWCString incoming, char *recv_queue,char *queue_mgr)
{
	
   //FILE * fp ;                      // Console


  ImqQueueManager mgr;             // Queue manager
  ImqQueue queueA;                  // Queue
  ImqQueue queueB;                  // Queue
  ImqMessage msg;                  // Data message
  ImqMessage msg2;                  // Data message
  
  int      buflen;                 // Buffer length
  char     buffer[ 1024 ] = {""};          // Message buffer
  ImqDistributionList dlist;	   // Distribution List
  ImqChannel * pchannel = 0 ;      // Channel definition

  strcpy(buffer, incoming);

 // printf( "Sample IMQSPUT start\n" );
 	
  char test_input[] = "SYSTEM.DEF.SVRCONN/TCP/127.0.0.1(1414)";
  ImqString strParse( test_input );
 // printf("valor de test > %s\n", test_input);
	  
  ImqString strToken ;

  pchannel = new ImqChannel ;
  pchannel -> setHeartBeatInterval( 1L );

    // Break down the channel definition,
    // which is of the form "channel-name/transport-type/connection-name".
    if ( strParse.cutOut( strToken, '/' ) ) {
      pchannel -> setChannelName( strToken );
      if ( strParse.cutOut( strToken, '/' ) ) {

        // Interpret the transport type.
        if ( strToken.upperCase( ) == (ImqString)"LU62" ) {
          pchannel -> setTransportType( MQXPT_LU62 );
        }
        if ( strToken.upperCase( ) == (ImqString)"NETBIOS" ) {
          pchannel -> setTransportType( MQXPT_NETBIOS );
        }
        if ( strToken.upperCase( ) == (ImqString)"SPX" ) {
          pchannel -> setTransportType( MQXPT_SPX );
        }
        if ( strToken.upperCase( ) == (ImqString)"TCP" ) {
          pchannel -> setTransportType( MQXPT_TCP );
        }

        // Establish the connection name.
        if ( strParse.cutOut( strToken ) ) {
          pchannel -> setConnectionName( strToken );
       
		
		
		}
      }

    
	
	mgr.setChannelReference( pchannel );
	
	 
  }


  
  mgr.setName( queue_mgr );
  //mgr.setName( "QM_victort8100" );
  
  // Connect to queue manager

  if ( ! mgr.connect( ) ) {

    /* stop if it failed */
    printf( "ImqQueueManager::connect ended with reason code %d\n",
            (int)mgr.reasonCode( ) );
    exit( (int)mgr.reasonCode( ) );
  }

  ImqString strManagerName( mgr.name( ) );
 // printf("Successful connection to queue manager %s\n",
   //                                     (char *)strManagerName );

  // Associate distribution list with queue manager
//  dlist.setConnectionReference( mgr);
  // Associate queue with queue manager.
 // queue.setConnectionReference( mgr );

  queueA.setConnectionReference( mgr );
  //queueB.setConnectionReference( mgr );

  queueA.setName( recv_queue );
//  queueB.setName( sql_queue );
  
  // Use parameter as the name of the target queue

 // printf( "First target queue is %s\n", (char *)queueA.name( ) );
 // printf( "Second target queue is %s\n", (char *)queueB.name( ) );

  queueA.setQueueManagerName( (char *)strManagerName );
//  queueB.setQueueManagerName( (char *)strManagerName );

 queueA.setOpenOptions( MQOO_OUTPUT /* open queue for output        */
    + MQOO_FAIL_IF_QUIESCING );     /* but not if MQM stopping      */
  queueA.open( );

// queueB.setOpenOptions( MQOO_OUTPUT /* open queue for output        */
//    + MQOO_FAIL_IF_QUIESCING );     /* but not if MQM stopping      */
 // queueB.open( );

  
  
  /* report reason, if any; stop if failed      */
  if ( queueA.reasonCode( ) ) {
    printf( "ImqQueue::open ended with reason code %d\n",
            (int)queueA.reasonCode( ) );
  }

  if ( queueA.completionCode( ) == MQCC_FAILED ) {
    printf( "unable to open queue for output\n" );
  }


//  if ( queueB.reasonCode( ) ) {
 //   printf( "ImqQueue::open ended with reason code %d\n",
 //           (int)queueB.reasonCode( ) );
//  }

//  if ( queueB.completionCode( ) == MQCC_FAILED ) {
//    printf( "unable to open queue for output\n" );
//  }

 // msg.setExpiry( 150 );  
  msg.useEmptyBuffer( buffer, sizeof( buffer ) );
  msg.setFormat( MQFMT_STRING );      /* character string format    */
//  msg2.useEmptyBuffer( buffer, sizeof( buffer ) );
//  msg2.setFormat( MQFMT_STRING );      /* character string format    */


     buflen = (int)strlen( buffer ); /* determine string length    */

     buffer[ buflen ] = '\0' ;            /* add line-end          */
 

   if ( buflen > 0 ) {
      msg.setMessageLength( buflen );
	   msg2.setMessageLength( buflen );
	 
      if ( ! queueA.put( msg ) ) {

        /* report reason, if any */
        printf( "ImqQueueA::put ended with reason code %d\n",
                (int)queueA.reasonCode( ) );
      }
//	   if ( ! queueB.put( msg2 ) ) {

        /* report reason, if any */
//        printf( "ImqQueueB::put ended with reason code %d\n",
//                (int)queueB.reasonCode( ) );
//      }


    } else {
      /* quit loop when empty line is read */
     // break ;
    }

	// Close the target queue (if it was opened)
  if ( ! queueA.close( ) ) {

    /* report reason, if any     */
    printf( "ImqQueue::close ended with reason code %d\n",
            (int)queueA.reasonCode( ) );
  }

 //if ( ! queueB.close( ) ) {

    /* report reason, if any     */
 //   printf( "ImqQueue::close ended with reason code %d\n",
//            (int)queueB.reasonCode( ) );
//  }



  // Disconnect from MQM if not already connected (the
  // ImqQueueManager object handles this situation automatically)
  if ( ! mgr.disconnect( ) ) {

    /* report reason, if any     */
    printf( "ImqQueueManager::disconnect ended with reason code %ld\n",
            (long)mgr.reasonCode( ) );
  }

  // Tidy up the channel object if allocated.
  if ( pchannel ) {
    mgr.setChannelReference( );
    delete pchannel ;
  }

 // printf( "Sample IMQSPUT end\n" );
  //return( 0 );
	
 	
	
	return 1;
}




RWCString Iso8583Msg::Get_Msg_From_SendQueueOld(   char *send_queue,char *queue_mgr)
//RWCString Iso8583Msg::Get_Msg_From_SendQueue( RWSocketPortal p,  char *send_queue,char *queue_mgr)

{
	
   RWCString retorno_msg = "";
   ImqQueueManager mgr;             // Queue manager
   ImqQueue queue ;                 // Queue
   ImqMessage msg;                  // Data message
   ImqGetMessageOptions gmo;        // Get message options
   char buffer[ 1024] = {""};       // Message buffer
   ImqChannel * pchannel = 0 ;      // Channel definition

	
  // Create object descriptor for subject queue
  queue.setName( send_queue );
  //queue.setName( "RECVQUEUE" );
 	
  mgr.setName( queue_mgr);
   //mgr.setName( "QM_victort8100");
  
  char test_input[] = "SYSTEM.DEF.SVRCONN/TCP/127.0.0.1(1414)";

    ImqString strParse( test_input );
    ImqString strToken ;

    pchannel = new ImqChannel ;
    pchannel -> setHeartBeatInterval( 1L );

    // Break down the channel definition,
    // which is of the form "channel-name/transport-type/connection-name".
    if ( strParse.cutOut( strToken, '/' ) ) {
      pchannel -> setChannelName( strToken );

      if ( strParse.cutOut( strToken, '/' ) ) {

        // Interpret the transport type.
        if ( strToken.upperCase( ) == (ImqString)"LU62" ) {
          pchannel -> setTransportType( MQXPT_LU62 );
        }
        if ( strToken.upperCase( ) == (ImqString)"NETBIOS" ) {
          pchannel -> setTransportType( MQXPT_NETBIOS );
        }
        if ( strToken.upperCase( ) == (ImqString)"SPX" ) {
          pchannel -> setTransportType( MQXPT_SPX );
        }
        if ( strToken.upperCase( ) == (ImqString)"TCP" ) {
          pchannel -> setTransportType( MQXPT_TCP );
        }

        // Establish the connection name.
        if ( strParse.cutOut( strToken ) ) {
          pchannel -> setConnectionName( strToken );
        }
      }
    }

    mgr.setChannelReference( pchannel );
 
  // Connect to queue manager
  if ( ! mgr.connect( ) ) {

    /* stop if it failed     */
    printf( "ImqQueueManager::connect failed with reason code %ld\n",
            (long)mgr.reasonCode( ) );
    exit( (int)mgr.reasonCode( ) );
  }

  // Associate queue with queue manager.
  queue.setConnectionReference( mgr );

  // Open the named message queue for input; exclusive or shared
  // use of the queue is controlled by the queue definition here
  queue.setOpenOptions(
                   MQOO_INPUT_AS_Q_DEF /* open queue for input      */
                 + MQOO_FAIL_IF_QUIESCING
                             );        /* but not if MQM stopping   */
  queue.open( );

  /* report reason, if any; stop if failed      */
  if ( queue.reasonCode( ) ) {
    printf( "ImqQueue::open ended with reason code %ld\n",
            (long)queue.reasonCode( ) );
  }

  if ( queue.completionCode( ) == MQCC_FAILED ) {
    printf( "unable to open queue for input\n" );
  }

  // Get messages from the message queue
  // Loop until there is a failure
  msg.useEmptyBuffer( buffer, sizeof( buffer ) - 1 );
                                 /* buffer size available for GET   */
  gmo.setOptions( MQGMO_WAIT |   /* wait for new messages           */
                  MQGMO_FAIL_IF_QUIESCING );
  //gmo.setWaitInterval( 1000 );  /* 15 second limit for waiting     */
  gmo.setWaitInterval( 1500 );  /* 15 second limit for waiting     */
//  gmo.setExpiry(10000 );  /* 15 second limit for waiting     */
  while ( queue.completionCode( ) != MQCC_FAILED ) 
  {

    // In order to read the messages in sequence, MsgId and
    // CorrelID must have the default value.  MQGET sets them
    // to the values in for message it returns, so re-initialise
    // them before every call
    msg.setMessageId( );
    msg.setCorrelationId( );
	RWCString test_1 ;
	RWCString incoming_0210;
	//cout << "dentro de get_message1 > " << endl;
    if ( queue.get( msg, gmo ) ) 
	{
  
      // Display each message received
      if ( msg.formatIs( MQFMT_STRING ) ) 
	  {
    
        buffer[ msg.dataLength( ) ] = 0 ;  /* add terminator          */
        //printf( "message <%s>\n", msg.bufferPointer( ) );
		test_1 = msg.bufferPointer( ) ;
			
		if((test_1(14,4)) == "0800")
		{
			retorno_msg = test_1 ;
		}
		if((test_1(14,4)) == "0200")
		{
			retorno_msg = test_1 ;
		}

		if((test_1(14,4)) == "0100")
		{
				retorno_msg = test_1 ;
		}
		if((test_1(12,4)) == "0420")
		{
			retorno_msg = test_1 ;
		}

		if((test_1(14,4)) == "0520")
		{
			retorno_msg = test_1 ;
		}

		if((test_1(0,4)) == "0800")
		{
			retorno_msg = test_1 ;
		}


		break;

      } 
	  else 
	  
	  {
        printf( "Non-text message\n" );
      }

    } 
//	else 
//	{
		/*
		RWCString output_no_response = "0210,000000,000000000000,000000000000,111111,222222,3333,444444444444,000000,91";
		output_no_response+="\n";
		char output_inoperative[150] = {""};
		strcpy(output_inoperative,output_no_response);
		cout << "dentro de get_message4 > " << endl;
		Iso8583Msg test_send2;
		
		test_send2.Send_Message_0210(output_inoperative);
		break;
		*/
      /* report reason, if any     */
      if ( queue.reasonCode( ) == MQRC_NO_MSG_AVAILABLE ) 
	  {
                                /* special report for normal end    */
        //printf( "no more messages\n" );
      } 
	  else 
	  {
                                /* general report for other reasons */
        printf( "ImqQueue::get ended with reason code %ld\n",
                (long)queue.reasonCode( ) );

        /*   treat truncated message as a failure for this sample   */
        if ( queue.reasonCode( ) == MQRC_TRUNCATED_MSG_FAILED ) 
		{
          break ;
        }
      }
    //}

  }

  // Close the source queue (if it was opened)
  if ( ! queue.close( ) ) {

    /* report reason, if any     */
    printf( "ImqQueue::close failed with reason code %ld\n",
            (long)queue.reasonCode( ) );
  }

  // Disconnect from MQM if not already connected (the
  // ImqQueueManager object handles this situation automatically)
  if ( ! mgr.disconnect( ) ) {

    /* report reason, if any     */
    printf( "ImqQueueManager::disconnect failed with reason code %ld\n",
            (long)mgr.reasonCode( ) );
  }

  // Tidy up the channel object if allocated.
  if ( pchannel ) 
  {
    mgr.setChannelReference( );
    delete pchannel ;
  }
//cout << "Salida >" << endl;
return retorno_msg;

} 
/*
RWCString Iso8583Msg::Get_Msg_From_Sock( RWSocketPortal p,  char *send_queue,char *queue_mgr)

{
	
   RWCString retorno_msg = "";
 

 
	RWCString test_1 ;
	RWCString incoming_0210;
	//test_1 = msg.bufferPointer( ) ;
			
	if((test_1(11,4)) == "0800")
	{
		Iso8583Msg test_send_0800;
		retorno_msg = test_send_0800.setIsoGeneric0800(test_1) ;
	}
	if((test_1(11,4)) == "0200")
	{
		Iso8583Msg test_send_0200;
		retorno_msg = test_send_0200.setIsoPostermFromGeneric0200(test_1) ;
		//cout << "Valor de retorno_msg > :" << retorno_msg << endl;
	}

					

return retorno_msg;

} 


RWCString Iso8583Msg::Send_Msg_To_Sock( RWSocketPortal p,  char *send_queue,char *queue_mgr)

{
	
   RWCString retorno_msg = "";
 

 
	RWCString test_1 ;
	RWCString incoming_0210;
	//test_1 = msg.bufferPointer( ) ;
			
	if((test_1(11,4)) == "0800")
	{
		Iso8583Msg test_send_0800;
		retorno_msg = test_send_0800.setIsoGeneric0800(test_1) ;
	}
	if((test_1(11,4)) == "0200")
	{
		Iso8583Msg test_send_0200;
		retorno_msg = test_send_0200.setIsoPostermFromGeneric0200(test_1) ;
		//cout << "Valor de retorno_msg > :" << retorno_msg << endl;
	}

					

return retorno_msg;

} 


*/

int Iso8583Msg::Send_Message_0210(char *input_msg )
{
	
  	RWCString iso_converted = input_msg;
	
	char output_0200[1024] = {""};
	RWCString outgoing_0210 = "";
	RWCString delimitador_coma = ",";
	RWCString outgoing_tcp_0200_tcp_header = "";
	

	
	if(iso_converted(0,4) != "0210")
	{
		
		
		cout << "Valor de outgoing_tcp_0200_tcp_header > " << outgoing_tcp_0200_tcp_header << endl;
		cout << "Longitud de outgoing_tcp_0200_tcp_header > " << outgoing_tcp_0200_tcp_header.length() << endl;
		



	}

	else
	{
		outgoing_0210 = iso_converted;
	}
	
		return 0;

} 

RWCString Iso8583Msg::SetTcpHeader( RWCString incoming_tcp_header ) 

{
	RWCString msg_reponse_with_tcp_header = "";
//	cout << "Valor de incoming_tcp_header.length().............> " 
  //       << dec << incoming_tcp_header.length() << endl;
	char buffer[20] = {""};
    int  i = incoming_tcp_header.length();
   
	  _itoa( i, buffer, 16 );
 
	if(incoming_tcp_header.length() > 255)
	{
		RWCString hex_input_uno = RWCString(buffer)(0,1) ;
		RWCString hex_input_dos = RWCString(buffer)(1,2) ;

		char primer_valor = RetornoHexadecimal(hex_input_uno);
		char segundo_valor = RetornoHexadecimal(hex_input_dos);
	
		//cout << "Valor de primer_valor y segundo_valor............> " << hex << int( primer_valor) 
		//	 << hex << int(segundo_valor) <<   endl;
		//cout << endl;

		//cout << "Valor de primer_valor y segundo_valor en ascii...> " << primer_valor 
		//	 <<segundo_valor <<   endl;
		//cout << endl;
	
		msg_reponse_with_tcp_header = RWCString(primer_valor)+RWCString(segundo_valor)+incoming_tcp_header;

		}
	else
	{
		
		RWCString hex_input_uno = "00";
		RWCString hex_input_dos = RWCString(buffer)(0,2) ;
		char segundo_valor = RetornoHexadecimal(hex_input_dos);
		char primer_valor  = RetornoHexadecimal(hex_input_uno);
	//	cout << "Valor de  segundo_valor...........................> " << hex << (int)segundo_valor <<   endl;
		
	//	cout << "Valor de hex_input_uno y segundo_valor en ascii...> " << primer_valor 
	//		 <<  segundo_valor <<   endl;
	
	//	cout << endl;

		msg_reponse_with_tcp_header = RWCString(primer_valor)+RWCString(segundo_valor)+incoming_tcp_header ;
	

	}


return msg_reponse_with_tcp_header;				

}

char Iso8583Msg::RetornoHexadecimal(RWCString hex_input)
{
	

	if ((hex_input == "0") || (hex_input == "00"))
		return '\x0';
	if ((hex_input == "1") || (hex_input == "01"))
		return '\x01';
	if ((hex_input == "2") || (hex_input == "02"))
		return '\x02';
	if ((hex_input == "3") || (hex_input == "03"))
		return '\x03';
	if ((hex_input == "4") || (hex_input == "04"))
		return '\x04';
	if ((hex_input == "5") || (hex_input == "05"))
		return '\x05';
	if ((hex_input == "6") || (hex_input == "06"))
		return '\x06';
	if ((hex_input == "7") || (hex_input == "07"))
		return '\x07';
	if ((hex_input == "8") || (hex_input == "08"))
		return '\x08';
	if ((hex_input == "9") || (hex_input == "09"))
		return '\x09';
	if ((hex_input == "0a") || (hex_input == "a"))
		return '\x0a';
	if ((hex_input == "0b") || (hex_input == "b"))
		return '\x0b';
	if ((hex_input == "0c") || (hex_input == "c"))
		return '\x0c';
	if ((hex_input == "0d") || (hex_input == "d"))
		return '\x0d';
	if ((hex_input == "0e") || (hex_input == "e"))
		return '\x0e';
	if ((hex_input == "0f") || (hex_input == "f"))
		return '\x0f';

	if (hex_input == "10")
		return '\x10';
	if (hex_input == "11")
		return '\x11';
	if (hex_input == "12")
		return '\x12';
	
	if (hex_input == "13")
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




Iso8583Msg::~Iso8583Msg()
{
	//cout << "Dentro de destructor > " << endl;
}
