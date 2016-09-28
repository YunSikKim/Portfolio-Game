#pragma once

#include "cTextureManager.h"

class cGameIntro
{
private:
	int nFrame;
	int nLogoLevel;
	int nLogoAlpha;
	int nTextAlpha;
	float fLogoX;
public:
	cGameIntro();
	~cGameIntro();

	bool Update(float fDeltaTime);
	bool Render();
};

