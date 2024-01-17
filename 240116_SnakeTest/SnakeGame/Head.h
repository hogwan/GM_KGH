#pragma once
#include "Part.h"

class Head : public Part
{

protected:
	void Update() override;

private:
	int2 Dir = { 0,0 };
};

