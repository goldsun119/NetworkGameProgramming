//함수
//////////////////
#pragma once

bool IsAllClientReady(); // 모든 클라이언트의 레디 상태를 확인

void err_quit(char *msg); // 소켓 함수 오류 출력 후 종료
void err_display(char *msg); // 소켓 함수 오류 출력
int recvn(SOCKET s, char *buf, int len, int flags); // 사용자 정의 데이터 수신 함수

ClientInfoToHandle clientinfotohandle[2]; //클라이언트 접속관리
PlayerInfo playerInfo;
EnemyInfo enemyInfo;
int ClientCount = -1; //클라이언트 번호 할당

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
		if (clientinfotohandle[ClientNum].IsScene == E_MENU) { //메뉴화면 일때
			retval = recvn(ClientSock, (char*)&clientinfotohandle[ClientNum].IsReady, sizeof(clientinfotohandle[ClientNum].IsReady), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv() IsReady");
				break;
			}

			if (IsAllClientReady() == true) {
				clientinfotohandle[ClientNum].IsScene = E_INGAME; //게임플레이로 씬전환
				if (retval == SOCKET_ERROR) {
					err_display("send() Scene");
					break;
				}
			}
			else {
				printf("레디 해롸!\n");
			}
			retval = send(ClientSock, (char*)&clientinfotohandle[ClientNum].IsScene, sizeof(clientinfotohandle[ClientNum].IsScene), 0);//씬전환 전송
		}

		if (clientinfotohandle[ClientNum].IsScene == E_INGAME) { //게임 중 일때

			//초기값 설정 함수로 만들자!
			playerInfo.Pos = {10, 10};
			playerInfo.Hp=5;
			playerInfo.BulletCount=1;
			playerInfo.Shield=0;
			playerInfo.SubWeapon=1;
			playerInfo.Power=1;
			playerInfo.Score=0;

			retval = send(ClientSock, (char*)&playerInfo, sizeof(playerInfo), 0);//플레이어 정보 전송
			if (retval == SOCKET_ERROR) {
				err_display("send() playerInfo");
				break;
			}
			retval = recvn(ClientSock, (char*)&playerInfo, sizeof(playerInfo), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv() playerInfo");
				break;
			}

			printf("게임 중!\n");
		}

		if (clientinfotohandle[ClientNum].IsScene == E_GAMEOVER) { //게임 종료
		
		}

		if (clientinfotohandle[ClientNum].IsScene == E_RANK) { //랭크 출력

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