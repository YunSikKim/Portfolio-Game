#include "cGame.h"

cGame::cGame()
{	
	//SCENE_GAMEINTRO = new cGameIntro();
	SCENE_GAMEPLAY = new cGamePlay();
	//SCENE_GAMEHOWTOPLAY = new cGameHowtoPlay();
	//SCENE_GAMEKINECT = new cGameKinect();
	//SCENE_GAMEENDING = new cGameEnding(0);
	g_State = GAMEPLAY;

	stage = 1;

	SCENE_GAMEPLAY->SetStage(stage);
	SCENE_GAMEPLAY->SetMap();
}


cGame::~cGame()
{
	
}

bool cGame::Update(float fDeltaTime)
{
	switch(g_State)
	{
	case INTRO:
		if( !SCENE_GAMEINTRO->Update(fDeltaTime) )
		{
			g_State = TUTORIAL;

			delete SCENE_GAMEINTRO;
			SCENE_GAMETUTORIAL = new cGameTutorial();
		}
		break;

	case TUTORIAL:
		if( !(SCENE_GAMETUTORIAL->Update(fDeltaTime)) )
		{
			if( SCENE_GAMETUTORIAL->Return_Select() == 1 )
			{
				g_State = HOWTOPLAY;

				delete SCENE_GAMETUTORIAL;
				SCENE_GAMEHOWTOPLAY = new cGameHowtoPlay();
			}
			else if( SCENE_GAMETUTORIAL->Return_Select() == 2 )
			{
				g_State = GAMEPLAY;

				delete SCENE_GAMETUTORIAL;
				SCENE_GAMEPLAY = new cGamePlay();

				SCENE_GAMEPLAY->SetStage(stage);
				SCENE_GAMEPLAY->SetMap();
			}
		}
		break;

	case HOWTOPLAY:
		if( !SCENE_GAMEHOWTOPLAY->Update(fDeltaTime) )
		{
			g_State = GAMEPLAY;

			delete SCENE_GAMEHOWTOPLAY;
			SCENE_GAMEPLAY = new cGamePlay();

			SCENE_GAMEPLAY->SetStage(stage);
			SCENE_GAMEPLAY->SetMap();
		}
		break;

	case GAMEPLAY:
		if( !SCENE_GAMEPLAY->Update(fDeltaTime) )
		{
			if( SCENE_GAMEPLAY->GetState() == 1 )
			{
				g_State = ENDING;

				delete SCENE_GAMEPLAY;
				SCENE_GAMEENDING = new cGameEnding(SCENE_GAMEPLAY->GetScore());
			}
			else if( SCENE_GAMEPLAY->GetState() == 2 )
			{
				if( stage == 1 )
				{
					g_State = KINECT;

					delete SCENE_GAMEPLAY;
					SCENE_GAMEKINECT = new cGameKinect();
				}
				else if( stage+1 != 4 )
				{
					delete SCENE_GAMEPLAY;
					SCENE_GAMEPLAY = new cGamePlay();

					stage++;
					SCENE_GAMEPLAY->SetStage(stage);
					SCENE_GAMEPLAY->SetMap();
				}
				else
				{
					g_State = ENDING;

					delete SCENE_GAMEPLAY;
					SCENE_GAMEENDING = new cGameEnding(SCENE_GAMEPLAY->GetScore());
				}
			}
		}
		break;

	case KINECT:
		if( !SCENE_GAMEKINECT->Update(fDeltaTime) )
		{
			g_State = GAMEPLAY;

			delete SCENE_GAMEKINECT;
			SCENE_GAMEPLAY = new cGamePlay();

			stage++;
			SCENE_GAMEPLAY->SetStage(stage);
			SCENE_GAMEPLAY->SetMap();

			SCENE_GAMEPLAY->AddScore(5000);
		}
		break;
		
	case GAMEOVER:

		break;

	case ENDING:
		SCENE_GAMEENDING->Update(fDeltaTime);
		break;
	}

	return true;
}

bool cGame::Render()
{
	switch(g_State)
	{
	case INTRO:
		SCENE_GAMEINTRO->Render();
		break;

	case TUTORIAL:
		SCENE_GAMETUTORIAL->Render();
		break;

	case HOWTOPLAY:
		SCENE_GAMEHOWTOPLAY->Render();
		break;

	case GAMEPLAY:
		SCENE_GAMEPLAY->Render();
		break;

	case KINECT:
		SCENE_GAMEKINECT->Render();
		break;

	case GAMEOVER:

		break;

	case ENDING:
		SCENE_GAMEENDING->Render();
		break;
	}

	return true;
}