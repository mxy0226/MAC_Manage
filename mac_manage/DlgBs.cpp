// DlgBs.cpp : 实现文件
//

#include "stdafx.h"
#include "mac_manage.h"
#include "DlgBs.h"


// CDlgBs 对话框

IMPLEMENT_DYNAMIC(CDlgBs, CDialog)

CDlgBs::CDlgBs(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBs::IDD, pParent)
{
    BsNu = 0;
}

CDlgBs::~CDlgBs()
{
}

void CDlgBs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_BsInfoTitle);
    DDX_Control(pDX, IDC_LIST1, m_BsInfo);
    DDX_Control(pDX, IDC_BUTTON1, m_BsAdd);
    DDX_Control(pDX, IDC_BUTTON2, m_BsDel);
    DDX_Control(pDX, IDC_BUTTON3, m_BsFlush_BS);
    DDX_Control(pDX, IDC_BUTTON4, m_BsUpdate_Data);

}


BEGIN_MESSAGE_MAP(CDlgBs, CDialog)
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgBs 消息处理程序
BOOL CDlgBs::Create(CWnd* pParentWnd, const RECT& rect, DWORD dwStyle) 
{
	int rtn;
	rtn = CDialog::Create(IDD, pParentWnd);

	if (0 != rtn) {
		m_hParent = pParentWnd;

		SetWindowPos(pParentWnd, rect.left, rect.top, rect.right, rect.bottom, dwStyle);

	}

    initList();
	m_BsInfo.DeleteAllItems();
    InsertInfo(0,L"0.0.0.0",1);
    InsertInfo(1,L"0.0.0.0",1);
    InsertInfo(2,L"0.0.0.0",0);
	return rtn;
}

void CDlgBs::initList()
{
	LV_COLUMN lvcol;

	for (int i = 0; i < LST_BS_COL_NUM; i++) {
		lvcol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcol.fmt = LVCFMT_LEFT;
		switch(i) {
			case LST_BS_INDEX:
				lvcol.pszText = L"ID";
				lvcol.cx = 150;
				break;
			case LST_BS_IP:
				lvcol.pszText = L"IP地址";
				lvcol.cx = 300;
				break;
			case LST_BS_STATUS:
				lvcol.pszText = L"状态";
				lvcol.cx = 170;
				break;

		}
		lvcol.iSubItem = i;
	    m_BsInfo.InsertColumn(i,&lvcol);
	}
	m_BsInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

    // TODO: 在此添加控件通知处理程序代码


}

void CDlgBs::InsertInfo(int itemIdx, CString ipAddr, int Status)
{
	int i;
	LV_ITEM lvitem;
	CString strTemp;	

	for (i = 0; i < LST_BS_COL_NUM; i++) {
		lvitem.mask = LVIF_TEXT;
		lvitem.iItem = itemIdx;
		lvitem.iSubItem = i;
        
        switch(i) {
            case LST_BS_INDEX:
                strTemp.Format(L"%d", itemIdx);
                lvitem.pszText = strTemp.GetBuffer(strTemp.GetLength());
			    m_BsInfo.InsertItem(&lvitem);
                break;

            case LST_BS_IP:
			    lvitem.pszText = ipAddr.GetBuffer(ipAddr.GetLength());
			    m_BsInfo.SetItem(&lvitem);
                break;

            case LST_BS_STATUS:
                if (Status==0)
                    strTemp.Format(L"off");
                else
                    strTemp.Format(L"on");

                lvitem.pszText = strTemp.GetBuffer(strTemp.GetLength());
			    m_BsInfo.SetItem(&lvitem);
                break;
        }
	}
}

void CDlgBs::OnSize(UINT nType, int cx, int cy) 
{
    CRect rectL;
    CRect clirect;

    xprintf(SDK_DBG,"-->BS OnSize: %d , %d", cx, cy);
    
    this->GetClientRect(&clirect);
    xprintf(SDK_DBG, "this: (%d,%d),(%d,%d)",clirect.left, clirect.top, clirect.right, clirect.bottom);

#if 1
    if(m_BsInfoTitle.m_hWnd) {
        m_BsInfoTitle.GetWindowRect(&rectL);
        m_BsInfoTitle.ScreenToClient(&rectL);
        xprintf(SDK_DBG,"m_BsInfoTitle GetClientRect: %d %d %d %d",rectL.left, rectL.top, rectL.right, rectL.bottom);
        m_BsInfoTitle.MoveWindow(rectL.left, rectL.top,(cx-12),(cy-20),1); 
        m_BsInfoTitle.GetWindowRect(&rectL);
 
    }

    if(m_BsInfo.m_hWnd) {
        m_BsInfo.GetWindowRect(&rectL);
        this->ScreenToClient(rectL);

        m_BsInfo.MoveWindow(rectL.left, rectL.top,(cx-27),(cy-40),1);   
        m_BsInfo.GetWindowRect(&rectL);
 

    }

    if(m_BsAdd.m_hWnd) {
        m_BsAdd.MoveWindow(0, (cy-20),50,14,1);   
        m_BsAdd.GetWindowRect(&rectL);
 
    }
    if(m_BsDel.m_hWnd) {
        m_BsDel.MoveWindow(60, (cy-20),50,14,1);   
        m_BsDel.GetWindowRect(&rectL);

    }
    if(m_BsFlush_BS.m_hWnd) {
        m_BsFlush_BS.MoveWindow(120, (cy-20),50,14,1);   
        m_BsFlush_BS.GetWindowRect(&rectL);

    }
    if(m_BsUpdate_Data.m_hWnd) {
        m_BsUpdate_Data.MoveWindow(180, (cy-20),50,14,1);   
        m_BsUpdate_Data.GetWindowRect(&rectL);

    }
#else
    if(m_BsInfoTitle.m_hWnd) {
        m_BsInfoTitle.MoveWindow(2, 2,(cx-12),(cy-20),1); 
        xprintf(SDK_DBG,"title:%d %d(%d %d)",2,2,cx-12,cy-20);
        m_BsInfoTitle.GetWindowRect(&rectL);
        xprintf(SDK_DBG, "m_BsInfoTitle: (%d,%d),(%d,%d)",rectL.left, rectL.top, rectL.right, rectL.bottom);

    }

    if(m_BsInfo.m_hWnd) {
        m_BsInfo.MoveWindow(8, 15,(cx-27),(cy-40),1);   
        xprintf(SDK_DBG,"info:%d %d(%d %d)",8,15,cx-27,cy-40);
        m_BsInfo.GetWindowRect(&rectL);
        xprintf(SDK_DBG, "m_BsInfo: (%d,%d),(%d,%d)",rectL.left, rectL.top, rectL.right, rectL.bottom);

    }

    if(m_BsAdd.m_hWnd) {
        m_BsAdd.MoveWindow(0, (cy-21),50,14,1);   
        xprintf(SDK_DBG,"add:%d %d(%d %d)",0,cy-21,50,14);
        m_BsAdd.GetWindowRect(&rectL);
        xprintf(SDK_DBG, "m_BsAdd: (%d,%d),(%d,%d)",rectL.left, rectL.top, rectL.right, rectL.bottom);
    }
    if(m_BsDel.m_hWnd) {
        m_BsDel.MoveWindow(60, (cy-20),50,14,1);   
        xprintf(SDK_DBG,"del:%d %d(%d %d)",60,cy-21,50,14);
        m_BsDel.GetWindowRect(&rectL);
        xprintf(SDK_DBG, "m_BsDel: (%d,%d),(%d,%d)",rectL.left, rectL.top, rectL.right, rectL.bottom);
    }
    if(m_BsFlush_BS.m_hWnd) {
        m_BsFlush_BS.MoveWindow(120, (cy-20),50,14,1);   
        xprintf(SDK_DBG,"flush:%d %d(%d %d)",120,cy-21,50,14);
        m_BsFlush_BS.GetWindowRect(&rectL);
        xprintf(SDK_DBG, "m_BsFlush_BS: (%d,%d),(%d,%d)",rectL.left, rectL.top, rectL.right, rectL.bottom);
    }
    if(m_BsUpdate_Data.m_hWnd) {
        m_BsUpdate_Data.MoveWindow(180, (cy-20),50,14,1);   
        xprintf(SDK_DBG,"update:%d %d(%d %d)",180,cy-21,50,14);

        m_BsUpdate_Data.GetWindowRect(&rectL);
        xprintf(SDK_DBG, "m_BsUpdate_Data: (%d,%d),(%d,%d)",rectL.left, rectL.top, rectL.right, rectL.bottom);
    }

#endif
}

