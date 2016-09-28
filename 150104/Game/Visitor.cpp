#include "Visitor.h"

CVisitor::CVisitor(int nType, float fX, float fY)
: m_nType(nType), m_nStackCnt(0), m_nCurCnt(0), m_bCourseOK(false), m_nFrame(0), m_nMotion(0)
{
	SetX(fX);
	SetY(fY);

	m_Cur.nX = 0;
	m_Cur.nY = 0;

	TManager->TLoad(200, "./Images/Guest/boystd_l.png");
	TManager->TLoad(201, "./Images/Guest/boystd_b.png");
	TManager->TLoad(202, "./Images/Guest/boystd_r.png");
	TManager->TLoad(203, "./Images/Guest/boystd_f.png");
	TManager->TLoad(210, "./Images/Guest/girlstd_l.png");
	TManager->TLoad(211, "./Images/Guest/girlstd_b.png");
	TManager->TLoad(212, "./Images/Guest/girlstd_r.png");
	TManager->TLoad(213, "./Images/Guest/girlstd_f.png");
	TManager->TLoad(220, "./Images/Guest/man_l.png");
	TManager->TLoad(221, "./Images/Guest/man_b.png");
	TManager->TLoad(222, "./Images/Guest/man_r.png");
	TManager->TLoad(223, "./Images/Guest/man_f.png");
	TManager->TLoad(230, "./Images/Guest/woman_l.png");
	TManager->TLoad(231, "./Images/Guest/woman_b.png");
	TManager->TLoad(232, "./Images/Guest/woman_r.png");
	TManager->TLoad(233, "./Images/Guest/woman_f.png");

	for(int i=0; i<_MAP_HEIGHT; i++)
		for(int j=0; j<_MAP_WIDTH; j++)
			m_Check[i][j] = 0;
}

CVisitor::~CVisitor()
{
}

void CVisitor::MapInit(CTile*** Map)
{
	m_Map = *Map;

	for(int i=0; i<_MAP_HEIGHT; i++)
		for(int j=0; j<_MAP_WIDTH; j++)
			if( m_Map[i][j].GetID() == -1 )
				m_Check[i][j] = 1;
}

void CVisitor::Course(int nN, int nX, int nY)
{
	if( nX < 0 || nX >= _MAP_WIDTH
	 || nY < 0 || nY >= _MAP_HEIGHT
	 || m_Check[nY][nX] == 1
	 && m_bCourseOK )
	{
		if( m_nStackCnt < nN )
			m_nStackCnt = nN;
		return;
	}

	if( nX == _GAME_END_X && nY == _GAME_END_Y )
	{
		m_bCourseOK = true;
		return;
	}

	int r;

	switch( m_Map[nY][nX].GetID() )
	{
	case 6:
		while( 1 )
		{
			r = rand()%4;
		
			switch( r )
			{
			case 0:
				continue;
			case 1:
				if( m_Stack[nN-1] == BOTTOM )
					continue;
				m_Direction = TOP;
				break;
			case 2:
				if( m_Stack[nN-1] == LEFT )
					continue;
				m_Direction = RIGHT;
				break;
			case 3:
				if( m_Stack[nN-1] == TOP )
					continue;
				m_Direction = BOTTOM;
				break;
			}
			break;
		}
		break;
	case 7:
		while( 1 )
		{
			r = rand()%4;
		
			switch( r )
			{
			case 0:
				if( m_Stack[nN-1] == RIGHT )
					continue;
				m_Direction = LEFT;
				break;
			case 1:
				continue;
			case 2:
				if( m_Stack[nN-1] == LEFT )
					continue;
				m_Direction = RIGHT;
				break;
			case 3:
				if( m_Stack[nN-1] == TOP )
					continue;
				m_Direction = BOTTOM;
				break;
			}
			break;
		}
		break;
	case 8:
		while( 1 )
		{
			r = rand()%4;
		
			switch( r )
			{
			case 0:
				if( m_Stack[nN-1] == RIGHT )
					continue;
				m_Direction = LEFT;
				break;
			case 1:
				if( m_Stack[nN-1] == BOTTOM )
					continue;
				m_Direction = TOP;
				break;
			case 2:
				continue;
			case 3:
				if( m_Stack[nN-1] == TOP )
					continue;
				m_Direction = BOTTOM;
				break;
			}
			break;
		}
		break;
	case 9:
		while( 1 )
		{
			r = rand()%4;
		
			switch( r )
			{
			case 0:
				if( m_Stack[nN-1] == RIGHT )
					continue;
				m_Direction = LEFT;
				break;
			case 1:
				if( m_Stack[nN-1] == BOTTOM )
					continue;
				m_Direction = TOP;
				break;
			case 2:
				if( m_Stack[nN-1] == LEFT )
					continue;
				m_Direction = RIGHT;
				break;
			case 3:
				continue;
			}
			break;
		}
		break;
	case 10:
		while( 1 )
		{
			r = rand()%4;
		
			switch( r )
			{
			case 0:
				if( m_Stack[nN-1] == RIGHT )
					continue;
				m_Direction = LEFT;
				break;
			case 1:
				if( m_Stack[nN-1] == BOTTOM )
					continue;
				m_Direction = TOP;
				break;
			case 2:
				if( m_Stack[nN-1] == LEFT )
					continue;
				m_Direction = RIGHT;
				break;
			case 3:
				if( m_Stack[nN-1] == TOP )
					continue;
				m_Direction = BOTTOM;
				break;
			}

			break;
		}
		break;
	}

	//DFS
	if( m_Check[nY][nX-1] == 0 && nX-1 >= 0
	 && ( m_Map[nY][nX].GetID() == 0 || m_Map[nY][nX].GetID() == 2
	 || m_Map[nY][nX].GetID() == 4
	 || (m_Map[nY][nX].GetID() == 7 && m_Direction == LEFT)
	 || (m_Map[nY][nX].GetID() == 8 && m_Direction == LEFT)
	 || (m_Map[nY][nX].GetID() == 9 && m_Direction == LEFT)
	 || (m_Map[nY][nX].GetID() == 10 && m_Direction == LEFT) )
	 && !m_bCourseOK )
	{
		//LEFT
		m_Check[nY][nX] = 1;
		m_Stack[nN] = LEFT;

		Course(nN+1, nX-1, nY);
	}
	else if( m_Check[nY-1][nX] == 0 && nY-1 >= 0
		  && ( m_Map[nY][nX].GetID() == 1 || m_Map[nY][nX].GetID() == 2
		  || m_Map[nY][nX].GetID() == 3
		  || (m_Map[nY][nX].GetID() == 6 && m_Direction == TOP)
		  || (m_Map[nY][nX].GetID() == 8 && m_Direction == TOP)
		  || (m_Map[nY][nX].GetID() == 9 && m_Direction == TOP)
		  || (m_Map[nY][nX].GetID() == 10 && m_Direction == TOP) )
		  && !m_bCourseOK )
	{
		//TOP
		m_Check[nY][nX] = 1;
		m_Stack[nN] = TOP;

		Course(nN+1, nX, nY-1);
	}
	if( m_Check[nY][nX+1] == 0 && nX+1 <= _MAP_WIDTH
	 && ( m_Map[nY][nX].GetID() == 0 || m_Map[nY][nX].GetID() == 3
	 || m_Map[nY][nX].GetID() == 5
	 || (m_Map[nY][nX].GetID() == 6 && m_Direction == RIGHT)
	 || (m_Map[nY][nX].GetID() == 7 && m_Direction == RIGHT)
	 || (m_Map[nY][nX].GetID() == 9 && m_Direction == RIGHT)
	 || (m_Map[nY][nX].GetID() == 10 && m_Direction == RIGHT) )
	 && !m_bCourseOK )
	{
		//RIGHT
		m_Check[nY][nX] = 1;
		m_Stack[nN] = RIGHT;

		Course(nN+1, nX+1, nY);
	}
	if( m_Check[nY+1][nX] == 0 && nY+1 <= _MAP_HEIGHT
	 && ( m_Map[nY][nX].GetID() == 1 || m_Map[nY][nX].GetID() == 4
	 || m_Map[nY][nX].GetID() == 5
	 || (m_Map[nY][nX].GetID() == 6 && m_Direction == BOTTOM)
	 || (m_Map[nY][nX].GetID() == 7 && m_Direction == BOTTOM)
	 || (m_Map[nY][nX].GetID() == 8 && m_Direction == BOTTOM)
	 || (m_Map[nY][nX].GetID() == 10 && m_Direction == BOTTOM) )
	 && !m_bCourseOK )
	{
		//BOTTOM
		m_Check[nY][nX] = 1;
		m_Stack[nN] = BOTTOM;

		Course(nN+1, nX, nY+1);
	}

	switch( m_Map[nY][nX].GetID() )
	{
	case 6:
		while( 1 )
		{
			r = rand()%4;
		
			switch( r )
			{
			case 0:
				continue;
			case 1:
				if( m_Stack[nN-1] == BOTTOM || m_Stack[nN] == TOP )
					continue;
				m_Direction = TOP;
				break;
			case 2:
				if( m_Stack[nN-1] == LEFT || m_Stack[nN] == RIGHT )
					continue;
				m_Direction = RIGHT;
				break;
			case 3:
				if( m_Stack[nN-1] == TOP || m_Stack[nN] == BOTTOM )
					continue;
				m_Direction = BOTTOM;
				break;
			}
			break;
		}
		break;
	case 7:
		while( 1 )
		{
			r = rand()%4;
		
			switch( r )
			{
			case 0:
				if( m_Stack[nN-1] == RIGHT || m_Stack[nN] == LEFT )
					continue;
				m_Direction = LEFT;
				break;
			case 1:
				continue;
			case 2:
				if( m_Stack[nN-1] == LEFT || m_Stack[nN] == RIGHT )
					continue;
				m_Direction = RIGHT;
				break;
			case 3:
				if( m_Stack[nN-1] == TOP || m_Stack[nN] == BOTTOM )
					continue;
				m_Direction = BOTTOM;
				break;
			}
			break;
		}
		break;
	case 8:
		while( 1 )
		{
			r = rand()%4;
		
			switch( r )
			{
			case 0:
				if( m_Stack[nN-1] == RIGHT || m_Stack[nN] == LEFT )
					continue;
				m_Direction = LEFT;
				break;
			case 1:
				if( m_Stack[nN-1] == BOTTOM || m_Stack[nN] == TOP )
					continue;
				m_Direction = TOP;
				break;
			case 2:
				continue;
			case 3:
				if( m_Stack[nN-1] == TOP || m_Stack[nN] == BOTTOM )
					continue;
				m_Direction = BOTTOM;
				break;
			}
			break;
		}
		break;
	case 9:
		while( 1 )
		{
			r = rand()%4;
		
			switch( r )
			{
			case 0:
				if( m_Stack[nN-1] == RIGHT || m_Stack[nN] == LEFT )
					continue;
				m_Direction = LEFT;
				break;
			case 1:
				if( m_Stack[nN-1] == BOTTOM || m_Stack[nN] == TOP )
					continue;
				m_Direction = TOP;
				break;
			case 2:
				if( m_Stack[nN-1] == LEFT || m_Stack[nN] == RIGHT )
					continue;
				m_Direction = RIGHT;
				break;
			case 3:
				continue;
			}
			break;
		}
		break;
	case 10:
		while( 1 )
		{
			r = rand()%4;
		
			switch( r )
			{
			case 0:
				if( m_Stack[nN-1] == RIGHT || m_Stack[nN] == LEFT )
					continue;
				m_Direction = LEFT;
				break;
			case 1:
				if( m_Stack[nN-1] == BOTTOM || m_Stack[nN] == TOP )
					continue;
				m_Direction = TOP;
				break;
			case 2:
				if( m_Stack[nN-1] == LEFT || m_Stack[nN] == RIGHT )
					continue;
				m_Direction = RIGHT;
				break;
			case 3:
				if( m_Stack[nN-1] == TOP || m_Stack[nN] == BOTTOM )
					continue;
				m_Direction = BOTTOM;
				break;
			}

			break;
		}
		break;
	}

	if( m_Check[nY][nX-1] == 0 && nX-1 >= 0
	 && ( m_Map[nY][nX].GetID() == 0 || m_Map[nY][nX].GetID() == 2
	 || m_Map[nY][nX].GetID() == 4
	 || (m_Map[nY][nX].GetID() == 7 && m_Direction == LEFT)
	 || (m_Map[nY][nX].GetID() == 8 && m_Direction == LEFT)
	 || (m_Map[nY][nX].GetID() == 9 && m_Direction == LEFT)
	 || (m_Map[nY][nX].GetID() == 10 && m_Direction == LEFT) )
	 && !m_bCourseOK )
	{
		//LEFT
		m_Check[nY][nX] = 1;
		m_Stack[nN] = LEFT;

		Course(nN+1, nX-1, nY);
	}
	else if( m_Check[nY-1][nX] == 0 && nY-1 >= 0
		  && ( m_Map[nY][nX].GetID() == 1 || m_Map[nY][nX].GetID() == 2
		  || m_Map[nY][nX].GetID() == 3
		  || (m_Map[nY][nX].GetID() == 6 && m_Direction == TOP)
		  || (m_Map[nY][nX].GetID() == 8 && m_Direction == TOP)
		  || (m_Map[nY][nX].GetID() == 9 && m_Direction == TOP)
		  || (m_Map[nY][nX].GetID() == 10 && m_Direction == TOP) )
		  && !m_bCourseOK )
	{
		//TOP
		m_Check[nY][nX] = 1;
		m_Stack[nN] = TOP;

		Course(nN+1, nX, nY-1);
	}
	if( m_Check[nY][nX+1] == 0 && nX+1 <= _MAP_WIDTH
	 && ( m_Map[nY][nX].GetID() == 0 || m_Map[nY][nX].GetID() == 3
	 || m_Map[nY][nX].GetID() == 5
	 || (m_Map[nY][nX].GetID() == 6 && m_Direction == RIGHT)
	 || (m_Map[nY][nX].GetID() == 7 && m_Direction == RIGHT)
	 || (m_Map[nY][nX].GetID() == 9 && m_Direction == RIGHT)
	 || (m_Map[nY][nX].GetID() == 10 && m_Direction == RIGHT) )
	 && !m_bCourseOK )
	{
		//RIGHT
		m_Check[nY][nX] = 1;
		m_Stack[nN] = RIGHT;

		Course(nN+1, nX+1, nY);
	}
	if( m_Check[nY+1][nX] == 0 && nY+1 <= _MAP_HEIGHT
	 && ( m_Map[nY][nX].GetID() == 1 || m_Map[nY][nX].GetID() == 4
	 || m_Map[nY][nX].GetID() == 5
	 || (m_Map[nY][nX].GetID() == 6 && m_Direction == BOTTOM)
	 || (m_Map[nY][nX].GetID() == 7 && m_Direction == BOTTOM)
	 || (m_Map[nY][nX].GetID() == 8 && m_Direction == BOTTOM)
	 || (m_Map[nY][nX].GetID() == 10 && m_Direction == BOTTOM) )
	 && !m_bCourseOK )
	{
		//BOTTOM
		m_Check[nY][nX] = 1;
		m_Stack[nN] = BOTTOM;

		Course(nN+1, nX, nY+1);
	}
}

void CVisitor::Move()
{
	switch( m_Stack[m_nCurCnt] )
	{
	case LEFT:
		m_Dest.nX = m_Cur.nX-1;
		m_Dest.nY = m_Cur.nY;
		break;
	case TOP:
		m_Dest.nX = m_Cur.nX;
		m_Dest.nY = m_Cur.nY-1;
		break;
	case RIGHT:
		m_Dest.nX = m_Cur.nX+1;
		m_Dest.nY = m_Cur.nY;
		break;
	case BOTTOM:
		m_Dest.nX = m_Cur.nX;
		m_Dest.nY = m_Cur.nY+1;
		break;
	}

	if( m_Map[m_Dest.nY][m_Dest.nX].GetX() - _VISITOR_SPEED <= GetX()
	 && m_Map[m_Dest.nY][m_Dest.nX].GetX() + _VISITOR_SPEED >= GetX() )
	{
		SetX(m_Map[m_Dest.nY][m_Dest.nX].GetX());
	}
	if( m_Map[m_Dest.nY][m_Dest.nX].GetY() - _VISITOR_SPEED <= GetY()
	 && m_Map[m_Dest.nY][m_Dest.nX].GetY() + _VISITOR_SPEED >= GetY() )
	{
		SetY(m_Map[m_Dest.nY][m_Dest.nX].GetY());
	}

	if( GetX() == m_Map[m_Dest.nY][m_Dest.nX].GetX()
	 && GetY() == m_Map[m_Dest.nY][m_Dest.nX].GetY()
	 && ( m_Cur.nX != m_Dest.nX || m_Cur.nY != m_Dest.nY ) )
		m_Cur = m_Dest;

	if( m_Cur.nX == m_Dest.nX && m_Cur.nY == m_Dest.nY )
		m_nCurCnt++;
	else
	{
		switch( m_Stack[m_nCurCnt] )
		{
		case LEFT:
			if( m_Direction != m_Stack[m_nCurCnt] )
				m_nFrame = m_nMotion = 0;
			SetX(GetX() - _VISITOR_SPEED);
			m_Direction = LEFT;
			break;
		case TOP:
			if( m_Direction != m_Stack[m_nCurCnt] )
				m_nFrame = m_nMotion = 0;
			SetY(GetY() - _VISITOR_SPEED);
			m_Direction = TOP;
			break;
		case RIGHT:
			if( m_Direction != m_Stack[m_nCurCnt] )
				m_nFrame = m_nMotion = 0;
			SetX(GetX() + _VISITOR_SPEED);
			m_Direction = RIGHT;
			break;
		case BOTTOM:
			if( m_Direction != m_Stack[m_nCurCnt] )
				m_nFrame = m_nMotion = 0;
			SetY(GetY() + _VISITOR_SPEED);
			m_Direction = BOTTOM;
			break;
		}
	}
}

void CVisitor::SetCur(int nX, int nY)
{
	m_Cur.nX = nX;
	m_Cur.nY = nY;
}

bool CVisitor::IsFinish()
{
	if( m_Cur.nX == _GAME_END_X
	 && m_Cur.nY == _GAME_END_Y )
		return true;

	return false;
}

bool CVisitor::Update(float fDeltaTime)
{
	m_nFrame++;

	if( !(m_nFrame % _ANIMATION_TERM) )
	{
		m_nMotion++;

		if( ( m_Direction == TOP || m_Direction == BOTTOM )
		 && m_nMotion > 1 )
		{
			m_nMotion = 0;
			m_nFrame = 0;
		}
		else if( m_nMotion > 2 )
		{
			m_nMotion = 0;
			m_nFrame = 0;
		}
	}

	return true;
}

bool CVisitor::Render()
{
	RECT rect;
	SetRect(&rect, 57*m_nMotion, 0, 57*(m_nMotion+1), 103);
	TManager->TDraw(200+(m_nType*10)+m_Direction, GetX()+4.0f, GetY()-60.0f, &rect);

	return true;
}