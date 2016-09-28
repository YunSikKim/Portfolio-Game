#include "cGameKinect.h"

cGameKinect::cGameKinect()
{
	TManager->TLoad(4000, "./Images/Tutorial/BG.jpg");

	FManager->FLoad(10, "맑은 고딕", 40, 40);
	FManager->FLoad(20, "맑은 고딕", 40, 40);
	FManager->FLoad(1, "a낙서", 80, 80);

	FManager->FLoad(2, "a순정만화", 40, 30);

	SManager->AddSound(3, "./Sound/Kinect.wav");

	IsHandsUpMotion = false;
	IsHandsDownMotion = false;

	nHandsCount = 0;

	nTextFrame = 0;
	nTextSwitch = 0;

	nMainFrame = 0;
	nMainAlpha = 0;

	IsAnimation = false;

	//InitializeKinect();

	nextColorFrameEnt = CreateEvent(NULL, true, false, NULL);
	nextSkeletonFrameEnt = CreateEvent(NULL, true, false, NULL);

	image = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 4);
	gray = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 1);
	skeleton = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 4);

	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480, 0, 2, nextColorFrameEnt, &colorStreamHnd);

	if( FAILED(hr) )
		FManager->FDraw(10, "T_T", 200, 200, BLACK(255));

	hr = NuiSkeletonTrackingEnable(nextSkeletonFrameEnt, 0);

	SManager->Play(3);
}

cGameKinect::~cGameKinect()
{

}

void cGameKinect::InitializeKinect()
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

void cGameKinect::createRGBImage(HANDLE h, IplImage* image)
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

void cGameKinect::createSkeleton(HANDLE h, IplImage* image)
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
			if( nTextSwitch == 6 && nHandsCount < 5 ) HandMotion(skeletonFrame.SkeletonData[i], skeleton);
			if( nTextSwitch == 8 && nHandsCount < 6 ) FootMotion(skeletonFrame.SkeletonData[i], skeleton);
			if( nTextSwitch == 10 && nHandsCount < 6 ) BodyMotion(skeletonFrame.SkeletonData[i], skeleton);
		}

		//cvShowImage("skeleton", skeleton);
	}

	cvReleaseImage(&Skeleton_clear);
}

void cGameKinect::drawSkeleton(const NUI_SKELETON_DATA &position, IplImage* image)
{
	for(int i=0; i<NUI_SKELETON_POSITION_COUNT; i++)
	{
		points[i] = SkeletonToScreen(position.SkeletonPositions[i]);
		z[i] = position.SkeletonPositions[i].z;
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

CvPoint cGameKinect::SkeletonToScreen(Vector4 skeletonPoint)
{
	LONG x, y;
	USHORT depth;

	NuiTransformSkeletonToDepthImage(skeletonPoint, &x, &y, &depth, NUI_IMAGE_RESOLUTION_640x480);

	float screenPointX = (float)(x);
	float screenPointY = (float)(y);

	return cvPoint(screenPointX, screenPointY);

}

void cGameKinect::drawBone(const NUI_SKELETON_DATA &position, NUI_SKELETON_POSITION_INDEX j1, NUI_SKELETON_POSITION_INDEX j2, IplImage* image)
{
	NUI_SKELETON_POSITION_TRACKING_STATE j1state = position.eSkeletonPositionTrackingState[j1];
	NUI_SKELETON_POSITION_TRACKING_STATE j2state = position.eSkeletonPositionTrackingState[j2];

	if( j1state == NUI_SKELETON_POSITION_TRACKED && j2state == NUI_SKELETON_POSITION_TRACKED )
		cvLine(skeleton, points[j1], points[j2], CV_RGB(0, 0, 0), 1, 8, 0);
}

void cGameKinect::HandMotion(const NUI_SKELETON_DATA &position, IplImage* image)
{
	NUI_SKELETON_POSITION_TRACKING_STATE j1state = position.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_ELBOW_LEFT];
	NUI_SKELETON_POSITION_TRACKING_STATE j2state = position.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_ELBOW_RIGHT];
	NUI_SKELETON_POSITION_TRACKING_STATE j3state = position.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_LEFT];
	NUI_SKELETON_POSITION_TRACKING_STATE j4state = position.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_RIGHT];

	NUI_SKELETON_POSITION_INDEX j1 = NUI_SKELETON_POSITION_ELBOW_LEFT;
	NUI_SKELETON_POSITION_INDEX j2 = NUI_SKELETON_POSITION_ELBOW_RIGHT;
	NUI_SKELETON_POSITION_INDEX j3 = NUI_SKELETON_POSITION_HAND_LEFT;
	NUI_SKELETON_POSITION_INDEX j4 = NUI_SKELETON_POSITION_HAND_RIGHT;
	NUI_SKELETON_POSITION_INDEX handsup = NUI_SKELETON_POSITION_SHOULDER_CENTER;
	NUI_SKELETON_POSITION_INDEX handsdown = NUI_SKELETON_POSITION_SPINE;

	if( j1state == NUI_SKELETON_POSITION_TRACKED && j2state == NUI_SKELETON_POSITION_TRACKED && nTextSwitch == 6 )
	{
		if( points[j1].y < points[handsup].y-20.0f && points[j2].y < points[handsup].y-20.0f )
			IsHandsUpMotion = true;
		else
		{
			if( IsHandsUpMotion )
			{
				if( j3state == NUI_SKELETON_POSITION_TRACKED && j4state == NUI_SKELETON_POSITION_TRACKED )
				{
					if( points[j3].y > points[handsdown].y+20.0f && points[j4].y > points[handsdown].y+20.0f )
					{
						IsHandsDownMotion = true;
						IsHandsUpMotion = false;
						nHandsCount++;
					}	
				}
			}
		}
	}
}

void cGameKinect::FootMotion(const NUI_SKELETON_DATA &position, IplImage* image)
{
	NUI_SKELETON_POSITION_TRACKING_STATE j1state = position.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_KNEE_LEFT];
	NUI_SKELETON_POSITION_TRACKING_STATE j2state = position.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_KNEE_RIGHT];

	NUI_SKELETON_POSITION_INDEX j1 = NUI_SKELETON_POSITION_KNEE_LEFT;
	NUI_SKELETON_POSITION_INDEX j2 = NUI_SKELETON_POSITION_KNEE_RIGHT;
	NUI_SKELETON_POSITION_INDEX foots = NUI_SKELETON_POSITION_HIP_CENTER;

	if( j1state == NUI_SKELETON_POSITION_TRACKED && j2state == NUI_SKELETON_POSITION_TRACKED && nTextSwitch == 8 )
	{
		if( points[j1].y < points[foots].y+40.0f && !IsHandsUpMotion )
		{
			IsHandsUpMotion = true;
			IsHandsDownMotion = false;
			nHandsCount++;
		}

		if( points[j2].y < points[foots].y+40.0f && !IsHandsDownMotion )
		{
			IsHandsDownMotion = true;
			IsHandsUpMotion = false;
			nHandsCount++;
		}
	}
}

void cGameKinect::BodyMotion(const NUI_SKELETON_DATA &position, IplImage* image)
{
	NUI_SKELETON_POSITION_TRACKING_STATE j1state = position.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_LEFT];
	NUI_SKELETON_POSITION_TRACKING_STATE j2state = position.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_RIGHT];

	NUI_SKELETON_POSITION_INDEX j1 = NUI_SKELETON_POSITION_HAND_LEFT;
	NUI_SKELETON_POSITION_INDEX j2 = NUI_SKELETON_POSITION_HAND_RIGHT;
	NUI_SKELETON_POSITION_INDEX center = NUI_SKELETON_POSITION_SPINE;

	if( j1state == NUI_SKELETON_POSITION_TRACKED && j2state == NUI_SKELETON_POSITION_TRACKED && nTextSwitch == 10 )
	{
		if( points[j1].x < points[center].x && points[j2].x < points[center].x &&
			z[j1] > z[center] && !IsHandsUpMotion )
		{
			IsHandsUpMotion = true;
			IsHandsDownMotion = false;
			nHandsCount++;
		}

		if( points[j1].x > points[center].x && points[j2].x > points[center].x &&
			z[j2] > z[center] && !IsHandsDownMotion )
		{
			IsHandsDownMotion = true;
			IsHandsUpMotion = false;
			nHandsCount++;
		}
	}
}

bool cGameKinect::Update(float fDeltaTime)
{
	FManager->FSet(20, nHandsCount);
	
	if( !(nTextSwitch == 6 && nHandsCount < 5) && !(nTextSwitch == 8 && nHandsCount < 6) && !(nTextSwitch == 10 && nHandsCount < 6) )
		nMainFrame++;

	if( nTextSwitch != 6 && nTextSwitch != 8 && nTextSwitch != 10 && !IsAnimation )
		nTextFrame++;

	if( nMainAlpha < 255 && nMainFrame <= 51 )
		nMainAlpha += 5;
	else if( IsAnimation && nMainAlpha > 0 )
	{
		nMainAlpha -= 15;

		if( nMainAlpha <= 0 )
		{
			IsAnimation = false;
			nMainAlpha = 0;
		}
	}

	if( nTextFrame == 308 && !IsAnimation )
	{
		if( nMainAlpha != 0 )
			IsAnimation = true;
		if( !IsAnimation )
			nTextSwitch = 1;
		nMainFrame = 0;
	}

	if( nTextFrame == 428 && !IsAnimation )
	{
		nTextSwitch = 2;
	}

	if( nTextSwitch == 2 )
	{
		cvNamedWindow("test", CV_WINDOW_AUTOSIZE);
		//cvNamedWindow("skeleton", CV_WINDOW_AUTOSIZE);
	
		if( !IsAnimation )
			nTextSwitch = 3;
	}

	if( nTextSwitch >= 3 )
	{
		WaitForSingleObject(nextColorFrameEnt, 0);
		createRGBImage(colorStreamHnd, image);

		WaitForSingleObject(nextSkeletonFrameEnt, 0);
		createSkeleton(skeletonStreamHnd, skeleton);
	}

	if( nTextFrame == 548 && !IsAnimation )
	{
		if( nMainAlpha != 0 )
			IsAnimation = true;
		if( !IsAnimation )
			nTextSwitch = 4;
		nMainFrame = 0;
	}

	if( nTextFrame == 608 && !IsAnimation )
	{
		if( nMainAlpha != 0 )
			IsAnimation = true;
		if( !IsAnimation )
			nTextSwitch = 5;
		nMainFrame = 0;
	}

	if( nTextFrame == 728 && !IsAnimation && nHandsCount < 5 )
	{
		if( nMainAlpha != 0 )
			IsAnimation = true;
		if( !IsAnimation )
			nTextSwitch = 6;
		nMainFrame = 0;
	}


	if( nTextSwitch == 6 && nHandsCount == 5 )
	{
		if( nMainAlpha != 0 )
			IsAnimation = true;
		if( !IsAnimation )
		{
			nTextSwitch = 7;
			nHandsCount = 0;
			IsHandsUpMotion = false;
			IsHandsDownMotion = false;
			nMainFrame = 0;
		}
	}

	if( nTextFrame == 778 && !IsAnimation && nHandsCount < 6 )
	{
		if( nMainAlpha != 0 )
			IsAnimation = true;
		if( !IsAnimation )
			nTextSwitch = 8;
		nMainFrame = 0;
	}

	if( nTextSwitch == 8 && nHandsCount == 6 )
	{
		if( nMainAlpha != 0 )
			IsAnimation = true;
		if( !IsAnimation )
		{
			nTextSwitch = 9;
			nHandsCount = 0;
			IsHandsUpMotion = false;
			IsHandsDownMotion = false;
			nMainFrame = 0;
		}
	}

		if( nTextFrame == 818 && !IsAnimation && nHandsCount < 6 )
	{
		if( nMainAlpha != 0 )
			IsAnimation = true;
		if( !IsAnimation )
			nTextSwitch = 10;
		nMainFrame = 0;
	}

	if( nTextSwitch == 10 && nHandsCount == 6 )
	{
		if( nMainAlpha != 0 )
			IsAnimation = true;
		if( !IsAnimation )
		{
			nTextSwitch = 11;
			nHandsCount = 0;
			IsHandsUpMotion = false;
			IsHandsDownMotion = false;
			nMainFrame = 0;
		}
	}

	if( nTextSwitch == 11 )
	{
		if( nTextFrame == 938 )
		{
			SManager->Stop(3);
			return false;
		}
	}

	return true;
}

bool cGameKinect::Render()
{
	TManager->TDraw(4000, -700, 0);

	if( nTextSwitch == 0 )
		FManager->FDraw(1, "스트레칭!", 300.0f, 240.0f, BLACK(nMainAlpha));

	if( nTextSwitch >= 1 && nTextSwitch < 4 )
		FManager->FDraw(2, "간단한 스트레칭으로 몸을 풀어줍니다.", 160, 150, BLACK(nMainAlpha));

	if( nTextSwitch == 4 )
		FManager->FDraw(2, "스트레칭 완료시 보상이 주어집니다.", 160, 150, BLACK(nMainAlpha));

	if( nTextSwitch == 5 )
		FManager->FDraw(2, "그럼 이제 스트레칭을 시작하겠습니다.", 160, 250, BLACK(nMainAlpha));

	if( nTextSwitch == 6 )
	{
		FManager->FDraw(20, 160, 40, BLACK(nMainAlpha));
		FManager->FDraw(2, "먼저, 가볍게 두 손을 위로 올렸다 내려보세요.", 160, 150, BLACK(nMainAlpha));
		FManager->FDraw(2, "(5회 실시합니다)", 160, 200, BLACK(nMainAlpha));
	}

	if( nTextSwitch == 8 )
	{
		FManager->FDraw(20, 160, 40, BLACK(nMainAlpha));
		FManager->FDraw(2, "다음은 양 무릎을 번갈아가며 올려보세요.", 160, 150, BLACK(nMainAlpha));
		FManager->FDraw(2, "(양쪽 3회씩 총 6회 실시합니다)", 160, 200, BLACK(nMainAlpha));
	}

	if( nTextSwitch == 10 )
	{
		FManager->FDraw(20, 160, 40, BLACK(nMainAlpha));
		FManager->FDraw(2, "이제 손을 앞으로 내밀고 몸통을 돌려보세요.", 160, 150, BLACK(nMainAlpha));
		FManager->FDraw(2, "(양쪽 3회씩 총 6회 실시합니다)", 160, 200, BLACK(nMainAlpha));
	}

	if( nTextSwitch == 11 )
	{
		FManager->FDraw(2, "수고하셨습니다.", 160, 150, BLACK(nMainAlpha));
		FManager->FDraw(2, "다음 스테이지로 넘어갑니다.", 160, 200, BLACK(nMainAlpha));
		FManager->FDraw(2, "스코어 +5000", 160, 400, BLACK(nMainAlpha));
	}

	return true;
}