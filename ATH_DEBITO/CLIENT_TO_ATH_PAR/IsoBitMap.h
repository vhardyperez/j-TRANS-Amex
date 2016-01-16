// IsoBitMap.h: interface for the IsoBitMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISOBITMAP_H__AAAE91C7_3314_47E4_8AD8_0922072A9AB0__INCLUDED_)
#define AFX_ISOBITMAP_H__AAAE91C7_3314_47E4_8AD8_0922072A9AB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <rw/cstring.h>
#include <rw/rwdate.h>
#include <rw/rwtime.h>
#include <rw/ctoken.h>
#include <rw/thr/thrfunc.h>
#include <rw/toolpro/neterr.h>
#define LLVAR	2
#define LLLVAR	3
#define FIXED	0


class IsoBitMap  
{
public:
	IsoBitMap();
	virtual ~IsoBitMap();
	void ReturnIso8583FieldValue(char *msg_type, int field_value, RWCString field_name);
	RWCString Retorno_Msg_Generic_PostermB24(RWCString incoming , char *msg_type, int debug,RWCString application);
	RWCString Retorno_Msg_Iso_PostermB240810(RWCString incoming , char *msg_type, int debug,RWCString application);
	int       RetornoFieldNumber(int incoming_field);
	RWCString RetornoPreZeroes(int incoming_field );
	RWCString Retorno_Msg_Generic_Field125(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
	void ShowFieldIso8583B24(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);
private:

	RWCString lllvar;					;
	RWCString llvar	;
	RWCString response_0210_generic_from_iso;

};

#endif // !defined(AFX_ISOBITMAP_H__AAAE91C7_3314_47E4_8AD8_0922072A9AB0__INCLUDED_)
