#pragma once
class CInputManager :public CSingleTonBase<CInputManager> //: public FrameWork
{

private:
	DWORD m_dwKey;
	POINT	m_ptMousePos;

public:
	CInputManager();
	~CInputManager();

	
public:
	//키보드
	void SetKeyState();
	DWORD GetKeyState();

	//마우스
	void SetPos(void);
	POINT GetPos(void);
};

#pragma once
