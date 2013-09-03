// mac_manage.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "mac_manage.h"
#include "mac_manageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmac_manageApp

BEGIN_MESSAGE_MAP(Cmac_manageApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cmac_manageApp ����

Cmac_manageApp::Cmac_manageApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Cmac_manageApp ����

Cmac_manageApp theApp;


// Cmac_manageApp ��ʼ��

BOOL Cmac_manageApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	Cmac_manageDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


CWnd *GetMainFrmPointer(void)
{
	Cmac_manageDlg* pDlg = (Cmac_manageDlg *)theApp.m_pMainWnd;

	return pDlg;
}

void CMMessageBox(const TCHAR *fmt, ...)
{
	va_list args;
	TCHAR szBuf[1024];

	va_start(args, fmt);
	vswprintf(szBuf, fmt, args);

	AfxMessageBox(szBuf);
	va_end(args);
}
