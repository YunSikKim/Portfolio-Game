#include "cGameEnding.h"

cGameEnding::cGameEnding(int score)
{
	TManager->TLoad(1, "./Images/Tutorial/BG.jpg");

	FManager->FLoad(30, "a낙서", 45, 45);
	FManager->FLoad(31, "a순정만화", 30, 30);
	FManager->FLoad(32, "a순정만화", 30, 30);
	
	nScore = score;
}


cGameEnding::~cGameEnding()
{

}

bool cGameEnding::Update(float fDeltaTime)
{
	FManager->FSet(32, nScore);

	if( IManager->IsMouseDown(1) )
		exit(0);

	return true;
}

bool cGameEnding::Render()
{
	TManager->TDraw(1, -700, 0);

	FManager->FDraw(30, "플레이 해 주셔서 감사합니다.", 200, 200, BLACK(255));
	FManager->FDraw(30, "THANK YOU FOR PLAYING", 170, 300, BLACK(255));

	FManager->FDraw(31, "점수 : ", 270, 450, BLACK(255));
	FManager->FDraw(32, 380, 450, BLACK(255));

	return true;
}
