// mac_manage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmac_manageApp:
// �йش����ʵ�֣������ mac_manage.cpp
//

class Cmac_manageApp : public CWinApp
{
public:
	Cmac_manageApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmac_manageApp theApp;

CWnd*   GetMainFrmPointer(void);
void CMMessageBox(const TCHAR *fmt, ...);
