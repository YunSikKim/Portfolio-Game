#include "cTextureManager.h"

cTextureManager::~cTextureManager()
{
	Release();
}

void cTextureManager::TLoad(int nNumber, LPCSTR pFile)
{
	cTexture *tex = new cTexture();
	tex->TexLoad(pFile);
	m_TextureMap[nNumber] = tex;
}

void cTextureManager::TDraw(int nNumber, float fPosX, float fPosY, RECT* rRect, int nAlpha)
{
	m_TextureMap[nNumber]->TexDraw(fPosX, fPosY, rRect, nAlpha);
}

void cTextureManager::Release()
{
	for(map<int, cTexture*>::iterator iter = m_TextureMap.begin();
		iter != m_TextureMap.end();
		iter++)
	{
		delete(iter->second);
	}

	m_TextureMap.clear();
}

cTextureManager* TManager = new cTextureManager();