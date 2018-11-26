#pragma once

#include "CGameObject.h"

class CMonster : public CGameObject
{
private:
	POINT Pos;
	float Size;

public:
	bool Boss1_Appear = false;
	bool Boss2_Appear = false;

	CMonster(E_OBJECT typeNum);
	CMonster();
	~CMonster();
public:
	virtual void Update();
	virtual void Render(HDC m_hdc);
};

