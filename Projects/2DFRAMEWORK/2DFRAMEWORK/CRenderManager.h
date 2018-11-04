#pragma once
#include "stdafx.h"
class MyImage
{
private:
	CImage*					m_image;
	int						m_Width;
	int						m_Height;

public:
	MyImage();
	MyImage(TCHAR* FilePath);
	~MyImage();

	void Init(TCHAR* filePath);

	void LoadCImage(TCHAR* filePath);

	int GetWidth() { return m_Width; }

	int GetHeight() { return m_Height; }

	CImage* GetCimage() { return m_image; }

	MyImage* GetImage() { return this; }

};

class CRenderManager : public CSingleTonBase<CRenderManager>
{
	std::map<std::string, std::vector<MyImage>> m_ImageMap;

public:
	CRenderManager();
	~CRenderManager();

public:
	std::vector<MyImage>* FindCImage(std::string name);
	void LoadCImage();
	void Render(HDC hdc, std::string name, POINT pos, int width, int height);
	//그려질 오브젝트가 추가될 때 만든다. ex)Timer에서 일정 시간이 지나면 어떤 오브젝트추가해라 할 때 쓰기 위해서 만들었다.
	void AddRenderObject(TCHAR* FilePath, std::string name);
};

