#include "stdafx.h"
#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}
//#include "stdafx.h"
//#include "InputManager.h"
//#include <iostream>
//
//CInputManager::CInputManager()
//{
//	m_vKeyState.reserve(YK_END);
//	m_sWheel = 0;
//	pt.x = pt.y = 0;
//
//}
//
//CInputManager::~CInputManager()
//{
//}
//
//void CInputManager::Load()
//{
//	//m_bKeyState = new bool[YK_END];
//
//	for (int i = 0; i < 256; ++i)
//	{
//		AddKey(YT_KEY(VK_LBUTTON + i), VK_LBUTTON + i);
//	}
//	memset(&m_bKeyState, false, sizeof(m_bKeyState));
//}
//
//void CInputManager::AddKey(YT_KEY key, BYTE input)
//{
//	tagKeyState keystate;
//	keystate.BKey = input;
//	keystate.ytkey = key;
//	m_vKeyState.push_back(keystate);
//}
//
//bool CInputManager::KeyDown(YT_KEY input)
//{
//	if (GetAsyncKeyState(m_vKeyState[input].BKey) & 0x8000)
//	{
//		if (!m_bKeyState[input])
//			return true;
//
//		m_bKeyState[input] = true;
//		return false;
//	}
//	return false;
//}
//
//bool CInputManager::KeyUp(YT_KEY input)
//{
//	if (GetAsyncKeyState(m_vKeyState[input].BKey) & 0x8000)
//	{
//		m_vKeyState[input].bUpCheck = true;
//		return false;
//	}
//	else if (m_vKeyState[input].bUpCheck)
//	{
//		m_bKeyState[input] = false;
//		m_vKeyState[input].bUpCheck = false;
//		return true;
//	}
//	return false;
//}
//
//bool CInputManager::OnlyKeyDown(YT_KEY input)
//{
//	if (GetAsyncKeyState(m_vKeyState[input - 1].BKey) & 0x8000)
//	{
//		if (!m_bKeyState[input])
//		{
//			m_bKeyState[input] = true;
//			return true;
//		}
//		return false;
//	}
//	else
//	{
//		m_bKeyState[input] = false;
//		m_vKeyState[input].bUpCheck = false;
//		return false;
//	}
//	return false;
//}
//
//void CInputManager::SetWheel(int wheel)
//{
//	if (wheel > WHEEL_NON)
//		m_sWheel = WHEEL_UP;
//
//	else if (wheel < WHEEL_NON)
//		m_sWheel = WHEEL_DOWN;
//
//	else
//		m_sWheel = WHEEL_NON;
//}
//
//void CInputManager::MouseWheel()
//{
//	if (GetAsyncKeyState(VK_MBUTTON) & 0x8000)
//		std::cout << "0x800" << std::endl;
//
//	if (GetAsyncKeyState(VK_MBUTTON) & 0xF0)
//		std::cout << "0xF0" << std::endl;
//
//	if (GetAsyncKeyState(VK_MBUTTON) & 0x00)
//		std::cout << "0x00" << std::endl;
//
//	if (GetAsyncKeyState(VK_MBUTTON) & 0x01)
//		std::cout << "0x01" << std::endl;
//
//	if (GetAsyncKeyState(VK_MBUTTON))
//		std::cout << "VK_MBUTTON" << std::endl;
//}
//
//void CInputManager::SetMousePoint(int x, int y)
//{
//	pt.x = x; pt.y = y;
//}
//
//void CInputManager::SetMousePoint(POINT _pt)
//{
//	pt = _pt;
//}
