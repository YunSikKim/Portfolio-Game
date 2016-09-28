#pragma once
#include "cWindow.h"

class cTexture
{
private:
	LPDIRECT3DTEXTURE9 m_pTexture;

	int m_nWidth;
	int m_nHeight;
public:
	cTexture();
	~cTexture();

	void TexLoad(LPCSTR dFIle);
	void TexDraw(float fPosX, float fPosY, RECT* rRect=NULL, int nAlpha=255);
	void Release();
};

