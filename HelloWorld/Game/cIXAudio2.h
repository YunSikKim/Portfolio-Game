#pragma once
#include <xaudio2.h>

class cIXAudio2
{
private:
	IXAudio2* m_pXAudio2;
	IXAudio2MasteringVoice* m_pMasteringVoice;
public:
	cIXAudio2(void);
	~cIXAudio2(void);

	IXAudio2* GetXAudio2() { return m_pXAudio2; }
	IXAudio2MasteringVoice* GetMasteringVoice() { return m_pMasteringVoice; }
};
