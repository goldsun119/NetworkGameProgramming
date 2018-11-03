#pragma once
class InputManager
{
public:
	InputManager();
	~InputManager();
};

#pragma once

//KYT '12.02.17
/*
Input Manager

KeyDown, KeyUp, MouseWheel, MouseClick

사용법
1. Define YT_KEY값에 사용할 키값을 추가한다.
- 순서지키는게 중요하다.
- 최적화를 위해 벡터로 하였기 때문이다.

2. Load서 방금 등록한 key값을 Add한다.
- AddKey(넣을 키값, 대응시킬 VK_KEY값)
- HashTable에도 string을 등록 시킨다.

함수 설명
1. Load : 사용할 키를 등록한다.
2. KeyDown( YT_KEY(enum) )값을 넣어서 판단.
- True : KeyDown
- KeyDown과 Up은 같이 사용해야 한다.

3. KeyUp (YT_KEY(enum))값을 넣어서 판단.
- KeyDown하고 같이 사용할 필요는 없다.

4. OnlyKeyDown은 KeyUp을 사용하지 않을때만 사용한다.
cuz. 스택에 데이터 집어넣는거 때문에 그럼.

5. GetWheel()은 어떤 장소에서나 데이터를 리턴받아서
- GetWheel() < 0 휠 아래로
- GetWheel() = 0 휠 안움직임
- GetWheel() > 0 휠 위로

6. GetInputQueue() = input Data의 Queue데이터이다.

*/

//#include <deque>
//#include <queue>
//
//typedef struct tagKeyState
//{
//	YT_KEY  ytkey;
//	bool	bUpCheck;
//	bool	bDownCheck;
//	BYTE	BKey;
//
//	tagKeyState::tagKeyState()
//	{
//		ytkey = YK_END;
//		bUpCheck = false;
//		bDownCheck = false;
//		BKey = NULL;
//	}
//
//}KEYSTATE;
//
//typedef struct KeyStateCheck
//{
//	YT_KEY key;
//	bool   bDown;
//
//	KeyStateCheck() {};
//
//	KeyStateCheck(YT_KEY inKey, bool inDown)
//	{
//		key = inKey;
//		bDown = inDown;
//	}
//};
//
//
//class CInputManager : public CSingleTonBase<CInputManager>
//{
//	//키보드
//private:
//	//Key Data
//	std::vector<KEYSTATE>				m_vKeyState;
//
//	//KeyState
//	bool								m_bKeyState[256];
//
//	std::vector<std::string>		    m_stHashTable;
//
//	int									m_sWheel;
//	POINT								pt;
//
//public:
//	CInputManager(const CInputManager& rhs) = delete;
//
//
//public:
//	CInputManager();
//
//	~CInputManager();
//
//public:
//	void Load();
//
//	// bKeyBoard_Container
//	void AddKey(YT_KEY key, BYTE input);
//	bool KeyDown(YT_KEY input);
//	bool KeyUp(YT_KEY input);
//
//	//KeyUp은 사용하지 않고 KeyDown만 사용하는 키에서 사용
//	bool OnlyKeyDown(YT_KEY input);
//
//	//Mouse
//	/*  Wheel Down < WheelNon < Wheel Up  */
//	void SetWheel(int wheel);
//	int GetWheel() { return m_sWheel; }
//	void MouseWheel();
//	void SetMousePoint(int qx, int y);
//	void SetMousePoint(POINT _pt);
//	POINT GetMousePoint() { return pt; }
//
//};
//
