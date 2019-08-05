
#include "Scene.h"
#include "pch.h"

void Scene::Start()
{
	bLoop = false;
	//info 채우는 부분
	bLoop = true;
}

void Scene::Loop(float Delta)
{
	if (!bLoop) return;
}

void Scene::End()
{
	bLoop = false;
	for (auto& it : info)
	{
		delete it;
		it = nullptr;
	}

	info.empty();
}

void Scene::Init()
{

}
void Scene::Update(float Delta)
{
}
void Scene::Render(Gdiplus::Graphics* MemG/*CDC* pDC*/)
{
}
void Scene::Release()
{
}
