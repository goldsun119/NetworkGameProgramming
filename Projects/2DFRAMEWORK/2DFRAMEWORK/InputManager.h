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
	//Ű����
	void SetKeyState();
	DWORD GetKeyState();

	//���콺
	void SetPos(void);
	POINT GetPos(void);
};

#pragma once
