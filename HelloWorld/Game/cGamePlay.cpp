#include "cGamePlay.h"

int cGamePlay::nScore = 0;

cGamePlay::cGamePlay()
{
	TManager->TLoad(1, "./Images/Tutorial/BG.jpg");
	TManager->TLoad(2, "./Images/Play/BG.png");
	TManager->TLoad(20, "./Images/Play/BG.png");
	TManager->TLoad(3, "./Images/Play/sun.png");
	TManager->TLoad(10, "./Images/Play/Mask.png");
	TManager->TLoad(4, "./Images/Play/Mark.png");
	TManager->TLoad(5, "./Images/Play/Process.png");

	SManager->AddSound(2, "./Sound/Play.wav");

	FManager->FLoad(1, "a순정만화", 40, 20);
	FManager->FLoad(2, "a순정만화", 40, 20);

	timeframe = 0;
	itemframe = 0;

	bSpeed = false;
	bJump = false;
	bDead = false;

	nTileCount = 0;
	nFruitCount = 0;
	nSkilCount = 0;
	MusicFrame = 0;

	m_fMarkX = MARKER_START_X;

	m_fBack1X = (float)MAP_START_X;
	m_fBack2X = (float)MAP_START_X + BG_IMAGE_SIZE;

	for(int i=0; i<100; i++)
		pFruitArray[i] = NULL;

	for(int i=0; i<100; i++)
		pSkilArray[i] = NULL;

	pChar = new cCharacter(CHAR_START_POSITION_X, CHAR_START_POSITION_Y, CHAR_MASH);
	pWorld = new cWorld();

	SManager->Play(2);
}

cGamePlay::~cGamePlay()
{
	delete pChar;
}

void cGamePlay::SetMap()
{
	switch( nStage )
	{
	case 1:
		fp.open("./MapData/Stage.txt");
		break;
		
	case 2:
		fp.open("./MapData/Stage2.txt");
		break;

	case 3:
		fp.open("./MapData/Stage3.txt");
		break;
	}

	if( fp.is_open() )
	{
		ppMap = new int*[MAP_SIZE_Y];

		for(int i=0; i<MAP_SIZE_Y; i++)
			ppMap[i] = new int[MAP_SIZE_X];

		for(int i=0; i<MAP_SIZE_Y; i++)
			for(int j=0; j<MAP_SIZE_X; j++)
			{
				fp >> ppMap[i][j];

				if( ppMap[i][j] == 1 || ppMap[i][j] == 2 )
					nTileCount++;

				if( ppMap[i][j] == 4 )
					nFruitCount++;

				if( ppMap[i][j] == 5 || ppMap[i][j] == 6 )
					nSkilCount++;
			}
	}

	pTileArray = new cTile[nTileCount];
	for(int i=0; i<nFruitCount; i++)
		pFruitArray[i] = new cFruit();
	for(int i=0; i<nSkilCount; i++)
		pSkilArray[i] = new cSkil();
	pFlag = new cFlag();

	int nTIdx = 0;
	int nFIdx = 0;
	int nSIdx = 0;

	for(int i=0; i<MAP_SIZE_Y; i++)
		for(int j=0; j<MAP_SIZE_X; j++)
			if( ppMap[i][j] == 1 || ppMap[i][j] == 2 )
			{
				pTileArray[nTIdx].SetX((float)(j * TILE_SIZE + MAP_START_X));
				pTileArray[nTIdx].SetY((float)(i * TILE_SIZE + MAP_START_Y));
				pTileArray[nTIdx].SetForce(TILE_MASH);
				pTileArray[nTIdx].SetType(ppMap[i][j]);

				nTIdx++;
			}
			else if( ppMap[i][j] == 3 )
			{
				pFlag->SetX((float)(j * TILE_SIZE + MAP_START_X));
				pFlag->SetY((float)(i * TILE_SIZE + MAP_START_Y + 10));
				pFlag->SetForce(TILE_MASH);
				pFlag->SetType(ppMap[i][j]);
			}
			else if( ppMap[i][j] == 4 )
			{
				pFruitArray[nFIdx]->SetX((float)(j * TILE_SIZE + MAP_START_X + (ITEM_FRUIT_SIZE / 2)));
				pFruitArray[nFIdx]->SetY((float)(i * TILE_SIZE + MAP_START_Y) + (ITEM_FRUIT_SIZE / 2));

				nFIdx++;
			}
			else if( ppMap[i][j] == 5 || ppMap[i][j] == 6 )
			{
				pSkilArray[nSIdx]->SetX((float)(j * TILE_SIZE + MAP_START_X));
				pSkilArray[nSIdx]->SetY((float)(i * TILE_SIZE + MAP_START_Y));
				pSkilArray[nSIdx]->SetType(ppMap[i][j]-5);

				nSIdx++;
			}
}

bool cGamePlay::Update(float fDeltaTime)
{
	timeframe++;
	MusicFrame++;

	FManager->FSet(2, MusicFrame);

	if( MusicFrame > 1800 )
		SManager->Play(2);

	if( bDead )
	{
		pChar->SetX(CHAR_START_POSITION_X);
		pChar->SetY(CHAR_START_POSITION_Y);

		if( pChar->GetLife() == -1 )
		{
			m_nState = 1;
			SManager->Stop(2);
			return false;
		}

		pChar->SetProtectState(true);
		bDead = false;
	}

	if( pChar->IsMove() )
		pChar->Animation();

	pChar->Update(fDeltaTime);

	

	pWorld->SetGravity(10.0f);

	pChar->SetWorld(pWorld);
	for(int i=0; i<nTileCount; i++)
		pTileArray[i].SetWorld(pWorld);
	pFlag->SetWorld(pWorld);

	pChar->Gravity();
	for(int i=0; i<nTileCount; i++)
	{
		pTileArray[i].Gravity();
		pTileArray[i].Update(fDeltaTime);
	}
	for(int i=0; i<nFruitCount; i++)
	{
		if( pFruitArray[i] != NULL )
			pFruitArray[i]->Update(fDeltaTime);
	}
	for(int i=0; i<nSkilCount; i++)
	{
		if( pSkilArray[i] != NULL )
			pSkilArray[i]->Update(fDeltaTime);
	}
	pFlag->Gravity();
	pFlag->Update(fDeltaTime);

	for(int i=0; i<ITEM_SKIL_COUNT; i++)
	{
		if( pSkilArray[i] != NULL )
			if( pSkilArray[i]->IsCrash(pChar->GetX(), pChar->GetY(), CHAR_SIZE_X, CHAR_SIZE_Y) )
			{
				switch( pSkilArray[i]->GetType() )
				{
				case SPEED:
					bSpeed = true;
					break;

				case JUMP:
					bJump = true;
					break;
				}

				delete pSkilArray[i];
				pSkilArray[i] = NULL;
			}
	}

	if( bSpeed )
	{
		itemframe++;
		pChar->SetSpeed(CHAR_SPEED * 1.5f);
		pChar->SetAnimation((int)(CHAR_ANIMATION_FRAME * 0.5));

		if( itemframe >= ITEM_SKIL_SPEED_TIME )
		{
			itemframe = 0;
			pChar->SetSpeed(CHAR_SPEED);
			pChar->SetAnimation((int)(CHAR_ANIMATION_FRAME));
			bSpeed = false;
		}
	}

	if( bJump )
	{
		itemframe++;
		pChar->SetJumpCount(2);

		if( itemframe >= ITEM_SKIL_JUMP_TIME )
		{
			itemframe = 0;
			pChar->SetJumpCount(1);
			bJump = false;
		}
	}

	for(int i=0; i<ITEM_FRUIT_COUNT; i++)
	{
		if( pFruitArray[i] != NULL )
			if( pFruitArray[i]->IsCrash(pChar->GetX(), pChar->GetY(), CHAR_SIZE_X, CHAR_SIZE_Y) )
			{
				nScore += ITEM_FRUIT_SCORE;

				delete pFruitArray[i];
				pFruitArray[i] = NULL;
			}
	}

	for(int i=0; i<nTileCount; i++)
	{
		if( pTileArray[i].IsCrash(pChar->GetX(), pChar->GetY(), CHAR_SIZE_X, CHAR_SIZE_Y) )
		{
			if( pTileArray[i].GetY() + (float)(TILE_SIZE / 2) > pChar->GetY() + CHAR_SIZE_Y
				&& !pChar->IsJump() )
			{
				
				pChar->SetJumpState(false);
				pChar->SetForce(2.0f);
				pChar->SetY(pTileArray[i].GetY() - CHAR_SIZE_Y -1);
			}
			else if( pTileArray[i].GetY() + (float)(TILE_SIZE / 2) < pChar->GetY() )
			{
				pChar->SetForce(10.0f);
 				pChar->SetY(pTileArray[i].GetY() 
					+ TILE_SIZE + 1);
			}

			if( !pChar->IsProtect() )
			{
				if( pTileArray[i].GetX() + (float)(TILE_SIZE / 2) > pChar->GetX() + CHAR_SIZE_X
					&& pChar->GetY() + CHAR_SIZE_Y > pTileArray[i].GetY() )
				{
					pChar->SetX(pTileArray[i].GetX() - CHAR_SIZE_X - 1);
				}
				else if( pTileArray[i].GetX() + (float)(TILE_SIZE / 2) < pChar->GetX()
						 && pChar->GetY() + CHAR_SIZE_Y > pTileArray[i].GetY() )
				{
					pChar->SetX(pTileArray[i].GetX() + TILE_SIZE + 1);
				}
			}
		}
	}

	if( pFlag->IsCrash(pChar->GetX(), pChar->GetY(), CHAR_SIZE_X, CHAR_SIZE_Y) )
	{
		m_nState = 2;
		SManager->Stop(2);
		return false;
	}

	if( pChar->GetX() + CHAR_SIZE_X < MAP_START_X || pChar->GetY() > 550.0f )
	{
		pChar->AddLife(-1);

		bDead = true;
	}
	
	if( !pFlag->IsFlag() )
		if( timeframe == 20 )
		{
			nScore += 10;
			timeframe = 0;
		}

	FManager->FSet(1, nScore);

	if( !pFlag->IsFlag() )
	{
		m_fBack1X -= CAMERA_BG_SPEED;
		m_fBack2X -= CAMERA_BG_SPEED;
	}

	if( m_fBack1X <= MAP_START_X - BG_IMAGE_SIZE )
	{
		m_fBack1X = MAP_START_X;
		m_fBack2X = MAP_START_X + BG_IMAGE_SIZE;
	}

	if( m_fMarkX < 650.0f )
		m_fMarkX += (450.0f * CAMERA_TILE_SPEED) / ((MAP_SIZE_X - 12) * 50);

	if( m_fMarkX >= 650.0f )
	{
		for(int i=0; i<nTileCount; i++)
			pTileArray[i].SetFlag(true);
		pFlag->SetFlag(true);
	}

	return true;
}

bool cGamePlay::Render()
{
	TManager->TDraw(1, -700.0f, 0.0f);
	TManager->TDraw(2, m_fBack1X, (float)MAP_START_Y);
	TManager->TDraw(20, m_fBack2X, (float)MAP_START_Y);
	TManager->TDraw(3, 550.0f, 50.0f);

	for(int i=0; i<nTileCount; i++)
		pTileArray[i].Render();

	for(int i=0; i<ITEM_FRUIT_COUNT; i++)
		if( pFruitArray[i] != NULL )
			pFruitArray[i]->Render();

	for(int i=0; i<ITEM_SKIL_COUNT; i++)
		if( pSkilArray[i] != NULL )
			pSkilArray[i]->Render();

	pFlag->Render();

	if( pChar != NULL )
		pChar->Render();

	FManager->FDraw(1, MAP_START_X + 500.0f, MAP_START_Y, BLACK(255));
	//FManager->FDraw(2, 400, 300, BLACK(255));
	TManager->TDraw(10, 0.0f, 0.0f);
	
	TManager->TDraw(5, MAP_START_X + 25.0f, 510.0f);

	TManager->TDraw(4, m_fMarkX, 530.0f);

	return true;
}