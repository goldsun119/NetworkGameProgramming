#include "stdafx.h"
#include "TimerManager.h"

#include "CObjectManager.h"


TimeManager::TimeManager() {}
TimeManager::~TimeManager() {}

void TimeManager::SetPrevElipsedTime()
{
	if (m_prevElipsedTime == 0.f) m_prevElipsedTime = GetTickCount();
}
void TimeManager::SetCurFimeElapsed()
{
	m_curfimeElapsed = GetTickCount();
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
