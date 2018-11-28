#pragma once

class CPlayer;
class CMonster;
class TimeManager;
class CScene //추상클래스. 객체화할 수 없다. 
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Render(HDC memDc) = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void CheckKey() = 0;
	
	
	

protected:
	CPlayer		*m_pPlayer;
	CPlayer		*m_p2Player;

	TimeManager *m_pTime;
};

