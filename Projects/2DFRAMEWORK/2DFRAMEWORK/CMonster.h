#pragma once

#include "CGameObject.h"

class CMonster : public CGameObject
{
private:
	float Size;
	bool alive = false;
	
public:
	
	bool Boss1_Appear = false;
	bool Boss2_Appear = false;

	CMonster(E_OBJECT typeNum);
	CMonster();
	void SetAlive(bool life) { alive = life; }
	bool getAlive() { return alive; }
	~CMonster();
public:
	virtual void Update();
	virtual void Render(HDC m_hdc);
};

