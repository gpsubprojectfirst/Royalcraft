#include "pch.h"
#include "UIElixirbar.h"

UIElixirbar::UIElixirbar()
{
	Init();
}

void UIElixirbar::Init()
{
	full = 100.0;
	curGage = 0.0;
	mycost = 0;
	AddDelta = 0.0;
	barRect = new Rect(160, 900, 385, 60);
	this->ParentImg = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\Elixir.png"));

	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile("Xml\\Elixir.xml");
	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* Node = Root->FirstChildElement("Data");
	tinyxml2::XMLElement* subNode = Node->FirstChildElement("UV");

	float x = subNode->FloatAttribute("Left") * ParentImg->GetWidth();
	float y = subNode->FloatAttribute("Top") * ParentImg->GetHeight();
	float width = (subNode->FloatAttribute("Right") * ParentImg->GetWidth()) - x;
	float height = (subNode->FloatAttribute("Bottom") * ParentImg->GetHeight()) - y;

	baseRect = new Gdiplus::Rect((int)(x + 0.5f), (int)(y + 0.5f), (int)(width + 0.5f), (int)(height + 0.5f));

	subNode = subNode->NextSiblingElement();

	x = subNode->FloatAttribute("Left") * ParentImg->GetWidth();
	y = subNode->FloatAttribute("Top") * ParentImg->GetHeight();
	width = (subNode->FloatAttribute("Right") * ParentImg->GetWidth()) - x;
	height = (subNode->FloatAttribute("Bottom") * ParentImg->GetHeight()) - y;

	elixirRect = new Gdiplus::Rect((int)(x + 0.5f), (int)(y + 0.5f), (int)(width + 0.5f), (int)(height + 0.5f));

	subNode = subNode->NextSiblingElement();

	x = subNode->FloatAttribute("Left") * ParentImg->GetWidth();
	y = subNode->FloatAttribute("Top") * ParentImg->GetHeight();
	width = (subNode->FloatAttribute("Right") * ParentImg->GetWidth()) - x;
	height = (subNode->FloatAttribute("Bottom") * ParentImg->GetHeight()) - y;

	barImgRect = new Gdiplus::Rect((int)(x + 0.5f), (int)(y + 0.5f), (int)(width + 0.5f), (int)(height + 0.5f));
}

void UIElixirbar::Update(float Delta)
{
	AddDelta += Delta;
	if (AddDelta > 0.01f)
	{
		if(curGage < full)
			curGage += 0.1f;
		else if (curGage >= full)
			curGage = full;
		AddDelta = 0;
	}
	
	rate = curGage / full;

	mycost = (int)curGage / 10;
	if (curGage / 100.0 >= 1)
		mycost = 10;
}
void UIElixirbar::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Bitmap* tempBitmap = new Bitmap(barRect->Width, barRect->Height);
	Gdiplus::Graphics* tempG = new Gdiplus::Graphics(tempBitmap);
	Gdiplus::Rect* tempRc = new Rect(0, 0, barRect->Width, barRect->Height);
	
	tempG->DrawImage(ParentImg, *tempRc, barImgRect->X, barImgRect->Y, barImgRect->Width, barImgRect->Height
		, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	tempRc = new Rect(0, 0, barRect->Width * 0.2, barRect->Height);
	tempG->DrawImage(ParentImg, *tempRc, baseRect->X, baseRect->Y, baseRect->Width, baseRect->Height
		, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	tempRc = new Rect(barRect->Width * 0.2, 1, barRect->Width * rate * 0.8, barRect->Height);
	tempG->DrawImage(ParentImg, *tempRc, elixirRect->X, elixirRect->Y, elixirRect->Width, elixirRect->Height
		, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	
	//엘릭서 정수 코스트
	Gdiplus::Font font(_T("Times New Roman"), 30, FontStyleBold, UnitPixel);
	SolidBrush sbrush(Gdiplus::Color::Black);
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	string tempstr = std::to_string(mycost);
	wstring wide_string = wstring(tempstr.begin(), tempstr.end());
	const WCHAR* result = wide_string.c_str();
	Gdiplus::RectF* tempFRc = new Gdiplus::RectF(150, 920, 80, 30);
	MemG->DrawImage(tempBitmap, *barRect);
	MemG->DrawString(result, -1, &font, *tempFRc, &format, &sbrush);
}
 