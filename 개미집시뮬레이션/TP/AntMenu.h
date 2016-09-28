#pragma once

#include "Princess.h"

class CAntMenu
{
private:
	CPrincess* pcinfo;
	int m_X;
	int m_Y;
	CRect m_Rect;
	CRect m_Ant[4];
public:
	CAntMenu();
	CAntMenu(int x, int y);
	~CAntMenu();

	void SetPrincess(CPrincess* pc) { pcinfo = pc; };

	bool IsClick(CPoint point);
	int Select(CPoint point);


	void Render(CDC* pDC);
};

