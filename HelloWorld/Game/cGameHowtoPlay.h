#pragma once

#include "cTextureManager.h"
#include "cFontManager.h"
#include "cInputManager.h"
#include "cSoundManager.h"
#include "cDefine.h"

class cGameHowtoPlay
{
private:
	float fX, fY;

	int nTextFrame;
	int nTextSwitch;
	int nTitleAlpha;

public:
	cGameHowtoPlay();
	~cGameHowtoPlay();

	bool Update(float fDeltaTime);
	bool Render();
};

