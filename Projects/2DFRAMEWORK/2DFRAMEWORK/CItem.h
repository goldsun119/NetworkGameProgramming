#pragma once
#include "stdafx.h"
#include "MyPacket.h"
#include "CGameObject.h"

class I_BULLET;
class I_SUB;
class I_POWER;
class I_SKILL;
class I_SHEILD;

class CItem : public CGameObject
{
protected:
	bool m_XDir, m_YDir = true;

public:
	CItem();
	~CItem();
	void SetDir(char c, bool b);
	bool GetDir(char c) const;
	void ItemGet(vector<I_BULLET> I_bullet, vector<I_SUB> I_sub, vector<I_POWER> I_power, vector<I_SKILL> I_skill, vector<I_SHEILD> I_sheild);
	virtual void Update();
	
	//bool IsGet(Player& p);

};
class I_BULLET : public CItem {

public:
	I_BULLET(ItemInfo itemInfo);
	//virtual void Update();

};

class I_SUB : public  CItem {

public:
	I_SUB(ItemInfo itemInfo);
	//virtual void Update();

};

class I_POWER : public CItem {

public:
	I_POWER(ItemInfo itemInfo);
	//virtual void Update();

};

class I_SKILL : public  CItem {

public:
	I_SKILL(ItemInfo itemInfo);
	//virtual void Update();

};
class I_SHEILD : public  CItem {

public:
	I_SHEILD(ItemInfo itemInfo);
	//virtual void Update();

};