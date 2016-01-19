#include "StdAfx.h"

#include "MyListBox.h"

CMyListBox::CMyListBox()
{
	m_toolTipMessage = NULL;
}

CMyListBox::~CMyListBox()
{

}

BEGIN_MESSAGE_MAP(CMyListBox, CListBox)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



BOOL CMyListBox::CreateToolTip()
{
	if (NULL == m_toolTipMessage)
	{
		m_toolTipMessage = new CToolTipCtrl();
		if (m_toolTipMessage->Create(this, TTS_ALWAYSTIP|TTS_NOPREFIX))
		{
			m_toolTipMessage->Activate(TRUE);
			m_toolTipMessage->SetDelayTime(50);
			m_toolTipMessage->SetMaxTipWidth(500);
			m_toolTipMessage->SetTipTextColor(RGB(0,0,255));
			m_toolTipMessage->SetTipBkColor(RGB(255,255,255));
			m_toolTipMessage->AddTool(this);// 帮定控件tooltip
			//m_toolTipMessage->SetToolRect(this,0,&CRect(0,30,0,10));

			return TRUE;
		}
	}
	return FALSE;
}

void CMyListBox::SetTipMessage(CString &message)
{
	if (message.IsEmpty())
	{
		return ;
	}

	if (m_toolTipMessage->GetSafeHwnd() != NULL)
	{
		//m_toolTipMessage->UpdateTipText(message, this);  // 更新要显示的字符      
		m_toolTipMessage->AddTool(this, message);
	} 
	else
	{
		if (CreateToolTip())
		{
			m_toolTipMessage->AddTool(this, message);
		}
	}

	m_toolTipMessage->Activate(TRUE);
	
}

void CMyListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pt;// 当前鼠标所在位置
	GetCursorPos(&pt);
	ScreenToClient(&pt);// 转化为客户区的坐标

	CRect rect;// 控件的大小
	GetClientRect(&rect);
	BOOL inout;
	CString message;

	if (rect.PtInRect(pt))
	{
		int select = ItemFromPoint(pt, inout);// 鼠标所在的哪一条信息
		GetText(select, message);
		SetTipMessage(message);
	}

	CListBox::OnMouseMove(nFlags, point);
}

BOOL CMyListBox::PreTranslateMessage(MSG* pMsg)
{
	if (m_toolTipMessage->GetSafeHwnd() != NULL)
	{
		if (pMsg->message == WM_MOUSEMOVE)
		{
			m_toolTipMessage->RelayEvent(pMsg);
			SendMessage(WM_MOUSEMOVE);
		}
	}

	/*return CListBox::PreTranslateMessage(pMsg);*/
	return CWnd::PreTranslateMessage(pMsg);
}
