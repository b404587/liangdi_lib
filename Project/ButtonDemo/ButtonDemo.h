
// ButtonDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CButtonDemoApp:
// �йش����ʵ�֣������ ButtonDemo.cpp
//

class CButtonDemoApp : public CWinApp
{
public:
	CButtonDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CButtonDemoApp theApp;