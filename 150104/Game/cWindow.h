#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "winmm.lib")

/***************************************************/
/* Direct X ������ ������ �⺻���� ������ ���� Ŭ���� */
/***************************************************/
extern D3DPRESENT_PARAMETERS	g_d3dpp;
extern LPDIRECT3D9				g_pD3D;
extern LPDIRECT3DDEVICE9		g_pd3dDevice;
extern LPD3DXSPRITE				g_pSprite;

extern HWND g_hWnd;
extern HINSTANCE g_Instance;

HRESULT InitD3D(HWND hWnd, int nWidth, int nHeight, bool nWindowed);

void DestroyD3D();
bool LoadD3D();
void UnloadD3D();
void ResetD3D();
