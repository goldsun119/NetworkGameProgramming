#include "stdafx.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"
CScene::CScene()
{
	m_pPlayer = new CPlayer;
	m_pMonster1 = new CMonster;
	m_pMonster2 = new CMonster;
	m_pMonster3 = new CMonster;
	m_pBoss1 = new CMonster;
	m_pBoss2 = new CMonster;
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
