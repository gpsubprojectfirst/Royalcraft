#pragma once
class Mouse
{
public:
	static inline POINT GetMousePos(void)
	{
		POINT	pt;

		GetCursorPos(&pt);

		return pt;
	}

public:
	Mouse();
	~Mouse();
};

