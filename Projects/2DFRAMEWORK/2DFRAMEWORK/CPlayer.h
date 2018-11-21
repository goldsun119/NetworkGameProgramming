#pragma once
#include "CGameObject.h"
class CBullet;
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
	bool m_IsReady = false;
	bool GetIsReady() { return m_IsReady; }
	void SetReady(bool ready);
	virtual void Update();
	virtual void Render(HDC m_hdc);
	vector<CBullet*> m_PlayerBullet;
};

