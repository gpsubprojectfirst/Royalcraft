#pragma once

template <typename T>
class SingleTon
{
public:
	static T& SingleTon::GetInstance()
	{
		static T t;
		return t;
	}
};

