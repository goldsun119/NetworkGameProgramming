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
	MYRENDERMANAGER->LoadCImage();				//�����Ŵ����� ���� �̹��� ���� �ε�

}

void FrameWork::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	m_hWnd = hMainWnd;
	m_hInstance = hInstance;

	//�Ŵ��� ����

	//TODO Ÿ�̸�, ����Ŵ���
	MYRENDERMANAGER->LoadCImage();				//�����Ŵ���


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
