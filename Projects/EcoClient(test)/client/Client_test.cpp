#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    1024
// BUFSIZE가 작으면 지금 소켓이 블로킹소켓이기 때문에
// 작으면 그만큼 블락되는 시간이 적은거고 크면 더길어짐
//대기시간을 줄이고 용량도 크면 좋음!

#pragma pack(1)
class Test {
public:
	bool IsReady=false;
	bool IsDead=false;
	int IsScene = 0; //씬 메뉴 초기값, 1 게임플레이

};

#pragma pack(1)
class PlayerInfo {
public:
	POINT Pos = {10,10};
	int Hp=5;
	int BulletCount=1;
	bool Shield=0;
	bool SubWeapon=1;
	bool Power=1;
	int Score=0;
};
// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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



int main(int argc, char *argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	Test test;
	PlayerInfo playerInfo;
	int count = 0;
	while (true)
	{
		if (test.IsScene == 0) {//메뉴화면
			retval = send(sock, (char*)&test.IsReady, sizeof(test.IsReady), 0);//구조체 보냄
			if (retval == SOCKET_ERROR) {
				err_display("send()");
			}
			retval = recv(sock, (char*)&test.IsScene, sizeof(test.IsScene), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recvn() IsScene");
			}
		}
		if (test.IsScene == 1) {//게임중
			retval = recv(sock, (char*)&playerInfo, sizeof(playerInfo), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recvn() playerInfo");
			}
			retval = send(sock, (char*)&playerInfo, sizeof(playerInfo), 0);
			if (retval == SOCKET_ERROR) {
				err_display("send() playerInfo");
			}

		}

		printf("%d\n", playerInfo.Hp);

		if (count > 5) { //테스트용 
			test.IsReady = true;
		}
		count++;
	}
	// closesocket()
	closesocket(sock);

	// 윈속 종료
	WSACleanup();

	return 0;
}