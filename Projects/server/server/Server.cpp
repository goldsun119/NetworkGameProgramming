#include "stdafx.h"

ClientInfoToHandle clientinfotohandle[2]; //Ŭ���̾�Ʈ ���Ӱ���
PlayerInfo playerInfo[2];
EnemyInfo enemyInfo;
int ClientCount = -1; //Ŭ���̾�Ʈ ��ȣ �Ҵ�

InputManager Input;
DWORD KeyInput;

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
bool IsAllClientReady()
{
	//todo ����
	if (playerInfo[0].IsReady == true && playerInfo[1].IsReady == true) { //11.12 ���� ��ģ��
		clientinfotohandle[0].IsReady == true;
		clientinfotohandle[1].IsReady == true;

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


DWORD WINAPI ProcessClient(LPVOID arg) {
	ClientCount++;
	SOCKET ClientSock = (SOCKET)arg;
	SOCKADDR ClientAddr;
	int AddrLen;
	AddrLen = sizeof(ClientAddr);
	getpeername(ClientSock, (SOCKADDR*)&ClientAddr, &AddrLen);

	int retval = 0;

	int ClientNum = ClientCount;
	SetInitData(playerInfo[ClientNum], ClientNum);

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
				//for(int i = 0;i<ClientNum;++i)
					retval = send(ClientSock, (char*)&clientinfotohandle[ClientNum].IsScene, sizeof(clientinfotohandle[ClientNum].IsScene), 0);//����ȯ ����
				if (retval == SOCKET_ERROR) {
					err_display("send() Scene");
					break;
				}
			}
			else {
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
			KeyInput = -1;
			switch (KeyInput) //Ű���� �� �ڼ��ϰ�
			{
			case Key::E_LEFT:
				//playerInfo->Pos.x -= 3;
				printf("��!\n");

				break;

			case Key::E_RIGHT:
				//playerInfo->Pos.x += 3;
				printf("��!\n");

				break;

			case Key::E_UP:
				//playerInfo->Pos.y -= 3;
				printf("��!\n");

				break;

			case Key::E_DOWN:

				//playerInfo->Pos.y += 3;
				printf("��!\n");

				break;
			}
			//retval = send(ClientSock, (char*)&playerInfo, sizeof(playerInfo), 0);//�÷��̾� ���� ����
			if (retval == SOCKET_ERROR) {
				err_display("send() playerInfo");
				break;
			}
			//printf("���� ��!\n");
			break;

			//���� ����
		case E_Scene::E_GAMEOVER:
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
	SOCKET ClientSock;
	SOCKADDR_IN ClientAddr;
	int addrlen;

	while (1)
	{
		addrlen = sizeof(ClientAddr);
		ClientSock = accept(ListenSock, (SOCKADDR *)&ClientAddr, &addrlen);
		if (ClientSock == INVALID_SOCKET) {
			err_display("accept()");
			exit(1);
		}
		// ������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));

		CreateThread(NULL, 0, ProcessClient, (LPVOID)ClientSock, 0, NULL);
	
	}
	// closesocket()
	closesocket(ListenSock);

	// ���� ����
	WSACleanup();
	return 0;
}


