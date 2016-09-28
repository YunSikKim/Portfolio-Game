#pragma once

#include "cDefine.h"
#include "cItem.h"

#include "cTextureManager.h"

class cFruit : public cItem
{
private:
	RECT self;
	cWorld* m_pWorld;
	float m_fX, m_fY;
	float m_fForce;

	int m_nAdd;
	int m_nAnimation;
	int m_nAniStep;

	int frame;
public:
	cFruit();
	~cFruit();

	virtual void SetWorld(cWorld* pWorld) { m_pWorld = pWorld; };
	void Gravity() { m_fY -= m_pWorld->GetGravity() + m_fForce; };

	virtual float GetX() { return m_fX + GetGravity(); };
	virtual float GetY() { return m_fY + GetGravity(); };

	virtual void SetX(float fX) { m_fX = fX; };
	virtual void SetY(float fY) { m_fY = fY; };

	bool IsCrash(float fTargetX, float fTargetY, float fTargetWidth, float fTargetHeight);

	bool Update(float fDeltaTime);
	bool Render();
};

