//�Լ�
//////////////////
#pragma once

bool IsAllClientReady(); // ��� Ŭ���̾�Ʈ�� ���� ���¸� Ȯ��

void err_quit(char *msg); // ���� �Լ� ���� ��� �� ����
void err_display(char *msg); // ���� �Լ� ���� ���
int recvn(SOCKET s, char *buf, int len, int flags); // ����� ���� ������ ���� �Լ�

ClientInfoToHandle clientinfotohandle[2]; //Ŭ���̾�Ʈ ���Ӱ���
PlayerInfo playerInfo;
EnemyInfo enemyInfo;
int ClientCount = -1; //Ŭ���̾�Ʈ ��ȣ �Ҵ�

DWORD WINAPI ProcessClient(LPVOID arg) {
	ClientCount++;
	SOCKET ClientSock = (SOCKET)arg;
	SOCKADDR ClientAddr;
	int AddrLen;
	AddrLen = sizeof(ClientAddr);
	getpeername(ClientSock, (SOCKADDR*)&ClientAddr, &AddrLen);

	int retval;

	int ClientNum = ClientCount;
	while (true)
	{
		if (clientinfotohandle[ClientNum].IsScene == E_MENU) { //�޴�ȭ�� �϶�
			retval = recvn(ClientSock, (char*)&clientinfotohandle[ClientNum].IsReady, sizeof(clientinfotohandle[ClientNum].IsReady), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv() IsReady");
				break;
			}

			if (IsAllClientReady() == true) {
				clientinfotohandle[ClientNum].IsScene = E_INGAME; //�����÷��̷� ����ȯ
				if (retval == SOCKET_ERROR) {
					err_display("send() Scene");
					break;
				}
			}
			else {
				printf("���� �ط�!\n");
			}
			retval = send(ClientSock, (char*)&clientinfotohandle[ClientNum].IsScene, sizeof(clientinfotohandle[ClientNum].IsScene), 0);//����ȯ ����
		}

		if (clientinfotohandle[ClientNum].IsScene == E_INGAME) { //���� �� �϶�

			//�ʱⰪ ���� �Լ��� ������!
			playerInfo.Pos = {10, 10};
			playerInfo.Hp=5;
			playerInfo.BulletCount=1;
			playerInfo.Shield=0;
			playerInfo.SubWeapon=1;
			playerInfo.Power=1;
			playerInfo.Score=0;

			retval = send(ClientSock, (char*)&playerInfo, sizeof(playerInfo), 0);//�÷��̾� ���� ����
			if (retval == SOCKET_ERROR) {
				err_display("send() playerInfo");
				break;
			}
			retval = recvn(ClientSock, (char*)&playerInfo, sizeof(playerInfo), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv() playerInfo");
				break;
			}

			printf("���� ��!\n");
		}

		if (clientinfotohandle[ClientNum].IsScene == E_GAMEOVER) { //���� ����
		
		}

		if (clientinfotohandle[ClientNum].IsScene == E_RANK) { //��ũ ���

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