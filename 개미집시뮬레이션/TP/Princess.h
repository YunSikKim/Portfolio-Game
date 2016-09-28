#pragma once
class CPrincess
{
private:
	int m_X;
	int m_Y;
	int m_Larva;

	bool m_Worker;
	bool m_Soldier;
	bool m_Male;
	bool m_Female;
	CRect m_Rect;
public:
	CPrincess();
	CPrincess(int x, int y);
	~CPrincess();

	int GetX() { return m_X; };
	int GetY() { return m_Y; };
	int GetLarva() { return m_Larva; };
	void SetPos(int x, int y);
	void SetLarva(int value) { m_Larva += value; };

	bool IsClick(CPoint point);
	bool IsWorker() { return m_Worker; };
	bool IsSoldier() { return m_Soldier; };
	bool IsMale() { return m_Male; };
	bool IsFemale() { return m_Female; };
	void SetSoldier(bool status) { m_Soldier = status; };
	void SetMale(bool status) { m_Male = status; };
	void SetFemale(bool status) { m_Female = status; };

	CPrincess* GetPrincess() { return this; };

	void Render(CDC* pDC);
};

