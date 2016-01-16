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

	response_0210_generic_from_iso		= "";
	lllvar								= "";
	llvar								= "";

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
//	RWCString  delimiter_igual = '\x03';
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
				//response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+msg_for_processing(next_field,var_field);
				response_0210_generic_from_iso +=msg_for_processing(next_field,var_field);
				response_0210_generic_from_iso +=delimiter;
				next_field = next_field+var_field;
				//if((j+1) == 125)

				break;
		
			case LLVAR:
				
				llvar	= msg_for_processing(next_field,LLVAR);
				var_field = atoi(llvar);
				next_field = next_field+LLVAR;
				if(debug == 1)
					ReturnIso8583FieldValue(msg_input, j+1  , msg_for_processing(next_field,var_field));
				//response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+msg_for_processing(next_field,var_field);
				response_0210_generic_from_iso +=msg_for_processing(next_field,var_field);
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
						
						//response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+test_iso_new.RetornoAsciiComplete(msg_processing_053(0,8),8) ;
						response_0210_generic_from_iso +=test_iso_new.RetornoAsciiComplete(msg_processing_053(0,8),8) ;
						response_0210_generic_from_iso +=delimiter;
					}
					else
					{
						if(debug == 1)
							ReturnIso8583FieldValue(msg_input, j+1  , msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]));
					
						//response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]);
						response_0210_generic_from_iso +=msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]);
						response_0210_generic_from_iso +=delimiter;
					}
				}
			
			}
		}
		
	}

    //iso_field_length[125] 
	return response_0210_generic_from_iso;

}
RWCString IsoBitMap::Retorno_Msg_Generic_Field125(RWCString incoming , char *msg_type, 
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
					retorno_125 = msg_for_processing(next_field,var_field);
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

void IsoBitMap::ShowFieldIso8583B24(RWCString incoming , char *msg_type, 
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
				//response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+msg_for_processing(next_field,var_field);
				response_0210_generic_from_iso +=msg_for_processing(next_field,var_field);
				if((j+1) == 125)
					retorno_125 = msg_for_processing(next_field,var_field);
				response_0210_generic_from_iso +=delimiter;
				next_field = next_field+var_field;
				

				break;
		
			case LLVAR:
				
				llvar	= msg_for_processing(next_field,LLVAR);
				var_field = atoi(llvar);
				next_field = next_field+LLVAR;
				if(debug == 1)
					ReturnIso8583FieldValue(msg_input, j+1  , msg_for_processing(next_field,var_field));
				//response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+msg_for_processing(next_field,var_field);
				response_0210_generic_from_iso +=msg_for_processing(next_field,var_field);
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
						
						//response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+test_iso_new.RetornoAsciiComplete(msg_processing_053(0,8),8) ;
						response_0210_generic_from_iso +=test_iso_new.RetornoAsciiComplete(msg_processing_053(0,8),8) ;
						response_0210_generic_from_iso +=delimiter;
					}
					else
					{
						if(debug == 1)
							ReturnIso8583FieldValue(msg_input, j+1  , msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]));
					
						//response_0210_generic_from_iso +=field_length.RetornoPreZeroes(j+1)+msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]);
						response_0210_generic_from_iso +=msg_for_processing((next_field-iso_field_length[j+1]),iso_field_length[j+1]);
						response_0210_generic_from_iso +=delimiter;
					}
				}
			
			}
		}
		
	}

    //iso_field_length[125] 
//	return retorno_125;

}



RWCString IsoBitMap::Retorno_Msg_Iso_PostermB240810(RWCString incoming , char *msg_type, 
													          int debug, RWCString application)
{


	RWCString response_0810 = "";
	RWCString header_msg	;   //02
	RWCString msg_type_identifier;   //02
	RWCString bit_map_b24		;  //02
	RWCString transmition_date_time	;	//07     		
	RWCString system_trace			;	//11				
	RWCString network_mng_info_code	;	//70
	
		header_msg						= incoming(2,12);   //02
		msg_type_identifier				= incoming(14,4);   //02
		bit_map_b24						= incoming(18,32);  //02
		transmition_date_time			= incoming(50,10);	//07     		
		system_trace					= incoming(60,6);	//11				
		network_mng_info_code			= "001";//incoming(66,3);	//70
		//network_mng_info_code			= incoming(80,3);	//70
		
		
	

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
		response_0810 =header_msg+"0810"+bit_map_810+transmition_date_time+system_trace
			+"00"+network_mng_info_code+end_of_type;


//	cout << "Valor de output en funcion > " << response_0810 << endl;
	return response_0810;

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
