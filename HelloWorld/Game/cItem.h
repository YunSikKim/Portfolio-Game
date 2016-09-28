#pragma once

#include "cObject.h"

class cItem : public cObject
{
private:
	cWorld* m_pWorld;
	float m_fX, m_fY;
	float m_fForce;

	bool m_bUse;
public:
	virtual void SetWorld(cWorld* pWorld) { m_pWorld = pWorld; };
	void Gravity() { m_fY -= m_pWorld->GetGravity() + m_fForce; };

	virtual float GetX() { return m_fX + GetGravity(); };
	virtual float GetY() { return m_fY + GetGravity(); };

	virtual void SetX(float fX) { m_fX = fX; };
	virtual void SetY(float fY) { m_fY = fY; };

	virtual bool IsCrash(float fTargetX, float fTargetY, float fTargetWidth, float fTargetHeight)=0;
};

