#pragma once
#include "CScene.h"
#include "CObjectManager.h"

class CMyInGame : public CScene
{
public:
	std::map<std::string, std::vector<MyImage>> m_IngameImageMap;
	HDC								m_hdc;
	HWND							m_hWnd;
	HBITMAP							m_hBitmapFrameBuffer;
	HBITMAP							m_hBitmapSelect;
	DWORD							m_bBackgroundColor;
	CImage							m_PlayerImg;

	CObjectManager					MakeEnemy;

	int								m_nWndClientWidth = 403;
	int								m_nWndClientHeight = 599;

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

	virtual void CheckKey() override;

};

