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
	//pSceneMgr = new CSceneManager{};
	MYRENDERMANAGER->LoadCImage();				//랜더매니저가 가진 이미지 전부 로드

}

void FrameWork::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	m_hWnd = hMainWnd;
	m_hInstance = hInstance;

	//매니저 생성

	//TODO 타이머, 사운드매니저
	MYRENDERMANAGER->LoadCImage();				//랜더매니저


}

void FrameWork::Render(HDC memDc)
{

}

void FrameWork::Update()
{
}

void FrameWork::Destroy()
{
	//delete pSceneMgr;
	//pSceneMgr = nullptr;
}

void FrameWork::Enter(CScene * state)
{
	m_states.push_back(state);

}
