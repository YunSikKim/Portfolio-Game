#pragma once

#include "cDefine.h"
#include "cItem.h"

#include "cTextureManager.h"

class cSkil : public cItem
{
private:
	RECT self;
	cWorld* m_pWorld;
	float m_fX, m_fY;
	float m_fForce;

	int m_nType;
public:
	cSkil();
	~cSkil();

	void SetWorld(cWorld* pWorld) { m_pWorld = pWorld; };
	void Gravity() { m_fY -= m_pWorld->GetGravity() + m_fForce; };

	float GetX() { return m_fX + GetGravity(); };
	float GetY() { return m_fY + GetGravity(); };
	int GetType() { return m_nType; };

	void SetX(float fX) { m_fX = fX; };
	void SetY(float fY) { m_fY = fY; };
	void SetType(int nType) { m_nType = nType; };
	
	bool IsCrash(float fTargetX, float fTargetY, float fTargetWidth, float fTargetHeight);

	bool Update(float fDeltaTime);
	bool Render();
};

