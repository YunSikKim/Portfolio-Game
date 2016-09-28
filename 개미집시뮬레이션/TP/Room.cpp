#include "StdAfx.h"
#include "Room.h"
#include "TP.h"

#define MAXANT 30

CRoom::CRoom()
{
}

CRoom::~CRoom()
{
}

CRoom::CRoom(TYPE type, int x, int y)
: m_Type(type), m_X(x), m_Y(y), left(NULL), right(NULL), m_Check(false),
  m_Worker(0), m_Soldier(0), m_Male(0), m_Female(0), m_Food(0), m_Water(0), m_MaxAnt(MAXANT)
{
	m_Rect.SetRect(x, y+50, x+100, y+150);
}

void CRoom::Render(CDC *pDC)
{
	CDC backdc;
	CBitmap bitmap;

	backdc.CreateCompatibleDC(pDC);

	switch( m_Type )
	{
	case LEFT:
		bitmap.LoadBitmap(IDB_BITMAP2);
		break;

	case RIGHT:
		bitmap.LoadBitmap(IDB_BITMAP3);
		break;

	case ROOT:
		bitmap.LoadBitmap(IDB_BITMAP4);
		break;
	}

	BITMAP btinfo;
	bitmap.GetBitmap(&btinfo);

	backdc.SelectObject(&bitmap);
	pDC->TransparentBlt(m_X, m_Y, btinfo.bmWidth, btinfo.bmHeight, &backdc, 0, 0, btinfo.bmWidth, btinfo.bmHeight, RGB(255, 255, 255));

	CString str1, str2;
	str1.Format(_T("%d"), GetTotal());
	str2.Format(_T("%d"), m_MaxAnt);

	CFont font;
	font.CreatePointFont(80, _T("¸¼Àº °íµñ"));
	pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->TextOut(m_X+35, m_Y+135, str1+_T(" / ")+str2);

	if( left != NULL )
	{
		left->Render(pDC);
	}

	if( right != NULL )
	{
		right->Render(pDC);
	}
}

void CRoom::SetLeft(int& count)
{
	if( left != NULL )
		left->SetLeft(count);
	else
	{
		left = new CRoom(LEFT, m_X-100, m_Y+93);
		count++;
	}
}

void CRoom::SetRight(int& count)
{
	if( right != NULL )
		right->SetRight(count);
	else
	{
		right = new CRoom(RIGHT, m_X+100, m_Y+93);
		count++;
	}
}

void CRoom::GetMaxLevel(int curlevel, const CRoom root, int &max)
{
	static int result = 0;

	if( max < curlevel )
	{
		result = curlevel;
		max = result;
	}

	if( this->left != NULL )
		left->GetMaxLevel(curlevel+1, root, max);
		

	if( this->right != NULL )
		right->GetMaxLevel(curlevel+1, root, max);
}

void CRoom::ResetCheck()
{
	m_Check = false;
}

void CRoom::IsClick(CPoint point, CRoom*& room)
{
	if( this->m_Rect.PtInRect(point) )
		room = this;

	if( left != NULL )
		this->left->IsClick(point, room);

	if( right != NULL )
		this->right->IsClick(point, room);

	return;
}

void CRoom::Working()
{
	if( this->m_Worker > 0 )
	{
		int reduce = this->m_Worker / 4;

		this->m_Food -= reduce;
	}

	if( this->m_Food < 0 )
	{
		this->m_Worker += this->m_Food * 2;
		this->m_Food = 0;

		if( this->m_Worker < 0 )
			this->m_Worker = 0;
	}

	if( (this->m_Worker / 2) > 0 )
	{
		int food = this->m_Worker / 2;

		this->m_Food += food;
	}
	
	if( this->left != NULL )
		this->left->Working();
	if( this->right != NULL )
		this->right->Working();
}

void CRoom::GatherPower(int& power)
{
	this->m_Food -= this->m_Soldier;

	if( this->m_Food < 0 )
	{
		this->m_Soldier += this->m_Food;
		this->m_Food = 0;

		if( this->m_Soldier < 0 )
			this->m_Soldier = 0;
	}

	power += this->m_Soldier * 2;

	if( this->left != NULL )
		this->left->GatherPower(power);
	if( this->right != NULL )
		this->right->GatherPower(power);
}

void CRoom::CreateNewRoom(int& count)
{
	int total = m_Worker+m_Soldier+m_Male+m_Female;

	if( total > MAXANT / 2 )
	{
		int random = rand()%2;

		if( random == 0 )
		{
			if( this->right != NULL )
			{
				if( total == MAXANT && left == NULL )
					this->SetLeft(count);
				else
					this->right->CreateNewRoom(count);
			}

			if( this->left == NULL && this->right == NULL )
				this->SetLeft(count);
		}
		else if( random == 1 )
		{
			if( this->left != NULL )
			{
				if( total == MAXANT && right == NULL )
					this->SetRight(count);
				else
					this->left->CreateNewRoom(count);
			}

			if( this->right == NULL && this->left == NULL )
				this->SetRight(count);
		}

	}
}

void CRoom::Over()
{
	if( m_MaxAnt < GetTotal() )
	{
		int temp = GetTotal() - m_MaxAnt;

		while(1)
		{
			if( m_Female > 0 && temp > 0 )
			{
				m_Female--;
				temp--;
			}

			if( m_Male > 0 && temp > 0 )
			{
				m_Male--;
				temp--;
			}

			if( m_Soldier > 0 && temp > 0 )
			{
				m_Soldier--;
				temp--;
			}

			if( m_Worker > 0 && temp > 0 )
			{
				m_Worker--;
				temp--;
			}

			if( temp == 0 )
				break;
		}
	}
}

void CRoom::Drink()
{
	if( m_Water > 0 )
	{
		if( m_MaxAnt != MAXANT )
		{
			m_MaxAnt += 5;
		}

		m_Water--;
	}
	else
	{
		if( m_MaxAnt > 0 )
		{
			m_MaxAnt -= 10;
		}

		Over();
	}

	if( this->left != NULL )
		this->left->Drink();

	if( this->right != NULL )
		this->right->Drink();
}

void CRoom::Delete()
{
	if( left != NULL && left->GetMax() == 0 )
	{
		delete left;
		left = NULL;
	}
	else if( left != NULL )
		left->Delete();

	if( right != NULL && right->GetMax() == 0 )
	{
		delete right;
		right = NULL;
	}
	else if( right != NULL )
		right->Delete();
}

void CRoom::Breed(CPrincess*& pc)
{
	int temp;

	if( this->m_Male > 0 && this->m_Female > 0 )
	{
		if( m_Male > m_Female )
		{
			temp = m_Female;
			m_Male -= m_Female;
			m_Female = 0;
		}
		else
		{
			temp = m_Male;
			m_Female -= m_Male;
			m_Male = 0;
		}
		
		pc->SetLarva(temp);
	}
}

void CRoom::Rain()
{
	this->m_Water++;

	if( left != NULL )
		left->Rain();
	if( right != NULL )
		right->Rain();
}

void CRoom::Feeding()
{
	if( (this->m_Male / 2) > 0 )
	{
		int reduce = this->m_Male / 2;

		this->m_Food -= reduce;
	}

	if( this->m_Food < 0 )
	{
		this->m_Male += this->m_Food;
		this->m_Food = 0;

		if( this->m_Male < 0 )
			this->m_Male = 0;
	}

	if( this->m_Female > 0 )
	{
		int reduce = this->m_Female;

		this->m_Food -= reduce;
	}

	if( this->m_Food < 0 )
	{
		this->m_Female += this->m_Food;
		this->m_Food = 0;

		if( this->m_Female < 0 )
			this->m_Female = 0;
	}
}