#pragma once
#include "Enemy.h"
#include "Input.h"
#include "MyPacket.h"
#include "CGameObject.h"
#include "TimerManager.h"
#include "CItem.h"

class CGameObject;
class Server {
public:
	//클라이언트 접속관리
	PlayerInfo playerInfo[2];
	EnemyInfo enemyInfo[2];
	ItemInfo itemInfo[2];
	BulletInfo bulletInfo[2];
	TimeManager* m_pTime = new TimeManager();
	InputManager Input;
	DWORD KeyInput;
	

	vector<CBullet*> playerBullet[2];
	vector<CMonster*> m_Monster;
	vector<CItem*> m_Item;

	CMonster* m_pMonster = new CMonster;
	CItem* m_pItem = new CItem;

	int score = 1;

	CRITICAL_SECTION cs;
	//=====OBJTIME======
	float enemyTime1;
	float enemyTime2;
	float enemyTime3;
	float enemyTime4;
	float enemyTime5;

	float ItemTime1;
	float ItemTime2;
	float ItemTime3;
	float ItemTime4;
	float ItemTime5;


	// =========함수=========

	
	bool IsAllClientReady();
	void SetInitData(PlayerInfo& a, int num);
	void SendAllPlayerInfo(SOCKET sock, PlayerInfo P[]);
	void sendAllIngamePack(SOCKET sock);
	void MakeItem(SOCKET sock,int Cnum);
	void MakeEnemy(SOCKET sock, int Cnum);
	void CheckEnemybyPlayerBulletCollision(SOCKET sock, vector<CBullet*> Bullet, vector<CMonster*> Target);

	
	

};