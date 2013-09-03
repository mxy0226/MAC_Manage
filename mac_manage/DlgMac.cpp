// DlgMac.cpp : 实现文件
//

#include "stdafx.h"
#include "mac_manage.h"
#include "DlgMac.h"


// CDlgMac 对话框

IMPLEMENT_DYNAMIC(CDlgMac, CDialog)

CDlgMac::CDlgMac(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMac::IDD, pParent)
{

}

CDlgMac::~CDlgMac()
{
}

void CDlgMac::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_MacInfoTitle);
    DDX_Control(pDX, IDC_LIST1, m_MacInfo);
    DDX_Control(pDX, IDC_BUTTON2, m_MacAdd);
    DDX_Control(pDX, IDC_BUTTON3, m_MacDel);

}


BEGIN_MESSAGE_MAP(CDlgMac, CDialog)
    ON_BN_CLICKED(IDC_BUTTON2, &CDlgMac::OnBnClickedButton2)
    // for easysize
    ON_WM_SIZE()
	//ON_WM_SIZING()
    ON_BN_CLICKED(IDC_BUTTON3, &CDlgMac::OnBnClickedButton3)
END_MESSAGE_MAP()


BOOL CDlgMac::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// CDlgMac 消息处理程序
BOOL CDlgMac::Create(CWnd* pParentWnd, const RECT& rect, DWORD dwStyle) 
{
	int rtn;
	rtn = CDialog::Create(IDD, pParentWnd);

	if (0 != rtn) {
		m_hParent = pParentWnd;

		SetWindowPos(pParentWnd, rect.left, rect.top, rect.right, rect.bottom, dwStyle);

	}

    initList();
	m_MacInfo.DeleteAllItems();
    InsertInfo(0,L"0.0.0.0",L"0.0.0.0");
    InsertInfo(1,L"0.0.0.0",L"0.0.0.0");
    InsertInfo(2,L"0.0.0.0",L"0.0.0.0");

	return rtn;
}
void CDlgMac::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码
}


void CDlgMac::OnBnClickedButton3()
{
    // TODO: 在此添加控件通知处理程序代码
}
void CDlgMac::initList()
{
	LV_COLUMN lvcol;

	for (int i = 0; i < LST_MAC_COL_NUM; i++) {
		lvcol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcol.fmt = LVCFMT_LEFT;
		switch(i) {
			case LST_MAC_INDEX:
				lvcol.pszText = L"ID";
				lvcol.cx = 150;
				break;
			case LST_MAC_ADDR:
				lvcol.pszText = L"MAC地址";
				lvcol.cx = 300;
				break;
			case LST_MAC_MASK:
				lvcol.pszText = L"MASK";
				lvcol.cx = 170;
				break;

		}
		lvcol.iSubItem = i;
	    m_MacInfo.InsertColumn(i,&lvcol);
	}
	m_MacInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

    // TODO: 在此添加控件通知处理程序代码


}

void CDlgMac::InsertInfo(int itemIdx, CString macAddr, CString macMask)
{
	int i;
	LV_ITEM lvitem;
	CString strTemp;	

	for (i = 0; i < LST_MAC_COL_NUM; i++) {
		lvitem.mask = LVIF_TEXT;
		lvitem.iItem = itemIdx;
		lvitem.iSubItem = i;
        
        switch(i) {
            case LST_MAC_INDEX:
                strTemp.Format(L"%d", itemIdx);
                lvitem.pszText = strTemp.GetBuffer(strTemp.GetLength());
			    m_MacInfo.InsertItem(&lvitem);
                break;

            case LST_MAC_ADDR:
			    lvitem.pszText = macAddr.GetBuffer(macAddr.GetLength());
			    m_MacInfo.SetItem(&lvitem);
                break;

            case LST_MAC_MASK:
			    lvitem.pszText = macMask.GetBuffer(macMask.GetLength());
			    m_MacInfo.SetItem(&lvitem);
                break;
        }
	}
}

void CDlgMac::OnSize(UINT nType, int cx, int cy) 
{
    CRect rectL;

    //CFormView::OnSize(nType, cx, cy);

}

