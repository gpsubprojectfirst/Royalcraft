#pragma once
#include "SingleTon.h"
#include "Scene.h"

enum SCENE
{
	SCENE_LOGO,
	SCENE_LOBBY,
	SCENE_GAME,
	SCENE_END,
};

class SceneManager :
	public SingleTon< SceneManager>
{
public:
	SceneManager();
	void LoadScene(CString& pName);
	void SetState(SCENE _SceneState);
	Scene* GetCurScene();
	void SendLButtonDown(UINT nFlags, CPoint point);
	void Init();
	void RenderScene(Gdiplus::Graphics* MemG/*CDC* pDC*/);
	void Update(float Delta);

private:
	std::vector<Scene*> mScene; 
	Scene* CurScene;
};

