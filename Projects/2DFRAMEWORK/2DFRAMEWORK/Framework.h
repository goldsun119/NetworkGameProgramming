#pragma once

class CScene;
class FrameWork :public CSingleTonBase<FrameWork>
{
	std::vector<CScene*>			m_states;

public:
	HINSTANCE						m_hInstance;
	HWND							m_hWnd;
	FrameWork();
	virtual ~FrameWork();

public:
	void Init();
	void OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	virtual void Render(HDC memDc);
	virtual void Update();
	virtual void Destroy();

	//���� ���°� ��������

	void Enter(CScene *state);
//private:
//	CSceneManager * pSceneMgr;
};

