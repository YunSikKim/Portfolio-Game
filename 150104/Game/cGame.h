#pragma once
#include "cWindow.h"

#include "cGameMain.h"

enum
{
	INTRO,
	HOWTOPLAY,
	TITLE,
	// 기타 세부사항 추가

	GAMEPLAY,
	GAMEOVER,
	ENDING
};

class cGame
{
private:
	int g_State;

	// 세부사항 선언
	cGameMain* SCENE_GAMEMAIN;
public:
	cGame();
	~cGame();

	bool Update(float fDeltaTime);
	bool Render();
};