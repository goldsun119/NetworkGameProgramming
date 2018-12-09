#include "stdafx.h"
#include "server.h"

void err_quit(char *msg);
void err_display(char *msg);
int recvn(SOCKET s, char *buf, int len, int flags);
//=============================================================

ClientInfoToHandle clientinfotohandle[2];
int ClientCount = 0; //Ŭ���̾�Ʈ ��ȣ �Ҵ�
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
	if (playerInfo[0].IsReady == true && playerInfo[1].IsReady == true) { //11.12 ���� ��ģ��
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
	//�ʱⰪ ���� �Լ��� ������!
	a.Pos = { (num * 200) + 100, 500 };
	a.Hp = 3;
	a.BulletCount = 1;
	a.Shield = 0;
	a.SubWeapon = 1;
	a.Power = 1;
	a.Score = 0;
	a.skill = false;
}

void Server::SendAllPlayerInfo(SOCKET sock, PlayerInfo P[])
{
	
	send(sock, (char*)&P[0], sizeof(P[0]), 0);//�÷��̾� ���� ����
	send(sock, (char*)&P[1], sizeof(P[1]), 0);//�÷��̾� ���� ����
}
void Server::CheckItembyPlayerCollision(SOCKET sock, vector<CItem>& item, PlayerInfo& player)
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
						//printf("����");

					//p = item.erasep;
					break;
				}

			}
		}

	}

}

void Server::MakeItem(SOCKET sock, int Cnum)
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
				server.itemInfo[Cnum].Index = inum1;
				inum1++;
				server.itemInfo[Cnum].alive = true;
				server.itemInfo[Cnum].Type = E_IPOWER;
				EnterCriticalSection(&cs);
				server.m_Item.push_back(CItem(server.itemInfo[Cnum]));
				LeaveCriticalSection(&cs);
				//I_power.push_back( I_POWER());
				EnterCriticalSection(&cs);
				ItemTime1 = NowTime;
				LeaveCriticalSection(&cs);
			}
			//printf("�Ŀ� ����");
		}
		if (NowTime - ItemTime2 >= 20.0f)
		{
			if (inum2 < 10)
			{
				server.itemInfo[Cnum].Index = inum2;
				inum2++;
				server.itemInfo[Cnum].alive = true;
				server.itemInfo[Cnum].Type = E_ISKILL;
				EnterCriticalSection(&cs);
				server.m_Item.push_back(CItem(server.itemInfo[Cnum]));
				LeaveCriticalSection(&cs);
				//I_skill.push_back( I_SKILL());
				EnterCriticalSection(&cs);
				ItemTime2 = NowTime;
				LeaveCriticalSection(&cs);
			}

			//printf("��ų ����");

		}
		if (NowTime - ItemTime3 >= 30.0f)
		{
			if (inum3 < 10)
			{
				server.itemInfo[Cnum].Index = inum3;
				inum3++;
				server.itemInfo[Cnum].alive = true;
				server.itemInfo[Cnum].Type = E_IBULLET;
				EnterCriticalSection(&cs);
				server.m_Item.push_back(CItem(server.itemInfo[Cnum]));
				LeaveCriticalSection(&cs);
				//I_bullet.push_back( I_BULLET());
				EnterCriticalSection(&cs);
				ItemTime3 = NowTime;
				LeaveCriticalSection(&cs);
			}
			//printf("�����Ѿ� ����");

		}
		if (NowTime - ItemTime4 >= 40.0f)
		{
			if (inum4 < 10)
			{
				server.itemInfo[Cnum].Index = inum4;
				inum4++;
				server.itemInfo[Cnum].alive = true;
				server.itemInfo[Cnum].Type = E_ISUB;
				EnterCriticalSection(&cs);
				server.m_Item.push_back(CItem(server.itemInfo[Cnum]));
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
				server.itemInfo[Cnum].Index = inum5;
				inum5++;
				server.itemInfo[Cnum].alive = true;
				server.itemInfo[Cnum].Type = E_ISHIELD;
				EnterCriticalSection(&cs);
				server.m_Item.push_back(CItem(server.itemInfo[Cnum]));
				LeaveCriticalSection(&cs);
				//I_sheild.push_back( I_SHEILD());

				EnterCriticalSection(&cs);
				ItemTime5 = NowTime;
				LeaveCriticalSection(&cs);
			}
		}
	}
}
void Server::CheckEnemybyPlayerBulletCollision(SOCKET sock, vector<CBullet> &Bullet, vector<CMonster> &Target)
{
	for (vector<CBullet>::iterator bulletIter = Bullet.begin(); bulletIter < Bullet.end(); ++bulletIter)
	{
		for (vector<CMonster>::iterator enemy = Target.begin(); enemy < Target.end(); ++enemy)
		{
			if (bulletIter->m_IsActive == true && enemy->GetAlive() == true) {

				if (bulletIter->IsCrashtoEnemy(*enemy))
				{
					if (enemy->GetAlive() == true)
						bulletIter->m_IsActive = false;
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
		
		if (p->m_IsActive == true)
		{
			if (p->IsShootPlayer(player))
			{
				switch (p->getType())
				{
				case 0:
				case -1:
				case -2:
					p->m_IsActive = false;
					player.Hp -= 1;
					
					
					break;
				case 1:
					p->m_IsActive = false;
					player.Hp -= 1;
		
					break;
				case 2:
					p->m_IsActive = false;
					player.Hp -= 1;

					break;
				case 3:
					p->m_IsActive = false;
					player.Hp -= 1;

					break;
				case 4:
					p->m_IsActive = false;
					player.Hp -= 1;

					break;
				}

			}
		}

	}
}

void Server::MakeEnemy(SOCKET sock, int Cnum)
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
			server.enemyInfo[Cnum].Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo[Cnum].alive = true;
			server.enemyInfo[Cnum].Type = E_ENEMY1;
			EnterCriticalSection(&cs);
			m_Monster.push_back( CMonster(server.enemyInfo[Cnum]));
			LeaveCriticalSection(&cs);
			//printf("1�� ����\n");
			EnterCriticalSection(&cs);
			enemyTime1 = NowTime;
			LeaveCriticalSection(&cs);
		}
		//if (NowTime - enemyTime2 >= 5.0f)
		//{
		//	server.enemyInfo[Cnum].Index = MonsterNumber;
		//	MonsterNumber++;
		//	server.enemyInfo[Cnum].alive = true;
		//	server.enemyInfo[Cnum].Type = E_ENEMY2;
		//	EnterCriticalSection(&cs);
		//	m_Monster.push_back( CMonster(server.enemyInfo[Cnum]));
		//	LeaveCriticalSection(&cs);
		//	//printf("2�� ����\n");
		//	EnterCriticalSection(&cs);
		//	enemyTime2 = NowTime;
		//	LeaveCriticalSection(&cs);
		//}

	//	if (NowTime - enemyTime3 >= 10.0f)
	//	{
	//		server.enemyInfo[Cnum].Index = MonsterNumber;
	//		MonsterNumber++;
	//		server.enemyInfo[Cnum].alive = true;
	//		server.enemyInfo[Cnum].Type = E_ENEMY3;
	//		EnterCriticalSection(&cs);
	//		m_Monster.push_back( CMonster(server.enemyInfo[Cnum]));
	//		LeaveCriticalSection(&cs);
	//		//   printf("3�� ����\n");
	//		EnterCriticalSection(&cs);
	//		enemyTime3 = NowTime;
	//		LeaveCriticalSection(&cs);
	//	}
	//}

	//if (NowTime - enemyTime4 >= 50.0f)
	//{
	//	if (m_pMonster.Boss1_Appear == false)
	//	{
	//		server.enemyInfo[Cnum].Index = MonsterNumber;
	//		MonsterNumber++;
	//		server.enemyInfo[Cnum].alive = true;
	//		server.enemyInfo[Cnum].Type = E_BOSS1;
	//		EnterCriticalSection(&cs);
	//		m_Monster.push_back( CMonster(server.enemyInfo[Cnum]));
	//		LeaveCriticalSection(&cs);
	//		//printf("����1 ����\n");

	//		m_pMonster.Boss1_Appear = true;
	//		EnterCriticalSection(&cs);
	//		enemyTime4 = NowTime;
	//		LeaveCriticalSection(&cs);
	//	}
	//}

	//if (NowTime - enemyTime5 >= 80.0f)
	//{
	//	if (m_pMonster.Boss2_Appear == false)
	//	{
	//		server.enemyInfo[Cnum].Index = MonsterNumber;
	//		MonsterNumber++;
	//		server.enemyInfo[Cnum].alive = true;
	//		server.enemyInfo[Cnum].Type = E_BOSS2;
	//		EnterCriticalSection(&cs);
	//		m_Monster.push_back( CMonster(server.enemyInfo[Cnum]));
	//		LeaveCriticalSection(&cs);
	//		//printf("����2 ����\n");

	//		m_pMonster.Boss2_Appear = true;
	//		EnterCriticalSection(&cs);
	//		enemyTime5 = NowTime;
	//		LeaveCriticalSection(&cs);
	//	}
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

	//�ð�����

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
		case E_Scene::E_MENU: //�޴�ȭ���϶�
			printf("�޴����Դϴ�!\n");

			retval = recvn(ClientSock, (char*)&server.playerInfo[ClientNum].IsReady, sizeof(server.playerInfo[ClientNum].IsReady), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv() IsReady");
				break;
			}

			if (server.IsAllClientReady() == true) {
				clientinfotohandle[ClientNum].IsScene = E_Scene::E_INGAME; 
				//clientinfotohandle[ClientNum].IsScene = E_Scene::E_INGAME; //�����÷��̷� ����ȯ
				retval = send(ClientSock, (char*)&clientinfotohandle[ClientNum].IsScene, sizeof(clientinfotohandle[ClientNum].IsScene), 0);//����ȯ ����
				send(ClientSock, (char*)&clientinfotohandle[ClientNum].PlayNum, sizeof(clientinfotohandle[ClientNum].PlayNum), 0);
			}
			else {
				//�غ� �ƴҶ��� �޴����� �Ѱ������
				retval = send(ClientSock, (char*)&clientinfotohandle[ClientNum].IsScene, sizeof(clientinfotohandle[ClientNum].IsScene), 0);
				if (retval == SOCKET_ERROR) {
					err_display("send() Scene");
					break;
				}
				printf("���� ��!\n");
			}
			break;

			//���� �� �϶�
		case E_Scene::E_INGAME:
			//printf("�ΰ��Ӿ��Դϴ�\n");
			//g_IngameStartTime = GetTickCount();


			retval = recvn(ClientSock, (char*)&server.Input.m_KeyInput, sizeof(server.Input.m_KeyInput), 0);   //Ű �Է°� ���� ������ ����� ã��~
			if (retval == SOCKET_ERROR) {
				err_display("recv() KeyInput");
				return 0;
				break;
			}

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
					//printf("%d��Ŭ�� �����̽���!\n",ClientNum);
					server.BulletTime = NowTime;
				}
			}
			if (server.Input.m_KeyInput.Skill)
			{
				server.playerInfo[ClientNum].skill = true;
			
			}
		
			//server.playerInfo[ClientNum].skill = server.Input.m_KeyInput.Skill;
			//���� �÷��̾� ���� ���� Ȯ�� �� ����
			server.SendAllPlayerInfo(ClientSock, server.playerInfo);//�÷��̾�
			recv(ClientSock, (char*)&server.skillPlaying, sizeof(server.skillPlaying), 0);

			if (server.skillPlaying == true) {
				server.SkillCollision(server.m_Monster);

				int Msize = server.m_Monster.size();
				send(ClientSock, (char*)&Msize, sizeof(Msize), 0);//����ũ�Ⱑ �ʹ� Ŀ�� �̸� ������ �˷���
				for (vector<CMonster>::iterator enemy = server.m_Monster.begin(); enemy < server.m_Monster.end(); ++enemy)
				{

					EnterCriticalSection(&server.cs);
					server.enemyInfo[ClientNum].alive = enemy->GetAlive();
					server.enemyInfo[ClientNum].Hp = enemy->GetHp();
					send(ClientSock, (char*)&server.enemyInfo[ClientNum], sizeof(server.enemyInfo[ClientNum]), 0);
					LeaveCriticalSection(&server.cs);
				
				}
				
			}

			//if (ClientNum == 0)
				server.MakeEnemy(ClientSock, ClientNum); //��
			Mnum = server.m_Monster.size();
			send(ClientSock, (char*)&Mnum, sizeof(Mnum), 0);
			for (int i = 0; i <Mnum; ++i)
			{
				EnterCriticalSection(&server.cs);
				server.m_Monster[i].Update();
				LeaveCriticalSection(&server.cs);

				EnterCriticalSection(&server.cs);
				server.enemyInfo[ClientNum].pos = server.m_Monster[i].GetPos();
				server.enemyInfo[ClientNum].Index = server.m_Monster[i].GetIndex();
				server.enemyInfo[ClientNum].Type = server.m_Monster[i].GetType();
				server.enemyInfo[ClientNum].alive = server.m_Monster[i].GetAlive();
				server.enemyInfo[ClientNum].Hp = server.m_Monster[i].GetHp();
				send(ClientSock, (char*)&server.enemyInfo[ClientNum], sizeof(server.enemyInfo[ClientNum]), 0);
				LeaveCriticalSection(&server.cs);
				

					EnterCriticalSection(&server.cs);
					Ebnum = server.m_Monster[i].m_EnemyBullet.size();
					send(ClientSock, (char*)&Ebnum, sizeof(Ebnum), 0);
					LeaveCriticalSection(&server.cs);
					if (Ebnum != 0) {
						for (int j = 0; j < Ebnum; ++j)
						{
							EnterCriticalSection(&server.cs);
							server.enemybulletInfo[ClientNum].Pos = server.m_Monster[i].m_EnemyBullet[j].GetPos();
							server.enemybulletInfo[ClientNum].Active = server.m_Monster[i].m_EnemyBullet[j].m_IsActive;
							send(ClientSock, (char*)&server.enemybulletInfo[ClientNum], sizeof(server.enemybulletInfo[ClientNum]), 0);
							LeaveCriticalSection(&server.cs);
						}
					}
			}
			//if(ClientNum==0)
				server.MakeItem(ClientSock, ClientNum); //������
			Inum = server.m_Item.size();
			send(ClientSock, (char*)&Inum, sizeof(Inum), 0);
			server.CheckItembyPlayerCollision(ClientSock, server.m_Item, server.playerInfo[ClientNum]);



			for (int i = 0; i < Inum; ++i)
			{

				EnterCriticalSection(&server.cs);
				server.m_Item[i].Update();
				server.itemInfo[ClientNum].Index = server.m_Item[i].MyIndex;
				server.itemInfo[ClientNum].pos = server.m_Item[i].GetPos();
				server.itemInfo[ClientNum].Type = server.m_Item[i].GetType();
				server.itemInfo[ClientNum].alive = server.m_Item[i].alive;
				send(ClientSock, (char*)&server.itemInfo[ClientNum], sizeof(server.itemInfo[ClientNum]), 0);
				LeaveCriticalSection(&server.cs);
			}

			//�浹üũ �� ������Ʈ
			EnterCriticalSection(&server.cs);
			Bnum = server.playerBullet[ClientNum].size();
			send(ClientSock, (char*)&Bnum, sizeof(Bnum), 0);//�Ѿ� ũ�� �̸� �˷���
			LeaveCriticalSection(&server.cs);
			
			if (server.playerBullet[ClientNum].size() > 0) {
				if (server.m_Monster.size() > 0) {
					server.CheckEnemybyPlayerBulletCollision(ClientSock, server.playerBullet[ClientNum], server.m_Monster);
					
				}
				for (vector<CBullet>::iterator bulletIter = server.playerBullet[ClientNum].begin(); bulletIter < server.playerBullet[ClientNum].end(); ++bulletIter)
				{
					server.bulletInfo[ClientNum].Active = bulletIter->GetActive();
					server.bulletInfo[ClientNum].Pos = bulletIter->GetPos();
					send(ClientSock, (char*)&server.bulletInfo[ClientNum], sizeof(server.bulletInfo[ClientNum]), 0);
				}
				
				int Msize = server.m_Monster.size();
				send(ClientSock, (char*)&Msize, sizeof(Msize), 0);//����ũ�Ⱑ �ʹ� Ŀ�� �̸� ������ �˷���
				
				for (vector<CMonster>::iterator enemy = server.m_Monster.begin(); enemy < server.m_Monster.end(); ++enemy)
				{
					server.enemyInfo[ClientNum].alive = enemy->GetAlive();
					server.enemyInfo[ClientNum].pos = enemy->GetPos();
					server.enemyInfo[ClientNum].Index = (*enemy).GetIndex();
					send(ClientSock, (char*)&server.enemyInfo[ClientNum], sizeof(server.enemyInfo[ClientNum]), 0);
				}
				
			}

			if (ClientNum == 0)
			{
				EnterCriticalSection(&server.cs);
				Bnum = server.playerBullet[1].size();
				send(ClientSock, (char*)&Bnum, sizeof(Bnum), 0);//�Ѿ� ũ�� �̸� �˷���
				if (Bnum > 0) {

					for (int i = 0; i <Bnum; ++i)
					{
						server.bulletInfo[1].Active = server.playerBullet[1][i].GetActive();
						server.bulletInfo[1].Pos = server.playerBullet[1][i].GetPos();
						send(ClientSock, (char*)&server.bulletInfo[1], sizeof(server.bulletInfo[1]), 0);
					}
					//for (vector<CBullet*>::iterator bulletIter = server.playerBullet[1].begin(); bulletIter != server.playerBullet[1].end(); ++bulletIter)
					//{
					//	server.bulletInfo[1].Active = bulletIter.GetActive();
					//	server.bulletInfo[1].Pos = bulletIter.GetPos();
					//	send(ClientSock, (char*)&server.bulletInfo[1], sizeof(server.bulletInfo[1]), 0);
					//}
				}
				LeaveCriticalSection(&server.cs);
			}
			else
			{
				EnterCriticalSection(&server.cs);
				Bnum = server.playerBullet[0].size();
				send(ClientSock, (char*)&Bnum, sizeof(Bnum), 0);//�Ѿ� ũ�� �̸� �˷���
				if (Bnum > 0) {
					for (int i = 0; i < Bnum; ++i)
					{
						server.bulletInfo[0].Active = server.playerBullet[0][i].GetActive();
						server.bulletInfo[0].Pos = server.playerBullet[0][i].GetPos();
						send(ClientSock, (char*)&server.bulletInfo[0], sizeof(server.bulletInfo[0]), 0);
					}
				}
				LeaveCriticalSection(&server.cs);

			}
			//���Ѿ� �浹üũ
			for (vector<CMonster>::iterator enemy = server.m_Monster.begin(); enemy < server.m_Monster.end(); ++enemy)
			{
				server.CheckPlayerbyEnemyBulletCollision(enemy->m_EnemyBullet, server.playerInfo[ClientNum]);
			}
//�÷��̾� �Ѿ�
			//�̵�
			for (auto p = server.playerBullet[ClientNum].begin(); p < server.playerBullet[ClientNum].end(); ++p)
			{
				if ((*p).GetActive())
				{
					(*p).SetYPos((*p).GetYPos() - 13);
					//printf("%d", p.GetYPos());
				}
			}

			//ȭ�� ���� �� ����
			for (int i = 0; i < server.playerBullet[ClientNum].size(); ++i)
			{
					EnterCriticalSection(&server.cs);
				if (server.playerBullet[ClientNum][i].GetYPos() < 0&&server.playerBullet[ClientNum][i].GetActive())
				{
					server.playerBullet[ClientNum][i].alive=false;
					swap(server.playerBullet[ClientNum][i], server.playerBullet[ClientNum].back());
					server.playerBullet[ClientNum].pop_back();
					//server.playerBullet[ClientNum].resize(server.playerBullet[ClientNum].size()-1);
				}
					LeaveCriticalSection(&server.cs);
			}
			break;

			for (int i = 0; i < server.m_Monster.size(); ++i)
			{
				if (server.m_Monster[i].GetYPos() < 0 && server.m_Monster[i].GetAlive())
				{
					
					server.m_Monster[i].SetAlive(false);
					swap(server.m_Monster[i], server.m_Monster.back());
					server.m_Monster.pop_back();
					//server.m_Monster.resize(server.m_Monster.size()-1);

				}
			}
			//�ΰ��� ������
		   //send(ClientSock, (char*)&playerInfo[ClientNum].m_PlayerBullet, sizeof(playerInfo[ClientNum].m_PlayerBullet), 0);
		   //���� ����
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
			//��ũ ���
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

	// ���� �ʱ�ȭ
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
	// ������ ��ſ� ����� ����
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
		// ������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
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

	// ���� ����
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