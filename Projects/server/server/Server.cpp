#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "class.h"
#include "Function.h"

#define SERVERPORT 9000
#define BUFSIZE    1024

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


