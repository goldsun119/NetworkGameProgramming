#include "stdafx.h"
#include "CGameObject.h"

CGameObject CGameObject::AllObjectList[MAXOBJECTNUM] = {  };
unsigned long CGameObject::ObjIndex = 0;

CGameObject::CGameObject()
{
	//while (AllObjectList[ObjIndex] != NULL)
	//{
	//	ObjIndex %= MAXOBJECTNUM;
	//	++ObjIndex;
	//}
	//AllObjectList[ObjIndex] = (*this);
	//myIdx = ObjIndex;
	//++ObjIndex;
}



//CGameObject::CGameObject(string name, POINT pos, float width, float height)
//{
//	m_name = name;
//	m_Pos = pos;
//	m_width = width;
//	m_height = height;
//	
//}

//CGameObject::CGameObject(string name, float destX, float destY, float width, float height)
//{
//
//}

CGameObject::~CGameObject()
{
	//AllObjectList[myIdx] = nullptr;
}

unsigned long CGameObject::GetMyIdx()
{
	return myIdx;
}

void CGameObject::Update()
{
}




//void Player::Draw(HDC memdc)
//{
//	//MYRENDERMANAGER->Render(memdc, name, pos, width, height);
//}
