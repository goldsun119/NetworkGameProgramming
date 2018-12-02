#pragma once
#include "CGameObject.h"

enum E_ITEM
{
	E_ITEM,
	E_IPOWER,
	E_ISKILL,
	E_ISUB,
	E_ISHIELD,
	E_IBULLET
};
#pragma pack(1)
class ItemInfo {
public:
	bool IsDraw;
	int Type;
	POINT pos;
	int Index;
};

class CItem : public CGameObject
{
protected:
	bool m_XDir, m_YDir = true;

public:
	bool IsDraw;
	int MyIndex;
	CItem();
	~CItem();
	CItem(ItemInfo itemInfo);
	void SetDir(char c, bool b);
	bool GetDir(char c) const;
	int GetIndex() { return MyIndex; }
	//void ItemGet(vector<I_BULLET> I_bullet, vector<I_SUB> I_sub, vector<I_POWER> I_power, vector<I_SKILL> I_skill, vector<I_SHEILD> I_sheild);
	virtual void Update();
	//bool IsGet(Player& p);

};