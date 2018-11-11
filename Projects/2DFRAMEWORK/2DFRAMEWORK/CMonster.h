#pragma once

#include "CGameObject.h"



class CMonster : public CGameObject
{
private:
	POINT Pos;
	float Size;
public:
	CMonster();
	~CMonster();
public:
	virtual void Update();
	virtual void Render(HDC m_hdc);
};

