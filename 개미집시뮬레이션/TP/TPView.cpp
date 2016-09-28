// TPView.cpp : CTPView Ŭ������ ����
//

#include "stdafx.h"
#include "TP.h"

#include "TPDoc.h"
#include "TPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SOLDIEROK 10
#define MALEOK 15
#define FEMALEOK 20

// CTPView

IMPLEMENT_DYNCREATE(CTPView, CView)

BEGIN_MESSAGE_MAP(CTPView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CTPView ����/�Ҹ�

CTPView::CTPView()
: m_Max(0), m_Count(1), m_Empty(false), m_Create(false), m_Foodcnt(0), m_TotalPower(0),
  m_Year(2014), m_Month(6), m_Day(12), m_Rain(false), m_Weather(1)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	srand(time(NULL));

	menu = NULL;
	info = NULL;
	eat = NULL;
	for(int i=0; i<5; i++)
		food[i] = NULL;
	room = new CRoom(ROOT, 350, 100);
	room->SetWater(3);

	pchome = room;
	pc = new CPrincess(pchome->GetX()+25, pchome->GetY()+80);
}

CTPView::~CTPView()
{
}

BOOL CTPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTPView �׸���

void CTPView::OnDraw(CDC* pDC)
{
	CTPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	GetClientRect(&m_rt);

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CDC memdc;
	CBitmap bitmap;

	memdc.CreateCompatibleDC(pDC);

	if( m_Rain )
		bitmap.LoadBitmap(IDB_BITMAP10);
	else
		bitmap.LoadBitmap(IDB_BITMAP1);

	memdc.SelectObject(&bitmap);
	
	//���⼭ Render
	memdc.SetBkMode(TRANSPARENT);

	room->Render(&memdc);
	pc->Render(&memdc);

	if( menu != NULL )
	{
		menu->SetPrincess(pc->GetPrincess());
		menu->Render(&memdc);

		CString str;
		str.Format(_T("%d"), pchome->GetFood());
		CFont foodfont;
		foodfont.CreatePointFont(80, _T("���� ���"));
		memdc.SelectObject(&foodfont);
		memdc.SetTextColor(RGB(255, 255, 255));
		if( pchome->GetType() == LEFT )
			memdc.TextOut(pchome->GetX()+102, pchome->GetY()+135, str);
		else
			memdc.TextOut(pchome->GetX()-62, pchome->GetY()+135, str);
	}

	if( info != NULL )
		info->Render(&memdc);

	for(int i=0; i<5; i++)
		if( food[i] != NULL )
			food[i]->Render(&memdc);

	if( eat != NULL )
		eat->Render(&memdc);
	
	if( m_Empty && m_Create )
	{
		CFont font;
		font.CreatePointFont(70, _T("���� ���"));
		memdc.SelectObject(&font);

		memdc.SetTextColor(RGB(255, 0, 0));
		memdc.TextOut(pc->GetX()-15, pc->GetY()+15, _T("������ �����մϴ�!"));
	}
	else if( m_Create )
	{
		CFont font;
		font.CreatePointFont(70, _T("���� ���"));
		memdc.SelectObject(&font);

		CString str;
		str.Format(_T("%d"), pc->GetLarva());

		memdc.SetTextColor(RGB(255, 255, 255));
		memdc.TextOut(pc->GetX()+20, pc->GetY()+20, str);
	}

	CRect rect;
	rect.SetRect(room->GetX()+5, room->GetY()+5, room->GetX()+100, room->GetY()+45);

	CString power;
	power.Format(_T("%d"), m_TotalPower);
	CFont powerfont;
	powerfont.CreatePointFont(300, _T("HY�߰��"));
	memdc.SelectObject(&powerfont);
	memdc.SetTextColor(RGB(255, 255, 0));
	memdc.DrawText(power, &rect, DT_CENTER);

	CString year, month, day;
	year.Format(_T("%d"), m_Year);
	month.Format(_T("%d"), m_Month);
	day.Format(_T("%d"), m_Day);
	CFont dayfont;
	dayfont.CreatePointFont(100, _T("���� ���"));
	memdc.SelectObject(&dayfont);
	memdc.SetTextColor(RGB(0, 0, 0));
	memdc.TextOut(5, 5, year+_T("�� ")+month+_T("�� ")+day+_T("��"));

	pDC->BitBlt(0, 0, m_rt.Width(), m_rt.Height(), &memdc, 0, 0, SRCCOPY);
}


// CTPView �μ�

BOOL CTPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CTPView ����

#ifdef _DEBUG
void CTPView::AssertValid() const
{
	CView::AssertValid();
}

void CTPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTPDoc* CTPView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTPDoc)));
	return (CTPDoc*)m_pDocument;
}
#endif //_DEBUG


// CTPView �޽��� ó����


void CTPView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.'
	for(int i=0; i<5; i++)
	{
		if( food[i] != NULL )
		{
			if( food[i]->IsClick(point) )
			{
				delete food[i];
				food[i] = NULL;

				pchome->SetFood(1);
			}
		}
	}

	if( eat != NULL )
	{
		if( eat->IsClick(point) )
		{
			if( pchome->GetFood() > 0 )
			{
				pchome->SetFood(-1);
				pc->SetLarva(2);

				m_Empty = false;
			}
		}
	}

	if( pc->IsClick(point) )
	{
		if( menu == NULL )
		{
			menu = new CAntMenu(pc->GetX()-55, pc->GetY()-10);
			
			if( pchome->GetType() == LEFT )
				eat = new CEatButton(pc->GetX()+53, pc->GetY()-1);
			else
				eat = new CEatButton(pc->GetX()-110, pc->GetY()-1);

			if( info != NULL )
			{
				delete info;
				info = NULL;
			}
		}
		else
		{
			delete menu;
			menu = NULL;
			m_Empty = false;

			delete eat;
			eat = NULL;
		}
	}

	CRoom* clickRoom = NULL;

	room->IsClick(point, clickRoom);

	if( clickRoom != NULL && !pc->IsClick(point) )
	{
		if( eat == NULL || !eat->IsClick(point) )
		{
			if( info == NULL )
			{
				if( menu == NULL || (menu != NULL && !menu->IsClick(point)) )
				{
					if( clickRoom->GetType() == LEFT )
						info = new CInfo(clickRoom->GetX()+105, clickRoom->GetY()+50);
					else
						info = new CInfo(clickRoom->GetX()-155, clickRoom->GetY()+50);

					info->SetRoom(clickRoom);
				}

				if( menu != NULL && !menu->IsClick(point) )
				{
					delete menu;
					menu = NULL;
					m_Empty = false;

					delete eat;
					eat = NULL;
				}
			}
			else
			{
				delete info;
				info = NULL;
			}
		}
	}

	if( m_Create && pchome != clickRoom && clickRoom != NULL )
	{
		m_Create = false;

		delete menu;
		menu = NULL;
		m_Empty = false;

		delete eat;
		eat = NULL;

		delete info;
		info = NULL;

		pchome = clickRoom;
		pc->SetPos(pchome->GetX()+25, pchome->GetY()+80);
	}

	if( menu != NULL && menu->IsClick(point) )
	{
		if( pc->GetLarva() > 0 )
		{
			if( pchome->GetTotal() < pchome->GetMax() )
			{
				menu->SetPrincess(pc->GetPrincess());

				switch( menu->Select(point) )
				{
				case 1:
					if( pc->IsWorker() )
					{
						pchome->SetWorker(1);
						pc->SetLarva(-1);
					}
					break;

				case 2:
					if( pc->IsSoldier() )
					{
						pchome->SetSoldier(1);
						pc->SetLarva(-1);
					}
					break;

				case 3:
					if( pc->IsMale() )
					{
						pchome->SetMale(2);
						pc->SetLarva(-1);
					}
					break;

				case 4:
					if( pc->IsFemale() )
					{
						pchome->SetFemale(1);
						pc->SetLarva(-1);
					}
					break;
				}
			}
		}
		else
		{
			m_Empty = true;
		}
	}

	if( menu != NULL )
		m_Create = true;
	else
		m_Create = false;

	if( pchome->GetWorker() >= SOLDIEROK )
		pc->SetSoldier(true);
	else
		pc->SetSoldier(false);
	if( pchome->GetWorker() >= MALEOK )
		pc->SetMale(true);
	else
		pc->SetMale(false);
	if( pchome->GetWorker() >= FEMALEOK )
		pc->SetFemale(true);
	else
		pc->SetFemale(false);

	Invalidate(false);

	CView::OnLButtonDown(nFlags, point);
}


void CTPView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int create = rand()%5;

	switch( nIDEvent )
	{
	case 1:
		if( create < 2 )
		{
			if( food[m_Foodcnt] != NULL )
			{
				delete food[m_Foodcnt];
				food[m_Foodcnt] = NULL;
			}

			if( food[m_Foodcnt] == NULL )
			{
				food[m_Foodcnt] = new CFood(rand()%780, 80);

				while(food[m_Foodcnt]->GetX() > 330 && food[m_Foodcnt]->GetX() < 450)
				{
					food[m_Foodcnt]->SetX(rand()%780);
				}

				if( m_Foodcnt != 4 )
					m_Foodcnt++;
				else
					m_Foodcnt = 0;
			}
		}
		break;

	case 2:
		room->Working();
		room->GatherPower(m_TotalPower);
		room->Feeding();
		room->CreateNewRoom(m_Count);
		break;

	case 3:
		room->Drink();
		room->Delete();
		break;

	case 4:
		m_Day++;

		if( m_Day > 30 )
		{
			m_Month++;
			m_Day = 1;

			if( m_Month > 12 )
			{
				m_Year++;
				m_Month = 1;
			}
		}
		break;

	case 5:
		room->Breed(pc);
		break;

	case 6:
		m_Weather = rand()%4;

		if( m_Weather == 0 )
		{
			m_Rain = true;
			room->Rain();
		}
		else
			m_Rain = false;
		break;
	}

	Invalidate(false);

	CView::OnTimer(nIDEvent);
}


int CTPView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	SetTimer(1, 5000, NULL);
	SetTimer(2, 10000, NULL);
	SetTimer(3, 60000, NULL);
	SetTimer(4, 60000, NULL);
	SetTimer(5, 30000, NULL);
	SetTimer(6, 20000, NULL);

	return 0;
}


void CTPView::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	KillTimer(5);
	KillTimer(6);

	CView::OnClose();
}