#pragma once
#include "SingleTon.h"
#include "Scene.h"
class SceneManager
	:public SingleTon<SceneManager>
{
public:
	SceneManager();
	void LoadScene(/*EScene _eState*/CString& pName);
	//static SceneManager& GetInstance();
	Scene* GetCurScene();
	
	void Init();
	void RenderScene(Gdiplus::Graphics* MemG);
	void Update(float Delta);
	void SendLButtonDown(UINT nFlags, CPoint point);	
	
private:
	std::vector<Scene*> mScene;
	Scene* CurScene;
};
