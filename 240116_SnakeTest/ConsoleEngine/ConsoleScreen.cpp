#include "ConsoleScreen.h"

// std �� �÷��� ���
#include <iostream>
#include <Windows.h>
#include <assert.h>
#include <conio.h>

// ��ü ���
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
		MsgBoxAssert("��ũ�� Xũ�Ⱑ 0�̱� ������ �ܼ� ��ũ���� ����� �����ϴ�");
	}

	if (0 >= _ScreenY)
	{
		MsgBoxAssert("��ũ�� Yũ�Ⱑ 0�̱� ������ �ܼ� ��ũ���� ����� �����ϴ�");
	}

	/*this->*/ScreenX = _ScreenX;
	/*this->*/ScreenY = _ScreenY;

	if (0 != ScreenData.size())
	{
		MsgBoxAssert("�̹� ��ũ���� ���� ���¿��� �ٽ� ����������ϴ�");
	}

	// std::vector<char>* Ptr = new std::vector<char>[ScreenY];

	ScreenData.resize(ScreenY+BufferSize*2);
	// ScreenData = new char* [ScreenY];
	if (BufferSize*2 >= ScreenData.size())
	{
		MsgBoxAssert("��ũ�� ������ �����߽��ϴ�. if (nullptr == ScreenData)");
	}

	for (int y = 0; y < ScreenY+BufferSize*2; y++)
	{
		ScreenData[y].resize(ScreenX + BufferSize*2 + 2);
		// ScreenData[y] = new char[ScreenX + 2] {0,};

		if (BufferSize*2 >= ScreenData[y].size())
		{
			MsgBoxAssert("��ũ�� ������ �����߽��ϴ�. if (nullptr == ScreenData[y])");
		}
	}

	ClearScreen();

	// �Լ��� ����Ǹ� ���ÿ� �� �Լ� �̸��� �޸𸮸� �׸���
	// �ɹ��Լ��� ����Ǹ� ���ο� this�� �ִٴ°��� ����ؾ� �Ѵ�.
	// new�� �ϸ� ������ �ʿ� ����. �ϴ� ������ �׷��� �Ѵ�.

}

void ConsoleScreen::ReleaseScreen()
{
	ScreenData.clear();

	// ���ﶧ�� �������� ������ �Ѵ�.
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

	printf_s("SizeUp�� �ʿ��� ���� : 4\n");
	printf_s("Size�� 4���� �ø��� �¸�\n");
	for (int y = BufferSize; y < ScreenY+ BufferSize; y++)
	{
		if (BufferSize >= ScreenData[y].size())
		{
			MsgBoxAssert("�������� ���� ������ ����Ϸ��� �߽��ϴ�");
		}

		std::vector<char>& Vector = ScreenData[y];
		char& FirstChar = Vector[BufferSize];
		char* PrintPtr = &FirstChar;
		printf_s(PrintPtr);
	}

	ClearScreen();
}