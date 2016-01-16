#if defined(WRITELOG_H)
#else

#define WRITELOG_H



void WriteLogMessage(DWORD	dwEventID, LPCTSTR	sourceKEY, char lpszMsg[80])

{

	
	HANDLE hEventSource = RegisterEventSource(0, sourceKEY);
//	 printf("Valor del RegisterEventSource : %ld\n",GetLastError());

	if( hEventSource != 0 ) 
	{
		LPCTSTR lpszMessage = lpszMsg;

		ReportEvent(
			hEventSource,	// handle of event source
			EVENTLOG_SUCCESS,
			//wEven//tType,		// event type
			0,				// event category
			//MSG_INFO_1,
			dwEventID,		// event ID
			0,
			//m_pUserSID,		// current user's SID
			1,				// strings in lpszStrings
			0,				// no bytes of raw data
			&lpszMessage,	// array of error strings
			0				// no raw data
		);

		::DeregisterEventSource(hEventSource);
    }

}
#endif