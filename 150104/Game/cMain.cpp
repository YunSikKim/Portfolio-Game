#include "cMain.h"
#include "cSourceVoice.h"

#define Width 1400						// 윈도우 가로 길이
#define Height 800						// 윈도우 세로 길이
#define Name L"EASY FrameWork v1.20"	// 윈도우 제목표시줄 (" " 안을 수정)
#define Windowed true					// 창모드=true, 전체화면=false

HWND g_hWnd = NULL;
HINSTANCE g_Instance = NULL;

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_DESTROY:
            delete GAME;
			delete IManager;
            PostQuitMessage( 0 );
            return 0;

		case WM_MOUSEMOVE:
			int nX = 0;
			int nY = 0;

			nX = LOWORD(lParam);
			nY = HIWORD(lParam);

			IManager->SetMousePos(nX, nY);

        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	wc.style			= CS_CLASSDC;
	wc.lpfnWndProc		= MsgProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= GetModuleHandle(NULL);
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= L"Main";

	RegisterClass(&wc);

	g_Instance = hInstance;

	HWND hWnd = CreateWindow(L"Main",
							 Name,				// 제목표시줄
					 		 WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX, 
							 0, 0, CW_USEDEFAULT, CW_USEDEFAULT,
							 GetDesktopWindow(),
							 NULL,
							 wc.hInstance,
							 NULL );

	if(S_OK != InitD3D(hWnd, Width, Height, Windowed))
	{
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 0;
	}

	if(!LoadD3D())
	{
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	IManager->Init();
	cSourceVoice::InitXAudio2();
	GAME = new cGame();

	g_fLastTime = timeGetTime() * 0.001f;

	while(1)
	{
		MSG msg;

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(WM_QUIT == msg.message)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			UpdateD3D();
			RenderD3D();
		}
	}
	
	UnloadD3D();
	DestroyD3D();

	UnregisterClass(wc.lpszClassName, wc.hInstance);

	return 0;
}


void UpdateD3D()
{
	float fCurTime = (float)timeGetTime() * 0.001f;

	g_fFPS = fCurTime - g_fLastTime;

	g_fLastTime = fCurTime;
	
	GAME->Update(g_fFPS);
	IManager->Update();
}

void RenderD3D()
{
	if(FAILED(g_pd3dDevice->TestCooperativeLevel()))
		ResetD3D();

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(256,256,256), 0.0f, 0);

	g_pd3dDevice->BeginScene();
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// 실제 Render가 이루어지는 곳
	GAME->Render();

	g_pSprite->End();
	g_pd3dDevice->EndScene();
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}