#pragma once

#include "Room.h"

class CInfo
{
private:
	CRoom* roominfo;
	int m_X;
	int m_Y;
	CRect m_Rect;
public:
	CInfo();
	CInfo(int x, int y);
	~CInfo();

	void SetRoom(CRoom* room) { roominfo = room; };

	void Render(CDC* pDC);
};

