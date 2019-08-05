#pragma once
class Scene
{

public:
	bool bLoop;
	CString Name;
	std::vector<Object*> info;
	Gdiplus::Image* img;

public:
	std::vector<Gdiplus::Image*>	m_vecImg;

	virtual void Init() {}
	virtual void Update(float Delta, int frame) {}
	virtual void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/) {}
	virtual void Release() {}


};

class LobbyScene :
	public Scene
{
public:
	CImage* bgImg;
	LobbyScene();

	void Init();
	void Update(float Delta, int frame);
	void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	void Release();
};

class LogoScene :
	public Scene
{
public:
	LogoScene();

	void Init();
	void Update(float Delta, int frame);
	void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	void Release();
};

class GameScene :
	public Scene
{
public:
	CImage* bgImg;
	GameScene();

	void Init();
	void Update(float Delta, int frame);
	void Render(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	void Release();
};




