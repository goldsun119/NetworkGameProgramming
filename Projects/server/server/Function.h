#pragma once

bool IsAllClientReady(); // ��� Ŭ���̾�Ʈ�� ���� ���¸� Ȯ��
void SetInitData(PlayerInfo a, int num);

void err_quit(char *msg); // ���� �Լ� ���� ��� �� ����
void err_display(char *msg); // ���� �Լ� ���� ���
int recvn(SOCKET s, char *buf, int len, int flags); // ����� ���� ������ ���� �Լ�

ClientInfoToHandle clientinfotohandle[2]; //Ŭ���̾�Ʈ ���Ӱ���
PlayerInfo playerInfo[2];
EnemyInfo enemyInfo;
int ClientCount = -1; //Ŭ���̾�Ʈ ��ȣ �Ҵ�
int KeyInput = 0;
enum Key
{
	E_LEFT,
	E_RIGHT,
	E_UP,
	E_DOWN,
	E_ATTACK,
	E_ULTIMATE
};

DWORD WINAPI ProcessClient(LPVOID arg) {
	ClientCount++;
	SOCKET ClientSock = (SOCKET)arg;
	SOCKADDR ClientAddr;
	int AddrLen;
	AddrLen = sizeof(ClientAddr);
	getpeername(ClientSock, (SOCKADDR*)&ClientAddr, &AddrLen);

	int retval;

	int ClientNum = ClientCount;
	SetInitData(playerInfo[ClientNum], ClientNum);

	while (true)
	{
		//�޴�ȭ�� �϶�
		if (clientinfotohandle[ClientNum].IsScene == Scene::E_MENU) {
			retval = recvn(ClientSock, (char*)&clientinfotohandle[ClientNum].IsReady, sizeof(clientinfotohandle[ClientNum].IsReady), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv() IsReady");
				break;
			}

			if (IsAllClientReady() == true) {
				clientinfotohandle[ClientNum].IsScene = Scene::E_INGAME; //�����÷��̷� ����ȯ
				retval = send(ClientSock, (char*)&clientinfotohandle[ClientNum].IsScene, sizeof(clientinfotohandle[ClientNum].IsScene), 0);//����ȯ ����
				if (retval == SOCKET_ERROR) {
					err_display("send() Scene");
					break;
				}
			}
			else {
				printf("���� �ط�!\n");
			}
		}

		//���� �� �϶�
		else if (clientinfotohandle[ClientNum].IsScene == Scene::E_INGAME) {
			retval = recvn(ClientSock, (char*)&KeyInput, sizeof(KeyInput), 0);	//Ű �Է°� ����
			if (retval == SOCKET_ERROR) {
				err_display("recv() KeyInput");
				break;
			}
			switch (KeyInput)
			{
			case Key::E_LEFT:
				playerInfo->Pos.x -= 3;
				break;

			case Key::E_RIGHT:
				playerInfo->Pos.x += 3;
				break;


			case Key::E_UP:
				playerInfo->Pos.y -= 3;
				break;


			case Key::E_DOWN:
				playerInfo->Pos.y += 3;
				break;

			}
			retval = send(ClientSock, (char*)&playerInfo, sizeof(playerInfo), 0);//�÷��̾� ���� ����
			if (retval == SOCKET_ERROR) {
				err_display("send() playerInfo");
				break;
			}
			printf("���� ��!\n");
		}

		//���� ����
		if (clientinfotohandle[ClientNum].IsScene == Scene::E_GAMEOVER) {
		
		}

		//��ũ ���
		if (clientinfotohandle[ClientNum].IsScene == Scene::E_RANK) {

		}
	}

	closesocket(ClientSock);

	return 0;
}
bool IsAllClientReady()
{
	if (clientinfotohandle[0].IsReady == true && clientinfotohandle[1].IsReady == true) {
		return true;
	}
	else {
		return false;
	}
}

void SetInitData(PlayerInfo a, int num)
{
	//�ʱⰪ ���� �Լ��� ������!
	a.Pos = { (num+1) * 100, 50 };
	a.Hp = 5;
	a.BulletCount = 1;
	a.Shield = 0;
	a.SubWeapon = 1;
	a.Power = 1;
	a.Score = 0;
}

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