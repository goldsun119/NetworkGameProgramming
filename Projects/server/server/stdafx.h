// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "winmm.lib") 
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <windows.h>

#define SERVERPORT 9000
#define BUFSIZE    1024
#define WndX 419
#define WndY 635
#define FPS_PERSECOND 30

using namespace std;
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.


#define BossBulletNum 36
#define MAXOBJECTNUM 300
#define RAD(x) 3.141592 / 180 * (x)