#pragma once
#include <string.h>
#include "cDefine.h"

#include "cFontManager.h"
#include "cTextureManager.h"
#include "cInputManager.h"
#include "cSoundManager.h"

class cGameTutorial
{
private:
	float fX, fY;
	float fSelectX;
	int nFrame;
	int nPressFrame;
	int nTextFrame;
	int nWaitFrame;
	int nReturnFrame;
	int nAlpha;
	int nPressAlpha;
	int nTitleAlpha;
	int nTextAlpha;
	int nIntroAlpha;
	int nChooseAlpha;
	int nSelectAlpha;
	int nTextSwitch;
	int nBackSwitch;

	bool bReturn;
public:
	cGameTutorial();
	~cGameTutorial();

	int Return_Select();

	bool Update(float fDeltaTime);
	bool Render();
};

