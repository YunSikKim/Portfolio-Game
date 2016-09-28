#include "cWindow.h"

D3DPRESENT_PARAMETERS	g_d3dpp;
LPDIRECT3D9				g_pD3D;
LPDIRECT3DDEVICE9		g_pd3dDevice;
LPD3DXSPRITE			g_pSprite;

HRESULT InitD3D(HWND hWnd, int nWidth, int nHeight, bool nWindowed)
{
	HRESULT hTemp;

	// Direct3D 객체 생성
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if(NULL == g_pD3D)
		return E_FAIL;

	// Direct3D 파라미터 설정
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed				= nWindowed;
	d3dpp.SwapEffect			= D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat		= D3DFMT_UNKNOWN;
	d3dpp.BackBufferWidth		= nWidth;
	d3dpp.BackBufferHeight		= nHeight;
	d3dpp.BackBufferCount		= 1;

	// Direct3D 디바이스 생성
	hTemp = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
								 D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
								 &d3dpp, &g_pd3dDevice);

	if(FAILED(hTemp))
		return E_FAIL;

	// 창모드시
	if(nWindowed)
	{
		DWORD	dwStyle = GetWindowLong(hWnd, GWL_STYLE);
		RECT	rc      = {0, 0, nWidth, nHeight};
		AdjustWindowRect(&rc, dwStyle, FALSE);

		SetWindowPos(hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);
	}

	return S_OK;
}

void DestroyD3D()
{
	if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}

bool LoadD3D()
{
	if(FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSprite)))
		return false;

	return true;
}

void UnloadD3D()
{
	if(g_pSprite)
		g_pSprite->Release();
}

void ResetD3D()
{
	g_pSprite->OnLostDevice();
	g_pd3dDevice->Reset(&g_d3dpp);
	g_pSprite->OnResetDevice();
}