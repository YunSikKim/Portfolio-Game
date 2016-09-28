#pragma once
#include <xaudio2.h>
#include "cIXAudio2.h"
#include "WaveFile.h"

// 소리를 재생시키기 위한 클래스
// 구조체 IXAudio2SorceVoice를 기반으로 하여 만듬
// 모든 cSourceVoice 객체는 IXAudio2 변수를 공유함
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
	EPLAYSTATE m_State;		// 콜백함수 호출시 무한루프 방지
	

public:
	cSourceVoice(char* szPath);
	~cSourceVoice(void);

	static void InitXAudio2();
	static void DeleteXAudio2();

	void Play();
	void Stop();
	void Pause();
	void Replay();

	// IXAudio2VoiceCallback 콜백함수. OnBufferEnd만 사용함
	STDMETHOD_(void, OnStreamEnd) (THIS) {   }
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {  }
	STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) { }
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext);
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) { }
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {  }
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) { }
};

