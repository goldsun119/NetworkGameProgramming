#pragma once
#include "CGameObject.h"
#include "MyPacket.h"


class CItem : public CGameObject
{
protected:
	bool m_XDir, m_YDir = true;
	
public:
	\
	int MyIndex;
	CItem();
	~CItem();
	CItem(ItemInfo itemInfo);
	void SetDir(char c, bool b);
	bool GetDir(char c) const;
	int GetIndex() { return MyIndex; }
	//void ItemGet(vector<I_BULLET> I_bullet, vector<I_SUB> I_sub, vector<I_POWER> I_power, vector<I_SKILL> I_skill, vector<I_SHEILD> I_sheild);
	virtual void Update();
	
	bool IsGetItem(PlayerInfo player);
	//bool IsGet(Player& p);
	
};