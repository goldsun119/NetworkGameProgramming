#pragma once
class CGameObject
{
protected:
	std::string m_name;
	POINT m_Pos;
	int width;
	int height;

	
	int m_size;
	int m_hp;
	static CGameObject* AllObjectList[MAXOBJECTNUM];
	static unsigned long ObjIndex;

	unsigned long myIdx;

public:
	CGameObject();
	virtual ~CGameObject();
	
public:
	// Set
	POINT GetPos() { return m_Pos; }
	int GetXPos() const { return m_Pos.x; }
	int GetYPos() const { return m_Pos.y; }
	int GetHp() { return m_hp; }
	int GetSize() { return m_size; }


	// Get
	unsigned long GetMyIdx();
	void SetPos(int x, int y) { m_Pos.x = x, m_Pos.y = y; }
	void SetXPos(int x) { m_Pos.x = x; }
	void SetYPos(int y) { m_Pos.y = y; }
	void SetHp(int hp) { m_hp = hp; }
	void SetSize(int size) { m_size = size; }

public:
	// ¿ÃπÃ¡ˆ
	void Render(HDC memdc, std::string name, POINT pos, int width, int height);
	virtual void Render(HDC m_hdc);
};


