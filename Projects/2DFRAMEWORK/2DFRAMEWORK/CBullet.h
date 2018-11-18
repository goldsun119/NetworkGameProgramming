#pragma once
#include "CGameObject.h"
class CBullet : public CGameObject
{
	int m_Type; // -2 - °­È­ÃÑ¾Ë, -1 - º¸Á¶ ÃÑ¾Ë, 0 - ÇÃ·¹ÀÌ¾î ÃÑ¾Ë, 1 - Àû1 ÃÑ¾Ë , 2 - Àû2 ÃÑ¾Ë , 3 - Àû3 ÃÑ¾Ë, 4 - º¸½º ÃÑ¾Ë

public:
	CBullet();
	CBullet(POINT pos, int typeNum);
	~CBullet();
	int getType() const { return m_Type; }

public:
	//void Update();
	virtual void Render(HDC m_hdc);
};

