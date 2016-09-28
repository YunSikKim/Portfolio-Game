#pragma once
#include "cWindow.h"
#include "cFont.h"
#include <map>

using std::map;

class cFontManager
{
private:
	map<int, cFont*> m_FontMap;
public:
	~cFontManager();

	void FLoad(int nNumber, LPCSTR cFaceFont, int nWidth, int nHeight, int nBold=500);
	void FSet(int nNumber, int nData);
	void FDraw(int nNumber, LPCSTR cText, float fPosX, float fPosY, D3DCOLOR Color=D3DCOLOR_RGBA(255, 255, 255, 255));
	void FDraw(int nNumber, float fPosX, float fPosY, D3DCOLOR Color=D3DCOLOR_RGBA(255, 255, 255, 255));
	void Release();
};

extern cFontManager* FManager;