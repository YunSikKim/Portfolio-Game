#include "cFlag.h"

cFlag::cFlag()
{
	TManager->TLoad(200, "./Images/Play/Finish.png");

	m_fX = m_fY = 0;

	m_nType = 0;

	m_bFlag = false;
}

cFlag::~cFlag()
{
	
}

void cFlag::SetWorld(cWorld* pWorld)
{
	m_pWorld = pWorld;
}

void cFlag::SetForce(float fForce)
{
	m_fForce = fForce;
}

bool cFlag::IsCrash(float fTargetX, float fTargetY, float fTargetWidth, float fTargetHeight)
{
	self.left = m_fX;
	self.top = m_fY;
	self.right = m_fX + FLAG_SIZE_X;
	self.bottom = m_fY + FLAG_SIZE_Y;

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

bool cFlag::Update(float fDeltaTime)
{
	if( !m_bFlag )
		m_fX -= CAMERA_TILE_SPEED;

	return true;
}

bool cFlag::Render()
{
	TManager->TDraw(200, m_fX, m_fY);

	return true;
}