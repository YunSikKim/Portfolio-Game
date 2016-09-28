#include "cGame.h"

cGame::cGame()
{	
	SCENE_GAMEMAIN = new cGameMain();

	g_State = INTRO;
}


cGame::~cGame()
{
}

bool cGame::Update(float fDeltaTime)
{
	switch(g_State)
	{
	case INTRO:
		SCENE_GAMEMAIN->Update(fDeltaTime);
		break;

	case HOWTOPLAY:

		break;
		
	case TITLE:

		break;

	case GAMEPLAY:

		break;
		
	case GAMEOVER:

		break;

	case ENDING:

		break;
	}

	return true;
}

bool cGame::Render()
{
	switch(g_State)
	{
	case INTRO:
		SCENE_GAMEMAIN->Render();
		break;

	case HOWTOPLAY:

		break;

	case TITLE:

		break;

	case GAMEPLAY:

		break;

	case GAMEOVER:

		break;

	case ENDING:

		break;
	}

	return true;
}