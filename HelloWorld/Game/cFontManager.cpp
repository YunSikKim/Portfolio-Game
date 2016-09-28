#include "cFontManager.h"

cFontManager::~cFontManager()
{
	Release();
}

void cFontManager::FLoad(int nNumber, LPCSTR cFaceFont, int nWidth, int nHeight, int nBold)
{
	cFont *font = new cFont();
	font->TextLoad(cFaceFont, nWidth, nHeight, nBold);
	m_FontMap[nNumber] = font;
}

void cFontManager::FSet(int nNumber, int nData)
{
	m_FontMap[nNumber]->TextSetting(nData);
}

void cFontManager::FDraw(int nNumber, LPCSTR cText, float fPosX, float fPosY, D3DCOLOR Color)
{
	m_FontMap[nNumber]->TextDraw(cText, fPosX, fPosY, Color);
}

void cFontManager::FDraw(int nNumber, float fPosX, float fPosY, D3DCOLOR Color)
{
	m_FontMap[nNumber]->TextDraw(fPosX, fPosY, Color);
}

void cFontManager::Release()
{
	for(map<int, cFont*>::iterator iter = m_FontMap.begin();
		iter != m_FontMap.end();
		iter++)
	{
			delete(iter->second);
	}

	m_FontMap.clear();
}

cFontManager* FManager = new cFontManager();