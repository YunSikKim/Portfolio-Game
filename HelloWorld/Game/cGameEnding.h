#pragma once
#include "cDefine.h"

#include "cTextureManager.h"
#include "cFontManager.h"
#include "cInputManager.h"

class cGameEnding
{
private:
	int nScore;
public:
	cGameEnding(int score);
	~cGameEnding();

	bool Update(float fDeltaTime);
	bool Render();
};

