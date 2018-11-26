#pragma once
#include "stdafx.h"

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
