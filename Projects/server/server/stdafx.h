// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
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
#include <map>
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
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.


#define BossBulletNum 36
#define MAXOBJECTNUM 300
#define RAD(x) 3.141592 / 180 * (x)