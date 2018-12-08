#pragma once
#include "stdafx.h"
#include "MyPacket.h"
#include "CGameObject.h"
#include "CBullet.h"

class CBullet;
class CMonster : public CGameObject
{
private:
	float Size;
	int MyIndex;
public:
	bool alive;
	bool Boss1_Appear = false;
	bool Boss2_Appear = false;
	bool Boss1_Stop = false;
	bool Boss2_Stop = false;
	//vector<CBullet> m_MonsterBullet;
	int radian[8] = { 0, 45, 90, 135, 180, 225, 270, 315 }; // 0 ¸Ç¿ìÃø
	int radian3[36] = { 5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155, 165, 175, 185,
					195, 205, 215, 225, 235, 245, 255, 265, 275, 285, 295, 305, 315, 325, 335, 345, 355 };

	bool m_XDir, m_YDir = true;
	vector<CBullet> m_EnemyBullet;
	void SetDir(char c, bool b);
	bool GetDir(char c) const;

	CMonster(EnemyInfo enemyInfo);
	CMonster();
	~CMonster();
public:
	virtual void Update();
	bool GetAlive() {return alive;}
	void SetAlive(bool life) { alive = life; }
	int GetIndex() { return MyIndex; }
	void SetIndex(int index) { MyIndex = index; }
	//virtual void Render(HDC m_hdc);
};
