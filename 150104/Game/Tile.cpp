#include "Tile.h"

CTile::CTile()
{
	TManager->TLoad(111, "./Images/tile.png");
	TManager->TLoad(112, "./Images/wood.png");
	TManager->TLoad(113, "./Images/marble.png");
	TManager->TLoad(100, "./Images/ropelr.png");
	TManager->TLoad(101, "./Images/ropeud.png");
	TManager->TLoad(102, "./Images/ropelu.png");
	TManager->TLoad(103, "./Images/ropeur.png");
	TManager->TLoad(104, "./Images/ropeld.png");
	TManager->TLoad(105, "./Images/roperd.png");
	TManager->TLoad(106, "./Images/ropeurd.png");
	TManager->TLoad(107, "./Images/ropelrd.png");
	TManager->TLoad(108, "./Images/ropelud.png");
	TManager->TLoad(109, "./Images/ropelur.png");
	TManager->TLoad(110, "./Images/ropelurd.png");
}

CTile::~CTile()
{

}

bool CTile::Render()
{
	TManager->TDraw(112, GetX(), GetY());

	if( m_nID >= 0 )
		TManager->TDraw(100+m_nID, GetX(), GetY());
	
	return true;
}