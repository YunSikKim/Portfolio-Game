#include "StdAfx.h"
#include "EatButton.h"
#include "TP.h"

CEatButton::CEatButton()
{
}

CEatButton::CEatButton(int x, int y)
: m_X(x), m_Y(y)
{
	m_Rect.SetRect(x, y, x+50, y+50);
}

CEatButton::~CEatButton()
{
}

bool CEatButton::IsClick(CPoint point)
{
	if( m_Rect.PtInRect(point) )
		return true;

	return false;
}

void CEatButton::Render(CDC* pDC)
{
	CDC backdc;
	CBitmap bitmap;

	backdc.CreateCompatibleDC(pDC);

	bitmap.LoadBitmap(IDB_BITMAP5);

	BITMAP btinfo;
	bitmap.GetBitmap(&btinfo);
	
	backdc.SelectObject(&bitmap);
	pDC->TransparentBlt(m_X, m_Y, btinfo.bmWidth, btinfo.bmHeight, &backdc, 0, 0, btinfo.bmWidth, btinfo.bmHeight, RGB(255, 0, 255));
}