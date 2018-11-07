#pragma once
#include "CScene.h"
class CMyGameOver : public CScene
{
public:
	CMyGameOver();
	virtual ~CMyGameOver();
public:
	virtual void Render(HDC memDc) override;
	virtual void Update() override;
	virtual void Destroy() override;
public:
	virtual void Enter() override;
	virtual void Exit() override;
};

