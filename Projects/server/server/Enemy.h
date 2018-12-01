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
	int BoomCount;
	bool IsBoom;
};


class CMonster : public CGameObject
{
private:
	float Size;
	int MyIndex;

public:
	bool Boss1_Appear = false;
	bool Boss2_Appear = false;

	CMonster(EnemyInfo enemyInfo);
	CMonster();
	~CMonster();
public:
	virtual void Update();
	int GetIndex() { return MyIndex; }
	void SetIndex(int index) { MyIndex = index; }
	//virtual void Render(HDC m_hdc);
};
