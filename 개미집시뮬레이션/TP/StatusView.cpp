// StatusView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TP.h"
#include "StatusView.h"


// CStatusView

IMPLEMENT_DYNCREATE(CStatusView, CView)

CStatusView::CStatusView()
{

}

CStatusView::~CStatusView()
{
}

BEGIN_MESSAGE_MAP(CStatusView, CView)
END_MESSAGE_MAP()


// CStatusView �׸����Դϴ�.

void CStatusView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CStatusView �����Դϴ�.

#ifdef _DEBUG
void CStatusView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CStatusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStatusView �޽��� ó�����Դϴ�.
