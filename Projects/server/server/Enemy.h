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
	bool alive;
public:
	bool Boss1_Appear = false;
	bool Boss2_Appear = false;
	vector<CBullet> m_MonsterBullet;

	vector<CBullet> enemy_bullet1;
	vector<CBullet> enemy_bullet2[3];
	vector<CBullet> enemy_bullet3[8];
	vector<CBullet> boss1_bullet1[36];
	vector<CBullet> boss1_bullet2[36];
	vector<CBullet> boss1_bullet3[3];
	vector<CBullet> boss1_bullet4[8];
	vector<CBullet> boss2_bullet[36];

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
