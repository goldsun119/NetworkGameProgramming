#include "stdafx.h"

ClientInfoToHandle clientinfotohandle[2]; //Ŭ���̾�Ʈ ���Ӱ���
PlayerInfo playerInfo[2];
EnemyInfo enemyInfo;
int ClientCount = 0; //Ŭ���̾�Ʈ ��ȣ �Ҵ�

InputManager Input;
DWORD KeyInput;

typedef pair<int, string> Score;

vector<Score> Rank;
CRITICAL_SECTION cs;
int score = 1;

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
	//todo ����
	if (playerInfo[0].IsReady == true && playerInfo[1].IsReady == true) { //11.12 ���� ��ģ��
		clientinfotohandle[0].IsReady = true;
		clientinfotohandle[1].IsReady = true;

		return true;
	}
	else {
		return false;
	}
}
void SetInitData(PlayerInfo a, int num)
{
	//�ʱⰪ ���� �Լ��� ������!
	a.Pos = { (num + 1) * 100, 50 };
	a.Hp = 5;
	a.BulletCount = 1;
	a.Shield = 0;
	a.SubWeapon = 1;
	a.Power = 1;
	a.Score = 0;
}

void SendAllPlayerInfo(PlayerInfo P[])
{	
	send(clientinfotohandle[0].Sock, (char*)&P, sizeof(P), 0);//�÷��̾� ���� ����
	send(clientinfotohandle[1].Sock, (char*)&P, sizeof(P), 0);//�÷��̾� ���� ����
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
	
	EnterCriticalSection(&cs);
	Rank.emplace_back(make_pair(score, inet_ntoa(clientinfotohandle[ClientNum].Addr.sin_addr)));
	LeaveCriticalSection(&cs);

	
	bool isClientnumSend = false;
	while (true)
	{
		int Snum=clientinfotohandle[ClientNum].IsScene;

	

		switch (Snum) {
		case E_Scene::E_MENU: //�޴�ȭ���϶�
			printf("�޴����Դϴ�!\n");

			retval = recvn(ClientSock, (char*)&playerInfo[ClientNum].IsReady, sizeof(playerInfo[ClientNum].IsReady), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv() IsReady");
				break;
			}

			if (IsAllClientReady() == true) {
				clientinfotohandle[ClientNum].IsScene = E_Scene::E_INGAME; //�����÷��̷� ����ȯ
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
			printf("�ΰ��Ӿ��Դϴ�\n");

			retval = recvn(ClientSock, (char*)&Input.m_dwKey, sizeof(Input.m_dwKey), 0);	//Ű �Է°� ���� ������ ����� ã��~
			if (retval == SOCKET_ERROR) {
				err_display("recv() KeyInput");
				break;
			}
			switch (Input.m_dwKey) //Ű���� �� �ڼ��ϰ�
			{
			case KEY_LEFT:
				playerInfo[ClientNum].Pos.x -= 3;
				printf("%d��Ŭ�� ��!\n",ClientNum);

				break;

			case KEY_RIGHT:
				playerInfo[ClientNum].Pos.x += 3;
				printf("%d��Ŭ�� ��!\n", ClientNum);

				break;

			case KEY_UP:
				playerInfo[ClientNum].Pos.y -= 3;
				printf("%d��Ŭ�� ��!\n", ClientNum);

				break;

			case KEY_DOWN:

				playerInfo[ClientNum].Pos.y += 3;
				printf("%d��Ŭ�� ��!\n", ClientNum);

				break;
			}
			SendAllPlayerInfo(playerInfo);
			
			if (retval == SOCKET_ERROR) {
				err_display("send() playerInfo");
				break;
			}
			//printf("���� ��!\n");
			break;

			//���� ����
		case E_Scene::E_GAMEOVER:
			//EnterCriticalSection(&cs);
			//for (vector<Score>::iterator iter = Rank.begin(); iter != Rank.end(); ++iter)
			//	cout << iter->second << " " << iter->first << endl;
			//LeaveCriticalSection(&cs);
			break;
			//��ũ ���
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
	int retval;
	InitializeCriticalSection(&cs);

	Rank.reserve(100);
	ifstream in("score.txt");
	if(!in.is_open())
		err_quit("Can't File Open");
	ReadInputFile(in, Rank);

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
	sort(Rank.begin(), Rank.end(), SortFunc);
	ofstream out("Score.txt");
	for (vector<Score>::iterator iter = Rank.begin(); iter != Rank.end(); ++iter)
	{
		out << iter->first << " " << iter->second << endl;
	}
	out.close();

	DeleteCriticalSection(&cs);
	closesocket(ListenSock);

	// ���� ����
	WSACleanup();
	return 0;
}


