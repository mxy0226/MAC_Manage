#pragma once


// CDlgMac 对话框
typedef enum{
    LST_MAC_INDEX = 0,
    LST_MAC_ADDR,
    LST_MAC_MASK,
    LST_MAC_COL_NUM
}MAC_ListCtrl;

class CDlgMac : public CDialog
{

	DECLARE_DYNAMIC(CDlgMac)

public:
	CDlgMac(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMac();

// 对话框数据
	enum { IDD = IDD_DIALOGBAR1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

public:
	CWnd *m_hParent;
    BOOL Create(CWnd* pParentWnd, const RECT& rect, DWORD dwStyle);

public:
	CStatic	    m_MacInfoTitle;
	CListCtrl   m_MacInfo;
	CButton     m_MacAdd;
	CButton     m_MacDel;

        
    void initList();
    void InsertInfo(int itemIdx, CString ipAddr, CString macMask);
	afx_msg void OnSize(UINT nType, int cx, int cy);

    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
};
