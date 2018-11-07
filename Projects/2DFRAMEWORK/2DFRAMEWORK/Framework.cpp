#include "stdafx.h"
#include "FrameWork.h"
#include "SceneManager.h"

FrameWork::FrameWork()
{
	m_hdc = GetDC(g_hWnd);
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
	//SCENEMANAGER->SetScene(E_MENU);
	MYRENDERMANAGER->LoadCImage();				//�����Ŵ���

	this->Enter(E_MENU);
}


void FrameWork::OnDraw()
{


}

void FrameWork::PreRender(DWORD dwColor)
{
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hdc, hBrush);
	::Rectangle(m_hdc, 0, 0, m_nWndClientWidth, m_nWndClientHeight);
	::SelectObject(m_hdc, hOldBrush);
	::DeleteObject(hBrush);
}

void FrameWork::BeginRender()
{
	HDC hDC = ::GetDC(m_hWnd);

	if (!m_hdc)
		m_hdc = ::CreateCompatibleDC(hDC);
	if (m_hBitmapFrameBuffer)
	{
		::SelectObject(m_hdc, NULL);
		::DeleteObject(m_hBitmapFrameBuffer);
		m_hBitmapFrameBuffer = NULL;
	}

	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_nWndClientWidth, m_nWndClientHeight);
	::SelectObject(m_hdc, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hdc, TRANSPARENT);
}



void FrameWork::Render()
{
	//MYRENDERMANAGER->Render(memDC,);
	//todo 
	//1. scene�� �ִٸ� �� ������ drawȣ��

	//�������� ���� �ƴϸ� �� ���� ������ �ִ� �̹����� �׷����Ѵ�. 
	//if (!m_states.empty())
	//{
	//	//m_states.back()->
	//}
	//CScene* state;
	//m_states.push_back(state);
	//if (!m_states.empty())
	//{
	//	m_states.back()->OnDraw(m_hdc);
	//}
	//// resume previous state
	//else if (!m_states.empty()) {
	//	states.back()->OnDraw(m_hdc);
	//}

	////1. ������۸� ó�� ���Ʒ���
	this->BeginRender();
	SCENEMANAGER->Render(m_hdc);

	this->EndRender();
	//2. �� ���̿� ���� ��ο�
	//m_states
	//m_states[0]->Enter();

}

void FrameWork::EndRender()
{
	HDC hDC = ::GetDC(m_hWnd);

	::BitBlt(hDC, 0, 0, m_nWndClientWidth, m_nWndClientHeight, m_hdc, 0, 0, SRCCOPY);
	::ReleaseDC(m_hWnd, hDC);

}

void FrameWork::Update()
{
	//update����. �� ������Ʈ �ؼ� ���� �޾ƿ��� �׷�����. 

	SCENEMANAGER->Update();
}

void FrameWork::Destroy()
{
	//delete pSceneMgr;
	//pSceneMgr = nullptr;
}

void FrameWork::Enter(E_SCENE state)
{
	//m_states.push_back(state);
	//m_states = state;
//	m_states.back()->Enter();

	//�� �� ��������
	//���� ������� ������ ���� ��
	//���� ��.
	SCENEMANAGER->SetScene(E_MENU);

}