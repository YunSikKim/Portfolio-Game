#pragma once
#include "cWindow.h"

#include "cGameMain.h"

enum
{
	INTRO,
	HOWTOPLAY,
	TITLE,
	// ��Ÿ ���λ��� �߰�

	GAMEPLAY,
	GAMEOVER,
	ENDING
};

class cGame
{
private:
	int g_State;

	// ���λ��� ����
	cGameMain* SCENE_GAMEMAIN;
public:
	cGame();
	~cGame();

	bool Update(float fDeltaTime);
	bool Render();
};