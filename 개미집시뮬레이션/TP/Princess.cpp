#include "StdAfx.h"
#include "Princess.h"
#include "TP.h"

CPrincess::CPrincess()
{
}

CPrincess::CPrincess(int x, int y)
: m_X(x), m_Y(y), m_Larva(2), m_Worker(true), m_Soldier(false), m_Male(false), m_Female(false)
{
	m_Rect.SetRect(x, y, x+48, y+48);
}

CPrincess::~CPrincess()
{
}

bool CPrincess::IsClick(CPoint point)
{
	if( m_Rect.PtInRect(point) )
		return true;

	return false;
}

void CPrincess::SetPos(int x, int y)
{
	m_X = x;
	m_Y = y;

	m_Rect.SetRect(x, y, x+48, y+48);
}

void CPrincess::Render(CDC* pDC)
{
	CDC backdc;
	CBitmap bitmap;

	backdc.CreateCompatibleDC(pDC);

	bitmap.LoadBitmap(IDB_BITMAP9);

	BITMAP btinfo;
	bitmap.GetBitmap(&btinfo);
	
	backdc.SelectObject(&bitmap);
	pDC->TransparentBlt(m_X, m_Y, btinfo.bmWidth, btinfo.bmHeight, &backdc, 0, 0, btinfo.bmWidth, btinfo.bmHeight, RGB(0, 0, 255));
}