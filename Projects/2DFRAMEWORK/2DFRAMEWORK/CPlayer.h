#pragma once
#include "CGameObject.h"

class CPlayer : public CGameObject
{

	float Speed;
	POINT Pos;
	float Size;
	
public:
	CPlayer();
	~CPlayer();

public:
	void CheckKey();

public:
	virtual void Update();
	virtual void Render(HDC m_hdc);
};

