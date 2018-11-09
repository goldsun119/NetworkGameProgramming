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
		MessageBox(NULL, FilePath, (LPCSTR)"��ΰ� �߸��Ǿ����ϴ�.", NULL);
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

	//�̹����� ã�Ƽ� �̹����� ������ �̹����ѱ�� ������ NULL��ȯ�Ѵ�.
	if (iter == m_ImageMap.end())
		return NULL;
	else
		return &iter->second;
}

void CRenderManager::LoadCImage()
{
	// ���� ���鼭 �̹������� �ҷ��´�.find����. 
	// �� �κ��� ����ȭ�� ���� �κ��̹Ƿ� ���߿� �۾���.
	// ���� ������ �� �̹����� ���� �θ��� �����ϰ��� ����.

	AddRenderObject((TCHAR*)"StartBackground.png", "MenuImage");
	AddRenderObject((TCHAR*)"background.png", "IngameBackGroundImage");
	AddRenderObject((TCHAR*)"Player1.png", "IngamePlayerImage");
<<<<<<< HEAD
	AddRenderObject((TCHAR*)"image/STARTBUTTON.PNG", "MenuStartButtonImage");
	AddRenderObject((TCHAR*)"image/EXITBUTTON.PNG", "MenuExitButtonImage");
	AddRenderObject((TCHAR*)"image/����.png", "MenuReadyButtonImage");




=======
	AddRenderObject((TCHAR*)"enemy1.png", "IngameEnemyImage");
>>>>>>> 578fee02186e0e0cc13a46f8495a6d479c5ce152

}

void CRenderManager::Render(HDC hdc, std::string name, POINT pos, int width, int height)
{
	//1. name���� ã�� �̸� �˻�.

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

