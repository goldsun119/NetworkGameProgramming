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
	EnemyInfo enemyInfo;
	ItemInfo itemInfo;
	BulletInfo bulletInfo;
	BulletInfo enemybulletInfo[2];
	TimeManager m_pTime = TimeManager();
	InputManager Input;
	DWORD KeyInput;
	
	EnemyBulletInfo enemyBulletInfo;
	vector<CBullet> playerBullet[2];
	vector<CMonster> m_Monster;
	vector<CItem> m_Item;
	vector<Score> Rank;

	CMonster m_pMonster = CMonster{};
	CItem m_pItem = CItem();

	int score = 1;
	bool skillPlaying =false;
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
	void SendAllPlayerInfo( PlayerInfo P[]);
	void MakeItem();
	void MakeEnemy();
	void CheckItembyPlayerCollision(vector<CItem> &item, PlayerInfo &player);
	void CheckEnemybyPlayerBulletCollision(vector<CBullet> &Bullet, vector<CMonster> &Target);
	void SkillCollision(vector<CMonster> &Target);
	void CheckPlayerbyEnemyBulletCollision(vector<CBullet> Bullet, PlayerInfo &player);
	
	void KeyInputFunc(int ClientNum);
	void SkillUpdate();
	void EnemyUpdate(int Mnum, int Ebnum, int ClientNum);
	void ItemUpdate(int Inum);
	void ChackAndUpdate(int Bnum);
	void EnemyBulletChack();
	void PlayerBulletUpdate();
	void RankScene(int SendCount, int ClientNum);

};