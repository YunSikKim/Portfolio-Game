#pragma once


// CStatusView ���Դϴ�.

class CStatusView : public CView
{
	DECLARE_DYNCREATE(CStatusView)

protected:
	CStatusView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CStatusView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


