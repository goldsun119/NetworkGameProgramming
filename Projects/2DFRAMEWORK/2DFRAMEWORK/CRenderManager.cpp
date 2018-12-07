#include "stdafx.h"
#include "CRenderManager.h"

MyImage::MyImage()
{
}

MyImage::MyImage(TCHAR * FilePath)
{
}

MyImage::~MyImage()
{
}

void MyImage::Init(TCHAR* FilePath)
{
	this->LoadCImage(FilePath);
}

void MyImage::LoadCImage(TCHAR* FilePath)
{
	m_image = new CImage();
	HRESULT result = m_image->Load(FilePath);
	if (result == S_OK)
	{
		m_Width = m_image->GetWidth();
		m_Height = m_image->GetHeight();
	}
	else
	{
		MessageBox(NULL, FilePath, (LPCSTR)"경로가 잘못되었습니다.", NULL);
	}
}

CRenderManager::CRenderManager()
{
}


CRenderManager::~CRenderManager()
{
}

std::vector<MyImage>* CRenderManager::FindCImage(std::string name)
{
	std::map<std::string, std::vector<MyImage>>::iterator iter = m_ImageMap.find(name);

	//이미지를 찾아서 이미지가 있으면 이미지넘기고 없으면 NULL반환한다.
	if (iter == m_ImageMap.end())
		return NULL;
	else
		return &iter->second;
}

void CRenderManager::LoadCImage()
{
	// 맵을 돌면서 이미지들을 불러온다.find만듬. 
	// 게임 시작할 때 이미지를 전부 부르고 시작하고자 만듬. 게임 중에 부르지 않으려고

	AddRenderObject((TCHAR*)"StartBackground.png", "MenuImage");
	AddRenderObject((TCHAR*)"GameOverBackground.png", "GameOverImage");
	AddRenderObject((TCHAR*)"background.png", "IngameBackGroundImage");
	AddRenderObject((TCHAR*)"Player1.png", "IngamePlayerImage");

	//UI
	AddRenderObject((TCHAR*)"image/목숨.png", "IngameHPImage");


	AddRenderObject((TCHAR*)"image/STARTBUTTON.PNG", "MenuStartButtonImage");
	AddRenderObject((TCHAR*)"image/EXITBUTTON.PNG", "MenuExitButtonImage");
	AddRenderObject((TCHAR*)"image/레디.png", "MenuReadyButtonImage");

	//몬스터
	AddRenderObject((TCHAR*)"enemy1.png", "IngameEnemyImage");

	//플레이어총알
	AddRenderObject((TCHAR*)"image/총알기본.png", "PlayerDefaultBulletImage");

	//아이템
	AddRenderObject((TCHAR*)"image/ITEM(총알).png", "ItemBullet");
	AddRenderObject((TCHAR*)"image/ITEM(방어막).png", "ItemShield");
	AddRenderObject((TCHAR*)"image/ITEM(필살기).png", "ItemUlt");
	AddRenderObject((TCHAR*)"image/ITEM(보조).png", "ItemSub");
	AddRenderObject((TCHAR*)"image/강화총알.png", "ItemPower");
	//AddRenderObject((TCHAR*)"image/ITEM(방어막).png", "ItemShield");

	//TODO 1118 천기오빠 이 같은이름은뭐죠
	//AddRenderObject((TCHAR*)"enemy1.png", "IngameEnemyImage");

}

void CRenderManager::Render(HDC hdc, std::string name, POINT pos, int width, int height)
{
	//1. name으로 찾은 이름 검색.

	std::vector<MyImage>* image = FindCImage(name);

	if (image)
		image->begin()->GetCimage()->Draw(hdc, pos.x, pos.y, width, height);

}

void CRenderManager::PreRender(DWORD dwColor)
{
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hdc, hBrush);
	::Rectangle(m_hdc, 0, 0, m_nWndClientWidth, m_nWndClientHeight);
	::SelectObject(m_hdc, hOldBrush);
	::DeleteObject(hBrush);
}

void CRenderManager::BeginRender()
{
	HDC hDC = ::GetDC(m_hWnd);

	if (!m_hdc)
		m_hdc = ::CreateCompatibleDC(hDC);
	if (m_hBitmapFrameBuffer)
	{
		::SelectObject(m_hdc, NULL);
		::DeleteObject(m_hBitmapFrameBuffer);
		m_hBitmapFrameBuffer = NULL;
	}

	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_nWndClientWidth, m_nWndClientHeight);
	::SelectObject(m_hdc, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hdc, TRANSPARENT);
}

void CRenderManager::Render(HDC hdc)
{
	this->BeginRender();
	this->Render(m_hdc);

	this->EndRender();
}

void CRenderManager::EndRender()
{
	HDC hDC = ::GetDC(m_hWnd);

	::BitBlt(hDC, 0, 0, m_nWndClientWidth, m_nWndClientHeight, m_hdc, 0, 0, SRCCOPY);
	::ReleaseDC(m_hWnd, hDC);
}

void CRenderManager::AddRenderObject(TCHAR* FilePath, std::string name)
{

	std::vector<MyImage> ImageList;
	MyImage img;
	img.LoadCImage(FilePath);
	ImageList.push_back(img);
	m_ImageMap.insert(std::make_pair(name, ImageList));

}

