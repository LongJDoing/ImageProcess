#pragma once

#include "DicomReadDlg.h" //涉及头文件相互引用的问题
#include "MyListBox.h"

// CPage1 dialog
//class CMyListBox;
class CDicomReadDlg;
class CPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage1();

// Dialog Data.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CMyListBox m_listbox;
	afx_msg void OnBnClickedRadioWcenter();
	afx_msg void OnBnClickedRadioWwidth();
	virtual BOOL OnInitDialog();

    void AdjustListBox();
	void ShowDicomInfo(char * path);
    CDicomReadDlg * m_pDlg;
	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

