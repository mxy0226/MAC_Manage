// SGradient.cpp: implementation of the SGradient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SGradient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SGradient::SGradient(CSize Size)
{
	m_Size=Size;
	m_dcMem=NULL;
}

SGradient::~SGradient()
{
	if(m_dcMem!=NULL)
		delete m_dcMem;
}

CSize SGradient::GetDimensions()
{
	return m_Size;
}

void  SGradient::SetDimensions(CSize Size)
{
	m_Size=Size;
}

void SGradient::PrepareVertical(CDC* pDC,DWORD m_StyleDisplay,COLORREF m_clr, int nRate)
{
	BYTE byRvalue =GetRValue(m_clr);//+(nRate==30 ?10:(15));
	BYTE byGvalue =GetGValue(m_clr);//+(nRate==30 ?10:(15));
	BYTE byBvalue =GetBValue(m_clr);//+(nRate==30 ?10:(15));
	if (m_StyleDisplay!= GUISTYLE_XP )
	{
		COLORREF clrNear=pDC->GetNearestColor(GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareVertical(pDC,222,234,253,141,178,223);
		else if(clrNear==8039069)
			PrepareVertical(pDC,243,251,221,179,194,138);
		else if(clrNear==13221564)
			PrepareVertical(pDC,248,248,250,165,160,184);
	}
	else
		PrepareVertical(pDC,250,250,249,byRvalue-30,byGvalue-30,byBvalue-30);
}

void SGradient::PrepareCaption(CDC* pDC,DWORD m_StyleDisplay)
{
	BYTE byRvalue = 0;
	BYTE byGvalue = 0;
	BYTE byBvalue = 0;

	if (m_StyleDisplay!= GUISTYLE_XP)
	{
		PrepareVertical(pDC,248,248,205,249,200,102);
		return;
	}
	else if (m_StyleDisplay == GUISTYLE_2003)
	{
		//byRvalue =GetRValue(GetRGBPressBXP());
		//byGvalue =GetGValue(GetRGBPressBXP());
		//byBvalue =GetBValue(GetRGBPressBXP());
	}
	else
	{
		//byRvalue =GetRValue(GetRGBColorShadow());
		//byGvalue =GetGValue(GetRGBColorShadow());
		//byBvalue =GetBValue(GetRGBColorShadow());
	}
	PrepareVertical(pDC,byRvalue,byGvalue,byBvalue,byRvalue-30,byGvalue-30,byBvalue-30);
}

void SGradient::PrepareCaptionVert(CDC* pDC,DWORD m_StyleDisplay)
{
	BYTE byRvalue = 0;
	BYTE byGvalue = 0;
	BYTE byBvalue = 0;

	if (m_StyleDisplay!= GUISTYLE_XP)
	{
		PrepareHorizontal(pDC,249,200,102,248,248,205);
		return;
	}
	else if (m_StyleDisplay == GUISTYLE_2003)
	{
		//byRvalue =GetRValue(GetRGBPressBXP());
		//byGvalue =GetGValue(GetRGBPressBXP());
		//byBvalue =GetBValue(GetRGBPressBXP());
	}
	else
	{
		//byRvalue =GetRValue(GetRGBColorShadow());
		//byGvalue =GetGValue(GetRGBColorShadow());
		//byBvalue =GetBValue(GetRGBColorShadow());
	}
	PrepareHorizontal(pDC,byRvalue,byGvalue,byBvalue,byRvalue-30,byGvalue-30,byBvalue-30);
}

void SGradient::PrepareTabs(CDC* pDC, COLORREF m_clrL,COLORREF m_clrH)
{

	BYTE byRvalueL =GetRValue(m_clrL);
	BYTE byGvalueL =GetGValue(m_clrL);
	BYTE byBvalueL =GetBValue(m_clrL);

	BYTE byRvalueH =GetRValue(m_clrH);
	BYTE byGvalueH =GetGValue(m_clrH);
	BYTE byBvalueH =GetBValue(m_clrH);
	PrepareVertical(pDC,byRvalueL,byGvalueL,byBvalueL,byRvalueH,byGvalueH,byBvalueH);
}

void SGradient::PrepareReverseVert(CDC* pDC,DWORD m_StyleDisplay,COLORREF m_clr)
{

	BYTE byRvalue =GetRValue(m_clr)+10;
	BYTE byGvalue =GetGValue(m_clr)+10;
	BYTE byBvalue =GetBValue(m_clr)+10;
	if (m_StyleDisplay!= GUISTYLE_XP)
	{
		COLORREF clrNear=pDC->GetNearestColor(GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareVertical(pDC,141,178,223,222,234,253);
		else if(clrNear==8039069)
			PrepareVertical(pDC,179,194,138,243,251,221);
		else if(clrNear==13221564)
			PrepareVertical(pDC,165,160,184,248,248,250);
	}
	else
		PrepareVertical(pDC,byRvalue-30,byGvalue-30,byBvalue-30,byRvalue,byGvalue,byBvalue);
}

void SGradient::PrepareReverseVertTab(CDC* pDC,DWORD m_StyleDisplay,COLORREF m_clr)
{

	BYTE byRvalue =GetRValue(m_clr)+10;
	BYTE byGvalue =GetGValue(m_clr)+10;
	BYTE byBvalue =GetBValue(m_clr)+10;
	if (m_StyleDisplay!= GUISTYLE_XP)
	{
		COLORREF clrNear=pDC->GetNearestColor(GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareVertical(pDC,216,228,243,255,255,255);
		else if(clrNear==8039069)
			PrepareVertical(pDC,233,237,220,255,255,255);
		else if(clrNear==13221564)
			PrepareVertical(pDC,234,233,239,255,255,255);
		else
			PrepareVertical(pDC,byRvalue-30,byGvalue-30,byBvalue-30,byRvalue,byGvalue,byBvalue);

	}
	else
		PrepareVertical(pDC,byRvalue-30,byGvalue-30,byBvalue-30,byRvalue,byGvalue,byBvalue);
}

void SGradient::PrepareReverseVertColorTab(CDC* pDC,DWORD m_StyleDisplay, COLORREF m_clrL, COLORREF m_clrH)
{

	BYTE byRvalueL =GetRValue(m_clrL);
	BYTE byGvalueL =GetGValue(m_clrL);
	BYTE byBvalueL =GetBValue(m_clrL);

	BYTE byRvalueH =GetRValue(m_clrH);
	BYTE byGvalueH =GetGValue(m_clrH);
	BYTE byBvalueH =GetBValue(m_clrH);

	PrepareVertical(pDC,byRvalueL,byGvalueL,byBvalueL,byRvalueH,byGvalueH,byBvalueH);
}

void SGradient::PrepareReverseHorzColorTab(CDC* pDC,DWORD m_StyleDisplay, COLORREF m_clrL, COLORREF m_clrH)
{

	BYTE byRvalueL =GetRValue(m_clrL);
	BYTE byGvalueL =GetGValue(m_clrL);
	BYTE byBvalueL =GetBValue(m_clrL);

	BYTE byRvalueH =GetRValue(m_clrH);
	BYTE byGvalueH =GetGValue(m_clrH);
	BYTE byBvalueH =GetBValue(m_clrH);

	PrepareHorizontal(pDC,byRvalueL,byGvalueL,byBvalueL,byRvalueH,byGvalueH,byBvalueH);
}

void SGradient::PrepareReverseHor(CDC* pDC,DWORD m_StyleDisplay,COLORREF m_clr)
{
	BYTE byRvalue =GetRValue(m_clr)+10;
	BYTE byGvalue =GetGValue(m_clr)+10;
	BYTE byBvalue =GetBValue(m_clr)+10;
	if (m_StyleDisplay!= GUISTYLE_XP)
	{
		COLORREF clrNear=pDC->GetNearestColor(GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareHorizontal(pDC,222,234,253,141,178,223);
		else if(clrNear==8039069)
			PrepareHorizontal(pDC,243,251,221,179,194,138);
		else if(clrNear==13221564)
			PrepareHorizontal(pDC,248,248,250,165,160,184);
	}
	else
		PrepareHorizontal(pDC,byRvalue,byGvalue,byBvalue,byRvalue-30,byGvalue-30,byBvalue-30);

}

void SGradient::PrepareHorizontal(CDC* pDC,DWORD m_StyleDisplay,COLORREF m_clr)
{
	BYTE byRvalue =GetRValue(m_clr)+10;
	BYTE byGvalue =GetGValue(m_clr)+10;
	BYTE byBvalue =GetBValue(m_clr)+10;
	if (m_StyleDisplay!= GUISTYLE_XP)
	{
		COLORREF clrNear=pDC->GetNearestColor(GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareHorizontal(pDC,141,178,223,222,234,253);
		else if(clrNear==8039069)
			PrepareHorizontal(pDC,179,194,138,243,251,221);
		else if(clrNear==13221564)
			PrepareHorizontal(pDC,165,160,184,248,248,250);
	}
	else
		PrepareHorizontal(pDC,byRvalue-30,byGvalue-30,byBvalue-30,byRvalue,byGvalue,byBvalue);
}

void SGradient::PrepareVertical(CDC *pDC,UINT RTop,UINT GTop,UINT BTop,UINT RBot,UINT GBot,UINT BBot)
{
	//Here we will create a memory bitmap and draw the colored bitmap on it
	//using my pretty Algorithm for generating colors.

	//if we have already a drawn DC then delete it so we will not have a
	//memory leak

	if(m_dcMem!=NULL)
	{
		delete m_dcMem;

	}

	//create the Memory Bitmap
	CBitmap Bitmap;
	m_dcMem=new CDC;	//new Device Context
	m_dcMem->CreateCompatibleDC(pDC);	//Make it Compatible with pDC
	m_dcMem->SetMapMode(MM_TEXT);		//Pixels Mapping Mode
	//Make the Bitmap compatible with the memory DC
	Bitmap.CreateCompatibleBitmap(pDC,m_Size.cx,m_Size.cy);	
	//Select the bitmap into the memory DC
	m_dcMem->SelectObject(&Bitmap);
	////////////////////////////////////////////////////////////////
	////Drawing The Gradient in a MemDC
	////////////////////////////////////////////////////////////////
	//ALGORITHM:
	//We will have the RGB values of the color at which we will start
	//and the RGB values of the color at which we will end
	//we will fill 256 rectangles using all colors that lie between
	//these two colors. this is done by moving the R,G, and B values slowly
	//from the Starting color to the Ending Color.
	//For example: if we have RTop=100 and RBot=150 then we will draw 256
	//rectangles colored with the R-values of 100,100+(150-100)/256,
	//100+2*(150-100)/256,100+3*(150-100)/256,...
	//and the same will happen to G and B values.

	//rStep,gStep, and bStep are variables that will be used
	//to hold the values at which R,G,B will be changed respectivily
	//For example: if we have RTop=100 and RBot=150 then 
	//rStep=(150-100)/256 so when we start at R=100 and draw 256 rectangles
	//we will end at R=150 when we finish drawing these rectangles
	double rStep,gStep,bStep;
	double rCount,gCount,bCount;
	double RectHeight=m_Size.cy/256.0;
	const int NUM_COLORS=256;
	//We will start counting from TopColor to BottomColor
	//So we give an initial value of the TopColor
	rCount=RTop;
	gCount=GTop;
	bCount=BTop;
	//Calcualte the step of R,G,B values
	rStep=-((double)RTop-RBot)/NUM_COLORS;
	gStep=-((double)GTop-GBot)/NUM_COLORS;
	bStep=-((double)BTop-BBot)/NUM_COLORS;

	for(int ColorCount=0;ColorCount<NUM_COLORS;ColorCount++)
	{
		//Draw using current RGB values and Change RGB values
		//to represent the next color in the chain
		m_dcMem->FillRect(CRect(0,int(ColorCount*RectHeight),m_Size.cx,int((ColorCount+1)*RectHeight)),&CBrush(RGB(rCount,gCount,bCount)));
		rCount+=rStep;
		gCount+=gStep;
		bCount+=bStep;
	}

}

void SGradient::PrepareHorizontal(CDC *pDC,UINT RLeft,UINT GLeft,UINT BLeft,UINT RRight,UINT GRight,UINT BRight)
{
	if(m_dcMem!=NULL)
	{
		delete m_dcMem;

	}
	CBitmap Bitmap;
	m_dcMem=new CDC;
	m_dcMem->CreateCompatibleDC(pDC);
	m_dcMem->SetMapMode(MM_TEXT);
	Bitmap.CreateCompatibleBitmap(pDC,m_Size.cx,m_Size.cy);
	m_dcMem->SelectObject(&Bitmap);
	////////////////////////////////////////////////////////////////
	////Drawing The Gradient in a MemDC
	double rStep,gStep,bStep;
	double rCount,gCount,bCount;
	double RectWidth=m_Size.cx/256.0;
	const int NUM_COLORS=256;
	rCount=RRight;
	gCount=GRight;
	bCount=BRight;
	rStep=-((double)RRight-RLeft)/NUM_COLORS;
	gStep=-((double)GRight-GLeft)/NUM_COLORS;
	bStep=-((double)BRight-BLeft)/NUM_COLORS;

	for(int ColorCount=0;ColorCount<NUM_COLORS;ColorCount++)
	{
		m_dcMem->FillRect(CRect(int(ColorCount*RectWidth),0,int((ColorCount+1)*RectWidth),m_Size.cy),&CBrush(RGB(rCount,gCount,bCount)));
		rCount+=rStep;
		gCount+=gStep;
		bCount+=bStep;
	}
}

void SGradient::Draw(CDC *pDC, int xDest,int yDest,int xSrc, int ySrc, int Width, int Height,DWORD Rop)
{
	//Use BitBlt to Draw on a DC

	pDC->BitBlt(xDest,yDest,Width,Height,m_dcMem,xSrc,ySrc,Rop);


}

COLORREF SGradient::GetRGBColorTabs()
{
	BYTE byRvalue =GetRValue(GetRGBColorXP());
	BYTE byGvalue =GetGValue(GetRGBColorXP());
	BYTE byBvalue =GetBValue(GetRGBColorXP());
	//	byRvalue =byRvalue>>2;
	//	byGvalue =byGvalue>>2;
	//	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.51);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	

}

COLORREF SGradient::GetRGBColorXP()
{
	COLORREF clr3DFace = ::GetSysColor (COLOR_3DFACE);
	return RGB (((3*GetRValue (clr3DFace)+240)/4)+1,
			((3*GetGValue (clr3DFace)+240)/4)+1,
			((3*GetBValue (clr3DFace)+240)/4)+1);
}

COLORREF SGradient::GetRGBCaptionXP()
{

	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
	return RGB(byRvalue+10,byGvalue+10,byBvalue+10);	
}

void SGradient::GetNextColor(int nIndex, COLORREF& m_lowColor, COLORREF& m_HighColor)
{

	int nResult= (nIndex >10 ) ? nIndex % 10 : nIndex;
	switch(nResult)
	{
		case 0:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB (147,174,230);
			break;
		case 1:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB( 255,223,133);
			break;
		case 2:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB (210,221,189);
			break;
		case 3:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB (244,189,189);
			break;
		case 4:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB (210,198,235);
			break;
		case 5:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB (186,211,204);
			break;
		case 6:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB (247,202,165);
			break;
		case 7:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB (219,177,197);
			break;
		case 8:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB (180,199,237);
			break;
		case 9:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB (244,189,189);
			break;
		default:
			m_lowColor=RGB(255,255,255);
			m_HighColor=RGB (247,202,165);
	}
}
