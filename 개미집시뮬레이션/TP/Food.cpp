#include "StdAfx.h"
#include "Food.h"
#include "TP.h"

CFood::CFood()
{
}

CFood::CFood(int x, int y)
: m_X(x), m_Y(y)
{
	m_Rect.SetRect(x, y, x+20, y+20);
}

CFood::~CFood()
{
}

bool CFood::IsClick(CPoint point)
{
	if( m_Rect.PtInRect(point) )
		return true;

	return false;
}

void CFood::SetX(int value)
{
	 m_X = value;

	 m_Rect.SetRect(m_X, m_Y, m_X+20, m_Y+20);
}

void CFood::Render(CDC* pDC)
{
	CDC backdc;
	CBitmap bitmap;

	backdc.CreateCompatibleDC(pDC);

	bitmap.LoadBitmap(IDB_BITMAP7);

	BITMAP btinfo;
	bitmap.GetBitmap(&btinfo);
	
	backdc.SelectObject(&bitmap);
	pDC->TransparentBlt(m_X, m_Y, btinfo.bmWidth, btinfo.bmHeight, &backdc, 0, 0, btinfo.bmWidth, btinfo.bmHeight, RGB(255, 255, 255));
}