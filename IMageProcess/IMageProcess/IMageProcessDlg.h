
// IMageProcessDlg.h : ͷ�ļ�
//

#pragma once
#include "MyMorphology.h"
#include "ConnectComponentLabel.h"
#include "DIdefine.h"
#include "queue.h"
#include "ImageOperate.h"
#include "K_Means.h"
#include "LeastQuadraticFiter.h"
#include "ISOData.h"
#include "MySlopeCluster.h"

// CIMageProcessDlg �Ի���
class CIMageProcessDlg : public CDialogEx
{
// ����
public:
	CIMageProcessDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IMAGEPROCESS_DIALOG };

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

	afx_msg void OnProcess1();
	afx_msg void OnProcess2();
	afx_msg void OnProcess3();
	afx_msg void OnProcess4();
	DECLARE_MESSAGE_MAP()

private:
	CMyMorphology * m_mymorphology;
	CImage * m_pImg;
	CConnectComponentLabel * m_pConnectComponentLabel;
	int m_Width, m_Height;
	int * labelmap;
	CImageOperate * m_myimageopreate;
	CK_Means * m_kmeans;
	CLeastQuadraticFiter * m_leastquadraticfiter;
	CISOData * m_isodata;
	CMySlopeCluster * m_myslopecluster;
public:
	
	void OnShow(CImage *);
	afx_msg void OnProcess5();
	afx_msg void OnProcess7();
};
