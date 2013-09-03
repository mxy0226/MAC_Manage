// SGradient.h: interface for the SGradient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SGRADIENT_H__87FFC4DE_D258_4707_AEEC_A6C8E506BBF4__INCLUDED_)
#define AFX_SGRADIENT_H__87FFC4DE_D258_4707_AEEC_A6C8E506BBF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SGradient  
{
	public:
		enum 
		{
			GUISTYLE_XP,GUISTYLE_2003
		};

	public:
		SGradient(CSize=CSize(800,600));
		virtual ~SGradient();

		//members
		virtual void PrepareVertical(CDC* pDC,DWORD m_StyleDisplay=GUISTYLE_2003,COLORREF m_clr=SGradient::GetRGBColorTabs(), int nRate=30);
		virtual void PrepareVertical(CDC *pDC,UINT RTop,UINT GTop,UINT BTOP,UINT RBot,UINT GBot,UINT BBot);
		virtual void PrepareHorizontal(CDC* pDC,DWORD m_StyleDisplay=GUISTYLE_2003,COLORREF m_clr=SGradient::GetRGBColorTabs());
		virtual void PrepareReverseHor(CDC* pDC,DWORD m_StyleDisplay=GUISTYLE_2003,COLORREF m_clr=SGradient::GetRGBColorTabs());
		void PrepareTabs(CDC* pDC, COLORREF m_clrL,COLORREF m_clrH );
		void PrepareCaption(CDC* pDC,DWORD m_StyleDisplay=GUISTYLE_2003);
		void PrepareCaptionVert(CDC* pDC,DWORD m_StyleDisplay=GUISTYLE_2003);
		void PrepareReverseVert(CDC* pDC,DWORD m_StyleDisplay=GUISTYLE_2003, COLORREF m_clr=SGradient::GetRGBColorTabs());
		void PrepareReverseVertTab(CDC* pDC,DWORD m_StyleDisplay=GUISTYLE_2003, COLORREF m_clr=SGradient::GetRGBColorTabs());
		void PrepareReverseVertColorTab(CDC* pDC,DWORD m_StyleDisplay=GUISTYLE_2003, COLORREF m_clrL=SGradient::GetRGBColorTabs(), COLORREF m_clrH=SGradient::GetRGBColorTabs());
		void PrepareReverseHorzColorTab(CDC* pDC,DWORD m_StyleDisplay=GUISTYLE_2003, COLORREF m_clrL=SGradient::GetRGBColorTabs(), COLORREF m_clrH=SGradient::GetRGBColorTabs());
		void PrepareHorizontal(CDC *pDC,UINT RRight,UINT GRight,UINT BRight,UINT RLeft,UINT GLeft,UINT BLeft);
		CSize GetDimensions();
		void  SetDimensions(CSize Size);
		void Draw(CDC *pDC, int xDest,int yDest,int xSrc, int ySrc, int Width, int Height,DWORD Rop);
		static void GetNextColor(int nIndex, COLORREF& m_lowColor, COLORREF& m_HighColor);
	private:
		static COLORREF GetRGBColorXP();
		static COLORREF GetRGBColorTabs();
		static COLORREF GetRGBCaptionXP();

	protected:
		CDC *m_dcMem;
		CSize m_Size;
};

#endif // !defined(AFX_SGRADIENT_H__87FFC4DE_D258_4707_AEEC_A6C8E506BBF4__INCLUDED_)
