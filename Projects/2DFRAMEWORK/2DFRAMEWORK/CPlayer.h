#pragma once
#include "CGameObject.h"
#include "MyPacket.h"
class CBullet;
class CPlayer : public CGameObject
{

	float Speed;
	POINT Pos;
	float Size;
	int playerNum;

	int BulletCount;
	bool Shield;
	bool SubWeapon;
	bool Power;
	int SkillCount;
	bool Skillplay;
public:
	CPlayer();
	~CPlayer();

public:
	void CheckKey();

public:
	bool m_IsReady = false;
	int GetPlayerNum() { return playerNum; }
	bool GetIsReady() { return m_IsReady; }
	void SetSkillPlay(bool sp) { Skillplay = sp; }
	bool GetSkillPlay() { return Skillplay; }
	void SetReady(bool ready);
	virtual void Update();
	virtual void Render(HDC m_hdc);
	vector<CBullet*> m_PlayerBullet;
	KeyIn m_KeyInput;
};

