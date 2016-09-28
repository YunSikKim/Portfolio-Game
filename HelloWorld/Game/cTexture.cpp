#include "cTexture.h"


cTexture::cTexture()
{
	m_pTexture = NULL;
	m_nWidth = 0;
	m_nHeight = 0;
}


cTexture::~cTexture()
{
	Release();
}

void cTexture::TexLoad(LPCSTR cFile)
{
	D3DXIMAGE_INFO pSrcInfo;

	if(FAILED(D3DXCreateTextureFromFileExA(
			  g_pd3dDevice,
		  	  cFile,
			  D3DX_DEFAULT_NONPOW2,
			  D3DX_DEFAULT_NONPOW2,
			  1,
			  0,
			  D3DFMT_UNKNOWN,
			  D3DPOOL_MANAGED,
			  D3DX_DEFAULT,
			  D3DX_DEFAULT,
			  D3DCOLOR_ARGB(255, 255, 255, 255),
			  &pSrcInfo,
			  NULL,
			  &m_pTexture)))
	{
		m_pTexture = NULL;
	}

	m_nWidth = pSrcInfo.Width;
	m_nHeight = pSrcInfo.Height;
}

void cTexture::TexDraw(float fPosX, float fPosY, RECT* rRect, int nAlpha)
{
	if(NULL == m_pTexture)
		return;

	g_pSprite->Draw(m_pTexture, rRect, NULL, &D3DXVECTOR3(fPosX, fPosY, 0.0f), D3DCOLOR_RGBA(255, 255, 255, nAlpha));
}

void cTexture::Release()
{
	m_pTexture->Release();
	m_pTexture = NULL;

	m_nWidth = 0;
	m_nHeight = 0;
}