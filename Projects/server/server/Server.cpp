#include "stdafx.h"
#include "server.h"

void err_quit(char *msg);
void err_display(char *msg);
int recvn(SOCKET s, char *buf, int len, int flags);
//=============================================================

ClientInfoToHandle clientinfotohandle[2];
int ClientCount = 0; //클라이언트 번호 할당
Server server;
typedef pair<int, string> Score;
vector<Score> Rank;

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
	a.Hp = 5;
	a.BulletCount = 1;
	a.Shield = 0;
	a.SubWeapon = 1;
	a.Power = 1;
	a.Score = 0;
}

void Server::SendAllPlayerInfo(SOCKET sock, PlayerInfo P[])
{
	send(sock, (char*)&P[0], sizeof(P[0]), 0);//플레이어 정보 전송
	send(sock, (char*)&P[1], sizeof(P[1]), 0);//플레이어 정보 전송
}
void Server::sendAllIngamePack(SOCKET sock) //인게임 아이템과 총알
{
	//send(sock, (char*)&I_power, sizeof(I_power), 0);
	//send(sock, (char*)&I_skill, sizeof(I_skill), 0);
	//send(sock, (char*)&I_bullet, sizeof(I_bullet), 0);
	//send(sock, (char*)&I_sub, sizeof(I_sub), 0);
	//send(sock, (char*)&I_sheild, sizeof(I_sheild), 0);

}
void Server::MakeItem(SOCKET sock, int Cnum)
{
	
	
	int iteamNumber = 0;
	float NowTime = (float)timeGetTime() * 0.001f;
	static int inum1 = 0;
	static int inum2 = 0;
	static int inum3 = 0;
	static int inum4 = 0;
	static int inum5 = 0;
	if (NowTime - ItemTime1 >= 10.0f)
	{
		if (inum1 < 10)
		{
			server.itemInfo[Cnum].Index = inum1;
			inum1++;
			server.itemInfo[Cnum].IsDraw = true;
			server.itemInfo[Cnum].Type = E_IPOWER;
			m_Item.push_back(CItem(server.itemInfo[Cnum]));
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
			server.itemInfo[Cnum].Index = inum2;
			inum2++;
			server.itemInfo[Cnum].IsDraw = true;
			server.itemInfo[Cnum].Type = E_ISKILL;
			m_Item.push_back(  CItem(server.itemInfo[Cnum]));
			//I_skill.push_back( I_SKILL());
			EnterCriticalSection(&cs);
			ItemTime2 = NowTime;
			LeaveCriticalSection(&cs);
		}

		//printf("스킬 생성");

	}
	if (NowTime - ItemTime3 >=30.0f)
	{
		if (inum3 < 10)
		{
			server.itemInfo[Cnum].Index = inum3;
			inum3++;
			server.itemInfo[Cnum].IsDraw = true;
			server.itemInfo[Cnum].Type = E_IBULLET;
			m_Item.push_back( CItem(server.itemInfo[Cnum]));
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
			server.itemInfo[Cnum].Index = inum4;
			inum4++;
			server.itemInfo[Cnum].IsDraw = true;
			server.itemInfo[Cnum].Type = E_ISUB;
			m_Item.push_back( CItem(server.itemInfo[Cnum]));
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
			server.itemInfo[Cnum].IsDraw = true;
			server.itemInfo[Cnum].Type = E_ISHIELD;
			m_Item.push_back( CItem(server.itemInfo[Cnum]));
			//I_sheild.push_back( I_SHEILD());
			
			EnterCriticalSection(&cs);
			ItemTime5 = NowTime;
			LeaveCriticalSection(&cs);
		}
	}
	int num = m_Item.size();
	send(sock, (char*)&num, sizeof(num), 0);

		for (int i = 0; i < num; ++i)
		{

			m_Item[i].Update();
			server.itemInfo[Cnum].Index = m_Item[i].MyIndex;
			server.itemInfo[Cnum].pos = m_Item[i].GetPos();
			server.itemInfo[Cnum].Type = m_Item[i].GetType();
			server.itemInfo[Cnum].IsDraw = m_Item[i].IsDraw;
			send(sock, (char*)&server.itemInfo[Cnum], sizeof(server.itemInfo[Cnum]), 0);
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

						//1. 여기 안들어오는거 같은데 왜 죽지?
					}

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
			m_Monster.push_back( CMonster(server.enemyInfo[Cnum]));
			//printf("1번 생성\n");
			EnterCriticalSection(&cs);
			enemyTime1 = NowTime;
			LeaveCriticalSection(&cs);
		}
		if (NowTime - enemyTime2 >= 5.0f)
		{
			server.enemyInfo[Cnum].Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo[Cnum].alive = true;
			server.enemyInfo[Cnum].Type = E_ENEMY2;
			m_Monster.push_back( CMonster(server.enemyInfo[Cnum]));
			//printf("2번 생성\n");
			EnterCriticalSection(&cs);
			enemyTime2 = NowTime;
			LeaveCriticalSection(&cs);
		}

		if (NowTime - enemyTime3 >= 10.0f)
		{
			server.enemyInfo[Cnum].Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo[Cnum].alive = true;
			server.enemyInfo[Cnum].Type = E_ENEMY3;
			m_Monster.push_back( CMonster(server.enemyInfo[Cnum]));
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
			server.enemyInfo[Cnum].Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo[Cnum].alive = true;
			server.enemyInfo[Cnum].Type = E_BOSS1;
			m_Monster.push_back( CMonster(server.enemyInfo[Cnum]));
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
			server.enemyInfo[Cnum].Index = MonsterNumber;
			MonsterNumber++;
			server.enemyInfo[Cnum].alive = true;
			server.enemyInfo[Cnum].Type = E_BOSS2;
			m_Monster.push_back( CMonster(server.enemyInfo[Cnum]));
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

	int num = m_Monster.size();
	send(sock, (char*)&num, sizeof(num), 0);
	for (int i = 0; i < m_Monster.size(); ++i)
	{
		EnterCriticalSection(&cs);
		m_Monster[i].Update();
		LeaveCriticalSection(&cs);
		
		server.enemyInfo[Cnum].pos = m_Monster[i].GetPos();
		server.enemyInfo[Cnum].Index = m_Monster[i].GetIndex();
		server.enemyInfo[Cnum].Type = m_Monster[i].GetType();
		server.enemyInfo[Cnum].alive = m_Monster[i].GetAlive();
		server.enemyInfo[Cnum].Hp = m_Monster[i].GetHp();
		send(sock, (char*)&server.enemyInfo[Cnum], sizeof(server.enemyInfo[Cnum]), 0);
	}
}



DWORD WINAPI ProcessClient(LPVOID arg) {
	SOCKET ClientSock = (SOCKET)arg;
	SOCKADDR ClientAddr;
	int AddrLen;
	AddrLen = sizeof(ClientAddr);
	getpeername(ClientSock, (SOCKADDR*)&ClientAddr, &AddrLen);
	//================================================================



	int retval = 0;

	int ClientNum = ClientCount - 1;
	clientinfotohandle[ClientNum].PlayNum = ClientNum;
	server.SetInitData(server.playerInfo[ClientNum], ClientNum);


	bool isClientnumSend = false;

	//시간설정
	server.enemyTime1 = server.enemyTime2 = server.enemyTime3 = server.enemyTime4 = server.enemyTime5 = (float)timeGetTime() * 0.001f;
	server.ItemTime1 = server.ItemTime2 = server.ItemTime3 = server.ItemTime4 = server.ItemTime5 = (float)timeGetTime() * 0.001f;

	server.m_pTime.m_CurrentTime = timeGetTime();
	server.m_pTime.m_eTime = server.m_pTime.m_CurrentTime - server.m_pTime.m_PrevTime;
	server.m_pTime.m_eActine += server.m_pTime.m_eTime;
	if (server.m_pTime.m_eActine > 1 / FPS_PERSECOND)
	{

	while (true)
	{
		server.m_pTime.m_eTime = 0.0f;

		int Snum = clientinfotohandle[ClientNum].IsScene;
		int idx = 0;
		int Bnum;

		switch (Snum) {
		case E_Scene::E_MENU: //메뉴화면일때
			printf("메뉴씬입니다!\n");

			retval = recvn(ClientSock, (char*)&server.playerInfo[ClientNum].IsReady, sizeof(server.playerInfo[ClientNum].IsReady), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv() IsReady");
				break;
			}

			if (server.IsAllClientReady() == true) {
				//clientinfotohandle[ClientNum].IsScene = E_Scene::E_GAMEOVER; 
				clientinfotohandle[ClientNum].IsScene = E_Scene::E_INGAME; //게임플레이로 씬전환
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
				server.playerBullet[ClientNum].emplace_back( CBullet(server.playerInfo[ClientNum].Pos, 0));
				//printf("%d번클라 스페이스바!\n",ClientNum);
			}

			server.playerInfo[ClientNum].Space = server.Input.m_KeyInput.Space;
			server.SendAllPlayerInfo(ClientSock, server.playerInfo);//플레이어
			server.MakeEnemy(ClientSock, ClientNum); //적
			server.MakeItem(ClientSock, ClientNum); //아이템

			//충돌체크 및 업데이트
			Bnum = server.playerBullet[ClientNum].size();
			send(ClientSock, (char*)&Bnum, sizeof(Bnum), 0);//총알 크기 미리 알려줌
			if (server.playerBullet[ClientNum].size() > 0) {
				if (server.m_Monster.size() > 0)
					server.CheckEnemybyPlayerBulletCollision(ClientSock, server.playerBullet[ClientNum], server.m_Monster);

				for (vector<CBullet>::iterator bulletIter = server.playerBullet[ClientNum].begin(); bulletIter < server.playerBullet[ClientNum].end(); ++bulletIter)
				{
					server.bulletInfo[ClientNum].Active = bulletIter->GetActive();
					server.bulletInfo[ClientNum].Pos = bulletIter->GetPos();
					send(ClientSock, (char*)&server.bulletInfo[ClientNum], sizeof(server.bulletInfo[ClientNum]), 0);
				}
				
				int Msize = server.m_Monster.size();
				send(ClientSock, (char*)&Msize, sizeof(Msize), 0);//몬스터크기가 너무 커서 미리 사이즈 알려줌
				
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
				Bnum = server.playerBullet[1].size();
				send(ClientSock, (char*)&Bnum, sizeof(Bnum), 0);//총알 크기 미리 알려줌
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
			}
			else
			{
				Bnum = server.playerBullet[0].size();
				send(ClientSock, (char*)&Bnum, sizeof(Bnum), 0);//총알 크기 미리 알려줌
				if (Bnum > 0) {
					for (int i = 0; i < Bnum; ++i)
					{
						server.bulletInfo[0].Active = server.playerBullet[0][i].GetActive();
						server.bulletInfo[0].Pos = server.playerBullet[0][i].GetPos();
						send(ClientSock, (char*)&server.bulletInfo[0], sizeof(server.bulletInfo[0]), 0);
					}
				}
					//for (vector<CBullet*>::iterator bulletIter = server.playerBullet[0].begin(); bulletIter != server.playerBullet[0].end(); ++bulletIter)
					//{
					//	server.bulletInfo[0].Active = bulletIter.GetActive();
					//	server.bulletInfo[0].Pos = bulletIter.GetPos();
					//	send(ClientSock, (char*)&server.bulletInfo[0], sizeof(server.bulletInfo[0]), 0);
					//}
			}
			
			//플레이어 총알
			//이동
			for (auto p = server.playerBullet[ClientNum].begin(); p < server.playerBullet[ClientNum].end(); ++p)
			{
				if ((*p).GetActive())
				{
					(*p).SetYPos((*p).GetYPos() - 13);
					//printf("%d", (*p).GetYPos());
				}
			}

			//화면 나갈 시 삭제
			for (int i = 0; i < server.playerBullet[ClientNum].size(); ++i)
			{
				if (server.playerBullet[ClientNum][i].GetYPos() > WndY)
				{
					server.playerBullet[ClientNum][i].SetActive(false);
					swap(server.playerBullet[ClientNum][i], server.playerBullet[ClientNum].back());
					server.playerBullet[ClientNum].pop_back();
				}
			}
			break;

			for (int i = 0; i < server.m_Monster.size(); ++i)
			{
				if (server.m_Monster[i].GetYPos() < 0)
				{
					
					server.m_Monster[i].SetAlive(false);
					swap(server.m_Monster[i], server.m_Monster.back());
					server.m_Monster.pop_back();
					
				}
			}
			//인게임 아이템
		   //send(ClientSock, (char*)&playerInfo[ClientNum].m_PlayerBullet, sizeof(playerInfo[ClientNum].m_PlayerBullet), 0);
		   //게임 종료
		case E_Scene::E_GAMEOVER:
			//EnterCriticalSection(&cs);
			//for (vector<Score>::iterator iter = Rank.begin(); iter != Rank.end(); ++iter)
			//   cout << iter.second << " " << iter.first << endl;
			//LeaveCriticalSection(&cs);
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

	Rank.reserve(100);
	ifstream in("score.txt");
	if (!in.is_open())
		err_quit("Can't File Open");
	ReadInputFile(in, Rank);

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
	sort(Rank.begin(), Rank.end(), SortFunc);
	ofstream out("Score.txt");
	for (vector<Score>::iterator iter = Rank.begin(); iter != Rank.end(); ++iter)
	{
		out << iter->first << " " << iter->second << endl;
	}
	out.close();


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