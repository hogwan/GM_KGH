#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"
#include <vector>

// 
// 1. ���� Ư�� �������� �����ߴٸ� ���� �Է¶��� �� �ݴ�������δ� ������ ����.
//    ���� �̵��ϴ� ������ �ݴ�������δ� ���� �ȵȴ�.
// 2. ���� �̵��� �ؼ� CurBody�� ȹ���ߴٸ� �� �������� �� �ٵ�� ���� ����;� �Ѵ�.

void Head::Update()
{
	int2 PrevPos = GetPos();
	this->PrevPosition = PrevPos;

	AddPos(Dir);

	if (GetPos().X == 0 || GetPos().X == GetCore()->Screen.GetScreenX() - 1
		|| GetPos().Y == 0 || GetPos().Y == GetCore()->Screen.GetScreenY() - 1)
	{
		GetCore()->EngineEnd();
	}

	std::vector<int2> MyBodyPositionVector;
	//�ٵ���� ��带 ����ٴϴ� ����
	Part* CurPart = this->Back;
	while (CurPart)
	{
		//����Ʈ�� ������ġ�� ����ؼ� �̵�
		Part* FrontPart = CurPart->Front;
		CurPart->PrevPosition = CurPart->GetPos();
		CurPart->SetPos(FrontPart->PrevPosition);

		//�ٵ���� �ٵ��Ϳ� ����
		int2 CurPosition = CurPart->GetPos();
		MyBodyPositionVector.push_back(CurPosition);

		CurPart = CurPart->Back;
	}

	//�ڱ� �ٵ� ���� ����
	std::vector<int2>::iterator StartIter = MyBodyPositionVector.begin();
	std::vector<int2>::iterator EndIter = MyBodyPositionVector.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		int2 BodyPiecePosition = *StartIter;
		if (GetPos() == BodyPiecePosition)
		{
			GetCore()->EngineEnd();
		}
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

		BodyManager::ResetBody();
	}

	int InputCount = _kbhit();
	if (0 == InputCount)
	{
		return;
	}
	int Select = _getch();


	switch (Select)
	{
	case 'A':
	case 'a':
		if (Dir != Right)
		{
			Dir = Left;
			SetRenderChar('<');
		}
		break;
	case 'S':
	case 's':
		if (Dir != Up)
		{
			Dir = Down;
			SetRenderChar('v');
		}
		break;
	case 'W':
	case 'w':
		if (Dir != Down)
		{
			Dir = Up;
			SetRenderChar('^');
		}
		break;
	case 'D':
	case 'd':
		if (Dir != Left)
		{
			Dir = Right;
			SetRenderChar('>');
		}
		break;
	case '1':
		GetCore()->EngineEnd();
		break;
	default:
		break;
	}

	
}

