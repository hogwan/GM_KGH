#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

// 
// 1. ���� Ư�� �������� �����ߴٸ� ���� �Է¶��� �� �ݴ�������δ� ������ ����.
//    ���� �̵��ϴ� ������ �ݴ�������δ� ���� �ȵȴ�.
// 2. ���� �̵��� �ؼ� CurBody�� ȹ���ߴٸ� �� �������� �� �ٵ�� ���� ����;� �Ѵ�.

void Head::Update()
{
	int InputCount = _kbhit();
	if (0 == InputCount)
	{
		return;
	}

	int Select = _getch();

	int2 PrevPos = GetPos();
	this->PrevPosition = PrevPos;

	switch (Select)
	{
	case 'A':
	case 'a':
		if (Dir != Right)
		{
			AddPos(Left);
			Dir = Left;
		}
		break;
	case 'S':
	case 's':
		if (Dir != Up)
		{
			AddPos(Down);
			Dir = Down;
		}
		break;
	case 'W':
	case 'w':
		if (Dir != Down)
		{
			AddPos(Up);
			Dir = Up;
		}
		break;
	case 'D':
	case 'd':
		if (Dir != Left)
		{
			AddPos(Right);
			Dir = Right;
		}
		break;
	case '1':
		GetCore()->EngineEnd();
		break;
	default:
		break;
	}

	Part* CurPart = this->Back;
	while (CurPart)
	{
		Part* FrontPart = CurPart->Front;
		CurPart->PrevPosition = CurPart->GetPos();
		CurPart->SetPos(FrontPart->PrevPosition);
		CurPart = CurPart->Back;
	}


	if (nullptr == BodyManager::GetCurBody())
	{
		MsgBoxAssert("������ �ִ� �ٵ� �������� �ʽ��ϴ�.");
		return;
	}

	Body* CurBody = BodyManager::GetCurBody();

	std::list<ConsoleObject*> AllList = GetCore()->GetUpdateGroup();

	if (CurBody->GetPos() == GetPos())
	{
		Part* CurNode = this;
		while (CurNode->Back)
		{
			CurNode = CurNode->Back;
		}

		CurNode->Back = CurBody;
		CurBody->Front = CurNode;
		CurBody->SetPos(CurNode->PrevPosition);
		CurBody->PrevPosition;

		BodyManager::ResetBody();
	}
	
}