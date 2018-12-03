#pragma once
#include "CGameObject.h"
class CBullet : public CGameObject
{
	int m_Type; // -2 - °­È­ÃÑ¾Ë, -1 - º¸Á¶ ÃÑ¾Ë, 0 - ÇÃ·¹ÀÌ¾î ÃÑ¾Ë, 1 - Àû1 ÃÑ¾Ë , 2 - Àû2 ÃÑ¾Ë , 3 - Àû3 ÃÑ¾Ë, 4 - º¸½º ÃÑ¾Ë
public:
	bool m_IsActive;
	CBullet(POINT pos, int typeNum);
	CBullet();
	~CBullet();
	int getType() const { return m_Type; }
	bool IsCrashtoEnemy(CGameObject* enemy);
	void SetActive(bool isActive) { m_IsActive = isActive; }
	bool GetActive() { return m_IsActive; }
	void Update();
public:
	
};

