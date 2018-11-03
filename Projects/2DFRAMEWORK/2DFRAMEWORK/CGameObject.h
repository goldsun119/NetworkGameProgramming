#pragma once

class CGameObject
{
	POINT m_Pos;
	int m_size;
	int m_hp;
public:
	CGameObject();
	virtual ~CGameObject();
// 
	
	void SetPos(int x, int y) { m_Pos.x = x, m_Pos.y = y; }
	POINT GetPos() { return m_Pos; }
	int GetxPos() const { return m_Pos.x; }
	void SetxPos(int x) { m_Pos.x = x; }
	void SetxPos(float x) { m_Pos.x = x; }
	int GetyPos() const { return m_Pos.y; }
	void SetyPos(int y) { m_Pos.y = y; }
	void SetyPos(float y) { m_Pos.y = y; }
	int GetHp() { return m_hp; }
	void SetHp(int hp) { m_hp = hp; }
	int GetSize() { return m_size; }
	void setSize(int i) { m_size = i; }
// ¿ÃπÃ¡ˆ
	void OnDraw(HDC memdc) {};

};

