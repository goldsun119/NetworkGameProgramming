#pragma once

class CScene;
class FrameWork :public CSingleTonBase<FrameWork>
{
	std::vector<CScene*>			m_states;

public:
	//CScene* m_states[5];
	HINSTANCE						m_hInstance;
	HWND							m_hWnd;
	FrameWork();
	virtual ~FrameWork();
	HDC								m_hdc;
	HBITMAP							m_hBitmapFrameBuffer;
	HBITMAP							m_hBitmapSelect;
	DWORD							m_bBackgroundColor;


	float							m_fTimeElapsed;
	int								m_nWndClientWidth;
	int								m_nWndClientHeight;
public:
	void Init();
	void OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	//void Update();
	void OnDraw();
	void PreRender(DWORD dwColor);
	void BeginRender();
	void Render();
	void EndRender();

	virtual void Update();
	virtual void Destroy();
	
	//씬에 들어가는거 만들어야지
	void Enter(E_SCENE state);
//private:
//	CSceneManager * pSceneMgr;
};

