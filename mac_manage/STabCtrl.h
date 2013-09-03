#if !defined(AFX_STABCTRL_H__C4A9BD4C_0659_4ED5_9B91_8A4E454C0982__INCLUDED_)
#define AFX_STABCTRL_H__C4A9BD4C_0659_4ED5_9B91_8A4E454C0982__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// STabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// STabCtrl window

class STabCtrl : public CTabCtrl
{
	// Construction
	public:
		enum emTabPosition
		{
			TP_TOP, TP_BOTTOM, TP_RIGHT, TP_LEFT
		};

		STabCtrl();
		virtual ~STabCtrl();

		// Attributes
	public:

	private:
		COLORREF m_clrBorder;
		COLORREF m_clrShadow;
		COLORREF m_clrBack;


		CFont m_Font,m_FontBold;
		CRect m_rcTabs;
		CRect m_rcClient;

		tagDRAWITEMSTRUCT m_SelectedDrawItemStruct;

		// Operations
	public:

		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(STabCtrl)
	protected:
		virtual void PreSubclassWindow();
		virtual void DrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
		//}}AFX_VIRTUAL

		// Implementation
	public:
		UINT GetTabPosition();
		void SetTabPosition(UINT _pos);

		void DrawTab(LPDRAWITEMSTRUCT _lpDrawItemStruct);
		void DrawTabs(CDC* pDC);
    	afx_msg void OnSize(UINT nType, int cx, int cy);

		// Generated message map functions
	protected:
		//{{AFX_MSG(STabCtrl)
		afx_msg void OnPaint();
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STABCTRL_H__C4A9BD4C_0659_4ED5_9B91_8A4E454C0982__INCLUDED_)
