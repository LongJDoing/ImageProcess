
// ImageCalculateDlg.h : 头文件
//

#pragma once
#include "Calculate.h"
#include "ConnectComponentLabel.h"


// CImageCalculateDlg 对话框
class CImageCalculateDlg : public CDialogEx
{
// 构造
public:
	CImageCalculateDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IMAGECALCULATE_DIALOG };

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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInput();
	CImage *m_pImage;
	void OnShow(CImage *);
	int * labelmap; // 标记图
	int m_labelIndex; // 标记的个数
	int m_MaxlabelIndex; //最大的标记值
	int m_MaxArea; // 最大面积
	bool b_input; 
	bool b_input2; //导入质量图2

	CConnectComponentLabel *m_pConnectComponentLabel;
	CCalculate *m_pCalculate;
	afx_msg void OndLabel();
	afx_msg void OnMean();
	afx_msg void OnArea();
	afx_msg void OnVariance();
};
