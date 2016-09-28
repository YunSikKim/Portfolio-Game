#pragma once

#include "cDefine.h"
#include "cObject.h"

#include "cTextureManager.h"

class cFlag : public cObject
{
private:
	cWorld* m_pWorld;
	RECT self;
	float m_fX, m_fY;
	float m_fForce;
	int m_nType;

	bool m_bFlag;
public:
	cFlag();
	~cFlag();

	void SetWorld(cWorld* pWorld);
	void Gravity() { m_fY -= m_pWorld->GetGravity() + m_fForce; };

	void SetForce(float fForce);
	void SetFlag(bool bState) { m_bFlag = bState; };

	bool IsCrash(float fTargetX, float fTargetY, float fTargetWidth, float fTargetHeight);
	bool IsFlag() { return m_bFlag; };

	float GetX() { return m_fX; };
	float GetY() { return m_fY; };
	
	void SetX(float fX) { m_fX = fX; };
	void SetY(float fY) { m_fY = fY; };
	void SetType(int nType) { m_nType = nType; };
	
	bool Update(float fDeltaTime);
	bool Render();
};

