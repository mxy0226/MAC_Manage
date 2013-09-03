#pragma once


// CDlgBs 对话框
typedef enum{
    LST_BS_INDEX = 0,
    LST_BS_IP,
    LST_BS_STATUS,
    LST_BS_COL_NUM
}BS_ListCtrl;
class CDlgBs : public CDialog
{
	DECLARE_DYNAMIC(CDlgBs)

public:
	CDlgBs(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBs();

// 对话框数据
	enum { IDD = IDD_DIALOGBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CWnd *m_hParent;
    int  BsNu;
    BOOL Create(CWnd* pParentWnd, const RECT& rect, DWORD dwStyle);

	CStatic	    m_BsInfoTitle;
	CListCtrl   m_BsInfo;
	CButton     m_BsAdd;
	CButton     m_BsDel;
	CButton     m_BsFlush_BS;
	CButton     m_BsUpdate_Data;

	afx_msg void OnSize(UINT nType, int cx, int cy);
    void initList();
    void InsertInfo(int itemIdx, CString ipAddr, int Status);

};
