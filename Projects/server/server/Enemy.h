#pragma once
#include "stdafx.h"
#include "CGameObject.h"
enum E_OBJECT
{
	E_BACKGROUND,
	E_PLAYER,
	E_ENEMY1,
	E_ENEMY2,
	E_ENEMY3,
	E_BOSS1,
	E_BOSS2
};
#pragma pack(1)
class EnemyInfo {
public:
	int Index;
	bool alive;
	POINT pos;
	int Type;
	int Hp;
};


class CMonster : public CGameObject
{
private:
	float Size;
	int MyIndex;
	bool alive;
public:
	bool Boss1_Appear = false;
	bool Boss2_Appear = false;

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
