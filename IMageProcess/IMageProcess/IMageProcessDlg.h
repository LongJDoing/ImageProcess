
// IMageProcessDlg.h : 头文件
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

// CIMageProcessDlg 对话框
class CIMageProcessDlg : public CDialogEx
{
// 构造
public:
	CIMageProcessDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IMAGEPROCESS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
