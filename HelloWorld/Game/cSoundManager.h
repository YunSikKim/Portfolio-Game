#pragma once

#include <map>

#include "singleton.h"
#include "cSourceVoice.h"

using std::map;

class cSoundManager : public Singleton <cSoundManager>
{
private:
	map<int, cSourceVoice*> m_SoundMap;
public:
	cSoundManager(void);
	~cSoundManager(void);

	void Clear();

	void AddSound(int nID, char* szPath);
	void Play(int nID) { m_SoundMap[nID]->Play(); }
	void Stop(int nID) { m_SoundMap[nID]->Stop(); }
	void Pause(int nID) { m_SoundMap[nID]->Pause(); }
	void Replay(int nID) { m_SoundMap[nID]->Replay(); }
};

extern cSoundManager* SManager;