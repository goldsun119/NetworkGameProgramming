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
	HDC								m_hdc;
	HWND							m_hWnd;
	HBITMAP							m_hBitmapFrameBuffer;
	HBITMAP							m_hBitmapSelect;
	DWORD							m_bBackgroundColor;
	int								m_nWndClientWidth;
	int								m_nWndClientHeight;
public:
	std::vector<MyImage>* FindCImage(std::string name);
	void LoadCImage();
	void Render(HDC hdc, std::string name, POINT pos, int width, int height);
	//�׷��� ������Ʈ�� �߰��� �� �����. ex)Timer���� ���� �ð��� ������ � ������Ʈ�߰��ض� �� �� ���� ���ؼ� �������.
	//void Render(HDC hdc);
	void PreRender(DWORD dwColor);
	void BeginRender();
	void Render(HDC hdc);
	void EndRender();

	
	void AddRenderObject(TCHAR* FilePath, std::string name);
};

