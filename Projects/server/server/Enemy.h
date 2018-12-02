#pragma once
#include "stdafx.h"
#include "MyPacket.h"
#include "CGameObject.h"

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
