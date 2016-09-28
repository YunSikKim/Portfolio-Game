#pragma once
#include "cWindow.h"

#include "cGameIntro.h"
#include "cGameTutorial.h"
#include "cGameHowtoPlay.h"
#include "cGamePlay.h"
#include "cGameKinect.h"
#include "cGameEnding.h"


enum
{
	INTRO,
	TUTORIAL,
	// 기타 세부사항 추가
	HOWTOPLAY,
	GAMEPLAY,
	GAMEOVER,
	KINECT,
	ENDING
};

class cGame
{
private:
	int g_State;
	int stage;

	// 세부사항 선언
	cGameIntro* SCENE_GAMEINTRO;
	cGameTutorial* SCENE_GAMETUTORIAL;
	cGameHowtoPlay* SCENE_GAMEHOWTOPLAY;
	cGamePlay* SCENE_GAMEPLAY;
	cGameKinect* SCENE_GAMEKINECT;
	cGameEnding* SCENE_GAMEENDING;
public:
	cGame();
	~cGame();

	bool Update(float fDeltaTime);
	bool Render();
};