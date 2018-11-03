#include "stdafx.h"
#include "FrameWork.h"
#include "SceneManager.h"

FrameWork::FrameWork()
{
}


FrameWork::~FrameWork()
{
	Destroy();
}

void FrameWork::Init()
{
	pSceneMgr = new CSceneManager{};
}

void FrameWork::Render(HDC memDc)
{

}

void FrameWork::Update()
{
}

void FrameWork::Destroy()
{
	delete pSceneMgr;
	pSceneMgr = nullptr;
}
