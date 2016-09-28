#include "StdAfx.h"
#include "AntMenu.h"
#include "TP.h"

CAntMenu::CAntMenu()
{
}

CAntMenu::~CAntMenu()
{
}

CAntMenu::CAntMenu(int x, int y)
: m_X(x), m_Y(y)
{
	m_Rect.SetRect(x, y, x+50, y+85);
	m_Ant[0].SetRect(x+5, y+5, x+45, y+20);
	m_Ant[1].SetRect(x+5, y+25, x+45, y+40);
	m_Ant[2].SetRect(x+5, y+45, x+45, y+60);
	m_Ant[3].SetRect(x+5, y+65, x+45, y+80);
}

bool CAntMenu::IsClick(CPoint point)
{
	if( m_Rect.PtInRect(point) )
		return true;

	return false;
}

int CAntMenu::Select(CPoint point)
{
	if( m_Ant[0].PtInRect(point) )
		return 1;
	if( m_Ant[1].PtInRect(point) )
		return 2;
	if( m_Ant[2].PtInRect(point) )
		return 3;
	if( m_Ant[3].PtInRect(point) )
		return 4;

	return 0;
}

void CAntMenu::Render(CDC* pDC)
{
	CDC backdc;
	CBitmap bitmap;

	backdc.CreateCompatibleDC(pDC);

	bitmap.LoadBitmap(IDB_BITMAP6);

	BITMAP btinfo;
	bitmap.GetBitmap(&btinfo);
	
	backdc.SelectObject(&bitmap);
	pDC->TransparentBlt(m_X, m_Y, btinfo.bmWidth, btinfo.bmHeight, &backdc, 0, 0, btinfo.bmWidth, btinfo.bmHeight, RGB(255, 255, 255));

	CFont font;
	font.CreatePointFont(75, _T("맑은 고딕"));
	pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(128, 255, 0));
	if( pcinfo->IsWorker() )
		pDC->DrawText(_T(" 일개미"), &m_Ant[0], DT_LEFT|DT_SINGLELINE);
	if( pcinfo->IsSoldier() )
		pDC->DrawText(_T("병정개미"), &m_Ant[1], DT_LEFT|DT_SINGLELINE);
	if( pcinfo->IsMale() )	
		pDC->DrawText(_T("수컷개미"), &m_Ant[2], DT_LEFT|DT_SINGLELINE);
	if( pcinfo->IsFemale() )	
		pDC->DrawText(_T("암컷개미"), &m_Ant[3], DT_LEFT|DT_SINGLELINE);
}