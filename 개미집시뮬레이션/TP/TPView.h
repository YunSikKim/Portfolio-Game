// TPView.h : CTPView 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CTPView();
	DECLARE_DYNCREATE(CTPView)

// 특성입니다.
public:
	CTPDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CTPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // TPView.cpp의 디버그 버전
inline CTPDoc* CTPView::GetDocument() const
   { return reinterpret_cast<CTPDoc*>(m_pDocument); }
#endif

