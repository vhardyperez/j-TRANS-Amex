// client_handler.cpp,v 1.13 2000/03/19 20:09:22 jcej Exp

/* In client_handler.h I alluded to the fact that we'll mess around
   with a Client_Acceptor pointer.  To do so, we need the
   Client_Acceptor object declaration.

   We know that including client_handler.h is redundant because
   client_acceptor.h includes it.  Still, the sentry prevents
   double-inclusion from causing problems and it's sometimes good to
   be explicit about what we're using.

   On the other hand, we don't directly include any ACE header files
   here.  */
#include "client_acceptor.h"
#include "client_handler.h"
#include "Iso8583Msg.h"
#include "IsoBitMap.h"
#include "IsoUtilityVar.h"
#include "MQUtility.h"
#include "FDumpHex.h"
#include "SqlUtil.h"
#include "VerificarParametros.h"
#include <SQLAPI.h> // main SQLAPI++ header
#include <odbcAPI.h>
int host_tandem1 = 0;
int host_tandem2 = 1;
int counter_fail = 0;

int the_first = 0;

int count = 0;
int debugSB = 0;
int procesar_bines = 0;

char send_queue[20]	     = {""};
char send_queue_eps[20]   = {""};
char send_queue_amex[20]  = {""};
char recv_queue[20]	     = {""};
char sql_queue[20]	     = {""};
char queue_mgr[20]	     = {""};
char header[20]		     = {""};
char application[20]      = {""};
char send_queue_saf[20]   = {""};
char user_from_ini[30]				= {""};
char pass_from_ini[30]				= {""};
char db_from_ini[30]				= {""};
char btrans_sql_type[30]			= {""};

RWCString bin_procesar;

RWTValDlist<RWCString> list_bin_privadas;

RWTValDlist<RWCString> list_bin_debito;




/* Our constructor doesn't do anything.  That's generally a good idea.
   Unless you want to start throwing exceptions, there isn't a really
   good way to indicate that a constructor has failed.  If I had my
   way, I'd have a boolean return code from it that would cause new to
   return 0 if I failed.  Oh well...  */
Client_Handler::Client_Handler (void)
{
}

/* Our destructor doesn't do anything either.  That is also by design.
   Remember, we really want folks to use destroy() to get rid of us.
   If that's so, then there's nothing left to do when the destructor
   gets invoked.  */
Client_Handler::~Client_Handler (void)
{
}

/* The much talked about destroy() method!  The reason I keep going on
   about this is because it's just a Bad Idea (TM) to do real work
   inside of a destructor.  Although this method is void, it really
   should return int so that it can tell the caller there was a
   problem.  Even as void you could at least throw an exception which
   you would never want to do in a destructor.  */
void
Client_Handler::destroy (void)
{
  /* Tell the reactor to forget all about us.  Notice that we use the
    same args here that we use in the open() method to register
    ourselves.  In addition, we use the DONT_CALL flag to prevent
    handle_close() being called.  Since we likely got here due to
    handle_close(), that could cause a bit of nasty recursion!  */
  this->reactor ()->remove_handler (this,
                                    ACE_Event_Handler::READ_MASK
                                    | ACE_Event_Handler::DONT_CALL);

  /* This is how we're able to tell folks not to use delete.  By
    deleting our own instance, we take care of memory leaks after
    ensuring that the object is shut down correctly.  */
  delete this;
}

/* As mentioned before, the open() method is called by the
   Client_Acceptor when a new client connection has been accepted.
   The Client_Acceptor instance pointer is cast to a void* and given
   to us here.  We'll use that to avoid some global data...  */
int
Client_Handler::open (void *void_acceptor)
{
 


	if(the_first == 0)
	{
		
			const static char* appName1 = "BSOURCES_TO_B24";
		const static char* appAddr1 = "\\BtransGeneric\\INI\\ATH\\SERVER_BSOURCES_ATH_DEBITO.INI";
		


		GetPrivateProfileString(appName1,"send_queue","",send_queue,sizeof(send_queue),appAddr1);
		if (strcmp(send_queue,"") == 0)
		{
			cout<< send_queue<<endl;
			cout << "Problem Opening Initialization File to get send_queue"<< endl;
		}

		GetPrivateProfileString(appName1,"send_queue_eps","",send_queue_eps,sizeof(send_queue_eps),appAddr1);
		if (strcmp(send_queue_eps,"") == 0)
		{
			cout<< send_queue_eps<<endl;
			cout << "Problem Opening Initialization File to get send_queue_eps"<< endl;
		}

		GetPrivateProfileString(appName1,"send_queue_amex","",send_queue_amex,sizeof(send_queue_amex),appAddr1);
		if (strcmp(send_queue_amex,"") == 0)
		{
			cout<< send_queue_amex<<endl;
			cout << "Problem Opening Initialization File to get send_queue_amex"<< endl;
		}

		
		GetPrivateProfileString(appName1,"recv_queue","",recv_queue,sizeof(recv_queue),appAddr1);
		if (strcmp(recv_queue,"") == 0)
		{
			cout<< recv_queue<<endl;
			cout << "Problem Opening Initialization File to get recv_queue"<< endl;
		}

		GetPrivateProfileString(appName1,"sql_queue","",sql_queue,sizeof(sql_queue),appAddr1);
		if (strcmp(sql_queue,"") == 0)
		{
			cout<< sql_queue<<endl;
			cout << "Problem Opening Initialization File to get sql_queue"<< endl;
		}

		GetPrivateProfileString(appName1,"header","",header,sizeof(header),appAddr1);
		if (strcmp(header,"") == 0)
		{
			cout<< header<<endl;
			cout << "Problem Opening Initialization File to get header"<< endl;
		}
		
		GetPrivateProfileString(appName1,"application","",application,sizeof(application),appAddr1);
		if (strcmp(application,"") == 0)
		{
			cout<< application<<endl;
			cout << "Problem Opening Initialization File to get application"<< endl;
		}

		GetPrivateProfileString(appName1,"queue_mgr","",queue_mgr,sizeof(queue_mgr),appAddr1);
		if (strcmp(queue_mgr,"") == 0)
		{
			cout<< queue_mgr<<endl;
			cout << "Problem Opening Initialization File to get queue_mgr"<< endl;
		}
		GetPrivateProfileString(appName1,"send_queue_saf","",send_queue_saf,sizeof(send_queue_saf),appAddr1);
		if (strcmp(send_queue_saf,"") == 0)
		{
			cout<< send_queue_saf<<endl;
			cout << "Problem Opening Initialization File to get send_queue_saf"<< endl;
		}

		debugSB = GetPrivateProfileInt(appName1,"debugSB",0,appAddr1);
		procesar_bines = GetPrivateProfileInt(appName1,"procesar_bines",0,appAddr1);


		const static char* appName = "SYSTEM_DEBITO_SD";
		const static char* appAddr = "\\BtransGeneric\\INI\\SYSTEM_WEB.INI";
	

	
		GetPrivateProfileString(appName,"user_from_ini","",user_from_ini,sizeof(user_from_ini),appAddr);
		if (strcmp(user_from_ini,"") == 0)
		{
			cout<< user_from_ini<<endl;
			cout << "Problem Opening Initialization File to get user_from_ini"<< endl;
			exit(0);
		}
		GetPrivateProfileString(appName,"pass_from_ini","",pass_from_ini,sizeof(pass_from_ini),appAddr);
	
		GetPrivateProfileString(appName,"db_from_ini","",db_from_ini,sizeof(db_from_ini),appAddr);
		if (strcmp(db_from_ini,"") == 0)
		{
			cout<< db_from_ini<<endl;
			cout << "Problem Opening Initialization File to get db_from_ini"<< endl;
			exit(0);
		}

		GetPrivateProfileString(appName,"btrans_sql_type","",btrans_sql_type,sizeof(btrans_sql_type),appAddr);
		if (strcmp(btrans_sql_type,"") == 0)
		{
			cout<< btrans_sql_type<<endl;
			cout << "Problem Opening Initialization File to get btrans_sql_type"<< endl;
			exit(0);
		}
	
      if (procesar_bines ==1 )
	  {
			SAConnection con; // create connection object

			if (btrans_sql_type == "SA_ODBC_Client")
				con.setClient( SAClient_t(SA_ODBC_Client) );
			 else
				con.setClient( SAClient_t(SA_SQLServer_Client) );
			

			SACommand cmd(&con);//,"SELECT * from  viewdetail_merchant where card_acceptor_terminal_id = :card_acceptor_terminal_id");    // command object

		
			try
			{

				
   
				con.Connect(
				db_from_ini,     // database name
				user_from_ini,   // user name
				pass_from_ini,   // password
				SA_ODBC_Client);

				cmd.setConnection(&con);
				//cout << name_user;
				cmd.setCommandText("SELECT bin from bin_debito(nolock)");    // command object
				//cmd.Param("username").setAsString() = name_user;
				list_bin_debito.clear();
				char bin_from_db_locales[20] = {""};
				cmd.Execute();
				while(cmd.FetchNext())
				{

					strcpy ( bin_from_db_locales, cmd.Field("bin").asString());
					list_bin_debito.insert(bin_from_db_locales);
				}


			
				con.Disconnect();

			

			}
			catch(SAException &x)
			{
				// SAConnection::Rollback()
				// can also throw an exception
				// (if a network error for example),
				// we will be ready
				try
				{
				   // on error rollback changes
					 con.Rollback();
				}
				catch(SAException &)
				{
				}
					// print error message
					printf("%s\n", (const char*)x.ErrText());
			}
	

	  }




	


		the_first = 1;
	}


 /* We need this to store the address of the client that we are now
     connected to.  We'll use it later to display a debug message.  */
  ACE_INET_Addr addr;

  /* Our ACE_Svc_Handler baseclass gives us the peer() method as a way
    to access our underlying ACE_SOCK_Stream.  On that object, we can
    invoke the get_remote_addr() method to get get an ACE_INET_Addr
    having our client's address information. As with most ACE methods,
    we'll get back (and return) a -1 if there was any kind of error.
    Once we have the ACE_INET_Addr, we can query it to find out the
    client's host name, TCP/IP address, TCP/IP port value and so
    forth.  One word of warning: the get_host_name() method of
    ACE_INET_Addr may return you an empty string if your name server
    can't resolve it.  On the other hand, get_host_addr() will always
    give you the dotted-decimal string representing the TCP/IP
    address.  */
  if (this->peer ().get_remote_addr (addr) == -1)

    return -1;

  /* Convert the void* to a Client_Acceptor*.  You should probably use
    those fancy ACE_*_cast macros but I can never remember how/when to
    do so.  Since you can cast just about anything around a void*
    without compiler warnings be very sure of what you're doing when
    you do this kind of thing.  That's where the new-style cast
    operators can save you.  */
  Client_Acceptor *acceptor = (Client_Acceptor *) void_acceptor;

  /* Our Client_Acceptor is constructed with a concurrency strategy.
    Here, we go back to it to find out what that strategy was.  If
    thread-per-connection was selected then we simply activate a
    thread for ourselves and exit.  Our svc() method will then begin
    executing in that thread.

    If we are told to use the single-threaded strategy, there is no
    difference between this and the Tutorial 5 implementation.

    Note that if we're in thread-per-connection mode, open() is exited
    at this point.  Furthermore, thread-per-connection mode does not
    use the reactor which means that handle_input() and it's fellows
    are not invoked.  */
  if (acceptor->thread_per_connection ())
    return this->activate (THR_DETACHED);

  // ************************************************************************
  // From here on, we're doing the traditional reactor thing.  If
  // you're operating in thread-per-connection mode, this code does
  // not apply.
  // ************************************************************************

  /* Our reactor reference will be set when we register ourselves but
    I decided to go ahead and set it here.  No good reason really...  */
  this->reactor (acceptor->reactor ());

  /* If we managed to get the client's address then we're connected to
    a real and valid client.  I suppose that in some cases, the client
    may connect and disconnect so quickly that it is invalid by the
    time we get here. In any case, the test above should always be
    done to ensure that the connection is worth keeping.

    Now, regiser ourselves with a reactor and tell that reactor that
    we want to be notified when there is something to read.  Remember,
    we took our reactor value from the acceptor which created us in
    the first place.  Since we're exploring a single-threaded
    implementation, this is the correct thing to do.  */
  if (this->reactor ()->register_handler (this,
                                          ACE_Event_Handler::READ_MASK) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "(%P|%t) can't register with reactor\n"),
                      -1);

  /* Here, we use the ACE_INET_Addr object to print a message with the
    name of the client we're connected to.  Again, it is possible that
    you'll get an empty string for the host name if your DNS isn't
    configured correctly or if there is some other reason that a
    TCP/IP addreess cannot be converted into a host name.  */
  ACE_DEBUG ((LM_DEBUG,
              "(%P|%t) connected with %s\n", addr.get_host_name ()));

  /* Always return zero on success.  */
  return 0;
}

/* As mentioned in the header, the typical way to close an object in a
   threaded context is to invoke it's close() method.  Since we
   already have a handle_close() method built to cleanup after us,
   we'll just forward the request on to that object.  */
int
Client_Handler::close(u_long flags)
{
  ACE_UNUSED_ARG (flags);

  /* We use the destroy() method to clean up after ourselves.  That
    will take care of removing us from the reactor and then freeing
    our memory.  */
  this->destroy ();

  /* Don't forward the close() to the baseclass!  handle_close() above
    has already taken care of delete'ing.  Forwarding close() would
    cause that to happen again and things would get really ugly at
    that point!  */
  return 0;
}

/* In the open() method, we registered with the reactor and requested
   to be notified when there is data to be read.  When the reactor
   sees that activity it will invoke this handle_input() method on us.
   As I mentioned, the _handle parameter isn't useful to us but it
   narrows the list of methods the reactor has to worry about and the
   list of possible virtual functions we would have to override.

   Again, this is not used if we're in thread-per-connection mode.  */
int
Client_Handler::handle_input (ACE_HANDLE handle)
{
  /* Some compilers don't like it when you fail to use a parameter.
    This macro will keep 'em quiet for you.  */
  ACE_UNUSED_ARG (handle);

  /* Now, we create and initialize a buffer for receiving the data.
    Since this is just a simple test app, we'll use a small buffer
    size.  */
  char buf[4096];

   cout << "Dentro de Handle Input > " << endl;

  /* Invoke the process() method with a pointer to our data area.
    We'll let that method worry about interfacing with the data.  You
    might choose to go ahead and read the data and then pass the
    result to process().  However, application logic may require that
    you read a few bytes to determine what else to read...  It's best
    if we push that all into the application-logic level.  */
  return this->process (buf, sizeof (buf));
}

/* If we return -1 out of handle_input() or if the reactor sees other
   problems with us then handle_close() will be called.  The reactor
   framework will take care of removing us (due to the -1), so we
   don't need to use the destroy() method.  Instead, we just delete
   ourselves directly.  */
int
Client_Handler::handle_close (ACE_HANDLE handle,
                              ACE_Reactor_Mask mask)
{
  ACE_UNUSED_ARG (handle);
  ACE_UNUSED_ARG (mask);

  this->destroy ();
  return 0;
}

/* The ACE_Svc_Handler<> is ultimately derived from ACE_Task<>.  If
   you want to create a multi-threaded application, these are your
   tools!  Simply override the svc() method in your derivative and
   arrange for your activate() method to be called.  The svc() method
   then executes in the new thread.

   Of course, this is only valid if we're in thread-per-connection
   mode.  If we're using the reactor model, then svc() never comes
   into play.  */
int
Client_Handler::svc(void)
{
  /* Like handle_input(), we create a buffer for loading the data.
    Doing so in handle_input() doesn't help any but there is a small
    performance increase by doing this here: the buffer is created
    once when the thread is created instead of for each invocation of
    process().  */
  char buf[4096];

  // Forever...
  while( 1 )
    {
      /* Invoke the process() method to read and process the data.
        This is exactly the way it is used by handle_input().  That's
        the reason I created process() in the first place: so that it
        can be used in either concurrency strategy.  Since process()
        has all of our application-level logic, it's nice that it
        doesn't have to change when we decide to go multi-threaded.

        Notice that since the recv() method call in process() blocks until
        there is data ready, this thread doesn't consume any CPU time until
        there is actually data sent from the client.  */
      if (this->process(buf, sizeof (buf)) == -1)
        return -1;
	 //cout << "Valor de sizeof (buf) > " << sizeof (buf) << endl;


    }

  return 0;
}

/* And, at last, we get to the application-logic level.  Out of
   everything we've done so far, this is the only thing that really
   has anything to do with what your application will do.  In this
   method we will read and process the client's data.  In a real
   appliation, you will probably have a bit more in main() to deal
   with command line options but after that point, all of the action
   takes place here.  */
int
Client_Handler::process (char *rdbuf,
                         int rdbuf_len)
{
  /* Using the buffer provided for us, we read the data from the
    client. If there is a read error (eg -- recv() returns -1) then
    it's a pretty good bet that the connection is gone.  Likewise, if
    we read zero bytes then something wrong has happened.  The reactor
    wouldn't have called us if there wasn't some kind of read activity
    but there wouldn't be activity if there were no bytes to read...

    On the other hand, if we got some data then we can display it in a
    debug message for everyone to see.  */
  ssize_t bytes_read;
  switch ( (bytes_read = this->peer ().recv (rdbuf, rdbuf_len)) )
  {
    case -1:
      ACE_ERROR_RETURN ((LM_ERROR,
                         "(%P|%t) %p bad read\n",
                         "client"),
                        -1);
    case 0:
      ACE_ERROR_RETURN ((LM_ERROR,
                         "(%P|%t) closing daemon (fd = %d)\n",
                         this->get_handle ()),
                        -1);
    default:
      rdbuf[bytes_read] = 0;
     
	  if(debugSB == 1)
		 ACE_DEBUG ((LM_DEBUG,
                  "(%P|%t) from client: %s",
                 rdbuf));


	char start_of_text = '\x02';
    char end_of_text	= '\x03';
	  
	int is_debit = 1;
	  
	RWCString valor_rw = rdbuf;

	if( (valor_rw(valor_rw.length()-2,1) == '\x0D') || (valor_rw(valor_rw.length()-2,1) == '\x0A') )
	{
		valor_rw = valor_rw(0,valor_rw.length()-2);
	
	}


		if( ( (valor_rw(1,4) == "0200") && (valor_rw(5,1) != ",")) || ((valor_rw(1,4) == "0220") && (valor_rw(5,1) != ",")) 
		|| ((valor_rw(1,4) == "0221") && (valor_rw(5,1) != ","))
		|| ( (valor_rw(1,4) == "0800") && (valor_rw(5,1) != ",")) || ((valor_rw(1,4) == "0420") && (valor_rw(5,1) != ","))
		|| ((valor_rw(1,4) == "0421") && (valor_rw(5,1) != ",")) || ((valor_rw(1,4) == "0500") && (valor_rw(5,1) != ",")) 
		|| (valor_rw(0,1) != start_of_text) || (valor_rw(valor_rw.length()-1,1) != end_of_text) )  
	{

					


		strcpy(rdbuf, RWCString(start_of_text)+"****FORMAT ERROR****"+RWCString(end_of_text));

		int test_len = 0;
		test_len = strlen(rdbuf);
		if (this->peer().send_n (rdbuf,
		test_len )== -1)
		ACE_ERROR_RETURN ((LM_ERROR,
		"%p\n",
		"send"),
		 -1);


	}

	else
	{

	RWCString incoming_for_return = "";
	
	int counter_token_begin = 0;
	RWCTokenizer next_begin(valor_rw);
	RWCString token3;
	//This evaluted if thera are more than one Message//
	while(!(token3=next_begin(	RWCString(start_of_text))).isNull())
	{	
		counter_token_begin++;
	}

	//cout << "valor de counter_token_begin " << counter_token_begin << endl;
	if(counter_token_begin > 1)
	{


		ACE_LOG_MSG->open
		(0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_AVS"));
		 ACE_DEBUG ((LM_DEBUG,
		 "(%P|%t|%T) ****SEVERAL MESSAGE FROM SERVCER AVS****%s\n",
					 valor_rw));
			//Envia los mensajes al standar error
		ACE_LOG_MSG->open (0);
			
		int counter_token_varios = 0;
		RWCTokenizer next_varios(valor_rw);
		RWCString token_varios;
		RWCString incoming_varios;
		RWCString valor_uno;
		RWCString valor_dos;
				
		//This extract the BIN from the Message//
		while(!(token_varios=next_varios(RWCString(start_of_text))).isNull())
		{	

	
			///////////////////////////////////////////////////////////////////////////////
		
	
			incoming_varios=token_varios(0,token_varios.length()-1);
			cout << endl;
			cout << "Valor de incoming_varios > " << incoming_varios << endl;
			cout << endl;
	
			if(incoming_varios(0,1) == start_of_text)
			{
				incoming_for_return = incoming_varios;
				incoming_varios=incoming_varios(1,incoming_varios.length()-1);;
				valor_rw = incoming_varios;
			}
			else
				valor_rw = incoming_varios;
	
			if (( valor_rw(0,4) == "0200"))
			{

				MQUtility set_tcp_header;
				
				IsoUtilityVar retorno_210_error;

				int parametro_de_retorno = 0;
				int retorno_valida = 1;
		
				VerificarParametros test_parametros;
				RWCString retorno_0210;
	
				int counter_token = 0;
				RWCString field_35_01;
				RWCString field_35_02;
				RWCString expiration_date_rw;
				RWCString iso8583_output_maximo;
			
				RWCString valor_de_track_and_acc = set_tcp_header.getTrack2FromGenericVarAndAcc(valor_rw);
				RWCTokenizer next1(valor_de_track_and_acc);
				RWCString token1;
					
				/*This extract the BIN from the Message*/
				while(!(token1=next1(",")).isNull())
				{	
					if (counter_token == 0)
					{
						field_35_01 = token1; 
					}			
					if (counter_token == 1)
					{
						field_35_02 = token1; 
					}			
					counter_token++;
				}
		
	 
				RWCString bin_procesar = field_35_01(0,6) ;

				int bin_procesar_int = atoi(bin_procesar);
		
				RWCString incoming_bin = bin_procesar;

				

			
				strcpy(send_queue, send_queue_eps);
				is_debit = 1;
	
	
			retorno_valida = set_tcp_header.VerifyGenericVar(valor_rw,application,header,0);


			if(retorno_valida == 1)
			{
				if( is_debit == 1)
				{
					//parametro_de_retorno = test_parametros.ResultOfParametrosATHDebito(set_tcp_header.setGenericFromGenericVar(valor_rw));
					parametro_de_retorno = - 1;
				}
				if( is_debit == 0)
				{
					//parametro_de_retorno = test_parametros.ResultOfParametrosATHCredito(set_tcp_header.setGenericFromGenericVar(valor_rw));
					parametro_de_retorno = - 1;
					is_debit = 1;
				}

				 if (procesar_bines ==1 )
				 {
					if( (list_bin_debito.contains(incoming_bin)))
					{	
										
						parametro_de_retorno = 6;
										
					}
				 }

				switch (parametro_de_retorno)
				{

		
					case  0:
			            retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"30,");
					  ACE_LOG_MSG->open
					  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
					  ACE_DEBUG ((LM_DEBUG,
						 "(%P|%t|%T) ****Format Error****%s\n",
							 valor_rw));
						//Envia los mensajes al standar error
					  ACE_LOG_MSG->open (0);
		
						break;
			
					case  1:
				      //iso8583_output = ConvertSendQueue(incoming_isogeneric);
			            retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"58,");
					  ACE_LOG_MSG->open
					  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
					  ACE_DEBUG ((LM_DEBUG,
						 "(%P|%t|%T) ****Invalid Terminal****%s\n",
							 valor_rw));
						//Envia los mensajes al standar error
					  ACE_LOG_MSG->open (0);
					  break;
				
					case  2:
					   cout << endl;
				      cout << "<*********************Amounts limits********************>" << endl;
					  cout << endl;
					  
					  ACE_LOG_MSG->open
					  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
					  ACE_DEBUG ((LM_DEBUG,
						 "(%P|%t|%T) ****Invalid Amounts****\n",
							 " "));
						//Envia los mensajes al standar error
					  ACE_LOG_MSG->open (0);
			            retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"61,");
						//cout << "Dentro de #2 > " << endl;
						break;
				
					case  3:
					 
					  cout << endl;
				      cout << "<**********transaction reach it their limits**********>" << endl;
					  cout << endl;

	  
					  ACE_LOG_MSG->open
					  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
					  ACE_DEBUG ((LM_DEBUG,
						 "(%P|%t|%T) ****transaction reach it their limits****\n",
							 " "));
						//Envia los mensajes al standar error
					  ACE_LOG_MSG->open (0);
					  
					  retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"57,");
						//cout << "Dentro de #3 > " << endl;
						break;
					case  5:
					   retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"91,");
					   //cout << "Dentro de #5 > " << endl;
						break;

					case  6:

						  cout << endl;
						  cout << "<**********Bin in the table of rejected**********>" << endl;
						  cout << endl;


						   ACE_LOG_MSG->open
						  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
						  ACE_DEBUG ((LM_DEBUG,
							 "(%P|%t|%T) **********Bin is on the table to be rejected**********\n",
								 " "));
							//Envia los mensajes al standar error
						  ACE_LOG_MSG->open (0);
					  		

						
						 set_tcp_header.SendMessageToQueueSql("00"+retorno_0210,sql_queue,queue_mgr);

						
						 
					 
						break;
			

					default:
						   //iso8583_output = ConvertSendQueue(incoming_isogeneric);
						//cout << "Dentro default > " << endl;
						break;
	      
				}



				if(parametro_de_retorno == -1)
				{


			
					retorno_0210 = set_tcp_header.setMapIsoPosTermFromGeneric(valor_rw,application,header, 1);
			
	
					retorno_0210=set_tcp_header.SendMessageToQueueNewATHDebito(set_tcp_header.SetTcpHeader(retorno_0210),send_queue,recv_queue,sql_queue,queue_mgr, debugSB);

					

		
					cout << "Valor de retorno_0210 > " << retorno_0210 << endl;
					cout << "Valor de retorno_0210.length() > " << retorno_0210.length() << endl;
				
					if (retorno_0210.length() == 0)
					{
					
				
						cout << "Dentro de time-out " << endl;
					}

					else//	if ( (retorno_0210.length() > 0) && (retorno_0210(0,4) == "0210"))
					{
						 retorno_0210+="\n";
				
						cout << "Outgoing 0210 to Client > " << retorno_0210 << endl; 
						strcpy(rdbuf, retorno_0210);

						int test_len = 0;
						test_len = strlen(rdbuf);
						if (this->peer().send_n (rdbuf,
							test_len )== -1)
							ACE_ERROR_RETURN ((LM_ERROR,
					       "%p\n",
						   "send"),
							 -1);
					}
			
				}
				else
				{

					retorno_0210+="\n";
						cout << endl;
		
						cout << "Outgoing 0210 to Client > " << retorno_0210 << endl; 
						strcpy(rdbuf, RWCString(start_of_text)+retorno_0210+RWCString(end_of_text));

						int test_len = 0;
						test_len = strlen(rdbuf);
						if (this->peer().send_n (rdbuf,
							test_len )== -1)
							ACE_ERROR_RETURN ((LM_ERROR,
							   "%p\n",
							   "send"),
								 -1);
				}

			}
			else
			{
			
			
			
				ACE_LOG_MSG->open
				(0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
				 ACE_DEBUG ((LM_DEBUG,
				"(%P|%t|%T) ****Format error****%s\n",
				 valor_rw));
				ACE_LOG_MSG->open (0);

				  
			
				RWCString retorno_0210;
				retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"30,");
				cout << endl;
				cout << "Outgoing 0210 to Client > " << retorno_0210 << endl; 
				strcpy(rdbuf, retorno_0210);

				int test_len = 0;
				test_len = strlen(rdbuf);
				if (this->peer().send_n (rdbuf,
				   test_len )== -1)
					ACE_ERROR_RETURN ((LM_ERROR,
					       "%p\n",
						   "send"),
							 -1);
			}

		
			counter_token_varios++;
		
		}//End of while
		

	}


	}
	else //Un solo menasaje
	{

    
		if(valor_rw(0,1) == start_of_text)
		{
			incoming_for_return = valor_rw;
			valor_rw=valor_rw(1,valor_rw.length()-2);;
		}
		
		MQUtility verifacion_mensaje;
		RWCString valor_of_125;
		
		
		int retorno_true = 0;

		if ( (valor_rw(0,4) == "0200") || ( valor_rw(0,4) == "0420") || ( valor_rw(0,4) == "0421"))
			retorno_true = verifacion_mensaje.VerifyGenericVar(valor_rw,"base24","ISO025000050",0);

		if ( retorno_true == 1)
		{
			valor_of_125 = verifacion_mensaje.GetFieldFromBtransFormat(valor_rw,125);

			if (valor_of_125.length() == 0)
				retorno_true = 0;

		}

		if ( (valor_rw(0,4) == "0500") || (valor_rw(0,4) == "0800"))
			retorno_true = 1;


	   if (retorno_true == 1)
	   {
		if (( valor_rw(0,4) == "0200"))
		{
			
		

			MQUtility set_tcp_header;
					
			IsoUtilityVar retorno_210_error;

			int parametro_de_retorno = 0;
			int retorno_valida = 1;
			
			VerificarParametros test_parametros;
			RWCString retorno_0210;



		
			RWTime b;
			cout << endl;
			cout << "Incoming 0200 " << "Time: " << b << " " << " *****<<<< Mensaje 0200 recibido >>>***** " << endl;

	

			int counter_token = 0;
			RWCString field_35_01;
			RWCString field_35_02;
			RWCString expiration_date_rw;
			RWCString iso8583_output_maximo;
			RWCString valor_de_track_and_acc = set_tcp_header.getTrack2FromGenericVarAndAcc(valor_rw);
			RWCTokenizer next1(valor_de_track_and_acc);
			RWCString token1;
				
			
			/*This extract the BIN from the Message*/
			while(!(token1=next1(",")).isNull())
			{	
				if (counter_token == 0)
				{
					field_35_01 = token1; 
				}			
				if (counter_token == 1)
				{
					field_35_02 = token1; 
				}			
				counter_token++;
			}

			//cout << endl;
			//cout << endl;
			RWCString bin_procesar = field_35_01(0,6) ;

			int bin_procesar_int = atoi(bin_procesar);
		
			RWCString incoming_bin = bin_procesar;

			
			if( host_tandem2 == 1)
			{
				strcpy(send_queue, send_queue_eps);
			}
			if(host_tandem1 == 1)
			{
				strcpy(send_queue_amex, send_queue_amex);
			
			}
			is_debit = 1;

			retorno_valida = set_tcp_header.VerifyGenericVar(valor_rw,application,header,0);

			if(retorno_valida == 1)
			{
				if( is_debit == 1)
				{
					parametro_de_retorno = - 1;
				}
				if( is_debit == 0)
				{
					parametro_de_retorno = - 1;
					is_debit = 1;
				}

				if (procesar_bines ==1 )
				{		
					if( (list_bin_debito.contains(incoming_bin)))
					{	
						
						parametro_de_retorno = 6;
										
					}
				}

			
				switch (parametro_de_retorno)
				{

			
					case  0:
							retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"30,");
						  ACE_LOG_MSG->open
						  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
						  ACE_DEBUG ((LM_DEBUG,
							 "(%P|%t|%T) ****Format Error****%s\n",
								 valor_rw));
							//Envia los mensajes al standar error
						  ACE_LOG_MSG->open (0);
			
							break;
				
					case  1:
						  //iso8583_output = ConvertSendQueue(incoming_isogeneric);
							retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"58,");
						  ACE_LOG_MSG->open
						  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
						  ACE_DEBUG ((LM_DEBUG,
							 "(%P|%t|%T) ****Invalid Terminal****%s\n",
								 valor_rw));
							//Envia los mensajes al standar error
						  ACE_LOG_MSG->open (0);
						  break;
					
					case  2:
						   cout << endl;
						  cout << "<*********************Amounts limits********************>" << endl;
						  cout << endl;
						  
						  ACE_LOG_MSG->open
						  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
						  ACE_DEBUG ((LM_DEBUG,
							 "(%P|%t|%T) ****Invalid Amounts****\n",
								 " "));
							//Envia los mensajes al standar error
						  ACE_LOG_MSG->open (0);
							retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"61,");
							//cout << "Dentro de #2 > " << endl;
							break;
					
					case  3:
						 
						  cout << endl;
						  cout << "<**********transaction reach it their limits**********>" << endl;
						  cout << endl;

		  
						  ACE_LOG_MSG->open
						  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
						  ACE_DEBUG ((LM_DEBUG,
							 "(%P|%t|%T) ****transaction reach it their limits****\n",
								 " "));
							//Envia los mensajes al standar error
						  ACE_LOG_MSG->open (0);
						  
						  retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"57,");
							//cout << "Dentro de #3 > " << endl;
							break;
					case  5:
						   retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"91,");
						   //cout << "Dentro de #5 > " << endl;
							break;

					case  6:

							cout << endl;
						  cout << "<**********Bin is on the table to be rejected**********>" << endl;
						  cout << endl;
					  		   ACE_LOG_MSG->open
						  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
						  ACE_DEBUG ((LM_DEBUG,
							 "(%P|%t|%T) **********Bin in the table of rejected**********\n",
								 " "));
							//Envia los mensajes al standar error
						  ACE_LOG_MSG->open (0);


						 


						
						 set_tcp_header.SendMessageToQueueSql("00"+retorno_0210,sql_queue,queue_mgr);

						
						 
						 
						 
						 
							break;


					default:
							   //iso8583_output = ConvertSendQueue(incoming_isogeneric);
							//cout << "Dentro default > " << endl;
							break;
			  
				}



				if(parametro_de_retorno == -1)
				{

					if(debugSB == 1)
						retorno_0210 = set_tcp_header.setMapIsoPosTermFromGeneric(valor_rw,application,header, debugSB);
					else
						retorno_0210 = set_tcp_header.setMapIsoPosTermFromGeneric(valor_rw,application,header, 0);
								


					if( host_tandem2 == 1)
					{

							retorno_0210=set_tcp_header.SendMessageToQueueNewATHDebito(set_tcp_header.SetTcpHeader(retorno_0210),send_queue,
								             recv_queue,sql_queue,queue_mgr,debugSB);

					}
					if(host_tandem1 == 1)

					{


						
						retorno_0210=set_tcp_header.SendMessageToQueueNewATHDebito(set_tcp_header.SetTcpHeader(retorno_0210),send_queue_amex,
							             recv_queue,sql_queue,queue_mgr,debugSB);
				
								
					}


				
					if (retorno_0210.length() == 0)
					{
						
						
						//cout << "Dentro de time out > " << endl;

						counter_fail+=1;
						if((counter_fail == 1) && (host_tandem2 == 1))
						{
							host_tandem1 = 1;
							host_tandem2 = 0;
							counter_fail = 0;
						}
						if((counter_fail == 1) && (host_tandem1 == 1))
						{
							host_tandem1 = 0;
							host_tandem2 = 1;
							counter_fail = 0;
						}

					}

					else //if ( (retorno_0210.length() > 0) && (retorno_0210(0,4) == "0210"))
					{
						retorno_0210+="\n";
		

						RWTime b;
						cout << endl;
						cout << "Sending  0210 " << "Time: " << b << " " << " *****<<<< Mensaje 0210 enviado  >>>***** " << endl;
 						cout << endl;

						
						strcpy(rdbuf, RWCString(start_of_text)+retorno_0210+RWCString(end_of_text));
							
						if(debugSB == 1)
			
							cout << "Outgoing 0210 to Client > " << rdbuf << endl; 

						int test_len = 0;
						test_len = strlen(rdbuf);
						if (this->peer().send_n (rdbuf,
							test_len )== -1)
							ACE_ERROR_RETURN ((LM_ERROR,
							   "%p\n",
							   "send"),
								 -1);
					}
						
					
				}
				else
				{

					retorno_0210+="\n";
						cout << endl;
		
						cout << "Outgoing 0210 to Client > " << retorno_0210 << endl; 
						strcpy(rdbuf, RWCString(start_of_text)+retorno_0210+RWCString(end_of_text));

						int test_len = 0;
						test_len = strlen(rdbuf);
						if (this->peer().send_n (rdbuf,
							test_len )== -1)
							ACE_ERROR_RETURN ((LM_ERROR,
							   "%p\n",
							   "send"),
								 -1);
				}

			}
			else
			{
				
				
				
				ACE_LOG_MSG->open
				(0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
				 ACE_DEBUG ((LM_DEBUG,
				 "(%P|%t|%T) ****Format error****%s\n",
					 valor_rw));
				 ACE_LOG_MSG->open (0);

					  
				
				RWCString retorno_0210;
				retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"30,");
				cout << endl;
				cout << "Outgoing 0210 to Client > " << retorno_0210 << endl; 
				strcpy(rdbuf, RWCString(start_of_text)+retorno_0210+RWCString(end_of_text));

				int test_len = 0;
				test_len = strlen(rdbuf);
				if (this->peer().send_n (rdbuf,
					 test_len )== -1)
					ACE_ERROR_RETURN ((LM_ERROR,
							   "%p\n",
							   "send"),
								 -1);
			}

		
		}
		else 
		if (( valor_rw(0,4) == "0420") || ( valor_rw(0,4) == "0421"))
		{
			
			
		
		

			MQUtility set_tcp_header;
					
			IsoUtilityVar retorno_210_error;

			int parametro_de_retorno = 0;
			int retorno_valida = 1;
			
			VerificarParametros test_parametros;
			RWCString retorno_0210;
		
			retorno_valida = set_tcp_header.VerifyGenericVar(valor_rw,application,header,0);

			if(retorno_valida == 1)
			{
			
				cout << "Antes de parametros" << endl;
				//parametro_de_retorno = test_parametros.ResultOfParametros0420ATHDebito(set_tcp_header.setGenericFromGenericVar(valor_rw));
				//cout << "Valor de parametro_de_retorno > " << parametro_de_retorno << endl;
				parametro_de_retorno	= -1 ;
				switch (parametro_de_retorno)
				{

			
					case  0:
							  
						  retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"30,");
						  ACE_LOG_MSG->open
						  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
						  ACE_DEBUG ((LM_DEBUG,
							 "(%P|%t|%T) ****Invalid Format****%s\n",
								 valor_rw));
							//Envia los mensajes al standar error
						  ACE_LOG_MSG->open (0);
						  break;
							break;
				
					case  1:
						  //iso8583_output = ConvertSendQueue(incoming_isogeneric);
							retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"58,");
						  ACE_LOG_MSG->open
						  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
						  ACE_DEBUG ((LM_DEBUG,
							 "(%P|%t|%T) ****Invalid Terminal****%s\n",
								 valor_rw));
							//Envia los mensajes al standar error
						  ACE_LOG_MSG->open (0);
						  break;
					
					case  2:
						   cout << endl;
						  cout << "<*********************Amounts limits********************>" << endl;
						  cout << endl;
						  
						  ACE_LOG_MSG->open
						  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
						  ACE_DEBUG ((LM_DEBUG,
							 "(%P|%t|%T) ****Invalid Amounts****\n",
								 " "));
							//Envia los mensajes al standar error
						  ACE_LOG_MSG->open (0);
							retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"61,");
							//cout << "Dentro de #2 > " << endl;
							break;
					
					case  3:
						 
						  cout << endl;
						  cout << "<**********transaction reach it their limits**********>" << endl;
						  cout << endl;

		  
						  ACE_LOG_MSG->open
						  (0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
						  ACE_DEBUG ((LM_DEBUG,
							 "(%P|%t|%T) ****transaction reach it their limits****\n",
								 " "));
							//Envia los mensajes al standar error
						  ACE_LOG_MSG->open (0);
						  
						  retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"57,");
							//cout << "Dentro de #3 > " << endl;
							break;
					case  5:
						   retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"91,");
						   //cout << "Dentro de #5 > " << endl;
							break;
				

					default:
							   //iso8583_output = ConvertSendQueue(incoming_isogeneric);
							//cout << "Dentro default > " << endl;
							break;
						


	   			}



				if(parametro_de_retorno == -1)
				{



					retorno_0210 = set_tcp_header.SetMapIso8583B24FromGenericVar0420(valor_rw,application,header, 1);
				
				


						if( (retorno_0210.length() > 50 ) && (retorno_0210(0,3) == "ISO"))
						{
							if( host_tandem2 == 1)
							{
								
								retorno_0210=set_tcp_header.SendMessageToQueueNewATHDebito(set_tcp_header.SetTcpHeader(retorno_0210),send_queue,
									             recv_queue,sql_queue,queue_mgr,debugSB);
				
							}
							if(host_tandem1 == 1)

							{

								
								retorno_0210=set_tcp_header.SendMessageToQueueNewATHDebito(set_tcp_header.SetTcpHeader(retorno_0210),send_queue_amex,
									recv_queue,sql_queue,queue_mgr,debugSB);
				
								
							}
					
							retorno_0210+="\n";
						}
						else
						{


							ACE_LOG_MSG->open
								(0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
							 ACE_DEBUG ((LM_DEBUG,
							"(%P|%t|%T) ****Format error****%s\n",
								valor_rw));
							ACE_LOG_MSG->open (0);

					  
				
							RWCString retorno_0210;
							strcpy(rdbuf, RWCString(start_of_text)+"*********FORMATO INCORRECTO*******"+RWCString(end_of_text));
							cout << "Outgoing 0210 to Client > " << rdbuf << endl; 
						
							int test_len = 0;
							test_len = strlen(rdbuf);
							if (this->peer().send_n (rdbuf,
							 test_len )== -1)
							ACE_ERROR_RETURN ((LM_ERROR,
							   "%p\n",
							   "send"),
								 -1);



						}
								
						retorno_0210+="\n";

						cout << endl;

						if( retorno_0210(0,4) == "0430")
						{

		
						cout << "Outgoing 0210 to Client > " << retorno_0210 << endl; 
						strcpy(rdbuf, RWCString(start_of_text)+retorno_0210+RWCString(end_of_text));

						int test_len = 0;
						test_len = strlen(rdbuf);
						if (this->peer().send_n (rdbuf,
						test_len )== -1)
						ACE_ERROR_RETURN ((LM_ERROR,
							   "%p\n",
							   "send"),
								 -1);
						}


				}
			
			}
			else
			{
				
				
				
				ACE_LOG_MSG->open
				(0, ACE_Log_Msg::SYSLOG, ACE_TEXT ("SERVER_BSOURCES_ATH_B24_VAR"));
				 ACE_DEBUG ((LM_DEBUG,
				 "(%P|%t|%T) ****Format error****%s\n",
					 valor_rw));
				 ACE_LOG_MSG->open (0);

					  
				
				RWCString retorno_0210;
				retorno_0210=retorno_210_error.getGeneric0210FromVar(valor_rw,"30,");
				cout << endl;
				cout << "Outgoing 0210 to Client > " << retorno_0210 << endl; 
				strcpy(rdbuf, RWCString(start_of_text)+retorno_0210+RWCString(end_of_text));

				int test_len = 0;
				test_len = strlen(rdbuf);
				if (this->peer().send_n (rdbuf,
					 test_len )== -1)
					ACE_ERROR_RETURN ((LM_ERROR,
							   "%p\n",
							   "send"),
								 -1);
			}

		
		}
		else
		if (( valor_rw(0,4) == "0800"))
		{

			
		
			
			
			MQUtility get_iso8583_b24_from_btrans_format;
			RWCString msg_0800 = "";
			RWCString msg_0810 = "";
			RWCString msg_0810_btrans_format = "";

			cout << endl;
				cout << "Valor de 0800 > " << valor_rw << endl;


			msg_0800 =	get_iso8583_b24_from_btrans_format.Set0800Iso8583B24FromBtransFormat(valor_rw,"base24","ISO025000056",1);
		

			if( host_tandem2 == 1)
			{
				get_iso8583_b24_from_btrans_format.SendMessageToQueueWithTimeout(msg_0800,send_queue_eps,
	             		queue_mgr);
			}
			if(host_tandem1 == 1)

			{

				get_iso8583_b24_from_btrans_format.SendMessageToQueueWithTimeout(msg_0800,send_queue_amex,
	             		queue_mgr);
		
								
			}



			cout << "Valor de msg_0800 > " << msg_0800 << endl;

			msg_0810 = get_iso8583_b24_from_btrans_format.Get_Msg_From_Queue(recv_queue,queue_mgr);

			cout << endl;
			cout << "Valor de msg_0810 " << msg_0810 << endl;

		
			if((msg_0810.length() > 0) && (msg_0810(0,3) == "ISO"))
				
			{
				msg_0810_btrans_format = get_iso8583_b24_from_btrans_format.SetBtransFormatFromB24Format("00"+msg_0810,"0810",1,"base24");
			
				cout << endl;
				cout << "valor de msg_0810_btrans_format > " << msg_0810_btrans_format << endl; 



				strcpy(rdbuf, RWCString(start_of_text)+msg_0810_btrans_format+RWCString(end_of_text));
				

				int test_len = 0;
				test_len = strlen(rdbuf);
				if (this->peer().send_n (rdbuf,
					 test_len )== -1)
					ACE_ERROR_RETURN ((LM_ERROR,
							   "%p\n",
							   "send"),
								 -1);
		
			}



		}
  
		else
		if (( valor_rw(0,4) == "0500"))
		{
							

		
			
			
			MQUtility get_iso8583_b24_from_btrans_format;
			RWCString msg_0500 = "";
			RWCString msg_0510 = "";
			RWCString msg_0510_btrans_format = "";

			cout << endl;
				cout << "Valor de 0500 > " << valor_rw << endl;



		
			MQUtility set_tcp_header;
			msg_0500 =	get_iso8583_b24_from_btrans_format.SetIso8583B24FromBtransFormat(valor_rw,"base24","ISO025000056",1);
			
			msg_0500 =	set_tcp_header.SetTcpHeader(msg_0500);
			


			if( host_tandem2 == 1)
			{
				get_iso8583_b24_from_btrans_format.SendMessageToQueueWithTimeout(msg_0500,send_queue_eps,
	             		queue_mgr);
			}
			if(host_tandem1 == 1)
		
			{
			
				get_iso8583_b24_from_btrans_format.SendMessageToQueueWithTimeout(msg_0500,send_queue_amex,
	             		queue_mgr);
			
								
			}




			cout << "Valor de msg_0500 > " << msg_0500 << endl;

			
			msg_0510 = get_iso8583_b24_from_btrans_format.Get_Msg_From_Queue(recv_queue,queue_mgr);

			cout << endl;
			cout << "Valor de msg_0510 " << msg_0510 << endl;

			
			if((msg_0510.length() > 0) && (msg_0510(0,3) == "ISO"))
				
			{
				msg_0510_btrans_format = get_iso8583_b24_from_btrans_format.SetBtransFormatFromB24Format("00"+msg_0510,"0510",1,"base24");
			
				cout << endl;
				cout << "valor de msg_0510_btrans_format > " << msg_0510_btrans_format << endl; 



				//cout << "Outgoing 0210 to Client > " << msg_0810_btrans_format << endl; 
				strcpy(rdbuf, RWCString(start_of_text)+msg_0510_btrans_format+RWCString(end_of_text));
				

				int test_len = 0;
				test_len = strlen(rdbuf);
				if (this->peer().send_n (rdbuf,
					 test_len )== -1)
					ACE_ERROR_RETURN ((LM_ERROR,
							   "%p\n",
							   "send"),
								 -1);
		
			}

			

		}
  
		else
		{

			cout << "*************Mensaje invalido*************" << endl;
		}
	}

	else
	{


			strcpy(rdbuf, RWCString(start_of_text)+"***ERROR EN FORMATO***"+RWCString(end_of_text));
				

				int test_len = 0;
				test_len = strlen(rdbuf);
				if (this->peer().send_n (rdbuf,
					 test_len )== -1)
					ACE_ERROR_RETURN ((LM_ERROR,
							   "%p\n",
							   "send"),
								 -1);
		
	}
}
}

 }

  return 0;

}
