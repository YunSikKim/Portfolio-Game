#pragma once
#define _MAP_LEFT_GAP 50.0f
#define _MAP_TOP_GAP 50.0f
#define _MAP_WIDTH 20
#define _MAP_HEIGHT 10
#define _TILE_SIZE 64.0f

#include <time.h>
#include <fstream>
#include <list>
#include "Tile.h"
#include "Visitor.h"

using namespace std;

class cGameMain
{
private:
	list<CVisitor*>::iterator iter;
	list<CVisitor*> m_VList;
	ifstream file;
	CTile** m_Map;

	int frame;
public:
	cGameMain();
	~cGameMain();

	bool Update(float fDeltaTime);
	bool Render();
};

