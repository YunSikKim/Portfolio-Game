#include "cSoundManager.h"

cSoundManager::cSoundManager(void)
{
	
}

cSoundManager::~cSoundManager(void)
{
	Clear();
}

void cSoundManager::Clear()
{
	for(map<int, cSourceVoice*>::iterator iter = m_SoundMap.begin();
		iter != m_SoundMap.end();
		iter++)
	{
		delete (iter->second);
	}
	m_SoundMap.clear();
}

void cSoundManager::AddSound(int nID, char* szPath)
{
	m_SoundMap[nID] = new cSourceVoice(szPath);
}

cSoundManager* GetSoundManager() { return cSoundManager::GetSingleton(); }

cSoundManager* SManager = new cSoundManager();