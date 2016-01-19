// ModalityWorklist.h: interface for the ModalityWorklist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODALITYWORKLIST_H__36D0BF52_394F_4896_AE5A_435C3B363D9D__INCLUDED_)
#define AFX_MODALITYWORKLIST_H__36D0BF52_394F_4896_AE5A_435C3B363D9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ModalityWorklist :
	public	CFindRQ,
	public	CFindRSP 
{
	public:
		virtual	BOOL	GetUID (UID	&uid)
		{ 
			uid.Set("1.2.840.10008.5.1.4.31");
			return ( TRUE );
		};
		//virtual	BOOL	uGetUID ( UID &) = 0;
		virtual	BOOL	SearchOn (	DICOMCommandObject	*,
									DICOMDataObject	*,
									Array < DICOMDataObject  *> 	*) = 0;
		virtual	BOOL	CallBack ( 	DICOMCommandObject	*,
									DICOMDataObject * ) = 0;
		BOOL	Read (	PDU_Service	*,
						DICOMCommandObject	*);
		BOOL	Write (	PDU_Service	*,
						DICOMDataObject	*);						
};

#endif // !defined(AFX_MODALITYWORKLIST_H__36D0BF52_394F_4896_AE5A_435C3B363D9D__INCLUDED_)
