#include "stdafx.h"
#include "server.h"

void err_quit(char *msg);
void err_display(char *msg);
int recvn(SOCKET s, char *buf, int len, int flags);
//=============================================================

ClientInfoToHandle clientinfotohandle[2];
int ClientCount = 0; //클라이언트 번호 할당
Server server;
char NICKNAME[2][4];
char Sum[10];
string Nick[2];
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

void SetRank(ofstream& out,vector<Score>& vec, Score temp)
{
	vec.emplace_back(temp);
	sort(vec.begin(), vec.end(), SortFunc);
}

bool Server::IsAllClientReady()
{
	if (playerInfo[0].IsReady == true && playerInfo[1].IsReady == true) { 
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
						p->SetPos(3000, 3000);
						break;
					case E_ISHIELD:
						if (!player.Shield)
							player.Shield = true;
						p->alive = false;
						p->SetPos(3000, 3000);
						break;
					case E_ISKILL:
						if (!player.skill)
							player.skill = true;
						p->alive = false;
						p->SetPos(3000, 3000);
						break;
					case E_ISUB:
						if (!player.SubWeapon)
							player.SubWeapon = true;
						p->alive = false;
						p->SetPos(3000, 3000);
						break;
					case E_IBULLET:
						if (player.BulletCount < 3)
							player.BulletCount += 1;
						p->alive = false;
						p->SetPos(3000, 3000);
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
				ItemTime2 = NowTime;
				LeaveCriticalSection(&cs);
			}

		

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

				ItemTime3 = NowTime;
				LeaveCriticalSection(&cs);
			}

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
						switch (enemy->GetType())
						{
						case E_ENEMY1:
							server.score += 10;
							break;
						case E_ENEMY2:
							server.score += 20;
							break;
						case E_ENEMY3:
							server.score += 30;
							break;
						case E_BOSS1:
							server.score += 100;
							break;
						case E_BOSS2:
							server.score += 100;
							break;
						}
						enemy->SetAlive(false);
						enemy->SetPos(3000, 3000);
						for (vector<CBullet>::iterator ebullet = enemy->m_EnemyBullet.begin(); ebullet < enemy->m_EnemyBullet.end(); ++ebullet)
						{
							ebullet->SetPos(3000, 3000);
							ebullet->SetAlive(false);
						}
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
			switch (enemy->GetType())
			{
			case E_ENEMY1:
				server.score += 10;
				break;
			case E_ENEMY2:
				server.score += 20;
				break;
			case E_ENEMY3:
				server.score += 30;
				break;
			case E_BOSS1:
				server.score += 100;
				break;
			case E_BOSS2:
				server.score += 100;
				break;
			}
			enemy->alive = false;
			enemy->SetPos(3000, 3000);
		}
	}
	
}
void Server::CheckPlayerbyEnemyBulletCollision(vector<CBullet>Bullet, PlayerInfo& player)
{
	for (vector<CBullet>::iterator p = Bullet.begin(); p < Bullet.end(); ++p)
	{
		
		if (p->GetAlive()&&player.Hp>0)
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
					p->SetPos(3000,3000);
					
					break;
				case 1:
					p->SetAlive(false);
					p->m_IsActive = false;
					player.Hp -= 1;
					p->SetPos(3000, 3000);
					break;
				case 2:
					p->SetAlive(false);
					p->m_IsActive = false;
					player.Hp -= 1;
					p->SetPos(3000, 3000);
					break;
				case 3:
					p->SetAlive(false);
					p->m_IsActive = false;
					player.Hp -= 1;
					p->SetPos(3000, 3000);
					break;
				case 4:
					p->SetAlive(false);
					p->m_IsActive = false;
					player.Hp -= 1;
					p->SetPos(3000, 3000);
					break;
				}

			}
		}

	}
}

void Server::MakeEnemy()
{
	static int MonsterNumber = 0;

	float NowTime = (float)timeGetTime() * 0.001f;

	if (MAXOBJECTNUM <= MonsterNumber) {return;}//몬스터 최대치

	if (m_pMonster.Boss2_Appear == false) {
		if (NowTime - enemyTime1 >= 3.0f)
		{
			server.enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo.alive = true;
			server.enemyInfo.Type = E_ENEMY1;
			EnterCriticalSection(&cs);
			m_Monster.push_back( CMonster(server.enemyInfo));
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
			m_pMonster.Boss1_Appear = true;
			EnterCriticalSection(&cs);
			m_Monster.push_back( CMonster(server.enemyInfo));
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
			m_pMonster.Boss2_Appear = true;
			EnterCriticalSection(&cs);
			m_Monster.push_back( CMonster(server.enemyInfo));
			enemyTime5 = NowTime;
			LeaveCriticalSection(&cs);
		}
	}
	
}
void Server::KeyInputFunc(int ClientNum) {
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
		if (server.playerInfo[ClientNum].Hp > 0)
		{
			float NowTime = (float)timeGetTime();
			if (NowTime - server.BulletTime >= 0.5f) {
				server.playerBullet[ClientNum].emplace_back(CBullet(server.playerInfo[ClientNum].Pos, 0));
				server.BulletTime = NowTime;
			}
		}
	}
	if (server.Input.m_KeyInput.Skill)
	{
		server.playerInfo[ClientNum].skill = true;
	}
}
void Server::SkillUpdate() {
	if (playerInfo[0].skill || playerInfo[1].skill) {


		int Msize = m_Monster.size();

		send(clientinfotohandle[1].Sock, (char*)&Msize, sizeof(Msize), 0);//몬스터크기가 너무 커서 미리 사이즈 알려줌
		send(clientinfotohandle[0].Sock, (char*)&Msize, sizeof(Msize), 0);
		if (Msize > 0) {
			SkillCollision(m_Monster);
			for (int i = 0; i < Msize; ++i)
			{


				enemyInfo.alive = m_Monster[i].GetAlive();
				enemyInfo.Hp = m_Monster[i].GetHp();

				send(clientinfotohandle[1].Sock, (char*)&enemyInfo, sizeof(enemyInfo), 0);
				send(clientinfotohandle[0].Sock, (char*)&enemyInfo, sizeof(enemyInfo), 0);
				for (vector<CBullet>::iterator enemy = m_Monster[i].m_EnemyBullet.begin(); enemy < m_Monster[i].m_EnemyBullet.end(); ++enemy) {
					enemy->alive == false;
					enemy->SetPos(3000, 3000);
				}

			}
			playerInfo[1].skill = false;
			playerInfo[0].skill = false;
		}

	}
}
void Server::EnemyUpdate(int Mnum, int Ebnum, int ClientNum) {
	Mnum = m_Monster.size();
	send(clientinfotohandle[1].Sock, (char*)&Mnum, sizeof(Mnum), 0);
	send(clientinfotohandle[0].Sock, (char*)&Mnum, sizeof(Mnum), 0);
	for (int i = 0; i < Mnum; ++i)
	{
		m_Monster[i].Update();

		enemyInfo.pos = m_Monster[i].GetPos();
		enemyInfo.Index = m_Monster[i].GetIndex();
		enemyInfo.Type = m_Monster[i].GetType();
		enemyInfo.alive = m_Monster[i].GetAlive();
		enemyInfo.Hp = m_Monster[i].GetHp();
		send(clientinfotohandle[1].Sock, (char*)&enemyInfo, sizeof(enemyInfo), 0);
		send(clientinfotohandle[0].Sock, (char*)&enemyInfo, sizeof(enemyInfo), 0);


		Ebnum = m_Monster[i].m_EnemyBullet.size();
		send(clientinfotohandle[1].Sock, (char*)&Ebnum, sizeof(Ebnum), 0);
		send(clientinfotohandle[0].Sock, (char*)&Ebnum, sizeof(Ebnum), 0);
		if (Ebnum != 0) {
			for (int j = 0; j < Ebnum; ++j)
			{
				if (m_Monster[i].alive == true) {
					enemybulletInfo[ClientNum].Pos = m_Monster[i].m_EnemyBullet[j].GetPos();
					enemybulletInfo[ClientNum].Active = m_Monster[i].m_EnemyBullet[j].GetAlive();
					send(clientinfotohandle[1].Sock, (char*)&enemybulletInfo[ClientNum], sizeof(enemybulletInfo[ClientNum]), 0);
					send(clientinfotohandle[0].Sock, (char*)&enemybulletInfo[ClientNum], sizeof(enemybulletInfo[ClientNum]), 0);
				}
			}
		}
	}
}
void Server::ItemUpdate(int Inum) {
	Inum = m_Item.size();
	send(clientinfotohandle[0].Sock, (char*)&Inum, sizeof(Inum), 0);
	send(clientinfotohandle[1].Sock, (char*)&Inum, sizeof(Inum), 0);
	CheckItembyPlayerCollision(m_Item, playerInfo[0]);
	CheckItembyPlayerCollision(m_Item, playerInfo[1]);



	for (int i = 0; i < Inum; ++i)
	{
		m_Item[i].Update();
		itemInfo.Index = m_Item[i].MyIndex;
		itemInfo.pos = m_Item[i].GetPos();
		itemInfo.Type = m_Item[i].GetType();
		itemInfo.alive = m_Item[i].alive;
		send(clientinfotohandle[0].Sock, (char*)&itemInfo, sizeof(itemInfo), 0);
		send(clientinfotohandle[1].Sock, (char*)&itemInfo, sizeof(itemInfo), 0);
	}
}
void Server::ChackAndUpdate(int Bnum) {
	for (int f = 0; f < 2; ++f)
	{
		Bnum = playerBullet[f].size();
		send(clientinfotohandle[0].Sock, (char*)&Bnum, sizeof(Bnum), 0);//총알 크기 미리 알려줌
		send(clientinfotohandle[1].Sock, (char*)&Bnum, sizeof(Bnum), 0);//총알 크기 미리 알려줌

		if (playerBullet[f].size() > 0) {
			if (m_Monster.size() > 0) {
				CheckEnemybyPlayerBulletCollision(playerBullet[f], m_Monster);

			}
			for (vector<CBullet>::iterator bulletIter = playerBullet[f].begin(); bulletIter < playerBullet[f].end(); ++bulletIter)
			{
				bulletInfo.Active = bulletIter->GetAlive();
				bulletInfo.Pos = bulletIter->GetPos();
				send(clientinfotohandle[0].Sock, (char*)&bulletInfo, sizeof(bulletInfo), 0);
				send(clientinfotohandle[1].Sock, (char*)&bulletInfo, sizeof(bulletInfo), 0);
			}

			int Msize = m_Monster.size();
			send(clientinfotohandle[0].Sock, (char*)&Msize, sizeof(Msize), 0);//몬스터크기가 너무 커서 미리 사이즈 알려줌
			send(clientinfotohandle[1].Sock, (char*)&Msize, sizeof(Msize), 0);//몬스터크기가 너무 커서 미리 사이즈 알려줌

			for (vector<CMonster>::iterator enemy = m_Monster.begin(); enemy <m_Monster.end(); ++enemy)
			{
				enemyInfo.alive = enemy->GetAlive();
				enemyInfo.pos = enemy->GetPos();
				enemyInfo.Index = (*enemy).GetIndex();
				send(clientinfotohandle[0].Sock, (char*)&enemyInfo, sizeof(enemyInfo), 0);
				send(clientinfotohandle[1].Sock, (char*)&enemyInfo, sizeof(enemyInfo), 0);
			}

		}
	}
}
void Server::EnemyBulletChack() {
	for (vector<CMonster>::iterator enemy = m_Monster.begin(); enemy < m_Monster.end(); ++enemy)
	{
		CheckPlayerbyEnemyBulletCollision(enemy->m_EnemyBullet, playerInfo[0]);
		CheckPlayerbyEnemyBulletCollision(enemy->m_EnemyBullet, playerInfo[1]);

		//적총알 삭제
		if (enemy->alive)
		{
			for (int i = 0; i < enemy->m_EnemyBullet.size(); ++i)
			{
				if (enemy->m_EnemyBullet[i].GetYPos() > WndY)
				{
					enemy->m_EnemyBullet[i].alive = false;
					swap(enemy->m_EnemyBullet[i], enemy->m_EnemyBullet.back());
					enemy->m_EnemyBullet.pop_back();
				}
			}
		}
	}
}

void Server::PlayerBulletUpdate() {
	for (int f = 0; f < 2; ++f)
	{
		for (int p = 0; p < playerBullet[f].size(); ++p)
		{
			if (playerBullet[f][p].GetAlive())
			{
				playerBullet[f][p].SetYPos(playerBullet[f][p].GetYPos() - 13);
				//printf("%d", p.GetYPos());

				//화면 나갈 시 삭제
				if (playerBullet[f][p].GetYPos() < 0 && playerBullet[f][p].GetAlive())
				{
					playerBullet[f][p].alive = false;
					swap(playerBullet[f][p], playerBullet[f].back());
					playerBullet[f].pop_back();
				}
			}
		}
	}
}
void Server::RankScene(int SendCount, int ClientNum) {
	if (SendCount == 0)
	{
		if (ClientNum == 0)
		{
			ofstream out("Score.txt");
			Score temp;
			temp.first = score;
			strcat(Sum, NICKNAME[0]);
			strcat(Sum, ",");
			strcat(Sum, NICKNAME[1]);

			temp.second = Sum;

			SetRank(out, Rank, temp);

			int Rnum = Rank.size();
			send(clientinfotohandle[1].Sock, (char*)&temp.first, sizeof(temp.first), 0);
			send(clientinfotohandle[1].Sock, (char*)&Rnum, sizeof(Rnum), 0);


			send(clientinfotohandle[0].Sock, (char*)&temp.first, sizeof(temp.first), 0);
			send(clientinfotohandle[0].Sock, (char*)&Rnum, sizeof(Rnum), 0);

			for (vector<Score>::iterator iter = Rank.begin(); iter != Rank.end(); ++iter)
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
}


DWORD WINAPI ProcessClient(LPVOID arg) {
	SOCKET ClientSock = (SOCKET)arg;
	SOCKADDR ClientAddr;
	int AddrLen;
	AddrLen = sizeof(ClientAddr);
	getpeername(ClientSock, (SOCKADDR*)&ClientAddr, &AddrLen);
	//================================================================

	int SendCount = 0;
	int Ebnum=0;

	int retval = 0;

	int ClientNum = ClientCount - 1;
	clientinfotohandle[ClientNum].PlayNum = ClientNum;
	server.SetInitData(server.playerInfo[ClientNum], ClientNum);

	bool isClientnumSend = false;

	int Scene;

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
		int idx = 0; int Bnum=0; int num=0; int Mnum=0; int Inum=0;

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
			retval = recvn(ClientSock, (char*)&server.Input.m_KeyInput, sizeof(server.Input.m_KeyInput), 0); 
			if (retval == SOCKET_ERROR) {
				err_display("recv() KeyInput");
				return 0;
				break;
			}
			EnterCriticalSection(&server.cs);
			server.KeyInputFunc(ClientNum);
			LeaveCriticalSection(&server.cs);

	
			if (ClientNum == 0)
			{
				server.SendAllPlayerInfo(server.playerInfo);//플레이어 정보

				//스킬 정보
				server.SkillUpdate();
				//적
				server.MakeEnemy();
				server.EnemyUpdate(Mnum, Ebnum, ClientNum);

				//아이템
				server.MakeItem(); 
				server.ItemUpdate(Inum);

				//충돌체크 및 업데이트
				server.ChackAndUpdate(Bnum);

				//적총알 체크
				server.EnemyBulletChack();

				//플레이어 총알 이동
				server.PlayerBulletUpdate();
					
				
			//씬넘김
			Scene = E_INGAME;
			if (server.playerInfo[0].Hp < 1 && server.playerInfo[1].Hp < 1)
			{
				Scene = E_GAMEOVER;
				clientinfotohandle[0].IsScene = E_Scene::E_GAMEOVER;
				clientinfotohandle[1].IsScene = E_Scene::E_GAMEOVER;
			}
			send(clientinfotohandle[1].Sock, (char*)&Scene, sizeof(Scene), 0);
			send(clientinfotohandle[0].Sock, (char*)&Scene, sizeof(Scene), 0);

			}
			recv(ClientSock, (char*)NICKNAME[ClientNum], sizeof(NICKNAME[ClientNum]), 0);
			break;
		case E_Scene::E_GAMEOVER:
			server.RankScene(SendCount,ClientNum);
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