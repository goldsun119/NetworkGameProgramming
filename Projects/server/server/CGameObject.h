#pragma once
#include "stdafx.h"
#define MAXOBJECTNUM 10000

class CGameObject
{
protected:
	string m_name;
	POINT m_Pos;

	int m_width;
	int m_height;

	int m_Type;

	int m_size;
	int m_hp;
	static CGameObject* AllObjectList[MAXOBJECTNUM];
	static unsigned long ObjIndex;

	unsigned long myIdx;

public:
	CGameObject();
	//CGameObject(string name, POINT pos, float width, float height);
	//CGameObject(string name, float destX, float destY, float width, float height);


	virtual ~CGameObject();


	// Get
	POINT GetPos() { return m_Pos; }
	int GetXPos() const { return m_Pos.x; }
	int GetYPos() const { return m_Pos.y; }
	int GetHp() { return m_hp; }
	int GetSize() { return m_size; }
	int GetType() { return m_Type; }

	unsigned long GetMyIdx();
	// Set
	void SetPos(int x, int y) { m_Pos.x = x, m_Pos.y = y; }
	void SetXPos(int x) { m_Pos.x = x; }
	void SetYPos(int y) { m_Pos.y = y; }
	void SetHp(int hp) { m_hp = hp; }
	void SetSize(int size) { m_size = size; }
	void SetType(int type) { m_Type = type; }
	// ¿ÃπÃ¡ˆ
	
public:
	virtual void Update();
	//virtual void Render(HDC m_hdc);
};


