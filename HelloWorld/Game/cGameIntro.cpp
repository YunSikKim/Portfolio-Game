#include "cGameIntro.h"

cGameIntro::cGameIntro()
{
	TManager->TLoad(1, "./Images/Intro/BG.jpg");
	TManager->TLoad(2, "./Images/Intro/logo.png");
	TManager->TLoad(3, "./Images/Intro/text.png");

	nFrame = 0;
	nLogoLevel = 1;
	nLogoAlpha = 255;
	nTextAlpha = 0;
	fLogoX = 337.5;
}

cGameIntro::~cGameIntro()
{
	TManager->Release();
}

bool cGameIntro::Update(float fDeltaTime)
{
	nFrame++;

	if( nLogoLevel <= 6 )
	{
		if( nFrame <= 60 )
		{
			if( !(nFrame % 15) )
				nLogoLevel++;
		}
		else
		{
			if( !(nFrame % 60) )
				nLogoLevel++;
		}
	}
	else if( nFrame > 240 )
	{
		if( nLogoAlpha && fLogoX > 140 )
			nLogoAlpha -= 17;
		else
		{
			if( nLogoAlpha != 255 )
			{
				fLogoX = 140;
				nLogoAlpha += 17;
			}
			else if( nFrame > 285 )
			{
				if( nTextAlpha != 255 )	
					nTextAlpha += 17;
			}
		}
	}

	if( nFrame == 480 )
		return false;

	return true;
}

bool cGameIntro::Render()
{
	TManager->TDraw(1, 0, 0);

	RECT rect = {125*(nLogoLevel-1), 0, 125*nLogoLevel, 180};
	TManager->TDraw(2, fLogoX, 200, &rect, nLogoAlpha);
	TManager->TDraw(3, 290, 200, NULL, nTextAlpha);

	return true;
}