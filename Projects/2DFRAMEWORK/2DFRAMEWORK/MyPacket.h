#include "stdafx.h"
#include "CBullet.h"
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
	bool Space;
	int Score;
	bool skill;
};

#pragma pack(1)
class BulletInfo {
public:
	bool Active;
	int index;
	POINT Pos;
};

#pragma pack(1)
class EnemyInfo {
public:
	int index;
	bool alive;
	POINT pos;
	int Type;
	int Hp;
};

#pragma pack(1)
class ItemInfo {
public:
	bool alive;
	int Type;
	POINT pos;
	int Index;
};

#pragma pack(1)
class KeyIn
{
public:
	bool Left;
	bool Right;
	bool Up;
	bool Down;
	bool Space;
	bool Skill;
};