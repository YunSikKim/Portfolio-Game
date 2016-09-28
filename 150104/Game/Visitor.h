#pragma once
#define _GAME_END_X 19
#define _GAME_END_Y 0
#define _MAP_WIDTH 20
#define _MAP_HEIGHT 10
#define _VISITOR_SPEED 6.0f
#define _ANIMATION_TERM 10

#include "Obj.h"
#include "Tile.h"

#include "cTextureManager.h"

enum DIRECTION
{
	LEFT,
	TOP,
	RIGHT,
	BOTTOM
};

class CVisitor : public CObj
{
private:
	CTile** m_Map;
	int m_Check[_MAP_HEIGHT][_MAP_WIDTH];
	int m_nType;
	int m_nStackCnt;
	int m_nCurCnt;
	int m_nFrame;
	int m_nMotion;
	bool m_bCourseOK;
	MapPos m_Cur;
	MapPos m_Dest;
	DIRECTION m_Direction;
	DIRECTION m_Stack[200];
public:
	CVisitor(int nType, float fX, float fY);
	~CVisitor();

	void MapInit(CTile*** Map);
	void Course(int nN, int nX, int nY);
	void Move();
	
	void SetCur(int nX, int nY);

	MapPos GetCur() { return m_Cur; };
	MapPos GetDest() { return m_Dest; };

	bool IsFinish();

	bool Update(float fDeltaTime);
	bool Render();
};

