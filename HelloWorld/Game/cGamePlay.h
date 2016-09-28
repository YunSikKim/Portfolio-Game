#pragma once
using namespace std;

#include "cDefine.h"
#include <fstream>

#include "cTextureManager.h"
#include "cInputManager.h"
#include "cFontManager.h"
#include "cSoundManager.h"

#include "cTile.h"
#include "cFlag.h"
#include "cCharacter.h"
#include "cFruit.h"
#include "cSkil.h"

enum
{
	SPEED = 0,
	JUMP = 1
};

class cGamePlay
{
private:	
	ifstream fp;
	int** ppMap;

	int nTileCount;
	int nFruitCount;
	int nSkilCount;
	cTile* pTileArray;
	cFruit* pFruitArray[100];
	cSkil* pSkilArray[100];
	cFlag* pFlag;
	cCharacter* pChar;
	cWorld* pWorld;

	int itemframe;
	int timeframe;
	static int nScore;

	bool bSpeed;
	bool bJump;
	bool bDead;

	int MusicFrame;

	float m_fMarkX;

	float m_fBack1X;
	float m_fBack2X;

	int m_nState;
	
	int nStage;
public:
	cGamePlay();
	~cGamePlay();

	int GetScore() { return nScore; };
	void SetMap();
	int GetState() { return m_nState; };
	void AddScore(int score) { nScore += score; };
	void SetStage(int stage) { nStage = stage; };

	bool Update(float fDeltaTime);
	bool Render();
};

