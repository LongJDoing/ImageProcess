
// DicomReadDlg.h : ͷ�ļ�
//
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "atlimage.h"
#include "Page1.h"
#include "Page2.h"

#include "dicom.hpp"

class PDU_Service;
class DICOMDataObject;
class CPage1;
class CPage2;

// CDicomReadDlg �Ի���
class CDicomReadDlg : public CDialogEx
{
// ����
public:
	CDicomReadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DICOMREAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//���ڿؼ�����
private:
	CTabCtrl m_tabMain;
	CPage1 * m_page1;
	CPage2 * m_page2;

public:
	int m_nWindowCenter;
	int m_nWindowWidth;
	int m_nCol;
	int m_nRow;

	CImage *m_pImage;
	CDC* m_pDC;
	CRect m_rect;
	CMenu m_menu;
	bool m_bFlag;//�жϹ��ֲ���
	CString m_path;
	CString m_Ext;

	RTC	*m_spRtc;
	PDU_Service*					m_pPDU;
	DICOMDataObject*				m_pDICOMData;
	int *m_pStoreData; // �洢DICOM����
 	int *m_pData;
	CPoint m_myPoint;

	CString m_szPatientName;
	CString m_szPatientSex;
	CString m_szInstitutionName;
	CString m_szStudyDescription;
	CString m_szPhotoMetric;

public:
	void Initialization();
	void ShowImage();
	int GetPixelValue(int i,int j);
	void RestoreData();
    BOOL dump();
public:
	afx_msg void OnTcnSelchangeTabmain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileDump();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
};
