// mac_manageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mac_manage.h"
#include "mac_manageDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cmac_manageDlg 对话框




Cmac_manageDlg::Cmac_manageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cmac_manageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmac_manageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab_menu);

}

BEGIN_MESSAGE_MAP(Cmac_manageDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

    ON_WM_SIZE()

	//}}AFX_MSG_MAP
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &Cmac_manageDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()

// Cmac_manageDlg 消息处理程序

BOOL Cmac_manageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    initSyslog();
    log_level(3);
	CreateTab();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cmac_manageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cmac_manageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR Cmac_manageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cmac_manageDlg::CreateTab()
{
	CWnd *pParent = CWnd::FromHandle(m_hWnd);
	TCHAR mcStr[1024];
	TCITEM tie; 
	RECT rtView, rtTab, rtItem;
	int tabIdx = 0;
	BOOL rtn;

	tie.mask = TCIF_TEXT | TCIF_IMAGE; 
	tie.iImage = -1;
	tie.pszText = mcStr;

	wcscpy(mcStr,L"基站列表");
	m_tab_menu.InsertItem(tabIdx, &tie);
	m_TabDlgs[tabIdx] = &m_DlgBs;
	tabIdx++;

	wcscpy(mcStr,L"MAC列表");
	m_tab_menu.InsertItem(tabIdx, &tie);
	m_TabDlgs[tabIdx] = &m_DlgMac;
	tabIdx++;	

	::GetWindowRect(m_hWnd, &rtView);
	::GetWindowRect(m_tab_menu.m_hWnd, &rtTab);
	m_tab_menu.GetItemRect(0, &rtItem);

    xprintf(SDK_DBG,"GetWindowRect Viw: %d %d %d %d",rtView.left, rtView.top, rtView.right, rtView.bottom);
    xprintf(SDK_DBG,"GetWindowRect tab: %d %d %d %d",rtTab.left, rtTab.top, rtTab.right, rtTab.bottom);
    xprintf(SDK_DBG,"GetItemRect   tab: %d %d %d %d",rtItem.left, rtItem.top, rtItem.right, rtItem.bottom);
/*
	rtItem.left += (rtTab.left - rtView.left) + 0;
	rtItem.top +=  rtItem.bottom +50;
	rtItem.right = 0;
	rtItem.bottom = 0;

	rtn = m_DlgBs.Create(pParent, rtItem, SWP_NOSIZE|SWP_NOZORDER);

*/
	
	rtItem.left += (rtTab.left - rtView.left);
	rtItem.top +=  rtItem.bottom ;
	rtItem.right =  rtTab.right-rtItem.left;
	rtItem.bottom = rtTab.bottom-rtItem.top;
	
    xprintf(SDK_DBG,"create tab: %d %d %d %d",rtItem.left, rtItem.top, rtItem.right, rtItem.bottom);
	//rtn = m_DlgBs.Create(pParent, rtItem, SWP_NOZORDER);
	rtn = m_DlgBs.Create(pParent, rtItem, SWP_SHOWWINDOW);
	if (FALSE == rtn) {
		CMMessageBox(L"m_DlgBs.Create FAIL\n");
		return;
	}

	rtn = m_DlgMac.Create(pParent, rtItem, SWP_HIDEWINDOW);
	if (FALSE == rtn) {
		CMMessageBox(L"m_DlgMac.Create FAIL\n");
		return;
	}
}

void Cmac_manageDlg::CloseTab()
{
	CWnd *pParent = CWnd::FromHandle(m_hWnd);

	m_DlgBs.DestroyWindow();
	m_DlgMac.DestroyWindow();
}

void Cmac_manageDlg::SelectTab(int nPage)
{
	RECT rtView, rtTab, rtItem;
	m_tab_menu.GetItemRect(0, &rtItem);
	m_tab_menu.GetWindowRect(&rtTab);

	::GetWindowRect(m_hWnd, &rtView);
	::GetWindowRect(m_tab_menu.m_hWnd, &rtTab);
	m_tab_menu.GetItemRect(0, &rtItem);

	rtItem.left += (rtTab.left - rtView.left);
	rtItem.top +=  rtItem.bottom ;
	rtItem.right =  rtTab.right-rtItem.left;
	rtItem.bottom = rtTab.bottom-rtItem.top;

	SetFocus();
	for (int i = 0; i < sizeof(m_TabDlgs)/sizeof(m_TabDlgs[0]); i++) {
		if (m_TabDlgs[i]) {
			if (i == nPage)
				m_TabDlgs[i]->ShowWindow(SW_SHOW);
        		//SetWindowPos(m_TabDlgs[i], rtItem.left, rtItem.top, rtItem.right, rtItem.bottom, SWP_SHOWWINDOW);
			else
				m_TabDlgs[i]->ShowWindow(SW_HIDE);
        		//SetWindowPos(m_TabDlgs[i], rtItem.left, rtItem.top, rtItem.right, rtItem.bottom, SWP_HIDEWINDOW);
		}


	}
}
BOOL Cmac_manageDlg::DestroyWindow()
{

	CloseTab();
	CDialog::DestroyWindow();

	return TRUE;
}

void Cmac_manageDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
	int nPage;

	nPage = TabCtrl_GetCurSel(pNMHDR->hwndFrom); 

	m_nCurTab = nPage;
	SelectTab(nPage);




    *pResult = 0;
}

void Cmac_manageDlg::OnSize(UINT nType, int cx, int cy) 
{
#if 0
if(AllocConsole())
{
    freopen("CONOUT$","w",stdout);
    printf("AllocConsole [OK]\n");
}
#endif


    if (m_tab_menu.m_hWnd) {

        RECT rcClient, rcWindow,rtTab,rtItem;
        POINT ptDiff;


    	m_tab_menu.GetWindowRect(&rtTab);
        ::GetClientRect(m_tab_menu.m_hWnd, &rcClient);
    	m_tab_menu.GetItemRect(0, &rtItem);
        
        m_tab_menu.MoveWindow(rcClient.left, rcClient.top,rcClient.right,rcClient.bottom,1);   
        if ((CDlgBs*)(m_TabDlgs[0])->GetSafeHwnd()) {
            ((CDlgBs*)(m_TabDlgs[0]))->MoveWindow(rcClient.left, rcClient.top+rtItem.top,rcClient.right, rcClient.bottom);
            ((CDlgBs*)(m_TabDlgs[0]))->OnSize(nType, cx, cy);
        }

    }
    //CFormView::OnSize(nType, cx, cy);
#if 0
    if(m_listCtrl.m_hWnd)    {
        if(firstRefreshSrcoll)
            m_listCtrl.MoveWindow(0,0,cx - 20,cy-40,1);   
        else
            m_listCtrl.MoveWindow(0,0,cx,cy-40,1);   
    }

    if(button1.m_hWnd)
       button1.MoveWindow(cx/2-40, cy-30,80,25,1);   


    if (m_TabDlgs[0]->m_hWnd)
        m_TabDlgs[0]->MoveWindow(cx/2-40, cy,40,20,1);

    if (m_TabDlgs[1]->m_hWnd)
        m_TabDlgs[1]->MoveWindow(cx/2-40, cy,40,20,1);

#endif


    
}
