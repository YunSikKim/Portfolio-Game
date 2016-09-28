#include "cFruit.h"

cFruit::cFruit()
{
	TManager->TLoad(300, "./Images/Play/Furit.png");

	frame = 0;

	m_nAdd = ITEM_FRUIT_SCORE;
	m_nAnimation = 1;
	m_nAniStep = 1;

	m_fForce = TILE_MASH;

	m_fX = m_fY = 0;
}

cFruit::~cFruit()
{
}

bool cFruit::IsCrash(float fTargetX, float fTargetY, float fTargetWidth, float fTargetHeight)
{
	self.left = m_fX;
	self.top = m_fY;
	self.right = m_fX + ITEM_FRUIT_SIZE;
	self.bottom = m_fY + ITEM_FRUIT_SIZE;

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

bool cFruit::Update(float fDeltaTime)
{
	frame++;

	if( frame == 20 )
	{
		if( BETWEEN(1, m_nAniStep, 3) )
		{
			m_nAnimation++;
			m_nAniStep++;
			frame = 0;
		}
		else if( BETWEEN(3, m_nAniStep, 5) )
		{
			m_nAnimation--;
			m_nAniStep++;
			frame = 0;
		}
		else
		{
			m_nAnimation = 1;
			m_nAniStep = 1;
			frame = 0;
		}
	}

	m_fX -= CAMERA_TILE_SPEED;

	return true;
}

bool cFruit::Render()
{
	RECT rt = {(m_nAnimation-1)*ITEM_FRUIT_SIZE, 0, m_nAnimation*ITEM_FRUIT_SIZE, ITEM_FRUIT_SIZE};

	TManager->TDraw(300, m_fX, m_fY, &rt);

	return true;
}