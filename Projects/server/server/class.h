#pragma once
#pragma pack(1)
class ClientInfoToHandle {
public:
	bool IsReady=false;
	bool IsDead=false;
	
}; 
class PlayerInfo {
		POINT Pos;
	int Hp;
	int BulletCount;
	bool Shield;
	bool SubWeapon;
	bool Power;
	int Score;
};

class EnemyInfo {
		int Type;
	int Hp;
	int BoomCount;
	bool IsBoom;
};
