#ifndef	iodbase_hpp
#define	iodbase_hpp
// C.2.1
// Class Module:PatientRelationshipModule
class	CO_PatientRelationshipModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PatientRelationshipModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ReferencedVisitSequence;
		VR_SQ	ReferencedStudySequence;
		VR_SQ	ReferencedPatientAliasSOPInstanceUIDs;
	}; // End of class defination for: PatientRelationshipModule

// Class Module:ReferencedVisitSequence
class	CO_ReferencedVisitSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedVisitSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedVisitSequence

// Class Module:ReferencedPatientAliasSOPInstanceUIDs
class	CO_ReferencedPatientAliasSOPInstanceUIDs	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedPatientAliasSOPInstanceUIDs(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedPatientAliasSOPInstanceUIDs

// C.2.2
// Class Module:PatientIdentificationModule
class	CO_PatientIdentificationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PatientIdentificationModule(CCO_Abstract *Composite=NULL);

		VR_PN	PatientsName;
		VR_LO	PatientID;
		VR_LO	IssuerOfPatientID;
		VR_LO	OtherPatientIDs;
		VR_PN	OtherPatientNames;
		VR_PN	PatientsMaidenName;
		VR_PN	PatientsMothersMaidenName;
		VR_LO	MedicalRecordLocator;
	}; // End of class defination for: PatientIdentificationModule

// C.2.3
// Class Module:PatientDemographicModule
class	CO_PatientDemographicModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PatientDemographicModule(CCO_Abstract *Composite=NULL);

		VR_LO	PatientsAddress;
		VR_LO	RegionOfResidence;
		VR_LO	CountryOfResidence;
		VR_SH	PatientsTelephoneNumbers;
		VR_DA	PatientsBirthDate;
		VR_TM	PatientsBirthTime;
		VR_SH	EthnicGroup;
		VR_CS	PatientsSex;
		VR_DS	PatientsSize;
		VR_DS	PatientsWeight;
		VR_LO	MilitaryRank;
		VR_LO	BranchOfService;
		VR_SQ	PatientsInsurencePlanCodeSequence;
		VR_LO	PatientsRelgiousPreference;
		VR_LT	PatientComments;
	}; // End of class defination for: PatientDemographicModule

// Class Module:PatientsInsurencePlanCodeSequence
class	CO_PatientsInsurencePlanCodeSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PatientsInsurencePlanCodeSequence(CCO_Abstract *Composite=NULL);

		VR_SH	CodeValue;
		VR_SH	CodingSchemeDesignator;
		VR_LO	CodeMeaning;
	}; // End of class defination for: PatientsInsurencePlanCodeSequence

// C.2.4
// Class Module:PatientMedicalModule
class	CO_PatientMedicalModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PatientMedicalModule(CCO_Abstract *Composite=NULL);

		VR_LO	PatientState;
		VR_US	PregnancyStatus;
		VR_LO	MedicalAlerts;
		VR_LO	ContrastAllergies;
		VR_LO	SpecialNeeds;
		VR_DA	LastMenstrualDate;
		VR_CS	SmokingStatus;
		VR_LT	AdditionalPatientHistory;
	}; // End of class defination for: PatientMedicalModule

// C.3.1
// Class Module:VisitRelationshipModule
class	CO_VisitRelationshipModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_VisitRelationshipModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ReferencedStudySequence;
		VR_SQ	ReferencedPatientSequence;
	}; // End of class defination for: VisitRelationshipModule

// C.3.2
// Class Module:VisitIdentificationModule
class	CO_VisitIdentificationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_VisitIdentificationModule(CCO_Abstract *Composite=NULL);

		VR_LO	InsitutionName;
		VR_ST	InsitutionAddress;
		VR_SQ	InsitutionCodeSequence;
		VR_LO	AdmissionID;
		VR_LO	IssuerOfAdmissionID;
	}; // End of class defination for: VisitIdentificationModule

// Class Module:InsitutionCodeSequence
class	CO_InsitutionCodeSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_InsitutionCodeSequence(CCO_Abstract *Composite=NULL);

		VR_SH	CodeValue;
		VR_SH	CodingSchemeDesignator;
		VR_LO	CodeMeaning;
	}; // End of class defination for: InsitutionCodeSequence

// C.3.3
// Class Module:VisitStatusModule
class	CO_VisitStatusModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_VisitStatusModule(CCO_Abstract *Composite=NULL);

		VR_CS	VisitStatusID;
		VR_LO	CurrentPatientLocation;
		VR_LO	PatientsInsitionResidence;
		VR_LT	VisitComments;
	}; // End of class defination for: VisitStatusModule

// C.3.4
// Class Module:VisitAdmissionModule
class	CO_VisitAdmissionModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_VisitAdmissionModule(CCO_Abstract *Composite=NULL);

		VR_DA	AdmittingDate;
		VR_TM	AdmittingTime;
		VR_LO	RouteOfAdmissions;
		VR_LO	AdmittingDiagnosisDescription;
		VR_SQ	AdmittingDiagnosisCodeSequence;
		VR_PN	ReferringPhysiciansName;
		VR_ST	ReferringPhysiciansAddress;
		VR_SH	ReferringPhysiciansPhoneNumbers;
	}; // End of class defination for: VisitAdmissionModule

// Class Module:AdmittingDiagnosisCodeSequence
class	CO_AdmittingDiagnosisCodeSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_AdmittingDiagnosisCodeSequence(CCO_Abstract *Composite=NULL);

		VR_SH	CodeValue;
		VR_SH	CodingSchemeDesignator;
		VR_LO	CodeMeaning;
	}; // End of class defination for: AdmittingDiagnosisCodeSequence

// C.3.5
// Class Module:VisitDischargeModule
class	CO_VisitDischargeModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_VisitDischargeModule(CCO_Abstract *Composite=NULL);

		VR_DA	DischargeDate;
		VR_TM	DischargeTime;
		VR_LO	DischargeDiagnosisDescription;
		VR_SQ	DischargeDiagnosisCodeSequence;
	}; // End of class defination for: VisitDischargeModule

// Class Module:DischargeDiagnosisCodeSequence
class	CO_DischargeDiagnosisCodeSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_DischargeDiagnosisCodeSequence(CCO_Abstract *Composite=NULL);

		VR_SH	CodeValue;
		VR_SH	CodingSchemeDesignator;
		VR_LO	CodeMeaning;
	}; // End of class defination for: DischargeDiagnosisCodeSequence

// C.3.6
// Class Module:VisitSchedulingModule
class	CO_VisitSchedulingModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_VisitSchedulingModule(CCO_Abstract *Composite=NULL);

		VR_DA	ScheduledAdmissionDate;
		VR_TM	ScheduledAdmissionTime;
		VR_DA	ScheduledDischargeDate;
		VR_TM	ScheduledDischargeTime;
		VR_LO	ScheduledPatientInsitutionResidence;
	}; // End of class defination for: VisitSchedulingModule

// C.4.1
// Class Module:StudyRelationshipModule
class	CO_StudyRelationshipModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_StudyRelationshipModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ReferencedVisitSequence;
		VR_SQ	ReferencedPatientSequence;
		VR_SQ	ReferencedResultsSequence;
		VR_SQ	ReferencedStudyComponentSequence;
		VR_UI	StudyInstanceUID;
		VR_SH	AccessionNumber;
	}; // End of class defination for: StudyRelationshipModule

// Class Module:ReferencedResultsSequence
class	CO_ReferencedResultsSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedResultsSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedResultsSequence

// Class Module:ReferencedStudyComponentSequence
class	CO_ReferencedStudyComponentSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedStudyComponentSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedStudyComponentSequence

// C.4.2
// Class Module:StudyIdentificationModule
class	CO_StudyIdentificationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_StudyIdentificationModule(CCO_Abstract *Composite=NULL);

		VR_SH	StudyID;
		VR_LO	StudyIDIssuer;
		VR_IS	OtherStudyNumbers;
	}; // End of class defination for: StudyIdentificationModule

// C.4.3
// Class Module:StudyModule
class	CO_StudyModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_StudyModule(CCO_Abstract *Composite=NULL);

		VR_CS	StudyStatusID;
		VR_CS	StudyPriorityID;
		VR_LT	StudyComments;
	}; // End of class defination for: StudyModule

// C.4.4
// Class Module:StudySchedulingModule
class	CO_StudySchedulingModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_StudySchedulingModule(CCO_Abstract *Composite=NULL);

		VR_DA	ScheduledStudyStartDate;
		VR_TM	ScheduledStudyStartTime;
		VR_DA	ScheduledStudyStopDate;
		VR_TM	ScheduledStudyStopTime;
		VR_LO	ScheduledStudyLocation;
		VR_AE	ScheduledStudyLocationAETitle;
		VR_LO	ReasonForStudy;
		VR_PN	RequestingPhysician;
		VR_LO	RequestingService;
		VR_LO	RequestedProcedureDescription;
		VR_SQ	RequestedProcedureCodeSequence;
		VR_LO	RequestedContrastAgent;
	}; // End of class defination for: StudySchedulingModule

// Class Module:RequestedProcedureCodeSequence
class	CO_RequestedProcedureCodeSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_RequestedProcedureCodeSequence(CCO_Abstract *Composite=NULL);

		VR_SH	CodeValue;
		VR_SH	CodingSchemeDesignator;
		VR_LO	CodeMeaning;
	}; // End of class defination for: RequestedProcedureCodeSequence

// C.4.5
// Class Module:StudyAcquisitionModule
class	CO_StudyAcquisitionModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_StudyAcquisitionModule(CCO_Abstract *Composite=NULL);

		VR_DA	StudyArrivalDate;
		VR_TM	StudyArrivalTime;
		VR_DA	StudyDate;
		VR_TM	StudyTime;
		VR_DA	StudyCompletionDate;
		VR_TM	StudyCompletionTime;
		VR_DA	StudyVerifiedDate;
		VR_TM	StudyVerifiedTime;
		VR_IS	SeriesInStudy;
		VR_IS	AcquisitionsInStudy;
	}; // End of class defination for: StudyAcquisitionModule

// C.4.6
// Class Module:StudyReadModule
class	CO_StudyReadModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_StudyReadModule(CCO_Abstract *Composite=NULL);

		VR_PN	NameOfPhysiciansReadingStudy;
		VR_DA	StudyReadDate;
		VR_TM	StudyReadTime;
	}; // End of class defination for: StudyReadModule

// C.4.7
// Class Module:StudyComponentModule
class	CO_StudyComponentModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_StudyComponentModule(CCO_Abstract *Composite=NULL);

		VR_SH	StudyID;
		VR_UI	StudyInstanceUID;
		VR_SQ	ReferencedSeriesSequence;
	}; // End of class defination for: StudyComponentModule

// Class Module:ReferencedSeriesSequence
class	CO_ReferencedSeriesSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedSeriesSequence(CCO_Abstract *Composite=NULL);

		VR_DA	SeriesDate;
		VR_TM	SeriesTime;
		VR_UI	SeriesInstanceUID;
		VR_AE	RetrieveAETitle;
		VR_SH	StorageMediaFileSetID;
		VR_UI	StorageMediaFileSetUID;
		VR_SQ	ReferencedImageSequence;
	}; // End of class defination for: ReferencedSeriesSequence

// C.4.8
// Class Module:StudyComponentRelationshipModule
class	CO_StudyComponentRelationshipModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_StudyComponentRelationshipModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ReferencedStudySequence;
	}; // End of class defination for: StudyComponentRelationshipModule

// C.4.9
// Class Module:StudyComponentStatusModule
class	CO_StudyComponentStatusModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_StudyComponentStatusModule(CCO_Abstract *Composite=NULL);

		VR_CS	Modality;
		VR_LO	StudyDescription;
		VR_SQ	ProcedureCodeSequence;
		VR_PN	AttendingPhysiciansName;
		VR_CS	StudyComponentStatusID;
	}; // End of class defination for: StudyComponentStatusModule

// Class Module:ProcedureCodeSequence
class	CO_ProcedureCodeSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ProcedureCodeSequence(CCO_Abstract *Composite=NULL);

		VR_SH	CodeValue;
		VR_SH	CodingSchemeDesignator;
		VR_LO	CodeMeaning;
	}; // End of class defination for: ProcedureCodeSequence

// C.5.1
// Class Module:ResultsRelationshipModule
class	CO_ResultsRelationshipModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ResultsRelationshipModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ReferencedInterpretationSequence;
	}; // End of class defination for: ResultsRelationshipModule

// Class Module:ReferencedInterpretationSequence
class	CO_ReferencedInterpretationSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedInterpretationSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedInterpretationSequence

// C.5.2
// Class Module:ResultsIdentificationModule
class	CO_ResultsIdentificationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ResultsIdentificationModule(CCO_Abstract *Composite=NULL);

		VR_SH	ResultsID;
		VR_LO	ResultsIDIssuer;
	}; // End of class defination for: ResultsIdentificationModule

// C.5.3	
// Class Module:ResultsImpressionsModule
class	CO_ResultsImpressionsModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ResultsImpressionsModule(CCO_Abstract *Composite=NULL);

		VR_ST	Impressions;
	}; // End of class defination for: ResultsImpressionsModule

// C.6.1
// Class Module:InterpretationRelationshipModule
class	CO_InterpretationRelationshipModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_InterpretationRelationshipModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ReferencedResultsSequence;
	}; // End of class defination for: InterpretationRelationshipModule

// C.6.2
// Class Module:InterpretationIdentificationModule
class	CO_InterpretationIdentificationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_InterpretationIdentificationModule(CCO_Abstract *Composite=NULL);

		VR_SH	InterpretationID;
		VR_LO	InterpretationIDIssuer;
	}; // End of class defination for: InterpretationIdentificationModule

// C.6.3
// Class Module:InterpretationStateModule
class	CO_InterpretationStateModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_InterpretationStateModule(CCO_Abstract *Composite=NULL);

		VR_CS	InterpretationTypeID;
		VR_CS	InterpretationStatusID;
	}; // End of class defination for: InterpretationStateModule

// C.6.4
// Class Module:InterpretationRecordingModule
class	CO_InterpretationRecordingModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_InterpretationRecordingModule(CCO_Abstract *Composite=NULL);

		VR_DA	InterpretationRecordedDate;
		VR_TM	InterpretationRecordedTime;
		VR_PN	InterpretationRecorder;
		VR_LO	ReferenceToRecordedSound;
	}; // End of class defination for: InterpretationRecordingModule

// C.6.5
// Class Module:InterpretationTranscriptionModule
class	CO_InterpretationTranscriptionModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_InterpretationTranscriptionModule(CCO_Abstract *Composite=NULL);

		VR_DA	InterpretationTranscriptionDate;
		VR_TM	InterpretationTranscriptionTime;
		VR_PN	InterpretationTranscriptionTranscriber;
		VR_ST	InterpretationTranscriptionText;
		VR_PN	InterpretationAuthor;
	}; // End of class defination for: InterpretationTranscriptionModule

// C.6.6
// Class Module:InterpretationApprovalModule
class	CO_InterpretationApprovalModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_InterpretationApprovalModule(CCO_Abstract *Composite=NULL);

		VR_SQ	InterpretationApproverSequence;
		VR_LT	InterpretationDiagnosisDescription;
		VR_SQ	InterpretationDiagnosisCodesSequence;
		VR_SQ	ResultsDistributionListSequence;
	}; // End of class defination for: InterpretationApprovalModule

// Class Module:InterpretationApproverSequence
class	CO_InterpretationApproverSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_InterpretationApproverSequence(CCO_Abstract *Composite=NULL);

		VR_DA	InterpretationApprovalDate;
		VR_TM	InterpretationApprovalTime;
		VR_PN	PhysiciansApprovingInterpretation;
	}; // End of class defination for: InterpretationApproverSequence

// Class Module:InterpretationDiagnosisCodesSequence
class	CO_InterpretationDiagnosisCodesSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_InterpretationDiagnosisCodesSequence(CCO_Abstract *Composite=NULL);

		VR_SH	CodeValue;
		VR_SH	CodingSchemeDesignator;
		VR_LO	CodeMeaning;
	}; // End of class defination for: InterpretationDiagnosisCodesSequence

// Class Module:ResultsDistributionListSequence
class	CO_ResultsDistributionListSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ResultsDistributionListSequence(CCO_Abstract *Composite=NULL);

		VR_PN	DistributionName;
		VR_LO	DistributionAddress;
	}; // End of class defination for: ResultsDistributionListSequence

// C.7.1
// Class Module:PatientModule
class	CO_PatientModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PatientModule(CCO_Abstract *Composite=NULL);

		VR_PN	PatientsName;
		VR_LO	PatientID;
		VR_DA	PatientsBirthDate;
		VR_CS	PatientsSex;
		VR_SQ	ReferencedPatientSequence;
		VR_TM	PatientsBirthTime;
		VR_LO	OtherPatientID;
		VR_PN	OtherPatientNames;
		VR_SH	EthnicGroup;
		VR_LT	PatientComments;
	}; // End of class defination for: PatientModule

// Class Module:ReferencedPatientSequence
class	CO_ReferencedPatientSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedPatientSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedPatientSequence

// C.7.2.1
// Class Module:GeneralStudyModule
class	CO_GeneralStudyModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_GeneralStudyModule(CCO_Abstract *Composite=NULL);

		VR_UI	StudyInstanceUID;
		VR_DA	StudyDate;
		VR_TM	StudyTime;
		VR_PN	ReferringPhysiciansName;
		VR_SH	StudyID;
		VR_SH	AccessionNumber;
		VR_LO	StudyDescription;
		VR_PN	NameOfPhysiciansReadingStudy;
		VR_SQ	ReferencedStudySequence;
	}; // End of class defination for: GeneralStudyModule

// Class Module:ReferencedStudySequence
class	CO_ReferencedStudySequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedStudySequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedStudySequence

// C.7.2.2
// Class Module:PatientStudyModule
class	CO_PatientStudyModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PatientStudyModule(CCO_Abstract *Composite=NULL);

		VR_LO	AdmittingDiagnosesDescription;
		VR_AS	PatientsAge;
		VR_DS	PatientsSize;
		VR_DS	PatientsWeight;
		VR_SH	Occupation;
		VR_LT	AdditionalPatientsHistory;
	}; // End of class defination for: PatientStudyModule

// C.7.3.1
// Class Module:GeneralSeriesModule
class	CO_GeneralSeriesModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_GeneralSeriesModule(CCO_Abstract *Composite=NULL);

		VR_CS	Modality;
		VR_UI	SeriesInstanceUID;
		VR_IS	SeriesNumber;
		VR_CS	Laterality;
		VR_DA	SeriesDate;
		VR_TM	SeriesTime;
		VR_PN	PerformingPhysiciansName;
		VR_LO	ProtocolName;
		VR_LO	SeriesDescription;
		VR_PN	OperatorsName;
		VR_SQ	ReferenedStudyComponentSequence;
		VR_CS	BodyPartExamined;
		VR_CS	PatientPosition;
		VR_XS	SmallestPixelValueInSeries;
		VR_XS	LargestPixelValueInSeries;
	}; // End of class defination for: GeneralSeriesModule

// C.7.4.1
// Class Module:FrameOfReferenceModule
class	CO_FrameOfReferenceModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_FrameOfReferenceModule(CCO_Abstract *Composite=NULL);

		VR_UI	FrameOfReferenceUID;
		VR_LO	PositionReferenceIndicator;
	}; // End of class defination for: FrameOfReferenceModule

// C.7.5.1
// Class Module:GeneralEquipmentModule
class	CO_GeneralEquipmentModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_GeneralEquipmentModule(CCO_Abstract *Composite=NULL);

		VR_LO	Manufacturer;
		VR_LO	InstitutionName;
		VR_ST	InstitutionAddress;
		VR_ST	StationName;
		VR_LO	InstitutionalDepartmentName;
		VR_LO	ManufacturersModelName;
		VR_LO	DeviceSerialNumber;
		VR_LO	SoftwareVersions;
		VR_DS	SpatialResolution;
		VR_DA	DateOfLastCalibration;
		VR_TM	TimeOfLastCalibration;
		VR_XS	PixelPaddingValue;
	}; // End of class defination for: GeneralEquipmentModule

// C.7.6.1
// Class Module:GeneralImageModule
class	CO_GeneralImageModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_GeneralImageModule(CCO_Abstract *Composite=NULL);

		VR_IS	ImageNumber;
		VR_CS	PatientOrientation;
		VR_DA	ImageDate;
		VR_TM	ImageTime;
		VR_CS	ImageType;
		VR_IS	AcquisitionNumber;
		VR_DA	AcquisitionDate;
		VR_TM	AcquisitionTime;
		VR_SQ	ReferencedImageSequence;
		VR_ST	DerivationDescription;
		VR_SQ	SourceImageSequence;
		VR_IS	ImagesInAcquisition;
		VR_LT	ImageComments;
	}; // End of class defination for: GeneralImageModule

// Class Module:SourceImageSequence
class	CO_SourceImageSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_SourceImageSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: SourceImageSequence

// C.7.6.2
// Class Module:ImagePlaneModule
class	CO_ImagePlaneModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ImagePlaneModule(CCO_Abstract *Composite=NULL);

		VR_DS	PixelSpacing;
		VR_DS	ImageOrientationPatient;
		VR_DS	ImagePositionPatient;
		VR_DS	SliceThickness;
		VR_DS	SliceLocation;
	}; // End of class defination for: ImagePlaneModule

// C.7.6.3
// Class Module:ImagePixelModule
class	CO_ImagePixelModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ImagePixelModule(CCO_Abstract *Composite=NULL);

		VR_US	SamplesPerPixel;
		VR_CS	PhotometricInterpretation;
		VR_US	Rows;
		VR_US	Columns;
		VR_US	BitsAllocated;
		VR_US	BitsStored;
		VR_US	HighBit;
		VR_US	PixelRepresentation;
		VR_OX	PixelData;
		VR_US	PlanarConfiguration;
		VR_IS	PixelAspectRatio;
		VR_XS	SmallestImagePixelValue;
		VR_XS	LargestImagePixelValue;
		VR_XS	RedPaletteColorLookupTableDescriptor;
		VR_XS	GreenPaletteColorLookupTableDescriptor;
		VR_XS	BluePaletteColorLookupTableDescriptor;
		VR_XS	RedPaletteColorLookupTableData;
		VR_XS	GreenPaletteColorLookupTableData;
		VR_XS	BluePaletteColorLookupTableData;
	}; // End of class defination for: ImagePixelModule

// C.7.6.4
// Class Module:ContrastBolusModule
class	CO_ContrastBolusModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ContrastBolusModule(CCO_Abstract *Composite=NULL);

		VR_LO	ContrastBolusAgent;
		VR_LO	ContrastBolusRoute;
		VR_DS	ContrastBolusVolume;
		VR_TM	ContrastBolusStartTime;
		VR_TM	ContrastBolusStopTime;
		VR_DS	ContrastBolusTotalDose;
	}; // End of class defination for: ContrastBolusModule

// C.7.6.5
// Class Module:CineModule
class	CO_CineModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_CineModule(CCO_Abstract *Composite=NULL);

		VR_DS	FrameTime;
		VR_DS	FrameTimeVector;
		VR_IS	StartTrim;
		VR_IS	StopTrim;
		VR_IS	RecommendedDisplayFrameRate;
		VR_IS	CineRate;
		VR_DS	FrameDelay;
		VR_DS	EffectiveDuration;
		VR_IS	ActualFrameDuration;
	}; // End of class defination for: CineModule

// C.7.6.6
// Class Module:MultiframeModule
class	CO_MultiframeModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_MultiframeModule(CCO_Abstract *Composite=NULL);

		VR_IS	NumberOfFrames;
		VR_AT	FrameIncrementPointer;
	}; // End of class defination for: MultiframeModule

// C.7.7
// Class Module:PatientSummaryModule
class	CO_PatientSummaryModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PatientSummaryModule(CCO_Abstract *Composite=NULL);

		VR_PN	PatientsName;
		VR_LO	PatientID;
	}; // End of class defination for: PatientSummaryModule

// C.7.8
// Class Module:StudyContentModule
class	CO_StudyContentModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_StudyContentModule(CCO_Abstract *Composite=NULL);

		VR_SH	StudyID;
		VR_UI	StudyInstanceUID;
		VR_SQ	ReferencedSeriesSequence;
	}; // End of class defination for: StudyContentModule

// Class Module:ReferencedImageSequence
class	CO_ReferencedImageSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedImageSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferenceSOPInstanceUID;
		VR_AE	RetrieveApplicationEntityTitle;
		VR_SH	StorageMediaFileSetID;
		VR_UI	StorageMediaFileSetUID;
	}; // End of class defination for: ReferencedImageSequence

// C.8.1.1
// Class Module:CRSeriesModule
class	CO_CRSeriesModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_CRSeriesModule(CCO_Abstract *Composite=NULL);

		VR_CS	BodyPartExamined;
		VR_CS	VeiwPosition;
		VR_SH	FilterType;
		VR_SH	CollimatorGridName;
		VR_DS	FocalSpot;
		VR_SH	PlateType;
		VR_LO	PhosphorType;
	}; // End of class defination for: CRSeriesModule

// C.8.1.2
// Class Module:CRImageModule
class	CO_CRImageModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_CRImageModule(CCO_Abstract *Composite=NULL);

		VR_DS	KVP;
		VR_LO	PlateID;
		VR_DS	DistanceSourceToDetector;
		VR_DS	DistanceSourceToPatient;
		VR_IS	ExposureTime;
		VR_IS	XRayTubeCurrent;
		VR_IS	Exposure;
		VR_IS	GeneratorPower;
		VR_LO	AcquisitionDeviceProcessingDescription;
		VR_LO	AcquisitionDeviceProcessingCode;
		VR_CS	CassetteOrientation;
		VR_CS	CassetteSize;
		VR_US	ExposuresOnPlate;
		VR_IS	RelativeXRayExposure;
		VR_DS	Sensitivity;
	}; // End of class defination for: CRImageModule

// C.8.2.1
// Class Module:CTImageModule
class	CO_CTImageModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_CTImageModule(CCO_Abstract *Composite=NULL);

		VR_CS	ImageType;
		VR_US	SamplesPerPixel;
		VR_CS	PhotometricInterpretation;
		VR_US	BitsAllocated;
		VR_US	BitsStored;
		VR_US	HighBit;
		VR_DS	RescaleIntercept;
		VR_DS	RescaleSlope;
		VR_DS	KVP;
		VR_IS	AcquisitionNumber;
		VR_CS	ScanOptions;
		VR_DS	DataCollectionDiameter;
		VR_DS	ReconstructionDiameter;
		VR_DS	DistanceSourceToDector;
		VR_DS	DistanceSourceToPatient;
		VR_DS	GantryDetectorTilt;
		VR_DS	TableHeight;
		VR_CS	RotationDirection;
		VR_IS	ExposureTime;
		VR_IS	XRayTubeCurrent;
		VR_IS	Exposure;
		VR_SH	FilterType;
		VR_IS	GeneratorPower;
		VR_DS	FocalSpot;
		VR_SH	ConvolutionKernel;
	}; // End of class defination for: CTImageModule

// C.8.3.1
// Class Module:MRImageModule
class	CO_MRImageModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_MRImageModule(CCO_Abstract *Composite=NULL);

		VR_CS	ImageType;
		VR_US	SamplesPerPixel;
		VR_CS	PhotometricInterpretation;
		VR_US	BitsAllocated;
		VR_SQ	ScanningSequence;
		VR_CS	DequenceVariant;
		VR_CS	ScanOptions;
		VR_CS	MRAcquisitionType;
		VR_DS	RepetitionTime;
		VR_DS	EchoTime;
		VR_IS	EchoTrainLength;
		VR_DS	InversionTime;
		VR_DS	TriggerTime;
		VR_SH	SequenceName;
		VR_CS	AngioFlag;
		VR_DS	NumberOfAverages;
		VR_DS	ImagingFrequency;
		VR_SH	ImagedNucleus;
		VR_IS	EchoNumber;
		VR_DS	MagneticFieldStrength;
		VR_DS	SpacingBetweenSlices;
		VR_IS	NumberOfPhaseEncodingSteps;
		VR_DS	PercentSampling;
		VR_DS	PercentPhaseFieldOfView;
		VR_DS	PixelBandwidth;
		VR_IS	NominalInterval;
		VR_CS	BeatRejectionFlag;
		VR_IS	LowRRValue;
		VR_IS	IntervalsAcquired;
		VR_IS	InvervalsRejected;
		VR_LO	PVCRejection;
		VR_IS	SkipBeats;
		VR_IS	HeartRate;
		VR_IS	CardiacNumberOfImages;
		VR_IS	TriggerWindow;
		VR_DS	ReconstructionDiameter;
		VR_SH	ReceivingCoil;
		VR_SH	TransmittingCoil;
		VR_US	AcquisitionMatrix;
		VR_CS	PhaseEncodingDirection;
		VR_DS	FlipAngle;
		VR_DS	SAR;
		VR_CS	VariableFlipAngleFlag;
		VR_DS	dBdt;
		VR_IS	TemporalPositionIdentifier;
		VR_IS	NumberOfTemporalPositions;
		VR_DS	TemporalResolution;
	}; // End of class defination for: MRImageModule

// C.8.4.1
// Class Module:NMSeriesModule
class	CO_NMSeriesModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_NMSeriesModule(CCO_Abstract *Composite=NULL);

		VR_LO	Radionuclide;
		VR_CS	NuclearMedicineSeriesType;
		VR_IS	ScanVelocity;
		VR_CS	WholeBodyTechnique;
		VR_IS	ScanLength;
		VR_LO	Radiopharmaceutical;
		VR_DS	EnergyWindowCenterline;
		VR_DS	EnergyWindowTotalWidth;
		VR_LO	InterventionDrugName;
		VR_TM	InterventionDrugStartTime;
		VR_DS	EffectiveSeriesDuration;
		VR_IS	SyringeCounts;
		VR_LO	TriggerSourceOrType;
		VR_LO	RadionuclideRoute;
		VR_DS	RadionuclideVolume;
		VR_TM	RadionuclideStartTime;
		VR_TM	RadionuclideStopTime;
		VR_DS	RadionuclideTotalDose;
		VR_DS	GantryDetectorTilt;
		VR_IS	IsotopeNumber;
	}; // End of class defination for: NMSeriesModule

// C.8.4.2
// Class Module:NMEquipmentModule
class	CO_NMEquipmentModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_NMEquipmentModule(CCO_Abstract *Composite=NULL);

		VR_DS	CenterOfRotationOffset;
		VR_CS	FieldOfViewShape;
		VR_IS	FieldOfViewDimensions;
		VR_SH	CollimatorGridName;
		VR_CS	CollimatorType;
		VR_IS	FocalDistance;
		VR_DS	XFocusCenter;
		VR_DS	YFocusCenter;
	}; // End of class defination for: NMEquipmentModule

// C.8.4.3
// Class Module:NMImageModule
class	CO_NMImageModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_NMImageModule(CCO_Abstract *Composite=NULL);

		VR_AT	FrameIncrementPointer;
		VR_DS	ZoomFactor;
		VR_IS	CountsAccumulated;
		VR_SQ	ReferencedOverlaySequence;
		VR_SQ	ReferencedCurveSequence;
		VR_CS	AcquisitionTerminationCondition;
		VR_DS	ReconstructionDiameter;
		VR_DS	DistanceSourceToDetector;
		VR_DS	TableHeight;
		VR_DS	TableTraverse;
		VR_DS	AngularPosition;
		VR_DS	RadialPosition;
		VR_SH	ConvolutionKernel;
		VR_IS	ActualFrameDuration;
		VR_IS	CountRate;
		VR_LO	PreprocessingFunction;
		VR_LO	PostprocessingFunction;
		VR_IS	PhaseNumber;
		VR_IS	IntervalNumber;
		VR_IS	TimeSlotNumber;
		VR_IS	AngleNumber;
		VR_DS	ZoomCenter;
		VR_CS	CorrectedImage;
	}; // End of class defination for: NMImageModule

// C.8.4.4
// Class Module:NMSPECTAcquisitionImageModule
class	CO_NMSPECTAcquisitionImageModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_NMSPECTAcquisitionImageModule(CCO_Abstract *Composite=NULL);

		VR_AT	FrameIncrementPointer;
		VR_DS	AngularStep;
		VR_DS	ZoomFactor;
		VR_DS	ScanArc;
		VR_DS	ReconstructionDiameter;
		VR_DS	DistanceSourceToDetector;
		VR_DS	TableHeight;
		VR_DS	TableTraverse;
		VR_CS	RotationDirection;
		VR_DS	AngularPosition;
		VR_DS	RadialPosition;
		VR_DS	RotationOffset;
		VR_IS	AngleNumber;
		VR_DS	ZoomCenter;
	}; // End of class defination for: NMSPECTAcquisitionImageModule

// C.8.4.5
// Class Module:NMMultigatedAcquisitionImageModule
class	CO_NMMultigatedAcquisitionImageModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_NMMultigatedAcquisitionImageModule(CCO_Abstract *Composite=NULL);

		VR_AT	FrameIncrementPointer;
		VR_LO	TriggerSourceORType;
		VR_DS	FrameTime;
		VR_DS	TriggerTime;
		VR_IS	NominalInterval;
		VR_LO	FramingType;
		VR_CS	BeatRejectionFlag;
		VR_IS	LowRRValue;
		VR_IS	HighRRValue;
		VR_IS	IntervalsAcquired;
		VR_IS	IntervalsRejected;
		VR_LO	PVCRejection;
		VR_IS	SkipBeats;
		VR_IS	HeartRate;
		VR_IS	CardiacNumberOfImages;
	}; // End of class defination for: NMMultigatedAcquisitionImageModule

// C.8.5.1
// Class Module:USFrameOfReferenceModule
class	CO_USFrameOfReferenceModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_USFrameOfReferenceModule(CCO_Abstract *Composite=NULL);

		VR_UL	RegionLocationMinX0;
		VR_UL	RegionLocationMinY0;
		VR_UL	RegionLocationMaxX1;
		VR_UL	RegionLocationMaxY1;
		VR_US	PhysicalUnitsXDirection;
		VR_US	PhysicalUnitsYDirection;
		VR_FD	PhysicalDeltaX;
		VR_FD	PhysicalDeltaY;
		VR_SL	ReferencePixelX0;
		VR_SL	ReferencePixelY0;
		VR_FD	RefPixelPhysicalValueX;
		VR_FD	RefPixelPhysicalValueY;
	}; // End of class defination for: USFrameOfReferenceModule

// C.8.5.2
// Class Module:USRegionCalibrationModule
class	CO_USRegionCalibrationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_USRegionCalibrationModule(CCO_Abstract *Composite=NULL);

		VR_SQ	SequenceOfUltrasoundRegions;
	}; // End of class defination for: USRegionCalibrationModule

// Class Module:SequenceOfUltrasoundRegions
class	CO_SequenceOfUltrasoundRegions	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_SequenceOfUltrasoundRegions(CCO_Abstract *Composite=NULL);

		VR_UL	RegionLocationMinX0;
		VR_UL	RegionLocationMinY0;
		VR_UL	RegionLocationMaxX1;
		VR_UL	RegionLocationMaxY1;
		VR_US	PhysicalUnitsXDirection;
		VR_US	PhysicalUnitsYDirection;
		VR_FD	PhysicalDeltaX;
		VR_FD	PhysicalDeltaY;
		VR_SL	ReferencePixelX0;
		VR_SL	ReferencePixelY0;
		VR_FD	RefPixelPhysicalValueX;
		VR_FD	RefPixelPhysicalValueY;
		VR_US	RegionSpatialFormat;
		VR_US	RegionDataType;
		VR_UL	RegionFlags;
		VR_US	PixelComponentOrganization;
		VR_UL	PixelComponentMask;
		VR_UL	PixelComponentRangeStart;
		VR_UL	PixelComponentRangeStop;
		VR_US	PixelComponentPhysicalUnits;
		VR_US	PixelComponentDataType;
		VR_UL	NumberOfTableBreakPoints;
		VR_UL	TableOfXBreakPoints;
		VR_FD	TableOfYBreakPoints;
		VR_UL	TransducerFrequency;
		VR_UL	PulseRepetitionFrequency;
		VR_FD	DopplerCorrectionAngle;
		VR_FD	SteeringAngle;
		VR_UL	DopplerSampleVolumeXPosition;
		VR_UL	DopplerSampleVolumeYPosition;
		VR_UL	TMLinePositionX0;
		VR_UL	TMLinePositionY0;
		VR_UL	TMLinePositionX1;
		VR_UL	TMLinePositionY1;
	}; // End of class defination for: SequenceOfUltrasoundRegions

// C.8.5.3
// Class Module:USImageModule
class	CO_USImageModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_USImageModule(CCO_Abstract *Composite=NULL);

		VR_CS	PhotometricInterpretation;
		VR_US	PixelRepresentation;
		VR_AT	FrameIncrementPointer;
		VR_CS	ImageType;
		VR_IS	NumberOfStages;
		VR_IS	NumberOfViewsInStage;
		VR_SQ	ReferencedOverlaySequence;
		VR_SQ	ReferencedCurveSequence;
		VR_SH	StageName;
		VR_IS	StageNumber;
		VR_IS	ViewNumber;
		VR_IS	NumberOfEventTimers;
		VR_DS	EventElapsedTimes;
		VR_LO	EventTimerNames;
		VR_CS	TransducerPosition;
		VR_CS	TransducerOrientation;
		VR_CS	AnatomicStructure;
		VR_DS	TriggerTime;
		VR_IS	MonimalInterval;
		VR_CS	BeatRejectionFlag;
		VR_IS	LowRRValue;
		VR_IS	HighRRValue;
		VR_IS	HeartRate;
		VR_SH	OutputPower;
		VR_LO	TransducerDate;
		VR_CS	TransducerType;
		VR_DS	FocusDepth;
		VR_LO	PreprocessingFunction;
		VR_DS	MechanicalIndex;
		VR_DS	BoneThermalIndex;
		VR_DS	CranialThermalIndex;
		VR_DS	SoftTissueThermalIndex;
		VR_DS	SoftTissueFocusThermalIndex;
		VR_DS	SoftTissueSurfaceThermalIndex;
		VR_IS	DepthOfScanField;
		VR_DS	ImageTransformationMatrix;
		VR_DS	ImageTranslationVector;
	}; // End of class defination for: USImageModule

// Class Module:ReferencedCurveSequence
class	CO_ReferencedCurveSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedCurveSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedCurveSequence

// C.8.6.1
// Class Module:SCEquipmentModule
class	CO_SCEquipmentModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_SCEquipmentModule(CCO_Abstract *Composite=NULL);

		VR_CS	ConversionType;
		VR_CS	Modality;
		VR_LO	SecondaryCaptureDeviseID;
		VR_LO	SecondaryCaptureDeviceManufacturer;
		VR_LO	SecondaryCaptureDeviceManufacturersModelName;
		VR_LO	SecondaryCaptureDeviceSoftwareVersion;
		VR_SH	VideoImageFormatAcquired;
		VR_LO	DigitalImageFormatAcquired;
	}; // End of class defination for: SCEquipmentModule

// C.8.6.2
// Class Module:SCImageModule
class	CO_SCImageModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_SCImageModule(CCO_Abstract *Composite=NULL);

		VR_DA	DateOfSecondaryCapture;
		VR_TM	TimeOfSecondaryCapture;
		VR_US	OverlayNumber;
		VR_DA	OverlayDate;
		VR_TM	OverlayTime;
		VR_SQ	ReferencedImageSequence;
	}; // End of class defination for: SCImageModule

// C.9.1
// Class Module:OverlayIdentificationModule
class	CO_OverlayIdentificationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_OverlayIdentificationModule(CCO_Abstract *Composite=NULL);

		VR_US	OverlayNumber;
		VR_DA	OverlayDate;
		VR_TM	OverlayTime;
		VR_SQ	ReferenceImageSequence;
	}; // End of class defination for: OverlayIdentificationModule

// C.9.2
// Class Module:OverlayPlaneModule
class	CO_OverlayPlaneModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_OverlayPlaneModule(CCO_Abstract *Composite=NULL);

		VR_US	Rows;
		VR_US	Columns;
		VR_CS	OverlayType;
		VR_SS	Origin;
		VR_US	BitsAllocated;
		VR_US	BitPosition;
		VR_OW	OverlayData;
		VR_IS	ROIArea;
		VR_DS	ROIMean;
		VR_DS	ROIStandardDeviation;
		VR_US	OverlayDescriptorGray;
		VR_US	OverlayDescriptorRed;
		VR_US	OverlayDescriptorGreen;
		VR_US	OverlayDescriptorBlue;
		VR_US	OverlaysGray;
		VR_US	OverlaysRed;
		VR_US	OverlaysGreen;
		VR_US	OverlaysBlue;
	}; // End of class defination for: OverlayPlaneModule

// C.9.3
// Class Module:MultiframeOverlayModule
class	CO_MultiframeOverlayModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_MultiframeOverlayModule(CCO_Abstract *Composite=NULL);

		VR_IS	NumberOfFramesInOverlay;
	}; // End of class defination for: MultiframeOverlayModule

// C.10.1
// Class Module:CurveIdentificationModule
class	CO_CurveIdentificationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_CurveIdentificationModule(CCO_Abstract *Composite=NULL);

		VR_US	CurveNumber;
		VR_DA	CurveDate;
		VR_TM	CurveTime;
		VR_SQ	ReferencedImageSequence;
		VR_SQ	ReferencedOverlaySequence;
		VR_SQ	ReferencedCurveSequence;
	}; // End of class defination for: CurveIdentificationModule

// Class Module:ReferencedOverlaySequence
class	CO_ReferencedOverlaySequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedOverlaySequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedOverlaySequence

// C.10.2
// Class Module:CurveModule
class	CO_CurveModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_CurveModule(CCO_Abstract *Composite=NULL);

		VR_US	CurveDimensions;
		VR_US	NumberOfPoints;
		VR_CS	TypeOfData;
		VR_US	DataValueRepresentation;
		VR_OX	CurveData;
		VR_LO	CurveDescription;
		VR_SH	AxisUnits;
		VR_SH	AxisLabels;
		VR_US	MinimumCoordinateValue;
		VR_US	MaximumCoordinateValue;
		VR_SH	CurveRange;
		VR_US	CurveDataDescriptor;
		VR_US	CoordinateStartValue;
		VR_US	CoordinateStepValue;
	}; // End of class defination for: CurveModule

// C.10.3
// Class Module:AudioModule
class	CO_AudioModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_AudioModule(CCO_Abstract *Composite=NULL);

		VR_US	AudioType;
		VR_US	AudioSampleFormat;
		VR_US	NumberOfChannels;
		VR_UL	NumberOfSamples;
		VR_UL	SampleRate;
		VR_UL	TotalTime;
		VR_OX	AudioSampleData;
		VR_SQ	ReferencedImageSequence;
		VR_LT	AudioComments;
	}; // End of class defination for: AudioModule

// C.11.1
// Class Module:ModalityLUTModule
class	CO_ModalityLUTModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ModalityLUTModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ModalityLUTSequence;
		VR_DS	RescaleIntercept;
		VR_DS	RescaleSlope;
		VR_LO	RescaleType;
	}; // End of class defination for: ModalityLUTModule

// Class Module:ModalityLUTSequence
class	CO_ModalityLUTSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ModalityLUTSequence(CCO_Abstract *Composite=NULL);

		VR_XS	LUTDescriptor;
		VR_LO	LUTExplanation;
		VR_LO	ModalityLUTType;
		VR_XS	LUTData;
	}; // End of class defination for: ModalityLUTSequence

// C.11.2
// Class Module:VOILUTModule
class	CO_VOILUTModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_VOILUTModule(CCO_Abstract *Composite=NULL);

		VR_SQ	VOILUTSequence;
		VR_DS	WindowCenter;
		VR_DS	WindowWidth;
		VR_LO	WindowCenterAndWidthExplanation;
	}; // End of class defination for: VOILUTModule

// Class Module:VOILUTSequence
class	CO_VOILUTSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_VOILUTSequence(CCO_Abstract *Composite=NULL);

		VR_XS	LUTDescriptor;
		VR_LO	LUTExplanation;
		VR_XS	LUTData;
	}; // End of class defination for: VOILUTSequence

// C.11.3
// Class Module:LUTIdentificationModule
class	CO_LUTIdentificationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_LUTIdentificationModule(CCO_Abstract *Composite=NULL);

		VR_IS	LUTNumber;
		VR_SQ	ReferencedImageSequence;
	}; // End of class defination for: LUTIdentificationModule

// C.12.1	
// Class Module:SOPCommonModule
class	CO_SOPCommonModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_SOPCommonModule(CCO_Abstract *Composite=NULL);

		VR_UI	SOPClassUID;
		VR_UI	SOPInstanceUID;
		VR_CS	SpecificCharacterSet;
		VR_DA	InstanceCreationDate;
		VR_TM	InstanceCreationTime;
		VR_UI	InstanceCreatorUID;
	}; // End of class defination for: SOPCommonModule

// C.13.1
// Class Module:BasicFilmSessionPresentationModule
class	CO_BasicFilmSessionPresentationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_BasicFilmSessionPresentationModule(CCO_Abstract *Composite=NULL);

		VR_IS	NumberOfCopies;
		VR_CS	PrintPriority;
		VR_CS	MediumType;
		VR_CS	FilmDestination;
		VR_LO	FilmSessionLabel;
		VR_IS	MemoryAllocation;
	}; // End of class defination for: BasicFilmSessionPresentationModule

// C.13.2
// Class Module:BasicFilmSessionRelationshipModule
class	CO_BasicFilmSessionRelationshipModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_BasicFilmSessionRelationshipModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ReferencedFilmBoxSequence;
	}; // End of class defination for: BasicFilmSessionRelationshipModule

// Class Module:ReferencedFilmBoxSequence
class	CO_ReferencedFilmBoxSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedFilmBoxSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedFilmBoxSequence

// C.13.3
// Class Module:BasicFilmBoxPresentationModule
class	CO_BasicFilmBoxPresentationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_BasicFilmBoxPresentationModule(CCO_Abstract *Composite=NULL);

		VR_ST	ImageDisplayFormat;
		VR_CS	AnnotationDisplayFormatID;
		VR_CS	FilmOrientation;
		VR_CS	FilmSizeID;
		VR_CS	MagnificationType;
		VR_CS	SmoothingType;
		VR_CS	BorderDensity;
		VR_CS	EmptyImageDensity;
		VR_US	MinDensity;
		VR_US	MaxDensity;
		VR_CS	Trim;
		VR_ST	ConfigurationInformation;
	}; // End of class defination for: BasicFilmBoxPresentationModule

// C.13.4
// Class Module:BasicFilmBoxRelationshipModule
class	CO_BasicFilmBoxRelationshipModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_BasicFilmBoxRelationshipModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ReferencedFilmSessionSequence;
		VR_SQ	ReferencedImageBoxSequence;
		VR_SQ	ReferencedBasicAnnotationBoxSequence;
	}; // End of class defination for: BasicFilmBoxRelationshipModule

// Class Module:ReferencedFilmSessionSequence
class	CO_ReferencedFilmSessionSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedFilmSessionSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedFilmSessionSequence

// Class Module:ReferencedImageBoxSequence
class	CO_ReferencedImageBoxSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedImageBoxSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedImageBoxSequence

// Class Module:ReferencedBasicAnnotationBoxSequence
class	CO_ReferencedBasicAnnotationBoxSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedBasicAnnotationBoxSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedBasicAnnotationBoxSequence

// C.13.5
// Class Module:ImageBoxPixelPresentationModule
class	CO_ImageBoxPixelPresentationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ImageBoxPixelPresentationModule(CCO_Abstract *Composite=NULL);

		VR_US	ImagePosition;
		VR_CS	Polarity;
		VR_CS	MagnificationType;
		VR_CS	SmoothingType;
		VR_DS	RequestedImageSize;
		VR_SQ	PreformattedGrayscaleImageSequence;
		VR_SQ	PreformattedColorImageSequence;
	}; // End of class defination for: ImageBoxPixelPresentationModule

// Class Module:PreformattedGrayscaleImageSequence
class	CO_PreformattedGrayscaleImageSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PreformattedGrayscaleImageSequence(CCO_Abstract *Composite=NULL);

		VR_US	SamplesPerPixel;
		VR_CS	PhotometricInterpretation;
		VR_US	Rows;
		VR_US	Columns;
		VR_IS	PixelAspectRatio;
		VR_US	BitsAllocated;
		VR_US	BitsStored;
		VR_US	HighBit;
		VR_US	PixelRepresentation;
		VR_OX	PixelData;
	}; // End of class defination for: PreformattedGrayscaleImageSequence

// Class Module:PreformattedColorImageSequence
class	CO_PreformattedColorImageSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PreformattedColorImageSequence(CCO_Abstract *Composite=NULL);

		VR_US	SamplesPerPixel;
		VR_CS	PhotometricInterpretation;
		VR_US	PlanarConfiguration;
		VR_US	Rows;
		VR_US	Columns;
		VR_IS	PixelAspectRatio;
		VR_US	BitsAllocated;
		VR_US	BitsStored;
		VR_US	HighBit;
		VR_US	PixelRepresentation;
		VR_OX	PixelData;
	}; // End of class defination for: PreformattedColorImageSequence

// C.13.6
// Class Module:ImageBoxRelationshipModule
class	CO_ImageBoxRelationshipModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ImageBoxRelationshipModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ReferencedImageSequence;
		VR_SQ	ReferencedImageOverlayBoxSequence;
		VR_SQ	ReferencedVOILUTSequence;
	}; // End of class defination for: ImageBoxRelationshipModule

// Class Module:ReferencedImageOverlayBoxSequence
class	CO_ReferencedImageOverlayBoxSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedImageOverlayBoxSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
		VR_UI	ReferencedFrameNumber;
	}; // End of class defination for: ReferencedImageOverlayBoxSequence

// Class Module:ReferencedVOILUTSequence
class	CO_ReferencedVOILUTSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedVOILUTSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
	}; // End of class defination for: ReferencedVOILUTSequence

// C.13.7
// Class Module:BasicAnnotationPresentationModule
class	CO_BasicAnnotationPresentationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_BasicAnnotationPresentationModule(CCO_Abstract *Composite=NULL);

		VR_US	AnnotationPosition;
		VR_LO	TextString;
	}; // End of class defination for: BasicAnnotationPresentationModule

// C.13.8
// Class Module:PrintJobModule
class	CO_PrintJobModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PrintJobModule(CCO_Abstract *Composite=NULL);

		VR_CS	ExecutionStatus;
		VR_CS	ExecutionStatusInfo;
		VR_DA	CreationDate;
		VR_TM	CreationTime;
		VR_CS	PrintPriority;
		VR_LO	PrinterName;
		VR_AE	Originator;
	}; // End of class defination for: PrintJobModule

// C.13.9
// Class Module:PrinterModule
class	CO_PrinterModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_PrinterModule(CCO_Abstract *Composite=NULL);

		VR_CS	PrinterStatus;
		VR_CS	PrinterStatusInfo;
		VR_LO	PrinterName;
		VR_LO	Manufacturer;
		VR_LO	ManufacturerModelName;
		VR_LO	DeviceSerialNumber;
		VR_LO	SoftwareVersions;
		VR_DA	DateOfLastCalibration;
		VR_TM	TimeOfLastCalibration;
	}; // End of class defination for: PrinterModule

// C.13.10
// Class Module:ImageOverlayBoxPresentationModule
class	CO_ImageOverlayBoxPresentationModule	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ImageOverlayBoxPresentationModule(CCO_Abstract *Composite=NULL);

		VR_SQ	ReferencedOverlayPlaneSequence;
		VR_CS	OverlayMagnificationType;
		VR_CS	OverlaySmoothingType;
		VR_CS	OverlayForegroundDensity;
		VR_CS	OverlayMode;
		VR_CS	ThresholdDensity;
	}; // End of class defination for: ImageOverlayBoxPresentationModule

// Class Module:ReferencedOverlayPlaneSequence
class	CO_ReferencedOverlayPlaneSequence	:
	virtual	public	CO_Abstract
	{
	public:
		BOOL	SetIf ( VR * );
		BOOL	Morph ( DICOMObject * );
		BOOL	Reset ();

		// Constuctor (to set VR group/element tags
		CO_ReferencedOverlayPlaneSequence(CCO_Abstract *Composite=NULL);

		VR_UI	ReferencedSOPClassUID;
		VR_UI	ReferencedSOPInstanceUID;
		VR_UI	ReferencedOverlayPlaneGroups;
	}; // End of class defination for: ReferencedOverlayPlaneSequence

#endif
