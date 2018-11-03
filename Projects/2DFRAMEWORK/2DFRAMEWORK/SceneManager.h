#pragma once
#include "Framework.h"

class CScene;
class CSceneManager : public FrameWork
{
public:
	CSceneManager();
	virtual ~CSceneManager();

public:
	virtual void Render(HDC memDc) override;
	virtual void Update() override;
	virtual void Destroy() override;

private:
	vector<CScene*> vSceneContainer;
};

