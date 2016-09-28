#pragma once

#include <highgui.h>
#include <cv.h>
#include <Windows.h>
#include <NuiApi.h>

#include "cDefine.h"

using namespace cv;

#include "cTextureManager.h"
#include "cFontManager.h"
#include "cSoundManager.h"

class cGameKinect
{
private:
	IplImage* image;
	IplImage* gray;
	IplImage* skeleton;

	HANDLE colorStreamHnd;
	HANDLE nextColorFrameEnt;
	HANDLE skeletonStreamHnd;
	HANDLE nextSkeletonFrameEnt;

	CvPoint points[NUI_SKELETON_POSITION_COUNT];
	FLOAT z[NUI_SKELETON_POSITION_COUNT];

	int nHandsCount;

	bool IsHandsUpMotion;
	bool IsHandsDownMotion;

	int nTextFrame;
	int nTextSwitch;
	int nMainFrame;
	int nMainAlpha;

	bool IsAnimation;

	HRESULT hr;
public:
	cGameKinect();
	~cGameKinect();
	
	void InitializeKinect();
	void createRGBImage(HANDLE h, IplImage* image);
	void createSkeleton(HANDLE h, IplImage* image);
	void drawSkeleton(const NUI_SKELETON_DATA &position, IplImage* image);
	CvPoint SkeletonToScreen(Vector4 skeletonPoint);
	void drawBone(const NUI_SKELETON_DATA &position, NUI_SKELETON_POSITION_INDEX j1, NUI_SKELETON_POSITION_INDEX j2, IplImage* image);
	void HandMotion(const NUI_SKELETON_DATA &position, IplImage* image);
	void FootMotion(const NUI_SKELETON_DATA &position, IplImage* image);
	void BodyMotion(const NUI_SKELETON_DATA &position, IplImage* image);

	bool Update(float fDeltaTime);
	bool Render();
};

