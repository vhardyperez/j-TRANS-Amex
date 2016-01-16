/**************************************************************************
 *
 * $Id:
 *
 ***************************************************************************
 *
 * Copyright (c) 1999-2000 Victor Contin.  All Rights Reserved.
 *
 * This computer software is owned by GM Group, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties. This computer software or any other copies thereof may not be
 * provided or otherwise made available to any other person.
 *
 * U.S. Government Restricted Rights.  This computer software is provided
 * with Restricted Rights.  Use, duplication, or disclosure by the
 * Government is subject to restrictions as set forth in subparagraph (c)
 * (1) (ii) of The Rights in Technical Data and Computer Software clause
 * at DFARS 252.227-7013 or subparagraphs (c) (1) and (2) of the
 * Commercial Computer Software – Restricted Rights at 48 CFR 52.227-19,
 * as applicable.  Manufacturer is GM Group, Inc.
 *
 **************************************************************************

 *  Original:   November 2002
 *  Latest:     11-22-2002 version 1.00
 *  Author:	    Victor Contin
 *
 *************************************************************************/


 /*************************************************************************
 
 Product Name 
 ServerBTrans.exe

 Functions
 Received transaction type cash register and convert it to Base24 ISO8583,
 when this convertion is finished this program make a PUT to a Queue named
 ISO-QUEUE.
      
 *********************************************************************/


//---------------------------------------------------------------------------
//                            ScotiaVoxBalTandem.cpp
//---------------------------------------------------------------------------

#include "Iso8583Msg.h" 
#include "IsoBitMap.h" 
#include "messageprocess.h"		// To Save Message
#include "MQUtility.h"
//#include "ace/Log_Msg.h"


using std::string;

void hello(void)                                             // 2
{
   cout << "Hello World!" << endl;
}


void report(const RWCString& string)
{
  cout << string << flush;
}

//void __cdecl main()
int main(int argc , char *argv[])

/*** CLIENT CODE ***/

{

	// Compile Time //
	time_t loadtime;
	UCHAR LoadDate[100];
	time (&loadtime);
	printf("\nCompiled on %s at %s.\n\n", __DATE__, __TIME__);
	sprintf((char*)LoadDate,"The server was started on %s\n", ctime(&loadtime));
	puts((char*)LoadDate);

	// Initialization Variables
	int counter = 1;
	static RWCString lastchar = '\n';
	RWWinSockInfo info;
/*
	
	const static char* appName = "B24_BTRANS_VEN";
	const static char* appAddr = "\\BtransGeneric\\INI\\CLIENT_TO_B24_VAR.INI";
*/		


	if(argc!=2)
	{
		cout << "Usage: AutoM? <AppName> " << endl;
		cout << "Example AppName GateTan1...6 " << endl;
		exit(1);
	}
	
	RWCString argumento1 = argv[1];
	argumentofortrace = argv[1];
	RWCString stringS1(argumento1);

	const static char* appName = argumento1;
	const static char* appAddr = "\\BtransGeneric\\INI\\CLIENT_TO_B24_VAR.INI";



	GetPrivateProfileString(appName,"appname","",APPName,sizeof(APPName),appAddr);
	if (strcmp(APPName,"") == 0)
	{
		cout << "Problem Opening Initialization File to get APPName"<< endl;
		exit(0);
	}
    
	
	GetPrivateProfileString(appName,"server_address","",SB1ADD,sizeof(SB1ADD),appAddr);
	if (SB1ADD == "              ")
	{
	
		char SB1ADD[15] = "10.1.10.7";
		cout << "Problem Opening Initialization File to get IP Address"<< endl;
	
		
	}

	port = GetPrivateProfileInt(appName,"server_port",0,appAddr);
	if (port == NULL)
	{
		cout << "Problem Opening Initialization File to get Port Number"<< endl;
		exit(0);
	}

	GetPrivateProfileString(appName,"server_address","",SB1ADD,sizeof(SB1ADD),appAddr);
	if (SB1ADD == "              ")
	{
	
		char SB1ADD[15] = "10.1.10.7";
		cout << "Problem Opening Initialization File to get IP Address"<< endl;
	
		
	}
	GetPrivateProfileString(appName,"header","",header,sizeof(header),appAddr);
	if (strcmp(header,"") == 0)
	{
		cout<< header<<endl;
		cout << "Problem Opening Initialization File to get header"<< endl;
		exit(0);
	}
	GetPrivateProfileString(appName,"tpdu_header","",tpdu_header,sizeof(tpdu_header),appAddr);
	if (strcmp(tpdu_header,"") == 0)
	{
		cout<< tpdu_header<<endl;
		cout << "Problem Opening Initialization File to get tpdu_header"<< endl;
		exit(0);
	}

	GetPrivateProfileString(appName,"application","",application,sizeof(application),appAddr);
	if (strcmp(application,"") == 0)
	{
		cout<< application<<endl;
		cout << "Problem Opening Initialization File to get application"<< endl;
		exit(0);
	}
	GetPrivateProfileString(appName,"file_name","",file_name,sizeof(file_name),appAddr);
	if (strcmp(file_name,"") == 0)
	{
		cout<< file_name<<endl;
		cout << "Problem Opening Initialization File to get file_name"<< endl;
		exit(0);
	}
	
	GetPrivateProfileString(appName,"file_name_trace","",file_name_trace,sizeof(file_name_trace),appAddr);
	if (strcmp(file_name_trace,"") == 0)
	{
		cout<< file_name_trace<<endl;
		cout << "Problem Opening Initialization File to get file_name_trace"<< endl;
		exit(0);
	}

	GetPrivateProfileString(appName,"send_queue","",send_queue,sizeof(send_queue),appAddr);
	if (strcmp(send_queue,"") == 0)
	{
		cout<< send_queue<<endl;
		cout << "Problem Opening Initialization File to get send_queue"<< endl;
		exit(0);
	}

	GetPrivateProfileString(appName,"recv_queue","",recv_queue,sizeof(recv_queue),appAddr);
	if (strcmp(recv_queue,"") == 0)
	{
		cout<< recv_queue<<endl;
		cout << "Problem Opening Initialization File to get recv_queue"<< endl;
		exit(0);
	}

	GetPrivateProfileString(appName,"sql_queue","",sql_queue,sizeof(sql_queue),appAddr);
	if (strcmp(sql_queue,"") == 0)
	{
		cout<< sql_queue<<endl;
		cout << "Problem Opening Initialization File to get sql_queue"<< endl;
		exit(0);
	}
	
	GetPrivateProfileString(appName,"monitor_queue","",monitor_queue,sizeof(monitor_queue),appAddr);
	if (strcmp(monitor_queue,"") == 0)
	{
		cout<< monitor_queue<<endl;
		cout << "Problem Opening Initialization File to get monitor_queue"<< endl;
		exit(0);
	}

	GetPrivateProfileString(appName,"queue_mgr","",queue_mgr,sizeof(queue_mgr),appAddr);
	if (strcmp(queue_mgr,"") == 0)
	{
		cout<< queue_mgr<<endl;
		cout << "Problem Opening Initialization File to get queue_mgr"<< endl;
		exit(0);
	}
	GetPrivateProfileString(appName,"directorio_archivo","",directorio_archivo,sizeof(directorio_archivo),appAddr);
	if (strcmp(directorio_archivo,"") == 0)
	{
		cout<< directorio_archivo<<endl;
		cout << "Problem Opening Initialization File to get directorio_archivo"<< endl;
		exit(0);
	}



	debugSB = GetPrivateProfileInt(appName,"debugSB",0,appAddr);
	debugtrace = GetPrivateProfileInt(appName,"debugtrace",0,appAddr);
	time_out_0800 = GetPrivateProfileInt(appName,"time_out_0800",0,appAddr);

	RWCString msgToServer	= "Client -->> Server - Conectados al Puerto TCP -->> ";
	RWCString msgFromServer	= "Client <<-- Server - ";


	RWCString localhost;
	RWInetHost thisHost = RWInetHost::me();
    localhost = thisHost.name();

	cout << "Valor de localhost >" << localhost << endl;
	strcpy(IPAddr , localhost);
	
	cout << "Opening IP Address: " << SB1ADD << endl;
	cout << "Opening Port Number: " << port << endl;
	char buffer3[20] = {""};
	long  h = port; // Response Code
	itoa( h, buffer3, 10 );
	SetConsoleTitle(APPName);
	
	//** Listening the Socket for Handshaking **//
	//RWSocketListener listener( RWInetAddr(port, IPAddr) );  
	 
	// INFINITE LOOP FOR //
	// SERVER CONNECTION //
	int lastLineNumber_ = 0;


	counter = 1;			
	

	
	RWCString test ;

					
	char buffer[512] = {""};
	int server_flag = 1; //Variable para hacer la conexion permanente y controlar
	client_flag = 1;					//la deconexion
	while(server_flag == 1)
	{	
		try
		{
		
			Sleep(5000);
			RWTime first_time;	  
			RWSocketPortal p;

			
			p.connect(RWInetAddr(port, SB1ADD));    
			try
			{
				

				cout << msgToServer << port << " y al HOST " <<  SB1ADD <<  endl;
				RWCString reply,packet,	incoming_0810, incoming_0210 , incoming_0800 ;
				RWCString stringS = "";
				RWCString type_msg_verification_210 = "";
				RWCString type_msg_verification_200 = "";
				RWCString type_msg_verification_810 = "";
				RWCString type_msg_verification_800 = "";
				RWCString converted_iso				 = "";
				RWCString outgoing_tcp_0200_tcp_header = "";
				RWCString return_message = "";
				client_flag = 1;
				int counter = 0;
			
					
				char msg_type[5] = {""};
			/*	
				GetPrivateProfileString(appName,"input_msg","",input_msg,sizeof(input_msg),appAddr);
				if (strcmp(input_msg,"") == 0)
				{
					cout << "Problem Opening Initialization File to get APPName"<< endl;
					exit(0);
				}
					
				GetPrivateProfileString(appName,"sent_0800","",sent_0800,sizeof(sent_0800),appAddr);
				if (strcmp(sent_0800,"") == 0)
				{
					cout << "Problem Opening Initialization File to get sent_0800"<< endl;
					exit(0);
				}
		*/
				while(client_flag == 1)
				{
				
					/*	
					GetPrivateProfileString(appName,"input_msg","",input_msg,sizeof(input_msg),appAddr);
					if (strcmp(input_msg,"") == 0)
					{
						cout << "Problem Opening Initialization File to get APPName"<< endl;
						exit(0);
					}
					*/
					if(debugSB == 1)
					{
			
					}
						RWCString test_canal = "";
						Iso8583Msg testiso;
						//RWThreadFunction production;

					
						RWThread t1, t2;

						//RWThreadFunction myThread1 = rwMakeThreadFunction( Get_Msg_From_Sock,p, send_queue,queue_mgr);
						//RWThreadFunction myThread2 = rwMakeThreadFunction( Send_Msg_To_Sock,p, send_queue,queue_mgr);

						t1 = rwMakeThreadFunction( Get_Msg_From_Sock,p, send_queue,queue_mgr);
						t2 = rwMakeThreadFunction( Send_Msg_To_Sock,p, send_queue,queue_mgr);
						
						// Start the threads
						//myThread1.start();
						// myThread2.start();
					/*	
						t1.start();
						t2.start();
					
					    // Wait for the threads to finish
						
						//myThread1.join();
						t1.join();
						client_flag = 0;
						t2.terminate();
						
						cout << "Salio del thread #1> " << endl;
							break;
						t2.join();
						t1.terminate();
							break;
				
						cout << "Salio del thread #2> " << endl;
						strcpy(input_msg,"");
					
						test = "";

				   */

						t1.start();
						t2.start();
					
					
						t1.join();
						cout << "Se recibio desconexion >>>>>>> #1 " << endl;
						//closesocket(1);
						break;
						t2.terminate();
						break;
						t2.join();
						cout << "Se recibio desconexion >>>>>>> #2 " << endl;
						t1.terminate();
						break;
						client_flag = 0;
					
				
						if(client_flag == 0)
						{
							break;
						}

						strcpy(input_msg,"");
					
						test = "";

		
				}//end while cliente


				RWTime second_time;
				// Log File Creation and Time Response Calculation
				int sprocess = second_time.seconds() - first_time.seconds();
				cout << "Valor del tiempo -> " << sprocess << endl;
		
			}
			catch (const RWSockErr& err)
			{
				if ( err.errorNumber() == RWNETECONNABORTED || err.errorNumber() 
					== RWNETECONNRESET )
				{
					cout << "Disonnected from the Host catch> "  << endl;
				} 
				else 
				{
					cout << "Dentro del if del throw > " << endl;	
					throw;
				}
			}
   
		}
		catch(RWxmsg& x)
		{
			cout << "Exception: " << x.why() << endl;

			MQUtility take_time_and_STAN;
			if(debugtrace == 1)
			{
	
				take_time_and_STAN.SendMessageToQueueWithTimeout(" *****<<<< The system will try to connect in 45 seconds >>>>***** ",monitor_queue,queue_mgr);

			}
	
			cout << " *****<<<< The system will try to connect in 45 seconds >>>>***** " << endl;
			Sleep(15000);
		
		}
	
	}//while server flag
	
 return 1;
}	
	
	
	
