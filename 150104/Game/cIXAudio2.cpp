#include "cIXAudio2.h"

cIXAudio2::cIXAudio2(void)
{
	m_pXAudio2 = NULL;
	m_pMasteringVoice = NULL;

	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	if(FAILED( XAudio2Create(&m_pXAudio2) ))
	{
		CoUninitialize();
		return;
	}

	if(FAILED( m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice) ))
	{
		return;
	}
}

cIXAudio2::~cIXAudio2(void)
{
	m_pMasteringVoice->DestroyVoice();
	CoUninitialize();
}
