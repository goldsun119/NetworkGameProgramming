#pragma once
#include "stdafx.h"
#include "CBullet.h"

enum E_Scene {
	E_TITLE,
	E_MENU,
	E_INGAME,
	E_GAMEOVER,
	E_RANK
};

#pragma pack(1)
class ClientInfoToHandle {
public:
	int PlayNum;
	bool IsReady = false;
	bool IsDead = false;
	int IsScene = E_MENU;
	SOCKET Sock;
	SOCKADDR_IN Addr;
};

#pragma pack(1)
class BulletInfo {
public:
	bool Active;
	int index;
	POINT Pos;
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
};
enum E_OBJECT
{
	E_BACKGROUND,
	E_PLAYER,
	E_ENEMY1,
	E_ENEMY2,
	E_ENEMY3,
	E_BOSS1,
	E_BOSS2
};
#pragma pack(1)
class EnemyInfo {
public:
	int Index;
	bool alive;
	POINT pos;
	int Type;
	int Hp;
};
enum E_ITEM
{
	E_ITEM,
	E_IPOWER,
	E_ISKILL,
	E_ISUB,
	E_ISHIELD,
	E_IBULLET
};
#pragma pack(1)
class ItemInfo {
public:
	bool IsDraw;
	int Type;
	POINT pos;
	int Index;
};