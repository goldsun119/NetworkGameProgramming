#include "stdafx.h"
#include "TimerManager.h"
#include <mmsystem.h>
#include "CObjectManager.h"

TimeManager::TimeManager() {}
TimeManager::~TimeManager() {}

void TimeManager::SetPrevElipsedTime()
{
	if (m_prevElipsedTime == 0.f) m_prevElipsedTime = timeGetTime();
}
void TimeManager::SetCurFimeElapsed()
{
	m_curfimeElapsed = timeGetTime();
}
void TimeManager::SetFimeElapsed()
{
	m_fTimeElapsed = m_curfimeElapsed - m_prevElipsedTime;
}
//================
DWORD TimeManager::GetPrevElipsedTime()
{
	return m_prevElipsedTime;
}

DWORD TimeManager::GetCurFimeElapsed()
{
	return m_curfimeElapsed;
}
DWORD TimeManager::GetFimeElapsed()
{
	return m_fTimeElapsed;
}
void TimeManager::SetEnemy()
{
	int eTiME = (float)m_fTimeElapsed / 1000.f;
	switch (eTiME)
	{
	case 10:
		//CObjectManager::AddGameObject(, E_ENEMY1);
		break;
	case 20:
		
		break;
	}
	
}