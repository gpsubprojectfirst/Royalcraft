#pragma once
#include "SingleTon.h"

class XmlManager
	: public SingleTon<XmlManager>
{
public:
	XmlManager();
	
	//xml init,delete
	void Init();
	void Release();

	//object º° ÆÄ¼­
	void UnitParser(MyUnit* InUnit);
	void BuildParser(Build* InBuild);
	void BulletParser(Bullet* InBullet);
	void UnitInfoParser(std::vector<Object*>** objVector);
	void UIHPBarParser(UIHPBar* InUI);
	void UIElixirBarParser(UIElixirBar* InUI);
	
private:
	tinyxml2::XMLDocument* doc;
	tinyxml2::XMLElement* Root;
	tinyxml2::XMLElement* Node;
};