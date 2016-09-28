#pragma once
#include <highgui.h>
#include <cv.h>
#include <Windows.h>
#include <NuiApi.h>

#include "cDefine.h"
#include "cObject.h"

#include "cTextureManager.h"
#include "cInputManager.h"
#include "cFontManager.h"

enum
{
	STAND = 0,
	LEFT = 1,
	RIGHT = 2,
	LEFTJUMP = 3,
	RIGHTJUMP = 4
};

class cCharacter : public cObject
{
private:
	IplImage* skeleton;
	IplImage* gray;
	IplImage* image;
	cWorld* m_pWorld;
	int m_nAnimation;
	float m_fX, m_fY;
	static int m_nLife;
	static int m_nCount;
	int m_nState;
	int m_nMoveSpeed;
	int m_nAniFrame;
	float m_fForce;
	int m_nJumpFrame;
	int m_nJumpCount;
	int m_nJumpNumber;

	bool m_bProtect;
	bool m_bDrop;
	bool m_bMove;
	bool m_bJump;
	bool m_bJumpDelay;
	bool m_bIsUpMotion;
	bool m_bIsDownMotion;
	bool m_bIsMotion;

	HANDLE skeletonStreamHnd;
	HANDLE nextSkeletonFrameEnt;
	HANDLE colorStreamHnd;
	HANDLE nextColorFrameEnt;

	CvPoint points[NUI_SKELETON_POSITION_COUNT];
	
	int alpha;
	int frame;
	int protectframe;

	HRESULT hr;
public:
	cCharacter(float fX, float fY, float fForce);
	~cCharacter();

	void Init();
	void Animation();

	void SetForce(float fForce);
	void SetSpeed(int nSpeed) { m_nMoveSpeed = nSpeed; };
	void SetJumpCount(int nJump) { m_nJumpNumber = nJump; };
	void SetAnimation(int nFrame) { m_nAniFrame = nFrame; };

	void SetGravity(float fGravity) { m_pWorld->SetGravity(fGravity); };
	void SetWorld(cWorld* pWorld);
	void Gravity() { m_fY -= m_pWorld->GetGravity() + m_fForce; };

	float GetX() { return m_fX; };
	float GetY() { return m_fY; };
	int GetLife() { return m_nLife; };
	
	void SetX(float fX) { m_fX = fX; };
	void SetY(float fY) { m_fY = fY; };
	void AddLife(int nLife) { m_nLife += nLife; };

	void SetJumpState(bool bState);
	void SetProtectState(bool bState);

	bool IsMove() { return m_bMove; };
	bool IsJump() { return m_bJump; };
	bool IsDrop() { return m_bDrop; };
	bool IsProtect() { return m_bProtect; };

	void InitializeKinect();
	void createRGBImage(HANDLE h, IplImage* image);
	void createSkeleton(HANDLE h, IplImage* image);
	void drawSkeleton(const NUI_SKELETON_DATA &position, IplImage* image);
	CvPoint SkeletonToScreen(Vector4 skeletonPoint);
	void drawBone(const NUI_SKELETON_DATA &position, NUI_SKELETON_POSITION_INDEX j1, NUI_SKELETON_POSITION_INDEX j2, IplImage* image);
	void JumpMotion(const NUI_SKELETON_DATA &position, IplImage* image);

	bool Update(float fDeltaTime);
	bool Render();
};

