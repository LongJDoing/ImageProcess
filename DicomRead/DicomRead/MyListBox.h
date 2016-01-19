#pragma once

class CMyListBox : public CListBox
{
public:
	CMyListBox();
	~CMyListBox();

	BOOL CreateToolTip();

	void SetTipMessage(CString &message);

	CToolTipCtrl     *m_toolTipMessage;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};