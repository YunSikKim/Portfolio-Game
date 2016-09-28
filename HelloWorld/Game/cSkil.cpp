#include "cSkil.h"

cSkil::cSkil()
{
	TManager->TLoad(400, "./Images/Play/Speed.png");
	TManager->TLoad(401, "./Images/Play/Jump.png");

	m_fX = m_fY = 0;
	m_fForce = TILE_MASH;

	m_nType = 0;
}

cSkil::~cSkil()
{

}

bool cSkil::IsCrash(float fTargetX, float fTargetY, float fTargetWidth, float fTargetHeight)
{
	self.left = m_fX;
	self.top = m_fY;
	self.right = m_fX + ITEM_SKIL_SIZE;
	self.bottom = m_fY + ITEM_SKIL_SIZE;

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

bool cSkil::Update(float fDeltaTime)
{
	m_fX -= CAMERA_TILE_SPEED;

	return true;
}

bool cSkil::Render()
{
	switch( m_nType )
	{
	case 0:
		TManager->TDraw(400, m_fX, m_fY);
		break;

	case 1:
		TManager->TDraw(401, m_fX, m_fY);
		break;
	}

	return true;
}