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

	// �ƴ� �� ��ΰ� �ȸԾ�
	AddRenderObject((TCHAR*)"StartBackground.png", "MenuImage");
}

void CRenderManager::Render(HDC hdc, std::string name, POINT pos, int width, int height)
{
	//1. name���� ã�� �̸� �˻�.

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

