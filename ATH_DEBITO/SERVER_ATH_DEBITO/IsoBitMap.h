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
	int       RetornoFieldNumber(int incoming_field);
	RWCString RetornoPreZeroes(int incoming_field );
	RWCString Retorno_210_B24(RWCString incoming , char *msg_type,int debug);
	RWCString Retorno_Msg_Iso8583_Field125(RWCString incoming , char *msg_type, 
										          int debug, RWCString application);


private:

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

	RWCString lllvar;					;
	RWCString llvar	;
	RWCString response_0210_generic_from_iso;
	RWCString bit_map_first_part;
	RWCString bit_map_second_part;

};

#endif // !defined(AFX_ISOBITMAP_H__AAAE91C7_3314_47E4_8AD8_0922072A9AB0__INCLUDED_)
