#pragma once
#include "CScene.h"
class CGameObject;
class CMyButton;

class CMyGameOver : public CScene
{
	list<CGameObject*>		m_ListButton;
public:
	CMyGameOver();
	virtual ~CMyGameOver();
	std::map<std::string, std::vector<MyImage>> m_GameOverImageMap;
	HDC								m_hdc;
	HWND							m_hWnd;
	HBITMAP							m_hBitmapFrameBuffer;
	HBITMAP							m_hBitmapSelect;
	DWORD							m_bBackgroundColor;
	int								m_nWndClientWidth = 800;
	int								m_nWndClientHeight = 600;

public:
	virtual void Render(HDC hdc) override;
	virtual void Update() override;
	virtual void Destroy() override;
public:
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void CheckKey() override;

};

