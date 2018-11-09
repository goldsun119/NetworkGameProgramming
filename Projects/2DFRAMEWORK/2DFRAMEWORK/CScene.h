#pragma once

class CPlayer;
class CScene //�߻�Ŭ����. ��üȭ�� �� ����. 
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

protected:
	CPlayer		*m_pPlayer;
};

