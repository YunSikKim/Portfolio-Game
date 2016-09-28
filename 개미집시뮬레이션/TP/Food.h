#pragma once

class CFood
{
private:
	int m_X;
	int m_Y;
	CRect m_Rect;
public:
	CFood();
	CFood(int x, int y);
	~CFood();

	int GetX() { return m_X; };
	void SetX(int value);
	bool IsClick(CPoint point);

	void Render(CDC* pDC);
};

