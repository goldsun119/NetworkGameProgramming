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
	BulletInfo enemybulletInfo[2];
	TimeManager m_pTime = TimeManager();
	InputManager Input;
	DWORD KeyInput;
	

	vector<CBullet> playerBullet[2];
	vector<CMonster> m_Monster;
	vector<CItem> m_Item;
	vector<Score> Rank;

	CMonster m_pMonster = CMonster{};
	CItem m_pItem = CItem();

	int score = 1;
	bool skillPlaying;
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

	float BulletTime;
	// =========함수=========

	
	bool IsAllClientReady();
	void SetInitData(PlayerInfo& a, int num);
	void SendAllPlayerInfo(SOCKET sock, PlayerInfo P[]);
	void MakeItem(SOCKET sock,int Cnum);
	void MakeEnemy(SOCKET sock, int Cnum);
	void CheckItembyPlayerCollision(SOCKET sock, vector<CItem>& item, PlayerInfo player);
	void CheckEnemybyPlayerBulletCollision(SOCKET sock, vector<CBullet>& Bullet, vector<CMonster> &Target);
	void SkillCollision(vector<CMonster> &Target);
	void CheckPlayerbyEnemyBulletCollision(SOCKET sock, vector<CBullet>& Bullet, PlayerInfo player);

	

};