#pragma once
#include "CScene.h"
class CGameObject;
class CMyButton;

class CMyMenu : public CScene
{
	list<CGameObject*>		m_ListButton;

public:
	CMyMenu();
	virtual ~CMyMenu();
	std::map<std::string, std::vector<MyImage>> m_MenuImageMap;
	HDC								m_hdc;
	HWND							m_hWnd;
	HBITMAP							m_hBitmapFrameBuffer;
	HBITMAP							m_hBitmapSelect;
	DWORD							m_bBackgroundColor;
	int								m_nWndClientWidth = 800;
	int								m_nWndClientHeight = 600;
	//bool							m_IsReady = false;

public:
	// CScene을(를) 통해 상속됨
	virtual void Render(HDC memDc) override;
	virtual void Update() override;
	virtual void Destroy() override;
public:
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void CheckKey() override;

	
	virtual void PreRender(DWORD dwColor);
	virtual void BeginRender();
	//virtual void Render(HDC hdc);
	virtual void EndRender();
};

