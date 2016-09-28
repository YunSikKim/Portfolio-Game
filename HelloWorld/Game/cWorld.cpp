#include "cWorld.h"

cWorld::cWorld()
{
	m_fGravity = 0;
}

cWorld::~cWorld()
{

}

void cWorld::SetGravity(float fGravity)
{
	m_fGravity = fGravity * -1;
}
