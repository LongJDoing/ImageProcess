
// ImageCalculate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CImageCalculateApp:
// �йش����ʵ�֣������ ImageCalculate.cpp
//

class CImageCalculateApp : public CWinApp
{
public:
	CImageCalculateApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CImageCalculateApp theApp;