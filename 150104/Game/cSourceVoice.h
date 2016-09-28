#pragma once
#include <xaudio2.h>
#include "cIXAudio2.h"
#include "WaveFile.h"

// �Ҹ��� �����Ű�� ���� Ŭ����
// ����ü IXAudio2SorceVoice�� ������� �Ͽ� ����
// ��� cSourceVoice ��ü�� IXAudio2 ������ ������
class cSourceVoice : public IXAudio2VoiceCallback
{
private:
	static cIXAudio2* s_pXAudio2;

	IXAudio2SourceVoice* m_pSourceVoice;
	BYTE* m_pbWaveData;
	DWORD m_cbWaveSize;
	XAUDIO2_BUFFER m_buffer;

	enum EPLAYSTATE
	{
		ePLAY,
		eSTOP,
		ePAUSE,
	};
	EPLAYSTATE m_State;		// �ݹ��Լ� ȣ��� ���ѷ��� ����
	

public:
	cSourceVoice(char* szPath);
	~cSourceVoice(void);

	static void InitXAudio2();
	static void DeleteXAudio2();

	void Play();
	void Stop();
	void Pause();
	void Replay();

	// IXAudio2VoiceCallback �ݹ��Լ�. OnBufferEnd�� �����
	STDMETHOD_(void, OnStreamEnd) (THIS) {   }
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {  }
	STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) { }
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext);
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) { }
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {  }
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) { }
};

