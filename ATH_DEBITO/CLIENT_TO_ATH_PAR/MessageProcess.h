#if defined(MESSAGEPROCESS_H)

#else
#define MESSAGEPROCESS_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <strstrea.h>
#include <fstream.h>
#include <iomanip.h>
#include "verificarretorno.h"
#include "writelog.h"
#include <time.h>
#include <rw/rwtime.h>
#include <rw/rwdate.h>
#include <rw/rstream.h>
#include <rw/rstream.h>
#include <rw/cstring.h>
#include <rw/timer.h> 
#include <rw/toolpro/sockaddr.h>
#include <rw/toolpro/sockport.h>
#include <rw/toolpro/inetaddr.h>
#include <rw/toolpro/winsock.h>
#include <rw/toolpro/portstrm.h>
#include <rw/toolpro/socket.h>
#include <rw/ctoken.h>
#include <rw/thr/thrfunc.h>
#include <rw/toolpro/neterr.h>
#include <rw/thr/threadid.h>
#include "MQUtility.h"
#include "FDumpHex.h"
#include "Iso8583Msg.h"



#include <string>

void MessageErrorLength(RWCString incoming_name, int correct_field_length,
int wrong_field_length); 

int VerifyNumericField(char *incoming, const int length_field, RWCString validated_field);
int VerifyHexField(char *incoming, const int length_field, RWCString validated_field);

int VerifyField(RWCString incomingS)
{

  if(incomingS.first('\x1c') == RW_NPOS )
	  cout << "No hay este caracter > "  << endl;
  return incomingS.length();


}





void MessageErrorLength(RWCString incoming_name, int wrong_field_length, int correct_field_length) 
{

	cout << "El largo de " <<  incoming_name << " es incorrecto > " 
	     << " es de " << wrong_field_length <<" y debe ser "
		 << correct_field_length << endl;
		 cout << "***********Transaccion abortada********** > " << endl;

}




char RetornoHexadecimal(RWCString hex_input)
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

RWCString SetTcpHeader( RWCString incoming_tcp_header ) 

{
	RWCString msg_reponse_with_tcp_header = "";
	char buffer[20] = {""};
    int  i = incoming_tcp_header.length();
   
	  _itoa( i, buffer, 16 );
 
	if(incoming_tcp_header.length() > 255)
	{
		RWCString hex_input_uno = RWCString(buffer)(0,1) ;
		RWCString hex_input_dos = RWCString(buffer)(1,2) ;

		char primer_valor = RetornoHexadecimal(hex_input_uno);
		char segundo_valor = RetornoHexadecimal(hex_input_dos);

		msg_reponse_with_tcp_header = RWCString(primer_valor)+RWCString(segundo_valor)+incoming_tcp_header;

		}
	else
	{
		
		RWCString hex_input_uno = "00";
		RWCString hex_input_dos = RWCString(buffer)(0,2) ;
		char segundo_valor = RetornoHexadecimal(hex_input_dos);
		char primer_valor  = RetornoHexadecimal(hex_input_uno);

		msg_reponse_with_tcp_header = RWCString(primer_valor)+RWCString(segundo_valor)+incoming_tcp_header ;
	

	}


return msg_reponse_with_tcp_header;				

}


RWCString SetB24Header0800( RWCString incoming_tcp_header ) 
{
	
	
	RWCString header_base24_0800= "ISO005000060";
	header_base24_0800+=incoming_tcp_header;
	return header_base24_0800;				


}

RWCString SetB24HeaderPos0200( RWCString incoming_tcp_header ) 
{
	
	
	RWCString header_base24_0200= "ISO025000066";
	header_base24_0200+=incoming_tcp_header;
	return header_base24_0200;				


}


RWCString SetB24HeaderAtm0200( RWCString incoming_tcp_header ) 
{
	
	
	RWCString header_base24_0200= "ISO015000060";
	header_base24_0200+=incoming_tcp_header;
	return header_base24_0200;				


}


RWCString Get_Msg_From_Sock( RWSocketPortal p,  char *send_queue,char *queue_mgr)

{
	
 	RWThreadId myID = rwThreadId();
	cout << "My native thread ID is >:"<< myID << endl;
	RWCString retorno_msg = "";
	RWCString incoming_msg = "";
	
while(1)
{	
	incoming_msg = p.recv();
	if (incoming_msg.isNull())
	{
		cout << "Received a Disonnected from the Host > " << endl;
		client_flag = 0;
		break;
	}


	FDumpHex header_length;

	MQUtility process_0200;

	int buffer_recv  = incoming_msg.length();
	int header_tcp = 2;
	int header_len = header_length.GetMesageLength(incoming_msg) ;
	int header_sub = 0;
	RWCString incoming_for_proccessing;
	RWCString incoming_next;
	int len_msg = 0;
	int msg_len = 0;
	int tcp_header = 2;


	if((incoming_msg(14,4)) == "0810")
	{
		Iso8583Msg get_bit_map_ascii;
		if(debugSB == 1)
		{
			//IsoBitMap show_field_iso8583;
			RWTime b;
			cout << "Incoming 0810 " << "Time: " << b << " " << " *****<<<< Mensaje 0810 recibido >>>***** " << endl;
   	
		}
		Iso8583Msg send_generic_810;

		send_generic_810.SendMessageToQueue(incoming_msg(2,incoming_msg.length()-2),
			recv_queue,queue_mgr);


	}

	if((incoming_msg(14,4)) == "0800")
	{
	
		Iso8583Msg get_bit_map_ascii;
	


		if(debugSB == 1)
		{
			RWTime b;
			cout << "Incoming 0800 " << "Time: " << b << " " << " *****<<<< Mensaje 0800 recibido >>>***** " << endl;
   	
		}
		IsoBitMap get_0810bitmap;
		retorno_msg = get_0810bitmap.Retorno_Msg_Iso_PostermB240810(incoming_msg, "0800",debugSB,"posterm");

		if(debugSB == 1)
		{
			RWTime b;
			cout << "Outgoing 0810 " << "Time: " << b << " " << " *****<<<< Mensaje 0810 enviado >>>>***** " << endl;
   	
		}
	
		if( (p.sendAtLeast(SetTcpHeader(retorno_msg),retorno_msg.length()) == 64))
		{
			
					
			try 
			{

			}
			catch (const RWSockErr& err) 
			{
			if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
			
			}
		}


		
	}




	if((incoming_msg(14,4)) == "0200")
	{
		Iso8583Msg get_bit_map_ascii;
		if(debugSB == 1)
		{
			RWTime c;
			cout << "Incoming 0200 " << "Time: " << c << " " << "<<< Mensaje 0200 enviado >>>" << endl;
		}		
		IsoBitMap get_firts_char_bitmap;
		Iso8583Msg send_generic_210;
			send_generic_210.SendMessageToQueue(get_firts_char_bitmap.Retorno_Msg_Generic_PostermB24(incoming_msg, "0200", debugSB, "base24"),
			recv_queue,queue_mgr);


	}
	
	if((incoming_msg(14,4)) == "0210")
	{
		int flag_error = 0;
		
		DWORD dwEventID = 5000;	
		char msg_210[5000] = {""};
		len_msg = header_length.GetMesageLength(incoming_msg) ;
		if( (msg_len >= 250) || (msg_len <= 4290))
		{
		
				

			if ( len_msg+tcp_header == incoming_msg.length())
			{
				RWTime b;
				cout << endl;
				cout << "Incoming 0210 " << "Time: " << b << " " << " *****<<<< Mensaje 0210 recibido >>>***** " << endl;
 				cout << endl;

		
			
				process_0200.Proccess_Message_PostilionNoField125(incoming_msg,recv_queue,queue_mgr);
				
			}
			else
			if ( (incoming_msg.length()) > len_msg )
			{
				incoming_for_proccessing = incoming_msg;
				int len_kept = incoming_msg.length();
				int salida = 1;
				char buffer_length[10] = {""};
				
				
				_itoa( len_kept, buffer_length, 10 );
				

				strcpy(msg_210 , RWCString(buffer_length)+incoming_for_proccessing);
					
				WriteLogMessage( dwEventID, APPName, msg_210);
				while(salida == 1)
				{
						
					msg_len = header_length.GetMesageLength(incoming_for_proccessing) ;
					if( (msg_len >= 300) || (msg_len <= 9290))
					{
				
						RWTime b;
						cout << endl;
						cout << "Incoming 0210 " << "Time: " << b << " " << " *****<<<< Mensaje 0210  recibido >>>***** " << endl;
   						cout << endl;
						//Aqui se saca el largo del mensaje 0210 para su proceso.
					
						//Se verifica la diferencia del meensaje a procesar y lo que queda del 
						//de los mensajes 0210 y si mensaje que queda es mayor se sigue procesando
						//Y sino es que hay algun error y se termina de procesar los mensajes
						len_msg = header_length.GetMesageLength(incoming_for_proccessing) ;
	

						if ( incoming_for_proccessing.length() >= len_msg+tcp_header )
						{
							//cout << "*********YES**************" << endl;

						}
						else
						{
							flag_error = 1;
							len_kept = 0;
							//cout << "*********NO**************" << endl;
							//cout << "Valor de incoming_for_proccessing.length() " <<
							//	incoming_for_proccessing.length() << endl;
							//cout << "Valor de len_msg+tcp_header " << len_msg+tcp_header << endl;

		
		
						}
					    //Aqui se asegura que si el mensaje no concuerda le lago del TCP/IP Header
						//con el largo extraido que aborte la transaccion
						if (flag_error == 0)
						{
							incoming_for_proccessing = incoming_for_proccessing(0,(tcp_header+msg_len));
			           


							process_0200.Proccess_Message_PostilionNoField125(incoming_for_proccessing,recv_queue,queue_mgr);
							
						

							len_kept = len_kept - (msg_len+tcp_header);

						}
						if(len_kept == 0)
						{
							salida = 0;
						}
							
						//Aquei se saca el restante del mensaje para precesarse de nuevo.	
						//incoming_next =  incoming_msg(len_kept,incoming_msg.length()-len_kept);
					
						if (flag_error == 0)
						{
					
							incoming_msg =  incoming_msg(msg_len+tcp_header,len_kept);
					
				
							incoming_for_proccessing = "";
							incoming_for_proccessing = incoming_msg;
					
						}
					}
					else
					{
						cout << "Longitud el mensaje es incorrecto> " << endl;
						//break;
						salida = 0;
					}
				}//Termina el while
			}
		}
		else
		{
			cout << "Longitud el mensaje es incorrecto> " << endl;
		}
	}
	if((incoming_msg(14,4)) == "0110")
	{
		Iso8583Msg get_bit_map_ascii;
		if(debugSB == 1)
			cout << "Valor de incoming_0110 > :" << incoming_msg << endl;
				
		IsoBitMap get_firts_char_bitmap;
		Iso8583Msg send_generic_110;
		send_generic_110.SendMessageToQueue(get_firts_char_bitmap.Retorno_Msg_Generic_PostermB24(incoming_msg, "0210", debugSB, "posterm"),
			recv_queue,queue_mgr);
				
	}


	
	if((incoming_msg(14,4)) == "0430")
	{
	
		RWTime b;
		cout << endl;
		cout << "Incoming 0430 " << "Time: " << b << " " << " *****<<<< Mensaje 0430 recibido >>>***** " << endl;
 		cout << endl;
   	
		
		Iso8583Msg get_bit_map_ascii;
	
		IsoBitMap get_firts_char_bitmap;
		Iso8583Msg send_generic_210;
		MQUtility send_generic_430;

		if ( (strcmp(recv_queue,"RECVATHNOGEN") == 0)  || (strcmp(recv_queue,"IWMHOSTM") == 0) )
		{
			send_generic_430.SendMessageToQueueNewATHDebito0430("00"+incoming_msg(2,incoming_msg.length()-2),
			recv_queue,queue_mgr);
	
		}
		else
		{
			send_generic_210.SendMessageToQueue(get_firts_char_bitmap.Retorno_Msg_Generic_PostermB24(incoming_msg, "0430", debugSB, "base24"),
				recv_queue,queue_mgr);

		}
		
	}

	if((incoming_msg(14,4)) == "0510")
	{
		Iso8583Msg get_bit_map_ascii;
		
		if(debugSB == 1)
		{
			RWTime b;
			cout << endl;
			cout << "Incoming 0210 " << "Time: " << b << " " << " *****<<<< Mensaje 0510 recibido >>>***** " << endl;
 			cout << endl;

		
		}
		
		process_0200.Proccess_Message_ATH(incoming_msg,sql_queue, recv_queue, queue_mgr);
			
	}

	if((incoming_msg(14,4)) == "0530")
	{
		Iso8583Msg get_bit_map_ascii;
		if(debugSB == 1)
			cout << "Valor de incoming_0530 > :" << incoming_msg << endl;
			
		IsoBitMap get_firts_char_bitmap;
		Iso8583Msg send_generic_210;
		send_generic_210.SendMessageToQueue(get_firts_char_bitmap.Retorno_Msg_Generic_PostermB24(incoming_msg, "0530", debugSB, "posterm"),
			recv_queue,queue_mgr);
	}

}

cout << "Salida de 	THREAD Get > " << endl;			

return retorno_msg;

} 


RWCString Send_Msg_To_Sock( RWSocketPortal p,  char *send_queue,char *queue_mgr)

{
	
   

	RWThreadId myID = rwThreadId();
	cout << "My native thread ID is >:"<< myID << endl;
	RWCString retorno_msg = "";
 	RWCString incoming_msg_from_socket;
    int trans_counter = 0;

while(1)
{

	Iso8583Msg msg_from_queue;

	MQUtility take_time_and_STAN;

	incoming_msg_from_socket = take_time_and_STAN.Get_Msg_From_SendQueueNew(send_queue,queue_mgr);
	if(incoming_msg_from_socket.length() == 0)
	{
		trans_counter+=1;
	}

	if(trans_counter >= time_out_0800)
	{
	    trans_counter = 0;
		RWCString msg_0800 = "";//"0800,000071111111111,00011123456,00012123456,000131111,00070301";
		msg_0800 = "0800,000071111111111,00011123456,00012123456,000131111,00070301";

		if(debugSB == 1)
		{
			RWTime b;
			cout << "Outgoing 0800 " << "Time: " << b << " " << " *****<<<< Mensaje 0800 enviado >>>>***** " << endl;
   			
		}
		Iso8583Msg test_send_0800;
	
		retorno_msg = test_send_0800.setMapIsoPosTermFromGeneric(msg_0800,application,tpdu_header,0) ;
	
		if( (p.sendAtLeast(SetTcpHeader(retorno_msg),retorno_msg.length()) == 64))
		{
			
					
			try 
			{
	
			}
			catch (const RWSockErr& err) 
			{
			if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
			
			}
		}

	
	}

	if((incoming_msg_from_socket(0,4)) == "0800")
	{
			
		
		if(debugSB == 1)
		{
			RWTime a;
			cout << endl;
			cout << "Incoming 0800 " << "Time: " << a << " " << incoming_msg_from_socket << endl;
		}	
					
		Iso8583Msg test_send_0800;
		retorno_msg = test_send_0800.setMapIsoPosTermFromGeneric(incoming_msg_from_socket,application,tpdu_header,debugSB) ;
		if(debugSB == 1)
		{
			cout << "Valor de retorno_msg > :" << retorno_msg << endl;
		    cout << endl;
		}
		if( (p.sendAtLeast(SetTcpHeader(retorno_msg),retorno_msg.length()) == 64))
		{
			
					
			try 
			{

			}
			catch (const RWSockErr& err) 
			{
			if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
			
			}
		}
	}


	if((incoming_msg_from_socket(12,4)) == "0800")
	{
			
		if(debugSB == 1)
		{
			//IsoBitMap show_field_iso8583;
			RWTime b;
			cout << "Incoming 0800 " << "Time: " << b << " " << " *****<<<< Mensaje 0800 enviado >>>***** " << endl;
   	
		}
	
	
		if( (p.sendAtLeast(SetTcpHeader(incoming_msg_from_socket),incoming_msg_from_socket.length()) > 35))
		{
			
					
			try 
			{
				/*
				incoming_0810 = p.recv();
				Iso8583Msg get_bit_map_ascii;
				if(debugSB == 1)
					cout << "Valor de incoming_0810    > :" << incoming_0810 << endl;
				    	
				IsoBitMap get_0810bitmap;
				Iso8583Msg send_generic_810;
				send_generic_810.SendMessageToQueue(get_0810bitmap.Retorno_Msg_Generic_Posterm(incoming_0810, "0810",debugSB),
					recv_queue,queue_mgr);
				*/
			}
			catch (const RWSockErr& err) 
			{
			if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
			
			}
		}
	}

	if((incoming_msg_from_socket(14,4)) == "0200")
	{
   		
		


		trans_counter=0;

	

		if(debugSB == 1)
		{
			RWTime b;
			cout << "Outgoing 0200 " << "Time: " << b << " " << " *****<<<< Mensaje 0200 enviado >>>>***** " << endl;
   	
		}
		if( (p.sendAtLeast(incoming_msg_from_socket,incoming_msg_from_socket.length()) > 65))
		{
	
			try 
			{

			}
			catch (const RWSockErr& err) 
			{
				if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
		
			}//end catch
		}//end if 0200 send
		
	}//end 0200 if
 
	if((incoming_msg_from_socket(0,4)) == "0100")
	{
		
		IsoBitMap retorno_field_125;
		//**Se toma el campo 125 y se copia al recv_queue**//		
		strcpy(recv_queue,retorno_field_125.Retorno_Msg_Generic_Field125(incoming_msg_from_socket, "0200", 0 , "base24"));

		if(debugSB == 1)
			cout << "Valor de incoming_0100 > :" << incoming_msg_from_socket << endl;

		
		if(debugSB == 1)
		{
			cout << "Valor de retorno_msg > :" << retorno_msg << endl;
		    cout << endl;
		}	
		if( (p.sendAtLeast(incoming_msg_from_socket,incoming_msg_from_socket.length()) > 65))
		{
	
			
			try 
			{

			}

			catch (const RWSockErr& err) 
			{
			if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
		
			}//end catch
		}//end if 0200 send
		
	}//end 0200 if
  

	if((incoming_msg_from_socket(12,4)) == "0420")
	{
		
		
			
		RWCString output_0420 = "";
		output_0420 = SetTcpHeader(incoming_msg_from_socket);
		
		if( (p.sendAtLeast(output_0420,output_0420.length()) > 65))
		{
	
		
			
			try 
			{

			}
			catch (const RWSockErr& err) 
			{
			if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
		
			}//end catch
		}//end if 0200 send
		
	}//end 0200 if
 
	if( (incoming_msg_from_socket(14,4) == "0420") || (incoming_msg_from_socket(14,4) == "0421"))
	{

		if(debugSB == 1)
		{
			//IsoBitMap show_field_iso8583;
			RWTime b;
			cout << "Incoming 0420 " << "Time: " << b << " " << " *****<<<< Mensaje 0420 enviado >>>***** " << endl;
   	
		}
	
		RWCString output_0420 = "";

		output_0420 = incoming_msg_from_socket;
		
		if( (p.sendAtLeast(output_0420,output_0420.length()) > 65))
		{
	
		
			
			try 
			{

			}
			catch (const RWSockErr& err) 
			{
			if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
		
			}//end catch
		}//end if 0200 send
	
	}//end 0200 if
 
	if( incoming_msg_from_socket(14,4) == "0500" )
	{
   		time_t now = time(0);
		RWCString output_0420 = "";


		if(debugSB == 1)
		{
			RWTime b;
			cout << "Outgoing 0500 " << "Time: " << b << " " << " *****<<<< Mensaje 0500 enviado >>>>***** " << endl;
   	
		}
	
		output_0420 = incoming_msg_from_socket;
		
		if( (p.sendAtLeast(output_0420,output_0420.length()) > 65))
		{
	
		
			
			try 
			{
	
			}
			catch (const RWSockErr& err) 
			{
			if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
		
			}//end catch
		}//end if 0200 send
		
	}//end 0200 if


	if((incoming_msg_from_socket(0,4)) == "0420")
	{
		
	
		
		
		IsoBitMap retorno_field_125;
		//**Se toma el campo 125 y se copia al recv_queue**//		
		strcpy(recv_queue,retorno_field_125.Retorno_Msg_Generic_Field125(incoming_msg_from_socket, "0200", 0 , "base24"));

		if(debugSB == 1)
			cout << "Valor de incoming_0420 > :" << incoming_msg_from_socket << endl;
				
		if(debugSB == 1)
		{
			cout << "Valor de retorno_msg > :" << retorno_msg << endl;
		    cout << endl;
		}
		if( (p.sendAtLeast(incoming_msg_from_socket,incoming_msg_from_socket.length()) > 65))
		{
	
		
			
			try 
			{

			}

			catch (const RWSockErr& err) 
			{
				if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
		
			}//end catch
		}//end if 0200 send
		
	}//end 0200 if


	if((incoming_msg_from_socket(0,4)) == "0520")
	{
		
		IsoBitMap retorno_field_125;
		//**Se toma el campo 125 y se copia al recv_queue**//		
		strcpy(recv_queue,retorno_field_125.Retorno_Msg_Generic_Field125(incoming_msg_from_socket, "0200", 0 , "base24"));

		if(debugSB == 1)
			cout << "Valor de incoming_0520 > :" << incoming_msg_from_socket << endl;
				
		if(debugSB == 1)
		{
			cout << "Valor de retorno_msg > :" << retorno_msg << endl;
		    cout << endl;
		}
		if( (p.sendAtLeast(incoming_msg_from_socket,incoming_msg_from_socket.length()) > 65))
		{
	
		
			
			try 
			{

			}

			catch (const RWSockErr& err) 
			{
			if ( err.errorNumber() == RWNETECONNABORTED ||
				err.errorNumber() == RWNETECONNRESET ) 
				{
					cout << "Disonnected from the Host> "  << endl;
					client_flag = 0;
				} 
				else 
				{
					throw;
				}
		
			}//end catch
		}//end if 0200 send
		
	}//end 0200 if

}				

	cout << "Salida de 	THREAD Send > " << endl;		
return retorno_msg;
} 




#endif