#include "StdAfx.h"
#include "Info.h"
#include "TP.h"

CInfo::CInfo()
{
}

CInfo::~CInfo()
{
}

CInfo::CInfo(int x, int y)
: m_X(x), m_Y(y)
{
	m_Rect.SetRect(x, y, x+150, y+150);
}

void CInfo::Render(CDC* pDC)
{
	CDC backdc;
	CBitmap bitmap;

	backdc.CreateCompatibleDC(pDC);

	bitmap.LoadBitmap(IDB_BITMAP8);

	BITMAP btinfo;
	bitmap.GetBitmap(&btinfo);
	
	backdc.SelectObject(&bitmap);
	pDC->TransparentBlt(m_X, m_Y, btinfo.bmWidth, btinfo.bmHeight, &backdc, 0, 0, btinfo.bmWidth, btinfo.bmHeight, RGB(255, 255, 255));

	CString str1, str2, str3, str4, str5, str6, str7;
	int total = roominfo->GetWorker() + roominfo->GetSoldier() + roominfo->GetMale() + roominfo->GetFemale();

	str1.Format(_T("%d"), roominfo->GetWorker());
	str2.Format(_T("%d"), roominfo->GetSoldier());
	str3.Format(_T("%d"), roominfo->GetMale());
	str4.Format(_T("%d"), roominfo->GetFemale());
	str5.Format(_T("%d"), total);

	str6.Format(_T("%d"), roominfo->GetFood());
	str7.Format(_T("%d"), roominfo->GetWater());

	CFont font;
	font.CreatePointFont(80, _T("맑은 고딕"));
	pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(128, 255, 0));
	pDC->TextOut(m_X+5, m_Y+5, _T("　일개미 : ")+str1+_T(" 마리"));
	pDC->TextOut(m_X+5, m_Y+25, _T("병정개미 : ")+str2+_T(" 마리"));
	pDC->TextOut(m_X+5, m_Y+45, _T("수컷개미 : ")+str3+_T(" 마리"));
	pDC->TextOut(m_X+5, m_Y+65, _T("암컷개미 : ")+str4+_T(" 마리"));
	pDC->TextOut(m_X+5, m_Y+85, _T("　　　총 : ")+str5+_T(" 마리"));
	
	pDC->TextOut(m_X+5, m_Y+110, _T("　　식량 : ")+str6+_T(" g"));
	pDC->TextOut(m_X+5, m_Y+130, _T("　　　물 : ")+str7+_T(" cc"));
}
