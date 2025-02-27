#include "stdafx.h"
#include "SceneManager.h"
#include "CMyMenu.h"
#include "CMyInGame.h"
#include "CMyGameOver.h"
CSceneManager::CSceneManager()
{

}


CSceneManager::~CSceneManager()
{
	Destroy();
}

void CSceneManager::Render(HDC memDc)
{
	if (m_pScene) m_pScene->Render(memDc);
}

void CSceneManager::Update()
{

	//TODO 천기옵 씬정보 받는거 해주세요
	//send(FRAMEWORK->GetSock(), (char*)&m_SceneType, sizeof(m_SceneType), 0); //씬타입 전송
	
	

	if (m_pScene)
		m_pScene->Update();


}

void CSceneManager::Destroy()
{
	//for (auto iter : vSceneContainer)
	//{
	//	if (iter != nullptr)
	//	{
	//		delete iter;
	//		iter = nullptr;
	//	}
	//}

	//vSceneContainer.shrink_to_fit();
	//vSceneContainer.clear();
}

void CSceneManager::ChangeState(E_SCENE state)
{
	m_IsChangeScene = false;
	//SetScene(state);
}

void CSceneManager::SetScene(E_SCENE state)
{
	if (m_pScene)
	{
		delete m_pScene;
		m_pScene = NULL;
	}
	switch (state)
	{
	case E_MENU:
		m_pScene = new CMyMenu;
		m_SceneType = E_MENU;

		break;
	case E_INGAME:
		m_pScene = new CMyInGame;
		m_SceneType = E_INGAME;

		break;
	case E_GAMEOVER:
		m_pScene = new CMyGameOver;
		m_SceneType = E_GAMEOVER;

		break;

	}

}

E_SCENE CSceneManager::GetScene()
{
	return m_SceneType;
}
