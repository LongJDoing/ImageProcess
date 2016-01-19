/****************************************************************************
          Copyright (C) 1995, University of California, Davis

          THIS SOFTWARE IS MADE AVAILABLE, AS IS, AND THE UNIVERSITY
          OF CALIFORNIA DOES NOT MAKE ANY WARRANTY ABOUT THE SOFTWARE, ITS
          PERFORMANCE, ITS MERCHANTABILITY OR FITNESS FOR ANY PARTICULAR
          USE, FREEDOM FROM ANY COMPUTER DISEASES OR ITS CONFORMITY TO ANY
          SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND PERFORMANCE OF
          THE SOFTWARE IS WITH THE USER.

          Copyright of the software and supporting documentation is
          owned by the University of California, and free access
          is hereby granted as a license to use this software, copy this
          software and prepare derivative works based upon this software.
          However, any distribution of this software source code or
          supporting documentation or derivative works (source code and
          supporting documentation) must include this copyright notice.
****************************************************************************/

/***************************************************************************
 *
 * University of California, Davis
 * UCDMC DICOM Network Transport Libraries
 * Version 0.1 Beta
 *
 * Technical Contact: mhoskin@ucdavis.edu
 *
 ***************************************************************************/

/***********************************************************************
 * PDU Service Classes:
 *	A-ASSOCIATE-RQ Class.  
 *
 * Base Classes:
 *	UID
 *	ApplicationContext
 *	AbstractSyntax
 *	TransferSyntax
 *	PresentationContext
 *	MaximumSubLength
 *	ImplementationClass
 *	ImplementationVersion
 *	UserInformation
 *
 *
 *
 *********************************************************************/
class	UID
	{
	UINT	Length;
	BYTE	uid[65];
	
	public:
			UID()	{ ZeroMem(uid, 64); Length = 0; };
			UID(BYTE *s) { Set ( s ); };
			UID(char *s) { Set ( (BYTE*)s ); };
			void	Set(BYTE *s)
				{
				if(!s)
					return;
				ZeroMem(uid, 64);
				strcpy((char *) uid, (char *) s);
				Length = strlen((char*) uid);
				};
			void	Set(UID	&u) { (*this) = u; };
			void	Set(char *s) { this->Set((BYTE *) s); };
			BYTE	*GetBuffer(UINT Min) { return(&uid[0]); };
			void	SetLength(UINT	L)	{ Length = L; while (L < 65) uid[L++] = '\0'; };
			UINT	GetSize()	{ return ( Length ); };
			BOOL	operator	==	(UID &ud)
				{ 	//if(GetSize()!=ud.GetSize()) return(FALSE);
					if(!strcmp((char*) GetBuffer(1), (char*) ud.GetBuffer(1)/*, (int) GetSize()*/))
						return(TRUE);
					return(FALSE); };
			BOOL	operator	!=	(UID &ud) { return (!((*this)==ud));
};
			BOOL	operator	=	(UID &ud)
				{	ByteCopy(uid, ud.GetBuffer(1), 64);
					SetLength(ud.GetSize());
					
					return(TRUE);
				}
	};

class	ApplicationContext
	{
	private:
		BYTE		ItemType;		// 0x10
		BYTE		Reserved1;
		UINT16		Length;
	public:
		UID			ApplicationContextName;

					ApplicationContext();
					ApplicationContext(UID	&);
					ApplicationContext(BYTE *);
					~ApplicationContext();
		void		Set(UID	&);
		void		Set(BYTE *);
		BOOL		Write(Buffer &);
		BOOL		Read(Buffer &);
		BOOL		ReadDynamic(Buffer	&);
		UINT32	Size();
	};

class	AbstractSyntax
	{
	private:
		BYTE		ItemType;	// 0x30
		BYTE		Reserved1;
		UINT16		Length;
	public:
		UID			AbstractSyntaxName;
					AbstractSyntax();
					AbstractSyntax(BYTE *);
					AbstractSyntax(UID &);
					~AbstractSyntax();
		void		Set(UID	&);
		void		Set(BYTE *);
		BOOL		Write(Buffer &);
		BOOL		Read(Buffer &);
		BOOL		ReadDynamic(Buffer	&);
		UINT32	Size();

	};

class	TransferSyntax
	{
	private:
		BYTE		ItemType;	// 0x40
		BYTE		Reserved1;
		UINT16		Length;
	public:
		UID			TransferSyntaxName;
		UINT		EndianType;
					TransferSyntax();
					TransferSyntax(BYTE *);
					TransferSyntax(UID &);
					~TransferSyntax();
		void		Set(UID	&);
		void		Set(BYTE *);
		void		SetType(UINT	T) { EndianType = T; };
		BOOL		Write(Buffer &);
		BOOL		Read(Buffer &);
		BOOL		ReadDynamic(Buffer	&);
		UINT32	Size();

	};

class	ImplementationClass
	{
	private:
		BYTE		ItemType;	// 0x52
		BYTE		Reserved1;
		UINT16		Length;
	public:
		UID			ImplementationName;
		UINT		EndianType;
					ImplementationClass();
					ImplementationClass(BYTE *);
					ImplementationClass(UID &);
					~ImplementationClass();
		void		Set(UID	&);
		void		Set(BYTE *);
		BOOL		Write(Buffer &);
		BOOL		Read(Buffer &);
		BOOL		ReadDynamic(Buffer	&);
		UINT32	Size();

	};


class	ImplementationVersion
	{
	private:
		BYTE		ItemType;	// 0x55
		BYTE		Reserved1;
		UINT16		Length;
	public:
		UID			Version;
		UINT		EndianType;
					ImplementationVersion();
					ImplementationVersion(BYTE *);
					ImplementationVersion(UID &);
					~ImplementationVersion();
		void		Set(UID	&);
		void		Set(BYTE *);
		BOOL		Write(Buffer &);
		BOOL		Read(Buffer &);
		BOOL		ReadDynamic(Buffer	&);
		UINT32	Size();

	};


class	SCPSCURoleSelect
	{
	private:
		BYTE		ItemType;	// 0x54
		BYTE		Reserved1;
		UINT16		Length;
	public:
		UID			uid;
		BYTE		SCURole;
		BYTE		SCPRole;
					SCPSCURoleSelect();
					~SCPSCURoleSelect();
		BOOL		Write(Buffer &);
		BOOL		Read(Buffer &);
		BOOL		ReadDynamic(Buffer	&);
		UINT32		Size();

	};


		
class	PresentationContext
	{
	private:
		BYTE							ItemType;	// 0x20
		BYTE							Reserved1;
		UINT16							Length;
	public:
		BYTE							PresentationContextID;
	private:
		BYTE							Reserved2;
		BYTE							Reserved3;
		BYTE							Reserved4;
	public:
		AbstractSyntax				AbsSyntax;
		Array<TransferSyntax>		TrnSyntax;
					PresentationContext();
					PresentationContext(AbstractSyntax &, TransferSyntax &);
					~PresentationContext();
		void		SetAbstractSyntax(AbstractSyntax	&);
		void		AddTransferSyntax(TransferSyntax	&);
		BOOL		Write(Buffer &);
		BOOL		Read(Buffer &);
		BOOL		ReadDynamic(Buffer	&);
		UINT32	Size();
		
	};

class	MaximumSubLength
	{
	private:
		BYTE						ItemType;	// 0x51
		BYTE						Reserved1;
		UINT16						Length;
		UINT32						MaximumLength;
	public:
					MaximumSubLength();
					MaximumSubLength(UINT32);
					~MaximumSubLength();
		void		Set(UINT32);
		UINT32		Get();
		BOOL		Write(Buffer &);
		BOOL		Read(Buffer &);
		BOOL		ReadDynamic(Buffer	&);
		UINT32	Size();
	};

class	UserInformation
	{
	private:
		BYTE						ItemType;	// 0x50
		BYTE						Reserved1;
		UINT16						Length;
	public:
		UINT32						UserInfoBaggage;
		MaximumSubLength			MaxSubLength;
		ImplementationClass			ImpClass;
		ImplementationVersion		ImpVersion;
		SCPSCURoleSelect			SCPSCURole;
	public:
					UserInformation();
					~UserInformation();
		void		SetMax(MaximumSubLength	&);
		UINT32		GetMax();
		BOOL		Write(Buffer &);
		BOOL		Read(Buffer &);
		BOOL		ReadDynamic(Buffer	&);
		UINT32		Size();
	};

class	AAssociateRQ
	{
	private:
		BYTE		ItemType;		// 0x01
		BYTE		Reserved1;
		UINT32	Length;
		UINT16	ProtocolVersion;	// 0x01
		UINT16	Reserved2;
	public:
		BYTE		CalledApTitle[17];	// 16 bytes transfered
		BYTE		CallingApTitle[17];	// 16 bytes transfered
		BYTE		Reserved3[32];

		ApplicationContext			AppContext;
		Array<PresentationContext>	PresContexts;
		UserInformation				UserInfo;
	public:
					AAssociateRQ();
					AAssociateRQ(BYTE	*, BYTE	*);
		virtual		~AAssociateRQ();
		void		SetCalledApTitle(BYTE	*);
		void		SetCallingApTitle(BYTE	*);
		void		SetApplicationContext(ApplicationContext &);
		void		SetApplicationContext(UID &);
		void		AddPresentationContext(PresentationContext &);
		void		ClearPresentationContexts();
		void		SetUserInformation(UserInformation &);
		BOOL		Write(Buffer &);
		BOOL		Read(Buffer &);
		BOOL		ReadDynamic(Buffer	&);
		UINT32		Size();
	};			


