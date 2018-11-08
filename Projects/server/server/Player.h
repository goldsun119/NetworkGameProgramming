#pragma once
#include "stdafx.h"
#pragma pack(1)
class ClientInfoToHandle {
public:
	bool IsReady = false;
	bool IsDead = false;
	int IsScene;
};

#pragma pack(1)
class PlayerInfo {
public:
	POINT Pos;
	int Hp;
	int BulletCount;
	bool Shield;
	bool SubWeapon;
	bool Power;
	int Score;
};
