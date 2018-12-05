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

CGameObject::CGameObject(string name, POINT pos, float width, float height)
	:m_name(name),m_Pos(pos),width(width),height(height)
{
}

CGameObject::CGameObject(string name, float destX, float destY, float width, float height)
	: m_name(name), width(width), height(height)
{
	m_Pos.x = destX;
	m_Pos.y = destY;

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

void CGameObject::Render(HDC m_hdc)
{


}

