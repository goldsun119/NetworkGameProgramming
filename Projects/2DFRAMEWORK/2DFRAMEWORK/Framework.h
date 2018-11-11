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
	
	//씬에 들어가는거 만들어야지
	void Enter(E_SCENE state);

public:
	//GET
	SOCKET GetSock() { return m_sock; }
	int GetRetval() { return m_retval; }
	bool GetReadyInfo() { return m_ClientInfo.IsReady; }

	ClientInfoToHandle GetClientInfo() { return m_ClientInfo; }

	//SET
	void SetClientReadyInfo() { m_ClientInfo.IsReady = true; }
	void SetClientInfo(ClientInfoToHandle CInfoFromServer) { m_ClientInfo = CInfoFromServer; }

	
	//서버
	int MakeServer();
	int recvn(SOCKET s, char *buf, int len, int flags);
	void err_display(const char *msg);


//private:
//	CSceneManager * pSceneMgr;
};

