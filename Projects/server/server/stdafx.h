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
#define FPS_PERSECOND 60

using namespace std;
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

const DWORD KEY_LEFT = 0x00000001;
const DWORD KEY_RIGHT = 0x00000002;
const DWORD KEY_UP = 0x00000004;
const DWORD KEY_DOWN = 0x00000008;
const DWORD KEY_SPACE = 0x00000010;
