// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "Enemy.h"
#include "Player.h"

#define SERVERPORT 9000
#define BUFSIZE    1024

using namespace std;
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

enum Key
{
	E_LEFT,
	E_RIGHT,
	E_UP,
	E_DOWN,
	E_ATTACK,
	E_ULTIMATE
};