// TPView.h : CTPView Ŭ������ �������̽�
//


#pragma once
#include "atltypes.h"

#include "Room.h"
#include "Princess.h"
#include "AntMenu.h"
#include "Info.h"
#include "Food.h"
#include "EatButton.h"

class CTPDoc;

class CTPView : public CView
{
protected: // serialization������ ��������ϴ�.
	CTPView();
	DECLARE_DYNCREATE(CTPView)

// Ư���Դϴ�.
public:
	CTPDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CTPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	CRect m_rt;
	CRoom* room;
	CRoom* pchome;
	CPrincess* pc;
	CAntMenu* menu;
	CFood* food[5];
	CInfo* info;
	CEatButton* eat;
	bool m_Empty;
	bool m_Create;
	int m_Max;
	int m_Count;
	int m_Foodcnt;
	int m_TotalPower;
	int m_Year, m_Month, m_Day;
	int m_Weather;
	bool m_Rain;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
};

#ifndef _DEBUG  // TPView.cpp�� ����� ����
inline CTPDoc* CTPView::GetDocument() const
   { return reinterpret_cast<CTPDoc*>(m_pDocument); }
#endif

