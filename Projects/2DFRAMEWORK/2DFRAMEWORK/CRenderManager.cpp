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
	// 이 부분은 최적화를 위한 부분이므로 나중에 작업함.
	// 게임 시작할 때 이미지를 전부 부르고 시작하고자 만듬.

	// 아니 왜 경로가 안먹어
	AddRenderObject((TCHAR*)"StartBackground.png", "MenuImage");
}

void CRenderManager::Render(HDC hdc, std::string name, POINT pos, int width, int height)
{
	//1. name으로 찾은 이름 검색.

	std::vector<MyImage>* image = FindCImage(name);

	if (image)
		image->begin()->GetCimage()->Draw(hdc, pos.x, pos.y, width, height);

}

void CRenderManager::AddRenderObject(TCHAR* FilePath, std::string name)
{

	std::vector<MyImage> ImageList;
	MyImage img;
	img.LoadCImage(FilePath);
	ImageList.push_back(img);
	m_ImageMap.insert(std::make_pair(name, ImageList));

}

