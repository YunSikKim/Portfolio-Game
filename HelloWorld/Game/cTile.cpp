#include "cTile.h"

cTile::cTile()
{
	TManager->TLoad(100, "./Images/Play/Tile.png");
	TManager->TLoad(101, "./Images/Play/Tile2.png");

	m_fX = m_fY = 0;

	m_nType = 0;
	m_bFlag = false;
}

cTile::~cTile()
{
	
}

void cTile::SetWorld(cWorld* pWorld)
{
	m_pWorld = pWorld;
}

void cTile::SetForce(float fForce)
{
	m_fForce = fForce;
}

bool cTile::IsCrash(float fTargetX, float fTargetY, float fTargetWidth, float fTargetHeight)
{
	self.left = m_fX;
	self.top = m_fY;
	self.right = m_fX + TILE_SIZE;
	self.bottom = m_fY + TILE_SIZE;

	RECT target = {fTargetX, fTargetY, fTargetX+fTargetWidth, fTargetY+fTargetHeight};

	if( self.right < target.left || self.left > target.right )
	{
		return false;
	}
	if( self.bottom < target.top || self.top > target.bottom )
	{
		return false;
	}

	return true;
}

bool cTile::Update(float fDeltaTime)
{
	if( !m_bFlag )
		m_fX -= CAMERA_TILE_SPEED;

	return true;
}

bool cTile::Render()
{
	switch( m_nType )
	{
	case 1:
		TManager->TDraw(100, m_fX, m_fY);
		break;

	case 2:
		TManager->TDraw(101, m_fX, m_fY);
		break;
	}

	return true;
}