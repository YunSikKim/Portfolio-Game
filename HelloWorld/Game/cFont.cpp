#include "cFont.h"

cFont::cFont()
{
}

cFont::~cFont()
{
	Release();
}

void cFont::TextLoad(LPCSTR cFaceFont, int nWidth, int nHeight, int nBold)
{

	D3DXCreateFontA(g_pd3dDevice,
					nHeight,
					nWidth,
					nBold,
					1,
					false,
					HANGUL_CHARSET,
					OUT_DEFAULT_PRECIS,
					ANTIALIASED_QUALITY,
					DEFAULT_PITCH | FF_DONTCARE,
			   		cFaceFont,
					&m_pFont);
}

void cFont::TextSetting(int nData)
{
	sprintf_s(dest, "%d", nData);
}

void cFont::TextSetting(float fData)
{
	sprintf_s(dest, "%f", fData);
}

void cFont::TextDraw(LPCSTR cText, float fPosX, float fPosY, D3DCOLOR Color)
{
	RECT rt = {fPosX, fPosY, 800, 600};

	m_pFont->DrawTextA(g_pSprite, cText, -1, &rt, DT_NOCLIP, Color);
}

void cFont::TextDraw(float fPosX, float fPosY, D3DCOLOR Color)
{
	RECT rt = {fPosX, fPosY, 800, 600};

	m_pFont->DrawTextA(g_pSprite, dest, -1, &rt, DT_NOCLIP, Color);
}

void cFont::Release()
{
	m_pFont->Release();
}