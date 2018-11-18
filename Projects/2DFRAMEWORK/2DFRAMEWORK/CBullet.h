#pragma once
#include "CGameObject.h"
class CBullet : public CGameObject
{
	int m_Type; // -2 - ��ȭ�Ѿ�, -1 - ���� �Ѿ�, 0 - �÷��̾� �Ѿ�, 1 - ��1 �Ѿ� , 2 - ��2 �Ѿ� , 3 - ��3 �Ѿ�, 4 - ���� �Ѿ�

public:
	CBullet();
	CBullet(POINT pos, int typeNum);
	~CBullet();
	int getType() const { return m_Type; }

public:
	//void Update();
	virtual void Render(HDC m_hdc);
};

