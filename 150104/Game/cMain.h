#pragma once
#include <Windows.h>
#include "cWindow.h"

#include "cInputManager.h"

#include "cGame.h"

/************************************/
/* 게임의 기본적인 세팅을 위한 클래스 */
/************************************/
cGame* GAME;

float g_fFPS		= 0;
float g_fLastTime	= 0;
int g_State			= 0;

void UpdateD3D();
void RenderD3D();