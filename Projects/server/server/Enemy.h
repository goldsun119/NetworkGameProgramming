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
	POINT Pos;

public:
	
	bool Boss1_Appear = false;
	bool Boss2_Appear = false;

	CMonster(E_OBJECT typeNum);
	CMonster();
	~CMonster();
public:
	virtual void Update();
	//virtual void Render(HDC m_hdc);
};
