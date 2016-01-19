#if !defined(_DCM_ERROR_SURPASS)
#define _DCM_ERROR_SURPASS

#include <comdef.h>

#define DCMCOREERROR		0x80000000
#define DATABASEERROR		0x40000000
#define APP_LAYER_ERROR		0x00000000
#define DICOM_DAEMON_ACTIVE	0x00000001
#define DICOM_DAEMON_UNACTIVE	0x00000002 
#define DICOM_NET_ACTIVE	0x00000101
#define DICOM_NET_UNACTIVE	0x00000102 

#define ERRORTYPE_ERROR   0
#define ERRORTYPE_WARNING 1
#define ERRORTYPE_EVENT   2

class CQLError
{
public:
	DWORD  ErrorCode;
	bstr_t Reason;
	bstr_t ModuleName;
	DWORD  ErrorType;
	bstr_t CallbackData;
	CQLError()
	{
		Reason = "";
		ModuleName = "";
		ErrorCode = APP_LAYER_ERROR;
		ErrorType = ERRORTYPE_ERROR;
		CallbackData="";
	};
};

class  CQLEvent : public CQLError
{
public:
	CQLEvent()
	{
		ErrorType = ERRORTYPE_EVENT;
	};
};

class CQWarning: public CQLError
{
public:
	CQWarning()
	{
		ErrorType = ERRORTYPE_WARNING;
	};
};


// used by Storage SOP
#define EVENT_IMAGESENDSUCCESS 0x01000000

class CDcmCoreError: public CQLError
{
public:
	CDcmCoreError()
	{
		ErrorCode = DCMCOREERROR;
	};
};

class CDBError:public CQLError
{
public:
	CDBError()
	{
		ErrorCode = DATABASEERROR;
	}
};
#endif _DCM_ERROR_SURPASS