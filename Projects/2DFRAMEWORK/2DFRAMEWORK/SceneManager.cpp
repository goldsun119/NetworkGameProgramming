#include "stdafx.h"
#include "SceneManager.h"
#include "CMyMenu.h"
#include "CMyInGame.h"
#include "CMyGameOver.h"
CSceneManager::CSceneManager()
{
	CScene* pScene = new CMyMenu{};

	vSceneContainer.push_back(pScene);
}


CSceneManager::~CSceneManager()
{
	Destroy();
}

void CSceneManager::Render(HDC memDc)
{
}

void CSceneManager::Update()
{
}

void CSceneManager::Destroy()
{
	for (auto iter : vSceneContainer)
	{
		if (iter != nullptr)
		{
			delete iter;
			iter = nullptr;
		}
	}

	vSceneContainer.shrink_to_fit();
	vSceneContainer.clear();
}
