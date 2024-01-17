#include "ConsoleScreen.h"

// std 및 플랫폼 헤더
#include <iostream>
#include <Windows.h>
#include <assert.h>
#include <conio.h>

// 자체 헤더
#include "ConsoleObject.h"

ConsoleScreen::ConsoleScreen()
{

}
ConsoleScreen::~ConsoleScreen()
{
	ReleaseScreen();
}

void ConsoleScreen::CreateScreen(/*&NewScreen => this, */int _ScreenX, int _ScreenY)
{
	ReleaseScreen();

	if (0 >= _ScreenX)
	{
		MsgBoxAssert("스크린 X크기가 0이기 때문에 콘솔 스크린을 만들수 없습니다");
	}

	if (0 >= _ScreenY)
	{
		MsgBoxAssert("스크린 Y크기가 0이기 때문에 콘솔 스크린을 만들수 없습니다");
	}

	/*this->*/ScreenX = _ScreenX;
	/*this->*/ScreenY = _ScreenY;

	if (0 != ScreenData.size())
	{
		MsgBoxAssert("이미 스크린을 만든 상태에서 다시 만들어졌습니다");
	}

	// std::vector<char>* Ptr = new std::vector<char>[ScreenY];

	ScreenData.resize(ScreenY+BufferSize*2);
	// ScreenData = new char* [ScreenY];
	if (BufferSize*2 >= ScreenData.size())
	{
		MsgBoxAssert("스크린 생성에 실패했습니다. if (nullptr == ScreenData)");
	}

	for (int y = 0; y < ScreenY+BufferSize*2; y++)
	{
		ScreenData[y].resize(ScreenX + BufferSize*2 + 2);
		// ScreenData[y] = new char[ScreenX + 2] {0,};

		if (BufferSize*2 >= ScreenData[y].size())
		{
			MsgBoxAssert("스크린 생성에 실패했습니다. if (nullptr == ScreenData[y])");
		}
	}

	ClearScreen();

	// 함수가 실행되면 스택에 그 함수 이름의 메모리를 그리면
	// 맴버함수는 실행되면 내부에 this가 있다는것을 기억해야 한다.
	// new를 하면 생각할 필요 없다. 일단 영역을 그려야 한다.

}

void ConsoleScreen::ReleaseScreen()
{
	ScreenData.clear();

	// 지울때는 역순으로 지워야 한다.
	//for (int y = 0; y < ScreenY; y++)
	//{
	//	if (nullptr == ScreenData[y])
	//	{
	//		continue;
	//	}

	//	delete[] ScreenData[y];
	//	ScreenData[y] = nullptr;
	//}

	//if (nullptr != ScreenData)
	//{
	//	delete[] ScreenData;
	//	ScreenData = nullptr;
	//}
}

void ConsoleScreen::SetChar(const ConsoleObject& _Object)
{
	SetChar(_Object.GetPos(), _Object.GetScale(), _Object.GetRenderChar());
}

void ConsoleScreen::SetChar(const ConsoleObject* _Object)
{
	SetChar(_Object->GetPos(), _Object->GetScale(), _Object->GetRenderChar());
}

void ConsoleScreen::SetChar(const int2& _Pos, const int _Scale, char _Char)
{
	int2 Pos = _Pos + int2{ BufferSize, BufferSize };
	int Scale = _Scale;
	int RightPadding = Scale / 2;
	int LeftPadding = (Scale % 2 == 1) ? RightPadding : RightPadding-1;


	for (int y = Pos.Y - LeftPadding; y <= Pos.Y + RightPadding; y++)
	{
		for (int x = Pos.X - LeftPadding; x <= Pos.X + RightPadding; x++)
		{
			ScreenData[y][x] = _Char;
		}
	}
}

void ConsoleScreen::ClearScreen()
{
	// char** ScreenData
	// char* ScreenData[0]
	// char ScreenData[0][0]

	// char** ScreenData
	// char* *ScreenData
	// char **ScreenData

	for (int y = BufferSize; y < ScreenY + BufferSize; y++)
	{
		for (int x = BufferSize; x < ScreenX + BufferSize; x++)
		{
			if (y == BufferSize || x == BufferSize || x == ScreenX + BufferSize - 1 || y == ScreenY + BufferSize - 1)
			{
				ScreenData[y][x] = '#';
			}
			else
			{
				ScreenData[y][x] = ' ';
			}
		}
		ScreenData[y][ScreenX + BufferSize] = '\n';
	}
}

void ConsoleScreen::PrintScreen()
{
	system("cls");

	printf_s("SizeUp에 필요한 개수 : 4\n");
	printf_s("Size를 4까지 늘리면 승리\n");
	for (int y = BufferSize; y < ScreenY+ BufferSize; y++)
	{
		if (BufferSize >= ScreenData[y].size())
		{
			MsgBoxAssert("존재하지 않은 라인을 출력하려고 했습니다");
		}

		std::vector<char>& Vector = ScreenData[y];
		char& FirstChar = Vector[BufferSize];
		char* PrintPtr = &FirstChar;
		printf_s(PrintPtr);
	}

	ClearScreen();
}