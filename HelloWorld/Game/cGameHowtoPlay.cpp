#include "cGameHowtoPlay.h"

cGameHowtoPlay::cGameHowtoPlay()
{
	TManager->TLoad(1, "./Images/Tutorial/BG.jpg");
	TManager->TLoad(500, "./Images/Tutorial/TutorialImage1.png");
	TManager->TLoad(501, "./Images/Tutorial/TutorialImage2.png");

	FManager->FLoad(1, "a낙서", 80, 80);
	FManager->FLoad(2, "a순정만화", 70, 70);
	FManager->FLoad(3, "a순정만화", 30, 30);

	fX = -700.0f;
	fY = 0.0f;

	nTextFrame = 0;
	nTextSwitch = 0;
	nTitleAlpha = 0;
}

cGameHowtoPlay::~cGameHowtoPlay()
{
	TManager->Release();
	FManager->Release();
}

bool cGameHowtoPlay::Update(float fDeltaTime)
{
	nTextFrame++;

	if( nTextSwitch == 0 && nTitleAlpha < 255 && nTextFrame <= 51 )
		nTitleAlpha += 5;
	else if( nTextSwitch == 0 && nTextFrame >= 171 && nTitleAlpha > 0 )
		nTitleAlpha -= 15;

	if( nTextFrame == 200 )
		nTextSwitch = 1;

	if( nTextSwitch == 3 )
	{
		if( IManager->IsMouseDown(1) || IManager->IsKeyDown(DIK_RETURN) )
		{
			SManager->Stop(1);
			return false;
		}
	}

	if( nTextSwitch == 1 || nTextSwitch == 2 )
	{
		if( IManager->IsMouseDown(1) ||  IManager->IsKeyDown(DIK_RETURN) )
			nTextSwitch++;
	}

	return true;
}

bool cGameHowtoPlay::Render()
{
	TManager->TDraw(1, fX, fY);

	FManager->FDraw(1, "Tutorial", 300.0f, 240.0f, BLACK(nTitleAlpha));

	if( nTextSwitch == 1 )
		TManager->TDraw(500, 0, 0);

	if( nTextSwitch == 2 )
		TManager->TDraw(501, 0, 0);

	if( nTextSwitch == 3 )
	{
		FManager->FDraw(2, "이제 시작해볼까요?", 230, 200, BLACK(255));
		FManager->FDraw(3, "ENTER를 누르면 게임을 시작합니다!", 270, 350, BLACK(255));
	}

	return true;
}
