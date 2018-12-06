#pragma once

#include "CGameObject.h"
class CBullet;
class CMonster : public CGameObject
{
private:
	
	
public:
	
	bool Boss1_Appear = false;
	bool Boss2_Appear = false;
	vector<CBullet> enemy_bullet1;

	//vector<CBullet> enemy_bullet1;
	vector<CBullet> enemy_bullet2[3];
	vector<CBullet> enemy_bullet3[8];
	CMonster(E_OBJECT typeNum);
	CMonster();
	
	~CMonster();
public:
	virtual void Update();
	virtual void Render(HDC m_hdc);
};

