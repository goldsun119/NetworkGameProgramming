#include "stdafx.h"
#include "CGameObject.h"


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
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
}
