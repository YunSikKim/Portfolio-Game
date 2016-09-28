#include "cInputManager.h"

#define B_DOWN(m_Key) (((m_KeyBeforeState[m_Key]) & 0x80) ? true : false)
#define B_UP(m_Key) (((m_KeyBeforeState[m_Key]) & 0x80) ? false : true)
#define DOWN(m_Key) (((m_KeyState[m_Key]) & 0x80) ? true : false)
#define UP(m_Key) (((m_KeyState[m_Key]) & 0x80) ? false : true)

cInputManager::cInputManager():m_pDi(NULL), m_pDidevKey(NULL), m_pDidevMouse(NULL), m_temp(S_OK), m_IsInClientRect(FALSE)
{
	memset(&m_MousePos, 0, sizeof(MousePos));

	memset(m_KeyBeforeState, 0, sizeof(BYTE)*256);
	memset(m_KeyState, 0, sizeof(BYTE)*256);

	memset(&m_MouseBeforeState, 0, sizeof(DIMOUSESTATE));
	memset(&m_MouseState, 0, sizeof(DIMOUSESTATE));
}


cInputManager::~cInputManager()
{
	Release();
}

BOOL cInputManager::Release()
{
	BOOL IsReturn = TRUE;

	if(m_pDi)
	{
		if(m_pDidevKey)
		{
			m_pDidevKey->Unacquire();
			m_pDidevKey->Release();
			m_pDidevKey = NULL;
		}
		if(m_pDidevMouse)
		{
			m_pDidevMouse->Unacquire();
			m_pDidevMouse->Release();
			m_pDidevMouse = NULL;
		}

		m_pDi->Release();
		m_pDi = NULL;
	}

	return IsReturn;
}

BOOL cInputManager::InitKeyboard()
{
	BOOL IsReturn = TRUE;

	if(FAILED(m_pDi->CreateDevice(GUID_SysKeyboard, &m_pDidevKey, NULL)))
		return FALSE;
	if(FAILED(m_pDidevKey->SetDataFormat(&c_dfDIKeyboard)))
		return FALSE;
	if(FAILED(m_pDidevKey->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY)))
		return FALSE;

	while(DIERR_INPUTLOST == m_pDidevKey->Acquire());
	
	return IsReturn;
}

BOOL cInputManager::InitMouse()
{
	BOOL IsReturn = TRUE;

	if(FAILED(m_pDi->CreateDevice(GUID_SysMouse, &m_pDidevMouse, NULL)))
		return false;
	if(FAILED(m_pDidevMouse->SetDataFormat(&c_dfDIMouse)))
		return false;
	if(FAILED(m_pDidevMouse->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
		return false;
	while(DIERR_INPUTLOST == m_pDidevMouse->Acquire());

	return IsReturn;
}

BOOL cInputManager::InitDirectInput(BOOL IsKeyboard, BOOL IsMouse)
{
	HRESULT temp;

	if(FAILED(temp = DirectInput8Create(g_Instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDi, NULL)))
	{
		return FALSE;
	}
	if(IsKeyboard) InitKeyboard();
	if(IsMouse) InitMouse();
	
	return TRUE;		
}

BOOL cInputManager::Init()
{
	BOOL IsReturn = TRUE;

	InitDirectInput(TRUE, TRUE);

	memset( &m_KeyBeforeState, 0, sizeof(BYTE)*256);		
	memset( &m_MouseBeforeState, 0, sizeof(DIMOUSESTATE));	
	memset( &m_KeyState, 0, sizeof(BYTE)*256);			
	memset( &m_MouseState, 0, sizeof(DIMOUSESTATE));		

	return IsReturn;
}

BOOL cInputManager::PreProcess()
{
	memcpy( &m_KeyBeforeState, &m_KeyState, sizeof(BYTE)*256);
	memcpy( &m_MouseBeforeState, &m_MouseState, sizeof(DIMOUSESTATE));
	
	return TRUE;
}

BOOL cInputManager::KeyProcess(BYTE *pKey)
{
	ZeroMemory(pKey, 256);

    if(!m_pDidevKey)
		return FALSE;

	m_temp = m_pDidevKey->GetDeviceState(256, pKey);
	if(FAILED(m_temp))							
	{
		m_temp = m_pDidevKey->Acquire();			
		while(m_temp == DIERR_INPUTLOST)			
			m_pDidevKey->Acquire();

		return FALSE;							
	}

	return TRUE;
}

BOOL cInputManager::MouseProcess(DIMOUSESTATE *pMouseState)
{
	ZeroMemory(pMouseState, sizeof(DIMOUSESTATE));

   if(!m_pDidevMouse)
	   return FALSE;

	m_temp = m_pDidevMouse->GetDeviceState(sizeof(DIMOUSESTATE), pMouseState);
	if(FAILED(m_temp))
	{
		m_temp = m_pDidevMouse->Acquire();	

		while(m_temp == DIERR_INPUTLOST)		
			m_pDidevMouse->Acquire();

		return FALSE;						
	}

	return TRUE;
}

BOOL cInputManager::Update()
{
	PreProcess();

	if(!KeyProcess(m_KeyState))
		return FALSE;				
	if(!MouseProcess(&m_MouseState))
		return FALSE;			

	POINT ptAbsMousePos;
	GetCursorPos(&ptAbsMousePos);

	RECT rtWinRect;
	GetWindowRect(g_hWnd, &rtWinRect);

	ShowCursor(TRUE);
	return TRUE;
}

BOOL cInputManager::IsKeyDown(DWORD dKeyCode)
{
	BOOL IsReturn = FALSE;

	if(B_UP(dKeyCode))
	{
		if(DOWN(dKeyCode))
			IsReturn = TRUE;
	}

	return IsReturn;
}

BOOL cInputManager::IsKeyUp(DWORD dKeyCode)
{
	BOOL IsReturn = FALSE;

	if(B_DOWN(dKeyCode))
	{
		if(!DOWN(dKeyCode))
			IsReturn = TRUE;
	}

	return IsReturn;
}

BOOL cInputManager::IsKeyPress(DWORD dKeyCode)
{
	BOOL IsReturn = FALSE;

	if(B_DOWN(dKeyCode))
	{
		if(DOWN(dKeyCode))
			IsReturn = TRUE;
	}

	return IsReturn;
}

BOOL cInputManager::IsMouseDown(int nMouseCode)
{
	BOOL IsReturn = FALSE;

	switch(nMouseCode)
	{
		case 1:
			if(!m_MouseBeforeState.rgbButtons[0])
			{
				if(m_MouseState.rgbButtons[0])
					IsReturn = TRUE;
			}
		case 2:
			if(!m_MouseBeforeState.rgbButtons[1])
			{
				if(m_MouseState.rgbButtons[1])
					IsReturn = TRUE;
			}
		case 3:
			if(!m_MouseBeforeState.rgbButtons[2])
			{
				if(m_MouseState.rgbButtons[2])
					IsReturn = TRUE;
			}
	}

	return IsReturn;
}

BOOL cInputManager::IsMouseUp(int nMouseCode)
{
	BOOL IsReturn = FALSE;

	switch(nMouseCode)
	{
		case 1:
			if(m_MouseBeforeState.rgbButtons[0])
			{
				if(!m_MouseState.rgbButtons[0])
					IsReturn = TRUE;
			}
		case 2:
			if(m_MouseBeforeState.rgbButtons[1])
			{
				if(!m_MouseState.rgbButtons[1])
					IsReturn = TRUE;
			}
		case 3:
			if(!m_MouseBeforeState.rgbButtons[2])
			{
				if(m_MouseState.rgbButtons[2])
					IsReturn = TRUE;
			}
	}

	return IsReturn;
}

BOOL cInputManager::IsMousePress(int nMouseCode)
{
	BOOL IsReturn = FALSE;

	switch(nMouseCode)
	{
		case 1:
			if(m_MouseBeforeState.rgbButtons[0])
			{
				if(m_MouseState.rgbButtons[0])
					IsReturn = TRUE;
			}
		case 2:
			if(m_MouseBeforeState.rgbButtons[1])
			{
				if(m_MouseState.rgbButtons[1])
					IsReturn = TRUE;
			}
		case 3:
			if(!m_MouseBeforeState.rgbButtons[2])
			{
				if(m_MouseState.rgbButtons[2])
					IsReturn = TRUE;
			}
	}

	return IsReturn;
}

MousePos* cInputManager::GetMousePos()
{
	return &m_MousePos;
}

void cInputManager::SetMousePos(LONG lMX, LONG lMY)
{
	m_MousePos.MX = lMX;
	m_MousePos.MY = lMY;
}

cInputManager* IManager = new cInputManager();