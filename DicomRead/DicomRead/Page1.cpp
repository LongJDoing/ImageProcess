// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "DicomRead.h"
#include "Page1.h"


// CPage1 dialog

IMPLEMENT_DYNAMIC(CPage1, CDialogEx)

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPage1::IDD, pParent)
{
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
}


BEGIN_MESSAGE_MAP(CPage1, CDialog)
	ON_BN_CLICKED(IDC_RADIO_WCENTER, &CPage1::OnBnClickedRadioWcenter)
	ON_BN_CLICKED(IDC_RADIO_WWIDTH, &CPage1::OnBnClickedRadioWwidth)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

BOOL CPage1::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pDlg = (CDicomReadDlg*)GetParent()->GetParent();

	CButton *pButton = (CButton*)GetDlgItem(IDC_RADIO_WCENTER);
	pButton->SetCheck(TRUE);

	CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_WCENTER);
	pSlidCtrl->SetRange(0,4096);
	pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_WWIDTH);
	pSlidCtrl->SetRange(0,4096*2);

	return TRUE;
}

void CPage1::ShowDicomInfo(char*path)
{
	CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_WCENTER);
	pSlidCtrl->SetPos(m_pDlg->m_nWindowCenter);
	pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_WWIDTH);
	pSlidCtrl->SetPos(m_pDlg->m_nWindowWidth);


	m_listbox.ResetContent();

    RTC	*spRtc = m_pDlg->m_spRtc;
	PDU_Service *spPduServ = m_pDlg->m_pPDU;
	DICOMDataObject *spDDO = m_pDlg->m_pDICOMData;

	CString str;
	CString str1;

	if (spDDO)
	{
		VR * spVr = spDDO->Pop();
		char desc[128];
		char text[256];
		UINT16 typecode = 0;
		while (spVr)
		{
			memset(desc, 0, sizeof(desc));
			memset(text, 0, sizeof(text));
			typecode = spRtc->RunTimeClass(spVr->Group, spVr->Element, desc);

			str1 = desc;
			switch(typecode)
			{
			case 'SL':
				//cout<<*(INT32*)(spVr->Data)<<endl;
				str.Format(_T("%d"),*(INT32*)(spVr->Data));
				//sout << *static_cast<INT16*>(spVr->Data);
				break;
			case 'SS':
				//cout<<*(INT16*)(spVr->Data)<<endl;
				break;
			case 'UL':
				//cout<<*(UINT32*)(spVr->Data)<<endl;
				break;
			case 'US':
				//cout<<*(UINT16*)(spVr->Data)<<endl;
				break;
			case 'SQ':
				//cout<<"sequence Item"<<endl;
				break;
			case 'OW':
				//cout<<"no value available"<<endl;
				break;
			default:
				if (spVr->Length <= 256)
				{
					memcpy(text, spVr->Data, spVr->Length);
					//cout << text << endl;
					str = text;
					//sout<<text;
				}
				else
				{
					//cout <<"not enough space\t" << endl;
				}
		    }

			spVr = spDDO->Pop();
			str = str1 +" : "+str;
			m_listbox.AddString(str);

			UpdateData(FALSE);
		}
	}
	AdjustListBox();
}


void CPage1::AdjustListBox()
{
	int dx=0; 
	CSize   sz; 
	CDC* pDC =   m_listbox.GetDC(); 

	CString   str; 
	for(int j= 0; j < m_listbox.GetCount();j++) 
	{ 
		m_listbox.GetText(j,   str); 
		sz   =   pDC-> GetTextExtent(str); 
		if   (   sz.cx   >   dx   ) 
			dx   =   sz.cx; 
	} 
	m_listbox.ReleaseDC(pDC); 
	m_listbox.SetHorizontalExtent(dx);
}

void CPage1::OnBnClickedRadioWcenter()
{
	m_pDlg->m_bFlag = TRUE;
}

void CPage1::OnBnClickedRadioWwidth()
{
	m_pDlg->m_bFlag = FALSE;
};

void CPage1::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_WCENTER);

    m_pDlg->m_nWindowCenter = pSlidCtrl->GetPos();

	pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_WWIDTH);

	m_pDlg->m_nWindowWidth = pSlidCtrl->GetPos();

	m_pDlg->ShowImage();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
