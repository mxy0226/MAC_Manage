// mac_manageDlg.h : 头文件
//

#pragma once
#include "DlgBs.h"
#include "DlgMac.h"
#include "STabCtrl.h"
enum emTabMenu
{
	eTabBs=0,
	eTabMac,
	eTabMenuNum,
};

enum emLedColor
{
	eLedRed=0,
	eLedGreen,
};

// Cmac_manageDlg 对话框
class Cmac_manageDlg : public CDialog
{
// 构造
public:
	Cmac_manageDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAC_MANAGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()


public:
    CDlgBs  m_DlgBs;
    CDlgMac m_DlgMac;
    CDialog*m_TabDlgs[eTabMenuNum];
    void    CreateTab();
    void    CloseTab();
    void    SelectTab(int nPage);
    int		GetSelectTab()		{return m_nCurTab;}
	virtual BOOL DestroyWindow();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	STabCtrl	m_tab_menu;

private:
	BOOL    m_bChangeTab;
	int	    m_nCurTab;
	int	    m_nPreChangedTab;

    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
