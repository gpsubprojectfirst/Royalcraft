#include "Scene.h"
#include "pch.h"


Scene::Scene()
{
	int tempSize = 20;
	m_vecImg[EScene_End].reserve(tempSize);
	tempSize = 100;
	vecInfo[EScene_End].reserve(tempSize);
}

Scene::~Scene()
{

}