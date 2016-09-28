#pragma once
#include "cWindow.h"
#include <stdio.h>

class cFont
{
private:
	ID3DXFont* m_pFont;

	char dest[100];
public:
	cFont();
	~cFont();

	void TextLoad(LPCSTR cFaceFont, int nWidth, int nHeight, int nBold=500);
	void TextSetting(int nData);
	void TextDraw(LPCSTR cText, float fPosX, float fPosY, D3DCOLOR Color=D3DCOLOR_RGBA(255, 255, 255, 255));
	void TextDraw(float fPosX, float fPosY, D3DCOLOR Color=D3DCOLOR_RGBA(255, 255, 255, 255));
	void Release();
};

