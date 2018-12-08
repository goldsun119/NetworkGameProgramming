#pragma once

#include "CGameObject.h"
class CBullet;
class CMonster : public CGameObject
{
private:
	
	
public:
	
	bool Boss1_Appear = false;
	bool Boss2_Appear = false;

	bool Boss1_Stop = false;
	bool Boss2_Stop = false;
	vector<CBullet> enemy_bullet;

	CMonster(E_OBJECT typeNum);
	CMonster();
	
	~CMonster();
public:
	virtual void Update();
	virtual void Render(HDC m_hdc);
};

