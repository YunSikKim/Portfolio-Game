#include "cCharacter.h"

int cCharacter::m_nLife = CHAR_LIFE;
int cCharacter::m_nCount = 0;

cCharacter::cCharacter(float fX, float fY, float fForce)
{
	m_fX = m_fY = 0.0f;
	m_fForce = fForce;
	m_nMoveSpeed = CHAR_SPEED;

	Init();

	SetX(fX);
	SetY(fY);
}

void cCharacter::Init()
{
	TManager->TLoad(1000, "./Images/Play/CharacterLeft.png");
	TManager->TLoad(1001, "./Images/Play/CharacterRight.png");
	TManager->TLoad(1002, "./Images/Play/Character.png");
	TManager->TLoad(1003, "./Images/Play/Life.png");

	frame = 0;
	protectframe = 0;
	alpha = 0;

	m_nState = STAND;
	m_nAnimation = 1;
	m_nJumpFrame = 0;
	m_nJumpCount = 0;
	m_nJumpNumber = 1;
	m_nAniFrame = CHAR_ANIMATION_FRAME;

	m_bMove = false;
	m_bJump = false;
	m_bJumpDelay = false;
	m_bDrop = false;
	m_bProtect = false;
	m_bIsMotion = false;
	m_bIsUpMotion = false;
	m_bIsDownMotion = false;

	if( m_nCount == 0 )
	{
		InitializeKinect();
		m_nCount++;
	}

	nextSkeletonFrameEnt = CreateEvent(NULL, true, false, NULL);
	nextColorFrameEnt = CreateEvent(NULL, true, false, NULL);

	image = cvCreateImage(cvSize(480, 480), IPL_DEPTH_8U, 4);
	gray = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 1);
	skeleton = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 4);

	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480, 0, 2, nextColorFrameEnt, &colorStreamHnd);

	if( FAILED(hr) )
		FManager->FDraw(10, "T_T", 200, 200, BLACK(255));

	cvNamedWindow("test", CV_WINDOW_AUTOSIZE);

	hr = NuiSkeletonTrackingEnable(nextSkeletonFrameEnt, 0);
}

cCharacter::~cCharacter()
{
	cvReleaseImageHeader(&image);
	cvReleaseImage(&gray);

	cvDestroyWindow("test");
}

void cCharacter::SetWorld(cWorld* pWorld)
{
	m_pWorld = pWorld;
}

void cCharacter::Animation()
{
	frame++;

	if( frame == m_nAniFrame )
	{
 		if( m_nAnimation < CHAR_ANIMATION_STEP )
			m_nAnimation++;
		else
			m_nAnimation = 1;

		frame = 0;
	}
	else if( frame > m_nAniFrame )
		frame = 0;
}

void cCharacter::SetJumpState(bool bState)
{
	m_bJump = bState;
	m_bJumpDelay = bState;
	m_nJumpFrame = 0;
	m_nJumpCount = 0;
}

void cCharacter::SetProtectState(bool bState)
{
	m_bProtect = true;
}

void cCharacter::SetForce(float fForce)
{
	m_fForce = fForce;
}

void cCharacter::InitializeKinect()
{
	bool FailToConnect;

	do
	{
		HRESULT hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_SKELETON);

		if( FAILED(hr) )
			FailToConnect = true;
		else
			FailToConnect = false;

	} while(FailToConnect);
}

void cCharacter::createRGBImage(HANDLE h, IplImage* image)
{
	const NUI_IMAGE_FRAME* pImageFrame = NULL;

	HRESULT hr = NuiImageStreamGetNextFrame(h, 1000, &pImageFrame);

	if( FAILED(hr) )
		return;

	INuiFrameTexture* pTexture = pImageFrame->pFrameTexture;
	NUI_LOCKED_RECT LockedRect;

	pTexture->LockRect(0, &LockedRect, NULL, 0);

	if( LockedRect.Pitch != 0 )
	{
		BYTE* pBuffer = (BYTE*)LockedRect.pBits;
		cvSetData(image, pBuffer, LockedRect.Pitch);
		cvShowImage("test", image);
	}

	NuiImageStreamReleaseFrame(h, pImageFrame);
}

void cCharacter::createSkeleton(HANDLE h, IplImage* image)
{
	NUI_SKELETON_FRAME skeletonFrame = {0};

	IplImage* Skeleton_clear = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 4);
	cvCopy(Skeleton_clear, skeleton);

	HRESULT hr = NuiSkeletonGetNextFrame(0, &skeletonFrame);

	if( FAILED(hr) )
		return;

	NuiTransformSmooth(&skeletonFrame, NULL);

	for(int i=0; i<NUI_SKELETON_COUNT; i++)
	{
		NUI_SKELETON_TRACKING_STATE state = skeletonFrame.SkeletonData[i].eTrackingState;

		if( NUI_SKELETON_TRACKED == state )
		{
			drawSkeleton(skeletonFrame.SkeletonData[i], skeleton);
			JumpMotion(skeletonFrame.SkeletonData[i], skeleton);
		}

		//cvShowImage("skeleton", skeleton);
	}

	cvReleaseImage(&Skeleton_clear);
}

void cCharacter::drawSkeleton(const NUI_SKELETON_DATA &position, IplImage* image)
{
	for(int i=0; i<NUI_SKELETON_POSITION_COUNT; i++)
	{
		points[i] = SkeletonToScreen(position.SkeletonPositions[i]);
	}

	drawBone(position, NUI_SKELETON_POSITION_SHOULDER_RIGHT, NUI_SKELETON_POSITION_ELBOW_RIGHT, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_ELBOW_RIGHT, NUI_SKELETON_POSITION_WRIST_RIGHT, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_WRIST_RIGHT, NUI_SKELETON_POSITION_HAND_RIGHT, skeleton);

	drawBone(position, NUI_SKELETON_POSITION_SHOULDER_LEFT, NUI_SKELETON_POSITION_ELBOW_LEFT, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_ELBOW_LEFT, NUI_SKELETON_POSITION_WRIST_LEFT, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_WRIST_LEFT, NUI_SKELETON_POSITION_HAND_LEFT, skeleton);

	drawBone(position, NUI_SKELETON_POSITION_HEAD, NUI_SKELETON_POSITION_SHOULDER_CENTER, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_LEFT, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_RIGHT, skeleton);

	drawBone(position, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SPINE, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_SPINE, NUI_SKELETON_POSITION_HIP_CENTER, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_LEFT, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_RIGHT, skeleton);

	drawBone(position, NUI_SKELETON_POSITION_HIP_LEFT, NUI_SKELETON_POSITION_KNEE_LEFT, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_KNEE_LEFT, NUI_SKELETON_POSITION_ANKLE_LEFT, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_ANKLE_LEFT, NUI_SKELETON_POSITION_FOOT_LEFT, skeleton);

	drawBone(position, NUI_SKELETON_POSITION_HIP_RIGHT, NUI_SKELETON_POSITION_KNEE_RIGHT, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_KNEE_RIGHT, NUI_SKELETON_POSITION_ANKLE_RIGHT, skeleton);
	drawBone(position, NUI_SKELETON_POSITION_ANKLE_RIGHT, NUI_SKELETON_POSITION_FOOT_RIGHT, skeleton);
}

CvPoint cCharacter::SkeletonToScreen(Vector4 skeletonPoint)
{
	LONG x, y;
	USHORT depth;

	NuiTransformSkeletonToDepthImage(skeletonPoint, &x, &y, &depth, NUI_IMAGE_RESOLUTION_640x480);

	float screenPointX = (float)(x);
	float screenPointY = (float)(y);

	return cvPoint(screenPointX, screenPointY);

}

void cCharacter::drawBone(const NUI_SKELETON_DATA &position, NUI_SKELETON_POSITION_INDEX j1, NUI_SKELETON_POSITION_INDEX j2, IplImage* image)
{
	NUI_SKELETON_POSITION_TRACKING_STATE j1state = position.eSkeletonPositionTrackingState[j1];
	NUI_SKELETON_POSITION_TRACKING_STATE j2state = position.eSkeletonPositionTrackingState[j2];

	if( j1state == NUI_SKELETON_POSITION_TRACKED && j2state == NUI_SKELETON_POSITION_TRACKED )
		cvLine(skeleton, points[j1], points[j2], CV_RGB(0, 0, 0), 1, 8, 0);
}

void cCharacter::JumpMotion(const NUI_SKELETON_DATA &position, IplImage* image)
{
	NUI_SKELETON_POSITION_TRACKING_STATE j1state = position.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_LEFT];
	NUI_SKELETON_POSITION_TRACKING_STATE j2state = position.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_RIGHT];

	NUI_SKELETON_POSITION_INDEX j1 = NUI_SKELETON_POSITION_HAND_LEFT;
	NUI_SKELETON_POSITION_INDEX center = NUI_SKELETON_POSITION_SPINE;

	if( j1state == NUI_SKELETON_POSITION_TRACKED )
	{
		if( points[j1].y < points[center].y - 20.0f && !m_bIsUpMotion )
		{
			m_bIsUpMotion = true;
			m_bIsMotion = true;
			m_bIsDownMotion = false;
		}
		else
		{
			if ( m_bIsUpMotion )
			{
				if( points[j1].y > points[center].y - 20.0f )
				{
					m_bIsDownMotion = true;
					m_bIsUpMotion = false;
				}
			}

			m_bIsMotion = false;
		}
	}
}

bool cCharacter::Update(float fDeltaTime)
{
	WaitForSingleObject(nextColorFrameEnt, 0);
	createRGBImage(colorStreamHnd, image);

	WaitForSingleObject(nextSkeletonFrameEnt, 0);
	createSkeleton(skeletonStreamHnd, skeleton);

	if( m_fForce == CHAR_MASH && !m_bJumpDelay )
	{
		m_nJumpCount = 1;
		m_bDrop = true;
	}
	else
		m_bDrop = false;
	
	if( IManager->IsMousePress(2) && m_fX < 700.0f )
	{
		m_bMove = true;
		m_nState = RIGHT;
		m_fX += m_nMoveSpeed;
	}
	else if( IManager->IsMousePress(1) && m_fX > MAP_START_X )
	{
		m_bMove = true;
		m_nState = LEFT;
		m_fX -= m_nMoveSpeed + CAMERA_TILE_SPEED;
	}
	else
	{
		m_bMove = false;
		if( !m_bJumpDelay )
			m_nState = STAND;
	}

	if( m_fX > 700.0f )
		m_fX = 699.0f;

	if( (m_bIsMotion || IManager->IsKeyDown(DIK_RETURN)) && ( m_nJumpCount <= m_nJumpNumber || !m_bDrop ) )
	{
		if( m_nJumpCount <= m_nJumpNumber )
		{
			m_nJumpFrame = 0;
			m_nJumpCount++;
	  		m_bJumpDelay = true;
			m_bJump = true;
			m_fForce = 18;
		}
	}

	if( m_bJumpDelay )
	{
		m_nJumpFrame++;
		
		if( m_nState == LEFT )
			m_nState = LEFTJUMP;
		else if( m_nState == RIGHT )
			m_nState = RIGHTJUMP;

		m_nAnimation = 5;
	}

	if( !m_bJump )
	{ 
		m_fForce = CHAR_MASH;
	}

	if( m_nJumpFrame == 20 )
		m_bJump = false;

	if( m_bProtect )
	{
		protectframe++;

		( alpha == 0 )? (alpha = 255) : (alpha = 0);

		if( !m_bJumpDelay && !m_bDrop )
			m_fForce = 10;

		if( m_fY + CHAR_SIZE_Y > 500.0f )
		{
			m_fY = 500.0f - CHAR_SIZE_Y -1;
			m_fForce = 10;
		}

		if( protectframe > 120 )
		{
			m_bProtect = false;
			protectframe = 0;
		}
	}

	return true;
}

bool cCharacter::Render()
{
	RECT rt = {(m_nAnimation-1)*CHAR_SIZE_X, 0, m_nAnimation*CHAR_SIZE_X, CHAR_SIZE_Y};

	if( !m_bProtect )
	{
		if( m_nState == LEFT || m_nState == LEFTJUMP )
			TManager->TDraw(1000, m_fX, m_fY, &rt);
		else if( m_nState == RIGHT || m_nState == RIGHTJUMP )
			TManager->TDraw(1001, m_fX, m_fY, &rt);
		else
			TManager->TDraw(1002, m_fX, m_fY);
	}
	else
	{
		if( m_nState == LEFT || m_nState == LEFTJUMP )
		TManager->TDraw(1000, m_fX, m_fY, &rt, alpha);
	else if( m_nState == RIGHT || m_nState == RIGHTJUMP )
		TManager->TDraw(1001, m_fX, m_fY, &rt, alpha);
	else
		TManager->TDraw(1002, m_fX, m_fY, NULL, alpha);
	}

	for(int i=0; i<m_nLife; i++)
		TManager->TDraw(1003, (float)MAP_START_X + (10*i) + (CHAR_SIZE_LIFE*i), (float)MAP_START_Y);

	return true;
}