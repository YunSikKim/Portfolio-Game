#pragma once

class cWorld
{
private:
	float m_fGravity;
public:
	cWorld();
	~cWorld();

	virtual void SetGravity(float fGravity);
	float GetGravity() { return m_fGravity; };
};