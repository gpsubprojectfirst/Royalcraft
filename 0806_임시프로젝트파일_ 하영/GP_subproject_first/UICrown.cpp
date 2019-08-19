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

	for (int i = 0; i < 30; i++)
	{
		animRc.emplace_back(Node->IntAttribute("x")
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

		if (frame > 10)
			frame = 0;
	}
	int frame_ = frame % animRc.size();
	rc = animRc[frame_];
}
void UICrown::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;

	Gdiplus::Rect Dst1(REAL_WINSIZE_X  / 2,REAL_WINSIZE_Y / 2,width,height );
	//Gdiplus::Rect Dst1(posRc.X, posRc.Y, width /2, height / 2);
	MemG->DrawImage(ParentImg, Dst1, rc.X, rc.Y, rc.Width, rc.Height, Gdiplus::Unit::UnitPixel,
		nullptr, 0, nullptr);
}