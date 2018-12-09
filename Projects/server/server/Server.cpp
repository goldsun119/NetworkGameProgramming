#include "stdafx.h"
#include "server.h"

void err_quit(char *msg);
void err_display(char *msg);
int recvn(SOCKET s, char *buf, int len, int flags);
//=============================================================

ClientInfoToHandle clientinfotohandle[2];
int ClientCount = 0; //클라이언트 번호 할당
Server server;
string Nick[2] = { "1st","2nd" };
bool nick[2] = { false };

//=============================================================
istream&ReadInputFile(istream& in, vector<Score>& vec)
{
	if (in)
	{
		vec.clear();
		Score mem;

		while (in >> mem.first >> mem.second)
		{
			vec.emplace_back(mem);
		}
		in.clear();
	}
	return in;
}

int SortFunc(Score a, Score b)
{
	return a.first > b.first;
}

bool Server::IsAllClientReady()
{
	if (playerInfo[0].IsReady == true && playerInfo[1].IsReady == true) { //11.12 소현 고친곳
		clientinfotohandle[0].IsReady = true;
		clientinfotohandle[1].IsReady = true;

		return true;
	}
	else {
		return false;
	}
}
void Server::SetInitData(PlayerInfo& a, int num)
{
	//초기값 설정 함수로 만들자!
	a.Pos = { (num * 200) + 100, 500 };
	a.Hp = 3;
	a.BulletCount = 1;
	a.Shield = 0;
	a.SubWeapon = 1;
	a.Power = 1;
	a.Score = 0;
	a.skill = false;
}

void Server::SendAllPlayerInfo( PlayerInfo P[])
{
	
	send(clientinfotohandle[0].Sock, (char*)&P[0], sizeof(P[0]), 0);//플레이어 정보 전송
	send(clientinfotohandle[0].Sock, (char*)&P[1], sizeof(P[1]), 0);//플레이어 정보 전송
	send(clientinfotohandle[1].Sock, (char*)&P[0], sizeof(P[0]), 0);//플레이어 정보 전송
	send(clientinfotohandle[1].Sock, (char*)&P[1], sizeof(P[1]), 0);//플레이어 정보 전송
}
void Server::CheckItembyPlayerCollision( vector<CItem>& item, PlayerInfo& player)
{

		for (vector<CItem>::iterator p = item.begin(); p < item.end(); ++p)

		{
			if (p->alive == true)
			{
				if (p->IsGetItem(player))
				{

					switch (p->GetType())
					{
					case E_IPOWER:
						if (!player.Power)
							player.Power = true;
						p->alive = false;

						//p = item.erasep;
						break;
					case E_ISHIELD:
						if (!player.Shield)
							player.Shield = true;
						p->alive = false;

						//p = item.erasep;
						break;
					case E_ISKILL:
						if (!player.skill)
							player.skill = true;
						p->alive = false;

						//p = item.erasep;
						break;
					case E_ISUB:
						if (!player.SubWeapon)
							player.SubWeapon = true;
						p->alive = false;


						//p = item.erasep;
						break;
					case E_IBULLET:
						if (player.BulletCount < 3)
							player.BulletCount += 1;
						p->alive = false;
						//printf("으후");

					//p = item.erasep;
						break;
					}

				}
			}

		}
	
}

void Server::MakeItem()
{
	
	
	int itemNumber = 0;
	float NowTime = (float)timeGetTime() * 0.001f;
	static int inum1 = 0;
	static int inum2 = 0;
	static int inum3 = 0;
	static int inum4 = 0;
	static int inum5 = 0;
	if (itemNumber < 10) {
		if (NowTime - ItemTime1 >= 10.0f)
		{
			if (inum1 < 10)
			{
				server.itemInfo.Index = inum1;
				inum1++;
				server.itemInfo.alive = true;
				server.itemInfo.Type = E_IPOWER;
				EnterCriticalSection(&cs);
				server.m_Item.push_back(CItem(server.itemInfo));
				LeaveCriticalSection(&cs);
				//I_power.push_back( I_POWER());
				EnterCriticalSection(&cs);
				ItemTime1 = NowTime;
				LeaveCriticalSection(&cs);
			}
			//printf("파워 생성");
		}
		if (NowTime - ItemTime2 >= 20.0f)
		{
			if (inum2 < 10)
			{
				server.itemInfo.Index = inum2;
				inum2++;
				server.itemInfo.alive = true;
				server.itemInfo.Type = E_ISKILL;
				EnterCriticalSection(&cs);
				server.m_Item.push_back(CItem(server.itemInfo));
				LeaveCriticalSection(&cs);
				//I_skill.push_back( I_SKILL());
				EnterCriticalSection(&cs);
				ItemTime2 = NowTime;
				LeaveCriticalSection(&cs);
			}

			//printf("스킬 생성");

		}
		if (NowTime - ItemTime3 >= 30.0f)
		{
			if (inum3 < 10)
			{
				server.itemInfo.Index = inum3;
				inum3++;
				server.itemInfo.alive = true;
				server.itemInfo.Type = E_IBULLET;
				EnterCriticalSection(&cs);
				server.m_Item.push_back(CItem(server.itemInfo));
				LeaveCriticalSection(&cs);
				//I_bullet.push_back( I_BULLET());
				EnterCriticalSection(&cs);
				ItemTime3 = NowTime;
				LeaveCriticalSection(&cs);
			}
			//printf("보조총알 생성");

		}
		if (NowTime - ItemTime4 >= 40.0f)
		{
			if (inum4 < 10)
			{
				server.itemInfo.Index = inum4;
				inum4++;
				server.itemInfo.alive = true;
				server.itemInfo.Type = E_ISUB;
				EnterCriticalSection(&cs);
				server.m_Item.push_back(CItem(server.itemInfo));
				LeaveCriticalSection(&cs);
				//I_sub.push_back( I_SUB());
				EnterCriticalSection(&cs);
				ItemTime4 = NowTime;
				LeaveCriticalSection(&cs);
			}

		}
		if (NowTime - ItemTime5 >= 50.0f)
		{
			if (inum5 < 10)
			{
				server.itemInfo.Index = inum5;
				inum5++;
				server.itemInfo.alive = true;
				server.itemInfo.Type = E_ISHIELD;
				EnterCriticalSection(&cs);
				server.m_Item.push_back(CItem(server.itemInfo));
				LeaveCriticalSection(&cs);
				//I_sheild.push_back( I_SHEILD());

				EnterCriticalSection(&cs);
				ItemTime5 = NowTime;
				LeaveCriticalSection(&cs);
			}
		}
	}
}
void Server::CheckEnemybyPlayerBulletCollision(vector<CBullet> &Bullet, vector<CMonster> &Target)
{
	for (vector<CBullet>::iterator bulletIter = Bullet.begin(); bulletIter < Bullet.end(); ++bulletIter)
	{
		for (vector<CMonster>::iterator enemy = Target.begin(); enemy < Target.end(); ++enemy)
		{
			if (bulletIter->GetAlive() && enemy->GetAlive() == true) {

				if (bulletIter->IsCrashtoEnemy(*enemy))
				{
					if (enemy->GetAlive() == true)
						bulletIter->SetAlive(false);
					if (bulletIter->getType() == -1)
					{
						enemy->SetHp(enemy->GetHp() - 10);
					}
					else if (bulletIter->getType() == 0)
					{
						enemy->SetHp(enemy->GetHp() - 10);
					}

					if (enemy->GetHp() <= 0)
					{
						enemy->SetAlive(false);
					}

				}
			}

		}
		
	}

}
void Server::SkillCollision(vector<CMonster> &Target) {
	
	for (vector<CMonster>::iterator enemy = Target.begin(); enemy < Target.end(); ++enemy)
	{
		if (enemy->GetAlive() == true)
			enemy->SetHp(enemy->GetHp() - 100);
		if (enemy->GetHp() <= 0)
		{
			enemy->alive = false;
			
		}
	}
	
}
void Server::CheckPlayerbyEnemyBulletCollision(vector<CBullet>Bullet, PlayerInfo& player)
{
	for (vector<CBullet>::iterator p = Bullet.begin(); p < Bullet.end(); ++p)
	{
		
		if (p->GetAlive())
		{
			if (p->IsShootPlayer(player))
			{
				switch (p->getType())
				{
				case 0:
				case -1:
				case -2:
					p->SetAlive(false);
					player.Hp -= 1;
					
					
					break;
				case 1:
					p->SetAlive(false);
					p->m_IsActive = false;
					player.Hp -= 1;
		
					break;
				case 2:
					p->SetAlive(false);
					p->m_IsActive = false;
					player.Hp -= 1;

					break;
				case 3:
					p->SetAlive(false);
					p->m_IsActive = false;
					player.Hp -= 1;

					break;
				case 4:
					p->SetAlive(false);
					p->m_IsActive = false;
					player.Hp -= 1;

					break;
				}

			}
		}

	}
}

void Server::MakeEnemy()
{
	
	
	static int MonsterNumber = 0;
	//g_makeEnemy1  = 3;
	//DWORD maketime = GetTickCount();
	float NowTime = (float)timeGetTime() * 0.001f;
	
	//maketime = maketime - time;
	//maketime += 1;
	//m_Monster.push_back( CMonster(E_ENEMY1));
	//send(sock, (char*)&maketime, sizeof(maketime), 0);
	if (m_pMonster.Boss2_Appear == false) {
		if (NowTime - enemyTime1 >= 3.0f)
		{
			server.enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo.alive = true;
			server.enemyInfo.Type = E_ENEMY1;
			EnterCriticalSection(&cs);
			m_Monster.push_back( CMonster(server.enemyInfo));
			LeaveCriticalSection(&cs);
			//printf("1번 생성\n");
			EnterCriticalSection(&cs);
			enemyTime1 = NowTime;
			LeaveCriticalSection(&cs);
		}
		if (NowTime - enemyTime2 >= 5.0f)
		{
			server.enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo.alive = true;
			server.enemyInfo.Type = E_ENEMY2;
			EnterCriticalSection(&cs);
			m_Monster.push_back( CMonster(server.enemyInfo));
			LeaveCriticalSection(&cs);
			//printf("2번 생성\n");
			EnterCriticalSection(&cs);
			enemyTime2 = NowTime;
			LeaveCriticalSection(&cs);
		}

		if (NowTime - enemyTime3 >= 10.0f)
		{
			server.enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo.alive = true;
			server.enemyInfo.Type = E_ENEMY3;
			EnterCriticalSection(&cs);
			m_Monster.push_back( CMonster(server.enemyInfo));
			LeaveCriticalSection(&cs);
			//   printf("3번 생성\n");
			EnterCriticalSection(&cs);
			enemyTime3 = NowTime;
			LeaveCriticalSection(&cs);
		}
	}

	if (NowTime - enemyTime4 >= 50.0f)
	{
		if (m_pMonster.Boss1_Appear == false)
		{
			server.enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo.alive = true;
			server.enemyInfo.Type = E_BOSS1;
			EnterCriticalSection(&cs);
			m_Monster.push_back( CMonster(server.enemyInfo));
			LeaveCriticalSection(&cs);
			//printf("보스1 생성\n");

			m_pMonster.Boss1_Appear = true;
			EnterCriticalSection(&cs);
			enemyTime4 = NowTime;
			LeaveCriticalSection(&cs);
		}
	}

	if (NowTime - enemyTime5 >= 80.0f)
	{
		if (m_pMonster.Boss2_Appear == false)
		{
			server.enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo.alive = true;
			server.enemyInfo.Type = E_BOSS2;
			EnterCriticalSection(&cs);
			m_Monster.push_back( CMonster(server.enemyInfo));
			LeaveCriticalSection(&cs);
			//printf("보스2 생성\n");

			m_pMonster.Boss2_Appear = true;
			EnterCriticalSection(&cs);
			enemyTime5 = NowTime;
			LeaveCriticalSection(&cs);
		}
	}
	if (MAXOBJECTNUM <= MonsterNumber) {
		return;
	}
}



DWORD WINAPI ProcessClient(LPVOID arg) {
	SOCKET ClientSock = (SOCKET)arg;
	SOCKADDR ClientAddr;
	int AddrLen;
	AddrLen = sizeof(ClientAddr);
	getpeername(ClientSock, (SOCKADDR*)&ClientAddr, &AddrLen);
	//================================================================

	int SendCount = 0;
	int Ebnum;

	int retval = 0;

	int ClientNum = ClientCount - 1;
	clientinfotohandle[ClientNum].PlayNum = ClientNum;
	server.SetInitData(server.playerInfo[ClientNum], ClientNum);


	bool isClientnumSend = false;

	//시간설정

	EnterCriticalSection(&server.cs);
	server.enemyTime1 = server.enemyTime2 = server.enemyTime3 = server.enemyTime4 = server.enemyTime5 = (float)timeGetTime() * 0.001f;
	server.ItemTime1 = server.ItemTime2 = server.ItemTime3 = server.ItemTime4 = server.ItemTime5 = (float)timeGetTime() * 0.001f;
	server.m_pTime.m_CurrentTime = timeGetTime();
	server.BulletTime = (float)timeGetTime() * 0.001f;
	server.m_pTime.m_eTime = server.m_pTime.m_CurrentTime - server.m_pTime.m_PrevTime;
	LeaveCriticalSection(&server.cs);
	server.m_pTime.m_eActine += server.m_pTime.m_eTime;
	if (server.m_pTime.m_eActine > 1 / FPS_PERSECOND)
	{

	while (true)
	{
		server.m_pTime.m_eTime = 0.0f;

		int Snum = clientinfotohandle[ClientNum].IsScene;
		int idx = 0;
		int Bnum;
		int num;
		int Mnum;
		int Inum;
		switch (Snum) {
		case E_Scene::E_MENU: //메뉴화면일때
			printf("메뉴씬입니다!\n");

			retval = recvn(ClientSock, (char*)&server.playerInfo[ClientNum].IsReady, sizeof(server.playerInfo[ClientNum].IsReady), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv() IsReady");
				break;
			}

			if (server.IsAllClientReady() == true) {
				clientinfotohandle[ClientNum].IsScene = E_Scene::E_INGAME; 
				//clientinfotohandle[ClientNum].IsScene = E_Scene::E_INGAME; //게임플레이로 씬전환
				retval = send(ClientSock, (char*)&clientinfotohandle[ClientNum].IsScene, sizeof(clientinfotohandle[ClientNum].IsScene), 0);//씬전환 전송
				send(ClientSock, (char*)&clientinfotohandle[ClientNum].PlayNum, sizeof(clientinfotohandle[ClientNum].PlayNum), 0);
			}
			else {
				//준비가 아닐때는 메뉴씬을 넘겨줘야함
				retval = send(ClientSock, (char*)&clientinfotohandle[ClientNum].IsScene, sizeof(clientinfotohandle[ClientNum].IsScene), 0);
				if (retval == SOCKET_ERROR) {
					err_display("send() Scene");
					break;
				}
				printf("레디 해!\n");
			}
			break;

			//게임 중 일때
		case E_Scene::E_INGAME:
			//printf("인게임씬입니다\n");
			//g_IngameStartTime = GetTickCount();


			retval = recvn(ClientSock, (char*)&server.Input.m_KeyInput, sizeof(server.Input.m_KeyInput), 0);   //키 입력값 받음 더좋은 방법을 찾자~
			if (retval == SOCKET_ERROR) {
				err_display("recv() KeyInput");
				return 0;
				break;
			}
			EnterCriticalSection(&server.cs);

			if (server.Input.m_KeyInput.Left)
			{
				server.playerInfo[ClientNum].Pos.x -= 3;
			}
			if (server.Input.m_KeyInput.Right)
			{
				server.playerInfo[ClientNum].Pos.x += 3;
			}
			if (server.Input.m_KeyInput.Up)
			{
				server.playerInfo[ClientNum].Pos.y -= 3;
			}
			if (server.Input.m_KeyInput.Down)
			{
				server.playerInfo[ClientNum].Pos.y += 3;
			}
			if (server.Input.m_KeyInput.Space)
			{
				float NowTime = (float)timeGetTime();
				if (NowTime - server.BulletTime >= 0.5f) {
					server.playerBullet[ClientNum].emplace_back(CBullet(server.playerInfo[ClientNum].Pos, 0));
					//printf("%d번클라 스페이스바!\n",ClientNum);
					server.BulletTime = NowTime;
				}
			}
			if (server.Input.m_KeyInput.Skill)
			{
				server.playerInfo[ClientNum].skill = true;
			}
			LeaveCriticalSection(&server.cs);

			//server.playerInfo[ClientNum].skill = server.Input.m_KeyInput.Skill;
			//여기 플레이어 생존 여부 확인 시 보냄
			if (ClientNum == 0)
			{
				EnterCriticalSection(&server.cs);
				server.SendAllPlayerInfo(server.playerInfo);//플레이어
				LeaveCriticalSection(&server.cs);
			

			// 여긴 좀 더 생각하기~!?@~@~!@?~!?@~!?@?~!@?~!?@~!?@~!?@?~!@?~!@?~!?@~!?@~!@~!?@~!
				
			
				if (server.playerInfo[ClientNum].skill == true) {


					int Msize = server.m_Monster.size();

					send(clientinfotohandle[1].Sock, (char*)&Msize, sizeof(Msize), 0);//몬스터크기가 너무 커서 미리 사이즈 알려줌
					send(clientinfotohandle[0].Sock, (char*)&Msize, sizeof(Msize), 0);
					if (Msize > 0) {
							server.SkillCollision(server.m_Monster);
						for (vector<CMonster>::iterator enemy = server.m_Monster.begin(); enemy < server.m_Monster.end(); ++enemy)
						{

									//EnterCriticalSection(&server.cs);
									server.enemyInfo.alive = enemy->GetAlive();
									server.enemyInfo.Hp = enemy->GetHp();

									send(clientinfotohandle[1].Sock, (char*)&server.enemyInfo, sizeof(server.enemyInfo), 0);
									send(clientinfotohandle[0].Sock, (char*)&server.enemyInfo, sizeof(server.enemyInfo), 0);
									//LeaveCriticalSection(&server.cs);

						}
					}
					server.playerInfo[1].skill = false;
					server.playerInfo[0].skill = false;
				}
			
					
			

			
				server.MakeEnemy(); //적
				Mnum = server.m_Monster.size();
				send(clientinfotohandle[1].Sock, (char*)&Mnum, sizeof(Mnum), 0);
				send(clientinfotohandle[0].Sock, (char*)&Mnum, sizeof(Mnum), 0);
				for (int i = 0; i < Mnum; ++i)
				{
					server.m_Monster[i].Update();

					server.enemyInfo.pos = server.m_Monster[i].GetPos();
					server.enemyInfo.Index = server.m_Monster[i].GetIndex();
					server.enemyInfo.Type = server.m_Monster[i].GetType();
					server.enemyInfo.alive = server.m_Monster[i].GetAlive();
					server.enemyInfo.Hp = server.m_Monster[i].GetHp();
					send(clientinfotohandle[1].Sock, (char*)&server.enemyInfo, sizeof(server.enemyInfo), 0);
					send(clientinfotohandle[0].Sock, (char*)&server.enemyInfo, sizeof(server.enemyInfo), 0);


					Ebnum = server.m_Monster[i].m_EnemyBullet.size();
					send(clientinfotohandle[1].Sock, (char*)&Ebnum, sizeof(Ebnum), 0);
					send(clientinfotohandle[0].Sock, (char*)&Ebnum, sizeof(Ebnum), 0);
					if (Ebnum != 0) {
						for (int j = 0; j < Ebnum; ++j)
						{
							server.enemybulletInfo[ClientNum].Pos = server.m_Monster[i].m_EnemyBullet[j].GetPos();
							server.enemybulletInfo[ClientNum].Active = server.m_Monster[i].m_EnemyBullet[j].GetAlive();
							send(clientinfotohandle[1].Sock, (char*)&server.enemybulletInfo[ClientNum], sizeof(server.enemybulletInfo[ClientNum]), 0);
							send(clientinfotohandle[0].Sock, (char*)&server.enemybulletInfo[ClientNum], sizeof(server.enemybulletInfo[ClientNum]), 0);
						}
					}
				}
			
			
				server.MakeItem(); //아이템
				Inum = server.m_Item.size();
				send(clientinfotohandle[0].Sock, (char*)&Inum, sizeof(Inum), 0);
				send(clientinfotohandle[1].Sock, (char*)&Inum, sizeof(Inum), 0);
				server.CheckItembyPlayerCollision(server.m_Item, server.playerInfo[0]);
				server.CheckItembyPlayerCollision(server.m_Item, server.playerInfo[1]);



				for (int i = 0; i < Inum; ++i)
				{
					server.m_Item[i].Update();
					server.itemInfo.Index = server.m_Item[i].MyIndex;
					server.itemInfo.pos = server.m_Item[i].GetPos();
					server.itemInfo.Type = server.m_Item[i].GetType();
					server.itemInfo.alive = server.m_Item[i].alive;
					send(clientinfotohandle[0].Sock, (char*)&server.itemInfo, sizeof(server.itemInfo), 0);
					send(clientinfotohandle[1].Sock, (char*)&server.itemInfo, sizeof(server.itemInfo), 0);
				}
			

				//충돌체크 및 업데이트
			
			
				for (int f = 0; f < 2; ++f)
				{
					Bnum = server.playerBullet[f].size();
					send(clientinfotohandle[0].Sock, (char*)&Bnum, sizeof(Bnum), 0);//총알 크기 미리 알려줌
					send(clientinfotohandle[1].Sock, (char*)&Bnum, sizeof(Bnum), 0);//총알 크기 미리 알려줌

					if (server.playerBullet[f].size() > 0) {
						if (server.m_Monster.size() > 0) {
							server.CheckEnemybyPlayerBulletCollision(server.playerBullet[f], server.m_Monster);

						}
						for (vector<CBullet>::iterator bulletIter = server.playerBullet[f].begin(); bulletIter < server.playerBullet[f].end(); ++bulletIter)
						{
							server.bulletInfo.Active = bulletIter->GetAlive();
							server.bulletInfo.Pos = bulletIter->GetPos();
							send(clientinfotohandle[0].Sock, (char*)&server.bulletInfo, sizeof(server.bulletInfo), 0);
							send(clientinfotohandle[1].Sock, (char*)&server.bulletInfo, sizeof(server.bulletInfo), 0);
						}

						int Msize = server.m_Monster.size();
						send(clientinfotohandle[0].Sock, (char*)&Msize, sizeof(Msize), 0);//몬스터크기가 너무 커서 미리 사이즈 알려줌
						send(clientinfotohandle[1].Sock, (char*)&Msize, sizeof(Msize), 0);//몬스터크기가 너무 커서 미리 사이즈 알려줌

						for (vector<CMonster>::iterator enemy = server.m_Monster.begin(); enemy < server.m_Monster.end(); ++enemy)
						{
							server.enemyInfo.alive = enemy->GetAlive();
							server.enemyInfo.pos = enemy->GetPos();
							server.enemyInfo.Index = (*enemy).GetIndex();
							send(clientinfotohandle[0].Sock, (char*)&server.enemyInfo, sizeof(server.enemyInfo), 0);
							send(clientinfotohandle[1].Sock, (char*)&server.enemyInfo, sizeof(server.enemyInfo), 0);
						}

					}
				}
			

				//적총알 충돌체크
			
				for (vector<CMonster>::iterator enemy = server.m_Monster.begin(); enemy < server.m_Monster.end(); ++enemy)
				{
					server.CheckPlayerbyEnemyBulletCollision(enemy->m_EnemyBullet, server.playerInfo[0]);
					server.CheckPlayerbyEnemyBulletCollision(enemy->m_EnemyBullet, server.playerInfo[1]);
				}
				//플레이어 총알
							//이동
				for (int f = 0; f < 2; ++f)
				{
					for (int p =0; p < server.playerBullet[f].size(); ++p)
					{
						if (server.playerBullet[f][p].GetAlive())
						{
							server.playerBullet[f][p].SetYPos(server.playerBullet[f][p].GetYPos() - 13);
							//printf("%d", p.GetYPos());
						
							//화면 나갈 시 삭제
							if (server.playerBullet[f][p].GetYPos() < 0 && server.playerBullet[f][p].GetAlive())
							{
								server.playerBullet[f][p].alive = false;
								swap(server.playerBullet[f][p], server.playerBullet[f].back());
								server.playerBullet[f].pop_back();
							}
						}
					}
				}
				
			}

			break;
				
			
			//인게임 아이템
		   //send(ClientSock, (char*)&playerInfo[ClientNum].m_PlayerBullet, sizeof(playerInfo[ClientNum].m_PlayerBullet), 0);
		   //게임 종료
		case E_Scene::E_GAMEOVER:
			if (SendCount == 0)
			{
				if (ClientNum == 0)
				{
					ofstream out("Score.txt");
					Score temp;
					temp.first = server.score;
					temp.second = Nick[0] + "," + Nick[1];
					server.Rank.emplace_back(temp);
					sort(server.Rank.begin(), server.Rank.end(), SortFunc);
					int Rnum = server.Rank.size();
					send(clientinfotohandle[1].Sock, (char*)&temp.first, sizeof(temp.first), 0);
					send(clientinfotohandle[1].Sock, (char*)&Rnum, sizeof(Rnum), 0);


					send(clientinfotohandle[0].Sock, (char*)&temp.first, sizeof(temp.first), 0);
					send(clientinfotohandle[0].Sock, (char*)&Rnum, sizeof(Rnum), 0);

					for (vector<Score>::iterator iter = server.Rank.begin(); iter != server.Rank.end(); ++iter)
					{
						out << iter->first << " " << iter->second << endl;
						send(clientinfotohandle[1].Sock, (char*)&iter->first, sizeof(iter->first), 0);
						send(clientinfotohandle[1].Sock, (char*)&iter->second, sizeof(iter->second), 0);
						send(clientinfotohandle[0].Sock, (char*)&iter->first, sizeof(iter->first), 0);
						send(clientinfotohandle[0].Sock, (char*)&iter->second, sizeof(iter->second), 0);
					}
					out.close();
					SendCount++;
				}
			}
			break;
			//랭크 출력
		case E_Scene::E_RANK:
			break;
		}
	}
	}

	closesocket(ClientSock);

	return 0;
}

//
/////////////////////////////////////////////////////
//
int main(int argc, char argv[])
{
	
	srand(time(NULL));
	int retval;
	InitializeCriticalSection(&server.cs);

	server.Rank.reserve(100);
	ifstream in("score.txt");
	if (!in.is_open())
		err_quit("Can't File Open");
	ReadInputFile(in, server.Rank);

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (ListenSock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN ServerAddr;
	ZeroMemory(&ServerAddr, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(SERVERPORT);
	retval = bind(ListenSock, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(ListenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");
	int sockopt = TRUE;
	setsockopt(clientinfotohandle[ClientCount].Sock, IPPROTO_TCP, TCP_NODELAY, (const char*)&sockopt, sizeof(sockopt));
	// 데이터 통신에 사용할 변수
	int addrlen;
	HANDLE hThread;

	while (1)
	{
		addrlen = sizeof(clientinfotohandle[ClientCount].Addr);
		clientinfotohandle[ClientCount].Sock = accept(ListenSock, (SOCKADDR *)&clientinfotohandle[ClientCount].Addr, &addrlen);
		if (clientinfotohandle[ClientCount].Sock == INVALID_SOCKET) {
			err_display("accept()");
			exit(1);
		}
		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientinfotohandle[ClientCount].Addr.sin_addr), ntohs(clientinfotohandle[ClientCount].Addr.sin_port));
		
		
		hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)clientinfotohandle[ClientCount].Sock, 0, NULL);
		
		
		if (hThread == NULL) { closesocket(ListenSock); }
		else
		{
			CloseHandle(hThread);
			ClientCount++;
		}
	}

	DeleteCriticalSection(&server.cs);
	closesocket(ListenSock);

	// 윈속 종료
	WSACleanup();
	return 0;
}




void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}