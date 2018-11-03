#pragma once

class CSceneManager;
class FrameWork
{
public:
	FrameWork();
	virtual ~FrameWork();

public:
	void Init();
	virtual void Render(HDC memDc);
	virtual void Update();
	virtual void Destroy();

private:
	CSceneManager * pSceneMgr;
};

