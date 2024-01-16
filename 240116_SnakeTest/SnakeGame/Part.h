#pragma once
#include <ConsoleEngine/ConsoleObject.h>

class Part : public ConsoleObject
{

public:
	int2 PrevPosition = { -99,-99 };
	Part* Front = nullptr;
	Part* Back = nullptr;
};

