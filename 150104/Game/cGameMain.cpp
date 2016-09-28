#include "cGameMain.h"

cGameMain::cGameMain()
: frame(0)
{
	srand(time(NULL));
	m_Map = new CTile*[_MAP_HEIGHT];
	for(int i=0; i<_MAP_HEIGHT; i++)
		m_Map[i] = new CTile[_MAP_WIDTH];

	file.open("./CSV/TileMap.csv");
	
	m_VList.push_back(new CVisitor(0, _MAP_LEFT_GAP, _MAP_TOP_GAP));

	for(int i=0; i<_MAP_HEIGHT; i++)
	{
		int id;
		char c;

		for(int j=0; j<_MAP_WIDTH; j++)
		{
			if( j < _MAP_WIDTH-1 )
				file >> id >> c;
			else
				file >> id;
			m_Map[i][j].SetID(id);
			m_Map[i][j].SetX(_MAP_LEFT_GAP+_TILE_SIZE*j);
			m_Map[i][j].SetY(_MAP_TOP_GAP+_TILE_SIZE*i);
		}
	}

	for(iter=m_VList.begin(); iter!=m_VList.end(); iter++)
	{
		if( iter != m_VList.end() )
		{
			(*iter)->MapInit(&m_Map);
			(*iter)->Course(0, 0, 0);
		}
	}
}

cGameMain::~cGameMain()
{

}

bool cGameMain::Update(float fDeltaTime)
{
	frame++;

	if( frame == 30 )
	{
		m_VList.push_back(new CVisitor(rand()%4, _MAP_LEFT_GAP, _MAP_TOP_GAP));
		frame = 0;
	}

	for(iter=m_VList.begin(); iter!=m_VList.end(); iter++)
	{
		if( iter != m_VList.end() )
		{
			(*iter)->MapInit(&m_Map);
			(*iter)->Course(0, 0, 0);
		}
	}

	for(iter=m_VList.begin(); iter!=m_VList.end(); iter++)
		if( iter != m_VList.end() )
			(*iter)->Update(fDeltaTime);

	for(iter=m_VList.begin(); iter!=m_VList.end(); iter++)
		if( iter != m_VList.end() )
			(*iter)->Move();

	for(iter=m_VList.begin(); iter!=m_VList.end();)
	{
		if( (*iter)->IsFinish() )
		{
			list<CVisitor*>::iterator temp;
			temp = iter;
			iter++;
			m_VList.erase(temp);
		}
		else
			iter++;
	}	
	
	return true;
}

bool cGameMain::Render()
{
	for(int i=0; i<_MAP_HEIGHT; i++)
		for(int j=0; j<_MAP_WIDTH; j++)
				m_Map[i][j].Render();

	for(iter=m_VList.begin(); iter!=m_VList.end(); iter++)
		if( iter != m_VList.end() )
			(*iter)->Render();

	return true;
}