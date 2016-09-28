#pragma once
class CEatButton
{
private:
	int m_X;
	int m_Y;
	CRect m_Rect;
public:
	CEatButton();
	CEatButton(int x, int y);
	~CEatButton();

	bool IsClick(CPoint point);

	void Render(CDC* pDC);
};

