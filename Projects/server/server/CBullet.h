#pragma once
#include "CGameObject.h"
class PlayerInfo;
class CBullet : public CGameObject
{
	int m_Type; // -2 - ��ȭ�Ѿ�, -1 - ���� �Ѿ�, 0 - �÷��̾� �Ѿ�, 1 - ��1 �Ѿ� , 2 - ��2 �Ѿ� , 3 - ��3 �Ѿ�, 4 - ���� �Ѿ�
public:
	bool m_IsActive;

	//int m_Count = 0;
	CBullet(POINT pos, int typeNum);
	CBullet();
	~CBullet();
	int getType() const { return m_Type; }
	bool IsCrashtoEnemy(CGameObject enemy);
	
	void Update();
	bool IsShootPlayer(PlayerInfo player);
public:
	
};

