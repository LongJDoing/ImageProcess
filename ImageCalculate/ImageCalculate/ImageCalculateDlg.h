
// ImageCalculateDlg.h : ͷ�ļ�
//

#pragma once
#include "Calculate.h"
#include "ConnectComponentLabel.h"


// CImageCalculateDlg �Ի���
class CImageCalculateDlg : public CDialogEx
{
// ����
public:
	CImageCalculateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IMAGECALCULATE_DIALOG };

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
public:
	afx_msg void OnInput();
	CImage *m_pImage;
	void OnShow(CImage *);
	int * labelmap; // ���ͼ
	int m_labelIndex; // ��ǵĸ���
	int m_MaxlabelIndex; //���ı��ֵ
	int m_MaxArea; // ������
	bool b_input; 
	bool b_input2; //��������ͼ2

	CConnectComponentLabel *m_pConnectComponentLabel;
	CCalculate *m_pCalculate;
	afx_msg void OndLabel();
	afx_msg void OnMean();
	afx_msg void OnArea();
	afx_msg void OnVariance();
};
