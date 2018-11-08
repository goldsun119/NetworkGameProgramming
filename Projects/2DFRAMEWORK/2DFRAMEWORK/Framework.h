#pragma once
#include "MyPacket.h"
class CScene;
class FrameWork :public CSingleTonBase<FrameWork>
{
	std::vector<CScene*>			m_states;

public:

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
	SOCKET							m_sock;
	int								m_retval;
	ClientInfoToHandle				m_ClientInfo;
	int								m_count;
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
	
	//���� ���°� ��������
	void Enter(E_SCENE state);

public:
	//GET
	SOCKET GetSock() { return m_sock; }
	int GetRetval() { return m_retval; }
	ClientInfoToHandle GetClientInfo() { return m_ClientInfo; }

	//SET
	void SetClientReadyInfo(bool isReady) { m_ClientInfo.IsReady = true; }
	
	//����
	int MakeServer();
//private:
//	CSceneManager * pSceneMgr;
};

