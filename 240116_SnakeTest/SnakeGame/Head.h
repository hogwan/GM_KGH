#pragma once
#include "Part.h"

class Head : public Part
{
public:

protected:
	void Update() override;

private:
	int2 Dir = { 0,0 };
	int SizeUpCount = 4;
	int CurRemain = 4;
};

