#include "stdafx.h"
#include "CGameObject.h"

CGameObject* CGameObject::AllObjectList[MAXOBJECTNUM] = { nullptr, };
unsigned long CGameObject::ObjIndex = 0;

CGameObject::CGameObject()
{
	while (AllObjectList[ObjIndex] != nullptr)
	{
		ObjIndex %= MAXOBJECTNUM;
		++ObjIndex;
	}
	AllObjectList[ObjIndex] = this;
	myIdx = ObjIndex;
	++ObjIndex;
}


CGameObject::~CGameObject()
{
	AllObjectList[myIdx] = nullptr;
}

unsigned long CGameObject::GetMyIdx()
{
	return myIdx;
}

void CGameObject::OnDraw(HDC memdc, std::string name, POINT pos, int width, int height)
{
	MYRENDERMANAGER->Render(memdc,name,pos,width,height);
}

//void Player::Draw(HDC memdc)
//{
//	//MYRENDERMANAGER->Render(memdc, name, pos, width, height);
//}

Player::Player()
{
//	m_size = 50;
}

Player::~Player()
{
}


