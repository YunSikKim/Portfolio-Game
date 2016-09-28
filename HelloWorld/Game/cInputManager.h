#pragma once
#include "cWindow.h"
#include <dinput.h>
#include <tchar.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

typedef struct st_MousePos
{
	LONG MX;
	LONG MY;
}MousePos;

class cInputManager
{
private:
	MousePos m_MousePos;

	LPDIRECTINPUT8			m_pDi;
	LPDIRECTINPUTDEVICE8	m_pDidevKey;
	LPDIRECTINPUTDEVICE8	m_pDidevMouse;

	BYTE					m_KeyBeforeState[256];
	BYTE					m_KeyState[256];	

	DIMOUSESTATE			m_MouseBeforeState;
	DIMOUSESTATE			m_MouseState;
	
	HRESULT					m_temp;
	BOOL					m_IsInClientRect;

	BOOL KeyProcess(BYTE *pKey);
	BOOL MouseProcess(DIMOUSESTATE *pMouseState);	
	BOOL PreProcess();
public:
	BOOL Init();
	BOOL InitKeyboard();
	BOOL InitMouse();
	BOOL InitDirectInput(BOOL IsKeyboard, BOOL IsMouse);

	BOOL Update();
	BOOL Render();
	BOOL Release();

	BOOL IsKeyDown(DWORD dKeyCode);
	BOOL IsKeyUp(DWORD dKeyCode);
	BOOL IsKeyPress(DWORD dKeyCode);

	BOOL IsMouseDown(int nMouseCode);
	BOOL IsMouseUp(int nMouseCode);
	BOOL IsMousePress(int nMouseCode);

	MousePos *GetMousePos();
	void SetMousePos(LONG lMX, LONG lMY);

	cInputManager();
	virtual ~cInputManager();
};

extern cInputManager* IManager;