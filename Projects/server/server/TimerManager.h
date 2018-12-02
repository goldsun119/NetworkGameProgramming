#pragma once


class TimeManager
{
private:
	DWORD m_prevElipsedTime = 0.f;
	DWORD m_curfimeElapsed =0.f;
	DWORD m_fTimeElapsed =0.f;
public:
	TimeManager();
	~TimeManager();
public:
	float m_eTime;
	float m_eActine;

	float m_CurrentTime;
	float m_FPS;
	float m_PrevTime;
	float m_TimeElapsed;
	void SetPrevElipsedTime();
	DWORD GetPrevElipsedTime();

	void SetCurFimeElapsed();
	DWORD GetCurFimeElapsed();

	void SetFimeElapsed();
	DWORD GetFimeElapsed();

};