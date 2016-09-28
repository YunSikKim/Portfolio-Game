#pragma once
#include "cTexture.h"
#include <map>

using std::map;

class cTextureManager
{
private:
	map<int, cTexture*> m_TextureMap;
public:
	~cTextureManager();

	void TLoad(int nNumber, LPCSTR pFile);
	void TDraw(int nNumber, float fPosX, float fPosY, RECT* rRect=NULL, int nAlpha=255);
	void Release();
};

extern cTextureManager* TManager;