#include "stdafx.h"
#include "CMybutton.h"


CMyButton::CMyButton()
{
}

CMyButton::CMyButton(string strName, POINT destPos, float w, float h)
	:CGameObject(strName, destPos,w,h)
{

}

CMyButton::CMyButton(string strName, float destX, float destY, float w, float h)
	: CGameObject(strName, destX,destY, w, h)
{
}




void CMyButton::Render(HDC m_hdc)
{
	//11.09 오류--> 일단 각각 그림ㅠㅠ
	/*TransparentBlt(m_hdc,
		m_Pos.x,m_Pos.y,width,height,
		MYRENDERMANAGER->FindCImage(m_name)->begin()->GetCimage()->GetDC(),0,0,
		MYRENDERMANAGER->FindCImage(m_name)->begin()->GetCimage()->GetWidth(),
		MYRENDERMANAGER->FindCImage(m_name)->begin()->GetCimage()->GetHeight(),
		RGB(255, 255, 255));*/
}

CMyButton::~CMyButton()
{
}
