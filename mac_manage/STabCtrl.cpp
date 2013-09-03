// STabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "STabCtrl.h"
#include "SGradient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// STabCtrl

STabCtrl::STabCtrl()
{
	m_clrBorder=RGB(135,155,179);
	m_clrShadow=RGB(198,197,201);
	m_clrBack=RGB(249,251,255);


	m_Font.CreateFont(-12,0,0,0,400,0,0,0,0,1,2,1,34,L"MS Sans Serif");
	m_FontBold.CreateFont(-12,2,0,0,FW_BOLD,0,0,0,0,1,2,1,34,L"MS Sans Serif");
}

STabCtrl::~STabCtrl()
{
}


BEGIN_MESSAGE_MAP(STabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(STabCtrl)
	ON_WM_PAINT()
    ON_WM_SIZE()
ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// STabCtrl message handlers

void STabCtrl::DrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect = lpDrawItemStruct->rcItem;
	//rect.top += ::GetSystemMetrics(SM_CYEDGE);

	int nTabIndex = lpDrawItemStruct->itemID;
	CRect rectItem=lpDrawItemStruct->rcItem;


	if (nTabIndex < 0) 
		return;

	BOOL bSelected = (nTabIndex == GetCurSel());

	UINT tab_position=GetTabPosition();


	COLORREF crSelected = GetSysColor(COLOR_BTNTEXT);
	COLORREF crNormal = GetSysColor(COLOR_BTNTEXT);
	COLORREF crDisabled = GetSysColor(COLOR_GRAYTEXT);

	TCHAR label[64];
	TC_ITEM item;
	item.mask = TCIF_TEXT|TCIF_IMAGE;
	item.pszText = label;     
	item.cchTextMax = 63;    	
	if (!GetItem(nTabIndex, &item))
		return;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	if (!pDC)
		return;

	int nSavedDC = pDC->SaveDC();


	POINT pt;

	//GetItemRect(nTabIndex, &rectItem);
	GetCursorPos(&pt);
	ScreenToClient(&pt);

	COLORREF low_color,high_color;
	SGradient::GetNextColor(nTabIndex,low_color,high_color);

	SGradient M(CSize(rect.Width(),rect.Height()));	

	switch (tab_position)
	{
		case TP_TOP:
			M.PrepareReverseVertColorTab(pDC,SGradient::GUISTYLE_2003,low_color,high_color);
			M.Draw(pDC,rect.left,rect.top,0,0,rect.Width(),rect.Height(),SRCCOPY);	
			break;
	}

	pDC->RestoreDC(nSavedDC);
}

void STabCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CTabCtrl::PreSubclassWindow();
	ModifyStyle(0, TCS_OWNERDRAWFIXED);
	SetFont(&m_Font);
}

void STabCtrl::OnPaint() 
{
	// TODO: Add your message handler code here
	CPaintDC dc(this); // device context for painting

	// Calculate Cilent Rect & Tabs Rect
	CRect tab_rc;
	for (int i=0;i<GetItemCount();i++)
	{
		GetItemRect(i,tab_rc);
		if (i==0)
			m_rcTabs=tab_rc;
		else
		{
			m_rcTabs.UnionRect(&m_rcTabs,&tab_rc);
		}
	}

	GetClientRect(m_rcClient);

	UINT tab_dir=GetTabPosition();
	switch (tab_dir)
	{
		case TP_TOP:
			m_rcClient.top=m_rcTabs.bottom+1;
			break;
		case TP_BOTTOM:
			m_rcClient.bottom=m_rcTabs.top-1;
			break;
		case TP_RIGHT:
			m_rcClient.right=m_rcTabs.left-1;
			break;
		case TP_LEFT:
			m_rcClient.left=m_rcTabs.right+1;
			break;
	}



	CPen pen(PS_SOLID,1,m_clrBorder);
	CBrush brush(m_clrBack);

	CBrush* p_old_brush=(CBrush*)dc.SelectObject(&brush);
	CPen* p_old_pen=(CPen*)dc.SelectObject(&pen);
	CFont* p_old_font=(CFont*)dc.SelectObject(&m_Font);

	//m_rcClient.DeflateRect(0,0,1,1);
	dc.Rectangle(m_rcClient);
	dc.Draw3dRect(m_rcClient.left,m_rcClient.right,
			m_rcClient.right,m_rcClient.bottom,m_clrBorder,m_clrShadow);
	dc.DrawFrameControl(m_rcClient,0,0);


	dc.SelectObject(p_old_brush);

	DrawTabs(&dc);

	dc.SelectObject(p_old_pen);
	dc.SelectObject(p_old_brush);
	dc.SelectObject(p_old_font);

	pen.DeleteObject();
	brush.DeleteObject();
	// Do not call CTabCtrl::OnPaint() for painting messages
}

UINT STabCtrl::GetTabPosition()
{
	DWORD window_style=GetStyle();
	UINT ret=TP_TOP;

	if (window_style&TCS_VERTICAL)
	{
		if (window_style&TCS_BOTTOM)
			ret=TP_RIGHT;
		else
			ret=TP_LEFT;
	}
	else
	{
		if (window_style&TCS_BOTTOM)
			ret=TP_BOTTOM;
	}

	return ret;
}

void STabCtrl::DrawTab(LPDRAWITEMSTRUCT _lpDrawItemStruct)
{
	int item_index= _lpDrawItemStruct->itemID;
	CRect item_rc= _lpDrawItemStruct->rcItem;
	UINT tab_position=GetTabPosition();

	item_rc.DeflateRect(1,1,1,1);

	// Get Item Information
	TCHAR item_text[64];
	TC_ITEM item;
	item.mask = TCIF_TEXT|TCIF_IMAGE;
	item.pszText = item_text;     
	item.cchTextMax = 63;   
	GetItem(item_index,&item);

	// Create CDC
	CDC* pDC = CDC::FromHandle(_lpDrawItemStruct->hDC);
	if (!pDC)
		return;

	int nSavedDC = pDC->SaveDC();


	// Fill Tab
	COLORREF low_color,high_color;
	SGradient::GetNextColor(item_index,low_color,high_color);

	SGradient M(CSize(item_rc.Width(),item_rc.Height()));	

	switch (tab_position)
	{
		case TP_TOP:
		case TP_BOTTOM:
			M.PrepareReverseVertColorTab(pDC,SGradient::GUISTYLE_2003,low_color,high_color);
			M.Draw(pDC,item_rc.left,item_rc.top,0,0,item_rc.Width(),item_rc.Height(),SRCCOPY);	
			break;
		case TP_LEFT:
		case TP_RIGHT:
			M.PrepareReverseHorzColorTab(pDC,SGradient::GUISTYLE_2003,low_color,high_color);
			M.Draw(pDC,item_rc.left,item_rc.top,0,0,item_rc.Width(),item_rc.Height(),SRCCOPY);	
			break;

	}


	// Draw Text

	pDC->SetBkMode(TRANSPARENT);

	switch (tab_position)
	{
		case TP_TOP:
		case TP_BOTTOM:
			pDC->DrawText(item_text,item_rc,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
			break;
		case TP_LEFT:
		case TP_RIGHT:
			{
				LOGFONT log_font;
				m_Font.GetLogFont(&log_font);

				if (tab_position==TP_LEFT)
					log_font.lfEscapement=900;
				else
					log_font.lfEscapement=2700;

				CFont font;
				font.CreateFontIndirect(&log_font);

				CFont* p_old_font=(CFont*)pDC->SelectObject(&font);
				CSize text_extend=pDC->GetTextExtent(item_text);


				switch (tab_position)
				{
					case TP_LEFT:
						pDC->ExtTextOut(item_rc.left+(item_rc.Width()-text_extend.cy)/2,
								item_rc.bottom-(item_rc.Height()-text_extend.cx)/2,ETO_CLIPPED,item_rc,
								item_text,NULL);
						break;
					case TP_RIGHT:
						pDC->ExtTextOut(item_rc.right-(item_rc.Width()-text_extend.cy)/2,
								item_rc.top+(item_rc.Height()-text_extend.cx)/2,ETO_CLIPPED,
								item_rc,item_text,NULL);
						break;

				}

				pDC->SelectObject(p_old_font);
				font.DeleteObject();

			}
			break;
	}

	pDC->SetBkMode(OPAQUE);

	pDC->RestoreDC(nSavedDC);
}

void STabCtrl::DrawTabs(CDC *pDC)
{
	CRect tab_rc,selected_item_rc;
	UINT selected_item=0;

	tagDRAWITEMSTRUCT drawitem;
	drawitem.hDC = pDC->GetSafeHdc();

	UINT tab_position=GetTabPosition();
	for (int i=0;i<GetItemCount();i++)
	{
		GetItemRect(i,tab_rc);

		if (i==GetCurSel())
		{
			selected_item=i;
			selected_item_rc=tab_rc;
			selected_item_rc.InflateRect(2,2,2,2);
			continue;
		}

		switch (tab_position)
		{
			case TP_TOP:
				tab_rc.DeflateRect(1,1,1,-2);
				break;
			case TP_BOTTOM:
				tab_rc.DeflateRect(1,-2,1,1);
				break;
			case TP_LEFT:
				tab_rc.DeflateRect(1,1,-2,1);
				break;
			case TP_RIGHT:
				tab_rc.DeflateRect(-2,1,1,1);
				break;
		}

		pDC->Rectangle(tab_rc);

		drawitem.itemID=i;
		drawitem.rcItem = tab_rc;

		DrawTab(&drawitem);
	}


	pDC->Rectangle(selected_item_rc);

	switch (tab_position)
	{
		case TP_TOP:
			selected_item_rc.InflateRect(0,0,0,1);
			break;
		case TP_BOTTOM:
			selected_item_rc.InflateRect(0,1,0,0);
			break;
		case TP_LEFT:
			selected_item_rc.InflateRect(0,0,1,0);
			break;
		case TP_RIGHT:
			selected_item_rc.DeflateRect(1,0,0,0);
			break;
	}

	drawitem.itemID=selected_item;
	drawitem.rcItem = selected_item_rc;
	DrawTab(&drawitem);
}

void STabCtrl::SetTabPosition(UINT _pos)
{
	switch (_pos)
	{
		case TP_TOP:
			ModifyStyle(TCS_BOTTOM|TCS_VERTICAL,NULL);
			break;
		case TP_BOTTOM:
			ModifyStyle(TCS_VERTICAL,TCS_BOTTOM,NULL);
			break;
		case TP_LEFT:
			ModifyStyle(TCS_BOTTOM,TCS_VERTICAL,NULL);
			break;
		case TP_RIGHT:
			ModifyStyle(0,TCS_BOTTOM|TCS_VERTICAL);
			break;
	}
}

int STabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here

	return 0;
}
void STabCtrl::OnSize(UINT nType, int cx, int cy) 
{

}

