#pragma once
#include "stdafx.h"

class TimeManager :public CSingleTonBase<TimeManager> {
private:
	DWORD m_prevElipsedTime = 0.f;
	DWORD m_curfimeElapsed =0.f;
	DWORD m_fTimeElapsed =0.f;
public:
	TimeManager();
	~TimeManager();
public:
	void SetPrevElipsedTime();
	DWORD GetPrevElipsedTime();

	void SetCurFimeElapsed();
	DWORD GetCurFimeElapsed();

	void SetFimeElapsed();
	DWORD GetFimeElapsed();

};