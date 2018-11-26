#include "stdafx.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"
CScene::CScene()
{
	
	m_pPlayer = new CPlayer;
}

CScene::~CScene()
{
}

void CScene::Enter()
{
}

void CScene::Exit()
{
}
