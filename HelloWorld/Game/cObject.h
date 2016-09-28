#pragma once

#include "cWorld.h"

class cObject : public cWorld
{
private:
	cWorld* m_pWorld;
	float m_fX, m_fY;
	float m_fForce;
public:
	virtual void SetWorld(cWorld* pWorld) { m_pWorld = pWorld; };

	virtual float GetX() { return m_fX + GetGravity(); };
	virtual float GetY() { return m_fY + GetGravity(); };

	virtual void SetX(float fX) { m_fX = fX; };
	virtual void SetY(float fY) { m_fY = fY; };

	virtual bool Update(float fDeltaTime)=0;
	virtual bool Render()=0;
};

