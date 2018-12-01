#include "stdafx.h"
#include "Enemy.h"
#include "Input.h"
#include "Player.h"
#include "CGameObject.h"
#include "CItem.h"

ClientInfoToHandle clientinfotohandle[2]; //클라이언트 접속관리
PlayerInfo playerInfo[2];
EnemyInfo enemyInfo;
class CGameObject;
int ClientCount = 0; //클라이언트 번호 할당
CMonster* m_pMonster = new CMonster;
CItem* m_pItem = new CItem;
CItem* m_pPower = new I_POWER;

InputManager Input;
DWORD KeyInput;
DWORD g_IngameStartTime;
DWORD g_CurTime;
DWORD g_PrevTime;
DWORD g_ElapsedTime;
#define g_makeEnemy1 200
#define g_makeEnemy2 100
#define g_makeEnemy3 590000000
#define g_makeBoss1 610000000
#define g_makeBoss2 910000000

#define g_makeItem1 39000
#define g_makeBullet 4000
#define g_makePower 5000
#define g_makeSkill 61000
#define g_makeSub 40000

#define g_makeShield 91000

#define MAXOBJECTNUM 10000

vector<CMonster*> m_Monster;
vector<I_BULLET*> I_bullet;
vector<I_SUB*> I_sub;
vector<I_POWER*> I_power;
vector<I_SKILL*> I_skill;
vector<I_SHEILD*> I_sheild;
typedef pair<int, string> Score;

vector<Score> Rank;
CRITICAL_SECTION cs;
int score = 1;

//===========
float enemyTime1;
float enemyTime2;
float enemyTime3;
float enemyTime4;
float enemyTime5;

//=======================================================================================
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
//=============================================================
istream& ReadInputFile(istream& in, vector<Score>& vec)
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

bool IsAllClientReady()
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
void SetInitData(PlayerInfo& a, int num)
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

void SendAllPlayerInfo(SOCKET sock, PlayerInfo P[])
{
	send(sock, (char*)&P[0], sizeof(P[0]), 0);//플레이어 정보 전송
	send(sock, (char*)&P[1], sizeof(P[1]), 0);//플레이어 정보 전송
}
void sendAllIngamePack(SOCKET sock) //인게임 아이템과 총알
{
	send(sock, (char*)&I_power, sizeof(I_power), 0);
	send(sock, (char*)&I_skill, sizeof(I_skill), 0);
	send(sock, (char*)&I_bullet, sizeof(I_bullet), 0);
	send(sock, (char*)&I_sub, sizeof(I_sub), 0);
	send(sock, (char*)&I_sheild, sizeof(I_sheild), 0);
}
void MakeItem(SOCKET sock)
{
	int iteamNumber = 0;
	DWORD ItemTimeCount = GetTickCount();
	ItemTimeCount += 1;
	send(sock, (char*)&ItemTimeCount, sizeof(ItemTimeCount), 0);
	if (ItemTimeCount /= g_makeItem1)
	{
		I_power.push_back(new I_POWER());

		//printf("파워 생성");
	}
	if (ItemTimeCount /= g_makeSkill)
	{
		I_skill.push_back(new I_SKILL());

		//printf("스킬 생성");

	}
	if (ItemTimeCount /= g_makeBullet)
	{
		I_bullet.push_back(new I_BULLET());

		//printf("보조총알 생성");

	}
	if (ItemTimeCount /= g_makeSub)
	{
		I_sub.push_back(new I_SUB());

	}
	if (ItemTimeCount /= g_makeShield)
	{
		I_sheild.push_back(new I_SHEILD());

	}

}
void MakeEnemy(SOCKET sock)
{
	static int MonsterNumber = 0;
	//g_makeEnemy1  = 3;
	//DWORD maketime = GetTickCount();
	float NowTime = (float)timeGetTime() * 0.001f;
	
	//maketime = maketime - time;
	//maketime += 1;
	//m_Monster.push_back(new CMonster(E_ENEMY1));
	//send(sock, (char*)&maketime, sizeof(maketime), 0);
	if (m_pMonster->Boss2_Appear == false) {
		if (NowTime - enemyTime1 >= 3.0f)
		{
			enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			enemyInfo.alive = true;
			enemyInfo.Type = E_ENEMY1;
			m_Monster.push_back(new CMonster(enemyInfo));
			//printf("1번 생성\n");
			enemyTime1 = NowTime;
		}
		if (NowTime - enemyTime2 >= 5.0f)
		{
			enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			enemyInfo.alive = true;
			enemyInfo.Type = E_ENEMY2;
			m_Monster.push_back(new CMonster(enemyInfo));
			//printf("2번 생성\n");
			enemyTime2 = NowTime;
		}

		if (NowTime - enemyTime3 >= 10.0f)
		{
			enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			enemyInfo.alive = true;
			enemyInfo.Type = E_ENEMY3;
			m_Monster.push_back(new CMonster(enemyInfo));
			//   printf("3번 생성\n");
			enemyTime3 = NowTime;
		}
	}

	if (NowTime - enemyTime4 >= 50.0f)
	{
		if (m_pMonster->Boss1_Appear == false)
		{
			enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			enemyInfo.alive = true;
			enemyInfo.Type = E_BOSS1;
			m_Monster.push_back(new CMonster(enemyInfo));
			//printf("보스1 생성\n");

			m_pMonster->Boss1_Appear = true;
			enemyTime4 = NowTime;
		}
	}

	if (NowTime - enemyTime5 >= 80.0f)
	{
		if (m_pMonster->Boss2_Appear == false)
		{
			enemyInfo.Index = MonsterNumber;
			MonsterNumber++;
			enemyInfo.alive = true;
			enemyInfo.Type = E_BOSS2;
			m_Monster.push_back(new CMonster(enemyInfo));
			//printf("보스2 생성\n");

			m_pMonster->Boss2_Appear = true;
			enemyTime5 = NowTime;
		}
	}
	if (MAXOBJECTNUM <= MonsterNumber) {
		return;
	}

	int num = m_Monster.size();
	send(sock, (char*)&num, sizeof(num), 0);
	for (int i = 0; i < m_Monster.size(); ++i)
	{

		m_Monster[i]->Update();
		enemyInfo.pos = m_Monster[i]->GetPos();
		enemyInfo.Index = m_Monster[i]->GetIndex();
		enemyInfo.Type = m_Monster[i]->GetType();
		enemyInfo.alive = m_Monster[i]->GetAlive();
		enemyInfo.Hp = m_Monster[i]->GetHp();
		send(sock, (char*)&enemyInfo, sizeof(enemyInfo), 0);
	}
}



DWORD WINAPI ProcessClient(LPVOID arg) {
	SOCKET ClientSock = (SOCKET)arg;
	SOCKADDR ClientAddr;
	int AddrLen;
	AddrLen = sizeof(ClientAddr);
	getpeername(ClientSock, (SOCKADDR*)&ClientAddr, &AddrLen);

	int retval = 0;

	int ClientNum = ClientCount - 1;
	clientinfotohandle[ClientNum].PlayNum = ClientNum;
	SetInitData(playerInfo[ClientNum], ClientNum);

	//EnterCriticalSection(&cs);
	//Rank.emplace_back(make_pair(score, inet_ntoa(clientinfotohandle[ClientNum].Addr.sin_addr)));
	//LeaveCriticalSection(&cs);


	bool isClientnumSend = false;
	//DWORD dwTime = GetTickCount();
	enemyTime1 = enemyTime2 = enemyTime3 = enemyTime4 = enemyTime5 = (float)timeGetTime() * 0.001f;

	while (true)
	{

		int Snum = clientinfotohandle[ClientNum].IsScene;

		switch (Snum) {
		case E_Scene::E_MENU: //메뉴화면일때
			printf("메뉴씬입니다!\n");

			retval = recvn(ClientSock, (char*)&playerInfo[ClientNum].IsReady, sizeof(playerInfo[ClientNum].IsReady), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv() IsReady");
				break;
			}

			if (IsAllClientReady() == true) {
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


			retval = recvn(ClientSock, (char*)&Input.m_KeyInput, sizeof(Input.m_KeyInput), 0);   //키 입력값 받음 더좋은 방법을 찾자~
			if (retval == SOCKET_ERROR) {
				err_display("recv() KeyInput");
				return 0;
				break;
			}

			if (Input.m_KeyInput.Left)
			{
				playerInfo[ClientNum].Pos.x -= 3;
			}
			if (Input.m_KeyInput.Right)
			{
				playerInfo[ClientNum].Pos.x += 3;
			}
			if (Input.m_KeyInput.Up)
			{
				playerInfo[ClientNum].Pos.y -= 3;
			}
			if (Input.m_KeyInput.Down)
			{
				playerInfo[ClientNum].Pos.y += 3;
			}
			if (Input.m_KeyInput.Space)
			{
				playerInfo[ClientNum].m_PlayerBullet.emplace_back(new CBullet(playerInfo[ClientNum].Pos, 0));
				//printf("%d번클라 스페이스바!\n",ClientNum);
			}

			SendAllPlayerInfo(ClientSock, playerInfo);
			MakeEnemy(ClientSock);
			//MakeItem(ClientSock);

			//for (int i = 0; i < I_power.size(); ++i)
			//{
			//	if (I_power[i]->GetXPos() + I_power[i]->GetSize() > WndX)
			//		I_power[i]->SetDir('x', false);
			//	else if (I_power[i]->GetXPos() < 0)
			//		I_power[i]->SetDir('x', true);

			//	if (I_power[i]->GetYPos() + I_power[i]->GetSize() > WndY)
			//		I_power[i]->SetDir('y', false);
			//	else if (I_power[i]->GetYPos() < 0)
			//		I_power[i]->SetDir('y', true);

			//	if (I_power[i]->GetDir('x'))
			//	{
			//		I_power[i]->SetXPos(I_power[i]->GetXPos() + 3);
			//		//printf("아이템의 x좌표: %d\n", I_power[i]->GetPos());
			//	}
			//	else
			//		I_power[i]->SetXPos(I_power[i]->GetXPos() - 3);

			//	if (I_power[i]->GetDir('y'))
			//		I_power[i]->SetYPos(I_power[i]->GetYPos() + 3);
			//	else
			//		I_power[i]->SetYPos(I_power[i]->GetYPos() - 3);

			//	//   send(ClientSock, (char*)&I_power[i]->GetPos(), sizeof(I_power[i]->GetPos()), 0);
			//}


			//for (int i = 0; i < I_skill.size(); ++i) // 필살기 아이템 이동
			//{
			//	if (I_skill[i]->GetXPos() + I_skill[i]->GetSize() > WndX)
			//		I_skill[i]->SetDir('x', false);
			//	else if (I_skill[i]->GetXPos() < 0)
			//		I_skill[i]->SetDir('x', true);

			//	if (I_skill[i]->GetYPos() + I_skill[i]->GetSize() > WndY)
			//		I_skill[i]->SetDir('y', false);
			//	else if (I_skill[i]->GetYPos() < 0)
			//		I_skill[i]->SetDir('y', true);

			//	if (I_skill[i]->GetDir('x'))
			//		I_skill[i]->SetXPos(I_skill[i]->GetXPos() + 3);
			//	else
			//		I_skill[i]->SetXPos(I_skill[i]->GetXPos() - 3);

			//	if (I_skill[i]->GetDir('y'))
			//		I_skill[i]->SetYPos(I_skill[i]->GetYPos() + 3);
			//	else
			//		I_skill[i]->SetYPos(I_skill[i]->GetYPos() - 3);
			//	//   send(ClientSock, (char*)&I_skill[i]->GetPos(), sizeof(I_skill[i]->GetPos()), 0);
			//}



			//for (int i = 0; i < I_bullet.size(); ++i) // 총알 아이템 이동
			//{
			//	if (I_bullet[i]->GetXPos() + I_bullet[i]->GetSize() > WndX)
			//		I_bullet[i]->SetDir('x', false);
			//	else if (I_bullet[i]->GetXPos() < 0)
			//		I_bullet[i]->SetDir('x', true);

			//	if (I_bullet[i]->GetYPos() + I_bullet[i]->GetSize() > WndY)
			//		I_bullet[i]->SetDir('y', false);
			//	else if (I_bullet[i]->GetYPos() < 0)
			//		I_bullet[i]->SetDir('y', true);

			//	if (I_bullet[i]->GetDir('x'))
			//		I_bullet[i]->SetXPos(I_bullet[i]->GetXPos() + 3);
			//	else
			//		I_bullet[i]->SetXPos(I_bullet[i]->GetXPos() - 3);

			//	if (I_bullet[i]->GetDir('y'))
			//		I_bullet[i]->SetYPos(I_bullet[i]->GetYPos() + 3);
			//	else
			//		I_bullet[i]->SetYPos(I_bullet[i]->GetYPos() - 3);
			//	//send(ClientSock, (char*)&I_bullet[i]->GetPos(), sizeof(I_bullet[i]->GetPos()), 0);
			//}



			//for (int i = 0; i < I_sub.size(); ++i)
			//{
			//	if (I_sub[i]->GetXPos() + I_sub[i]->GetSize() > WndX)
			//		I_sub[i]->SetDir('x', false);
			//	else if (I_sub[i]->GetXPos() < 0)
			//		I_sub[i]->SetDir('x', true);

			//	if (I_sub[i]->GetYPos() + I_sub[i]->GetSize() > WndY)
			//		I_sub[i]->SetDir('y', false);
			//	else if (I_sub[i]->GetYPos() < 0)
			//		I_sub[i]->SetDir('y', true);

			//	if (I_sub[i]->GetDir('x'))
			//		I_sub[i]->SetXPos(I_sub[i]->GetXPos() + 3);
			//	else
			//		I_sub[i]->SetXPos(I_sub[i]->GetXPos() - 3);

			//	if (I_sub[i]->GetDir('y'))
			//		I_sub[i]->SetYPos(I_sub[i]->GetYPos() + 3);
			//	else
			//		I_sub[i]->SetYPos(I_sub[i]->GetYPos() - 3);
			//	//send(ClientSock, (char*)&I_sub[i]->GetPos(), sizeof(I_sub[i]->GetPos()), 0);
			//}



			//for (int i = 0; i < I_sheild.size(); ++i) // 방어 아이템 이동
			//{
			//	if (I_sheild[i]->GetXPos() + I_sheild[i]->GetSize() > WndX)
			//		I_sheild[i]->SetDir('x', false);
			//	else if (I_sheild[i]->GetXPos() < 0)
			//		I_sheild[i]->SetDir('x', true);

			//	if (I_sheild[i]->GetYPos() + I_sheild[i]->GetSize() > WndY)
			//		I_sheild[i]->SetDir('y', false);
			//	else if (I_sheild[i]->GetYPos() < 0)
			//		I_sheild[i]->SetDir('y', true);

			//	if (I_sheild[i]->GetDir('x'))
			//		I_sheild[i]->SetXPos(I_sheild[i]->GetXPos() + 3);
			//	else
			//		I_sheild[i]->SetXPos(I_sheild[i]->GetXPos() - 3);

			//	if (I_sheild[i]->GetDir('y'))
			//		I_sheild[i]->SetYPos(I_sheild[i]->GetYPos() + 3);
			//	else
			//		I_sheild[i]->SetYPos(I_sheild[i]->GetYPos() - 3);
			//	//send(ClientSock, (char*)&I_sheild[i]->GetPos(), sizeof(I_sheild[i]->GetPos()), 0);
			//}
			////sendAllIngamePack(ClientSock);

			//m_pItem->Update(I_bullet, I_sub, I_power, I_skill, I_sheild);
			//m_pMonster->Update();
			//MoveEnemy();
			//플레이어 총알
			//이동
			for (auto p = playerInfo[ClientNum].m_PlayerBullet.begin(); p < playerInfo[ClientNum].m_PlayerBullet.end(); ++p)
			{
				if ((*p)->GetActive())
				{
					(*p)->SetYPos((*p)->GetYPos() - 13);
					//printf("%d", (*p)->GetYPos());
				}
			}

			//화면 나갈 시 삭제
			for (int i = 0; i < playerInfo[ClientNum].m_PlayerBullet.size(); ++i)
			{
				if (playerInfo[ClientNum].m_PlayerBullet[i]->GetYPos() > WndY)
				{
					playerInfo[ClientNum].m_PlayerBullet[i]->SetActive(false);
					iter_swap(playerInfo[ClientNum].m_PlayerBullet[i], playerInfo[ClientNum].m_PlayerBullet.back());
					if (playerInfo[ClientNum].m_PlayerBullet.back())
					{
						delete playerInfo[ClientNum].m_PlayerBullet.back();
						playerInfo[ClientNum].m_PlayerBullet.back() = nullptr;
					}
					playerInfo[ClientNum].m_PlayerBullet.pop_back();
				}
			}
			break;

			//인게임 아이템
		   //send(ClientSock, (char*)&playerInfo[ClientNum].m_PlayerBullet, sizeof(playerInfo[ClientNum].m_PlayerBullet), 0);
		   //게임 종료
		case E_Scene::E_GAMEOVER:
			//EnterCriticalSection(&cs);
			//for (vector<Score>::iterator iter = Rank.begin(); iter != Rank.end(); ++iter)
			//   cout << iter->second << " " << iter->first << endl;
			//LeaveCriticalSection(&cs);
			break;
			//랭크 출력
		case E_Scene::E_RANK:
			break;
		}
	}

	closesocket(ClientSock);

	return 0;
}





//
/////////////////////////////////////////////////////
//
int main(int argc, char *argv[])
{
	srand(time(NULL));
	int retval;
	InitializeCriticalSection(&cs);

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

	DeleteCriticalSection(&cs);
	closesocket(ListenSock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

