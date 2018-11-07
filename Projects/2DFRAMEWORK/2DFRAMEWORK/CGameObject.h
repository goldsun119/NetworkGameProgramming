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
// ÀÌ¹ÌÁö
	void OnDraw(HDC memdc, std::string name, POINT pos, int width, int height);
	
};

//¼öÁ¤Áß
class Player : public CGameObject
{
private:
	CImage pImg;
	CImage pImgL;
	CImage pImgR;
	CImage Skillimg;
	CImage Subimg;
	CImage Barrierimg;
	POINT SkillPos;

	bool Sub;
	bool PowerUp;
	bool Barrier;

	int SkillSize;
	int SubSize;
	int PlayerLR = 0;
	int bullet; // ÃÑ¾Ë °¹¼ö
	int bomb;	// ÆøÅº °¹¼ö
	int PowerUpCount;
	int BarrierCount;
public:
	Player();
	void setSkillyPos(int p) { SkillPos.y = p; }
	int getSkillyPos() const { return SkillPos.y; }
	void setSub(bool b) { Sub = b; }
	bool haveSub() const { return Sub; }
	void setPowerUp(bool b) { PowerUp = b; }
	bool getPowerUp() const { return PowerUp; }
	void setBullet(int b) { bullet = b; }
	int getBullet() const { return bullet; }
	void setBomb(int b) { bomb = b; }
	int getBomb() const { return bomb; }
	void setBarrier(bool b) { Barrier = b; }
	bool getBarrier() const { return Barrier; }
	int getPowerUpCount() const { return PowerUpCount; }
	void SetPowerUpCount(int i) { PowerUpCount = i; }
	int getBarrierCount() const { return BarrierCount; }
	void SetBarrierCount(int i) { BarrierCount = i; }
	//void usingBomb(HDC hdc);
	//void usingBarrier(HDC hdc);
	void setLR(int i)
	{
		if (i == 0)
		{
			PlayerLR = 0;
		}
		if (i == 1) // 1 - R , 2 - L
		{
			PlayerLR = 1;
		}
		if (i == 2)
		{
			PlayerLR = 2;
		}
	}
	//void Draw(HDC memdc);
};
