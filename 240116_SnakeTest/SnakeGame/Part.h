#pragma once
#include <ConsoleEngine/ConsoleObject.h>

class Part : public ConsoleObject
{

public:
	int2 PrevPosition = { 0,0 };
	Part* Front = nullptr;
	Part* Back = nullptr;
};

