#pragma once
#include "CScene.h"

class CMyInGame : public CScene
{
public:
	std::map<std::string, std::vector<MyImage>> m_IngameImageMap;
	HDC								m_hdc;
	HWND							m_hWnd;
	HBITMAP							m_hBitmapFrameBuffer;
	HBITMAP							m_hBitmapSelect;
	DWORD							m_bBackgroundColor;
	int								m_nWndClientWidth;
	int								m_nWndClientHeight;
	//CGameObject						*m_pGameObj;
	//Player							*m_pPlayer;
public:
	CMyInGame();
	virtual ~CMyInGame();
public:
	virtual void Render(HDC memDc) override;
	virtual void Update() override;
	virtual void Destroy() override;
public:
	virtual void Enter() override;
	virtual void Exit() override;
};

