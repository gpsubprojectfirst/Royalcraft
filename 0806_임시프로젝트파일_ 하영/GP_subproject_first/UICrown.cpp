#include "pch.h"
#include "UICrown.h"

UICrown::UICrown()
{

}
void UICrown::ParserXML()
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile("Xml\\endcrown.xml");
	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* Node = Root->FirstChildElement("sprite");

	for (int i = 0; i < 70; i++)
	{
		animRc[0].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
	}
	doc = new tinyxml2::XMLDocument();
	doc->LoadFile("Xml\\enduired.xml");
	Root = doc->RootElement();
	Node = Root->FirstChildElement("sprite");
	for (int i = 0; i < 70; i++)
	{
		animRc[1].emplace_back(Node->IntAttribute("x")
			, Node->IntAttribute("y")
			, Node->IntAttribute("w")
			, Node->IntAttribute("h"));
		Node = Node->NextSiblingElement();
	}
}
void UICrown::Update(float Delta)
{
	AddDelta += Delta;

	if (AddDelta > 0.1f)
	{
		frame++;
		AddDelta = 0;

		if (frame > 100)
			frame = 0;
	}
	if (teamblue)
	{
		int frame_ = frame % animRc[0].size();
		rc = animRc[0][frame_];
	}
	else
	{
		int frame_ = frame % animRc[1].size();
		rc = animRc[1][frame_];
	}
}
void UICrown::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;

	Gdiplus::Rect Dst1(REAL_WINSIZE_X  / 2,REAL_WINSIZE_Y / 2,width,height );
	//Gdiplus::Rect Dst1(posRc.X, posRc.Y, width /2, height / 2);
	if (teamblue)
	{
		MemG->DrawImage(bluecrown, Dst1, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
	else
	{
		MemG->DrawImage(redcrown, Dst1, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);
	}
}

void UICrown::SetTeam(bool Tflag)
{
	teamblue = Tflag;
}