#pragma once

#include "Obj.h"

#include "cTextureManager.h"

class CTile : public CObj
{
private:
	int m_nID;
public:
	CTile();
	~CTile();

	void SetID(int nValue) { m_nID = nValue; };

	int GetID() { return m_nID; };

	bool Render();
};

