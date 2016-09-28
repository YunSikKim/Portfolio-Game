#pragma once

#include "Princess.h"

enum TYPE
{ ROOT, LEFT, RIGHT };

class CRoom
{
private:
	TYPE m_Type;
	int m_X;
	int m_Y;
	int m_Worker;
	int m_Soldier;
	int m_Male;
	int m_Female;
	int m_Food;
	int m_Water;
	int m_MaxAnt;
	CRoom* left;
	CRoom* right;
	bool m_Check;
	
	CRect m_Rect;
public:
	CRoom();
	CRoom(TYPE type, int x, int y);
	~CRoom();

	int GetX() { return m_X; };
	int GetY() { return m_Y; };
	int GetWorker() { return m_Worker; };
	int GetSoldier() { return m_Soldier; };
	int GetMale() { return m_Male; };
	int GetFemale() { return m_Female; };
	int GetFood() { return m_Food; };
	int GetWater() { return m_Water; };
	int GetTotal() { return m_Worker + m_Soldier + m_Male + m_Female; };
	int GetMax() { return m_MaxAnt; };
	CRoom* GetLeft() { return left; };
	CRoom* GetRight() { return right; };
	TYPE GetType() { return m_Type; };
	bool IsCheck() { return m_Check; };
	void SetLeft(int& count);
	void SetRight(int& count);
	void SetCheck(bool state) { m_Check = state; };
	void SetWorker(int value) { m_Worker += value; };
	void SetSoldier(int value) { m_Soldier += value; };
	void SetMale(int value) { m_Male += value; };
	void SetFemale(int value) { m_Female += value; };
	void SetFood(int value) { m_Food += value; };
	void SetWater(int value) { m_Water += value; };
	void SetMax(int value) { m_MaxAnt += value; };

	void IsClick(CPoint point, CRoom*& room);
	void Working();
	void GatherPower(int& power);
	void Feeding();
	void Over();
	void Drink();
	void Delete();
	void Breed(CPrincess*& pc);
	void Rain();

	void GetMaxLevel(int curlevel, const CRoom root, int &max);
	void ResetCheck();
	void CreateNewRoom(int& count);

	CRoom* GetRoom() { return this; };

	void Render(CDC *pDC);
};
