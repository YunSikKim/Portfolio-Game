#include "cGameTutorial.h"

cGameTutorial::cGameTutorial()
{
	TManager->TLoad(1, "./Images/Tutorial/BG.jpg");
	TManager->TLoad(2, "./Images/Tutorial/Title.png");
	TManager->TLoad(3, "./Images/Tutorial/KeyPress.png");
	TManager->TLoad(4, "./Images/Tutorial/Select.png");

	FManager->FLoad(1, "a낙서", 80, 80);
	FManager->FLoad(2, "a순정만화", 40, 30);

	SManager->AddSound(1, "./Sound/Title.wav");

	nFrame = 0;
	nAlpha = 0;
	fX = fY = 0.0f;
	fSelectX = 155.0f;
	nTextSwitch = 0;
	nBackSwitch = 0;

	nPressFrame = 0;
	nPressAlpha = 0;

	nTitleAlpha = 0;
	
	nTextFrame = 0;
	nTextAlpha = 0;

	nWaitFrame = 0;
	nIntroAlpha = 0;
	nChooseAlpha = 0;
	nSelectAlpha = 255;

	bReturn = false;
	nReturnFrame = 0;

	SManager->Play(1);
}

cGameTutorial::~cGameTutorial()
{
	TManager->Release();
	FManager->Release();
}

bool cGameTutorial::Update(float fDeltaTIme)
{
	nFrame++;
	nPressFrame++;

	if( nFrame > 60 )
		if( nAlpha < 255 )
			nAlpha += 5;

	if( nTextSwitch == 2 && !(nPressFrame % 60) )
	{
		( nPressAlpha == 0 )? (nPressAlpha = 255) : (nPressAlpha = 0);

		nPressFrame = 0;
	}

	if( nAlpha == 255 )
		if( nFrame == 171)
			nTextSwitch = 1;

	if( nTextSwitch == 1 )
		if( nTitleAlpha < 255 )
				nTitleAlpha += 17;

	if( nFrame == 186 )
		nTextSwitch = 2;

	if( nTextSwitch == 2 && IManager->IsKeyDown(DIK_RETURN) )
		nTextSwitch = 3;

	if( nTextSwitch == 3 )
		fY -= 6.0f;

	if( nTextSwitch == 3 && fY == -600 )
		nTextSwitch = 4;

	if( nTextSwitch == 4 && nTextAlpha < 255 )
		nTextAlpha += 5;

	if( nTextSwitch == 4 && nTextAlpha == 255 )
		nTextSwitch = 5;

	if( nTextSwitch == 5 && nTextFrame++ == 60 )
		nTextSwitch = 6;

	if( nTextSwitch == 6 && nIntroAlpha < 255)
		nIntroAlpha += 17;

	if( nIntroAlpha == 255 )
		nWaitFrame++;

	if( nWaitFrame == 120 )
		nTextSwitch = 7;

	if( nTextSwitch == 7 && nChooseAlpha < 255 )
		nChooseAlpha += 15;

	if( nTextSwitch == 7 )
	{
		if( IManager->IsKeyDown(DIK_RIGHT) && fSelectX < 300 )
			fSelectX = 420.0f;
		if( IManager->IsKeyDown(DIK_LEFT) && fSelectX > 300 )
			fSelectX = 155.0f;

		if(  IManager->IsKeyDown(DIK_RETURN) )
		{
			bReturn = true;


		}

		if( bReturn )
		{
			nReturnFrame++;

			if( Return_Select() == 1 )
			{
				if( fY < 0.0f )
					fY += 12.0f;
				else if( fX > -700.0f && nReturnFrame >= 110 )
					fX -= 14.0f;
				else if( nReturnFrame == 220 )
				{
					return false;
				}
			}
			else
			{
				if( fY < 0.0f && fX != -700.0f )
					fY += 12.0f;
				else if( fX > -700.0f && nReturnFrame >= 110 )
					fX -= 14.0f;
				else if( fX == -700.0f && fY > -600.0f )
					fY -= 12.0f;
				else if( nReturnFrame == 270 )
				{
					SManager->Stop(1);
					return false;
				}
			}
		}
	}

	return true;
}

bool cGameTutorial::Render()
{
	TManager->TDraw(1, fX, fY, NULL, nAlpha);
	
	TManager->TDraw(2, 50.0f+fX, 200.0f+fY, NULL, nTitleAlpha);
	
	if( nTextSwitch == 2 )
		TManager->TDraw(3, 175.0f+fX, 450.0f+fY, NULL, nPressAlpha);

	if( nTextSwitch >= 4 )
		FManager->FDraw(1, "Hello!", 100.0f+fX, 700.0f+fY, BLACK(nTextAlpha));

	if( nTextSwitch >= 6 )
	{
		FManager->FDraw(2, "어서오십시오. 만나서 반갑습니다.", 80.0f+fX, 870.0f+fY, BLACK(nIntroAlpha));
		FManager->FDraw(2, "시작 전에 조작방법을 설명해드리겠습니다.", 80.0f+fX, 920.0f+fY, BLACK(nIntroAlpha));
		FManager->FDraw(2, "구경하시겠습니까?", 80.0f+fX, 970.0f+fY, BLACK(nIntroAlpha));
	}

	if( nTextSwitch == 7 )
	{
		FManager->FDraw(2, "네", 210.0f+fX, 1072.5f+fY, BLACK(nChooseAlpha));
		FManager->FDraw(2, "아니오", 450.0f+fX, 1072.5f+fY, BLACK(nChooseAlpha));
		TManager->TDraw(4, fSelectX+fX, 1067.5f+fY, NULL, nSelectAlpha);
	}

	return true;
}

int cGameTutorial::Return_Select()
{
	if( fSelectX == 155.0f )
		return 1;
	else if( fSelectX == 420.0f )
		return 2;

	return 0;
}