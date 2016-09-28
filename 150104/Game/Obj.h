#pragma once

struct MapPos
{
	int nX;
	int nY;
};

class CObj
{
private:
	float m_fX;
	float m_fY;
public:
	void SetX(float fValue) { m_fX = fValue; };
	void SetY(float fValue) { m_fY = fValue; };

	float GetX() { return m_fX; };
	float GetY() { return m_fY; };
};

