#include "stdafx.h"
#include <windef.h>
#pragma once

#pragma pack(1)
class ClientInfoToHandle {
public:
	int PlayNum;
	bool IsReady = false;
	bool IsDead = false;
	int IsScene = E_MENU;
};

#pragma pack(1)
class PlayerInfo {
public:
	bool IsReady = FALSE;
	POINT Pos;
	int Hp;
	int BulletCount;
	bool Shield;
	bool SubWeapon;
	bool Power;
	int Score;
};

#pragma pack(1)
class EnemyInfo {
public:
	int Type;
	int Hp;
	int BoomCount;
	bool IsBoom;
};
