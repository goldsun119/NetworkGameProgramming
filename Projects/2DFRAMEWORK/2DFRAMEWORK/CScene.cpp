#include "stdafx.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"
CScene::CScene()
{
	m_pPlayer = new CPlayer;
	m_pMonster = new CMonster;
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
