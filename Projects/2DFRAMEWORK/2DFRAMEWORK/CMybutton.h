#pragma once
#include "CGameObject.h"
class CMyButton : public CGameObject
{
	//int m_ButtonNum;
public:
	CMyButton();
	CMyButton(string strName, POINT pos, float fcx, float fcy);
	CMyButton(string strName, float destX, float destY, float w, float h);

	virtual void Render(HDC m_hdc);
	virtual ~CMyButton();
};

