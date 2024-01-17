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

	int2 MoveVector = Dir * GetScale();
	AddPos(MoveVector);

	int2 Pos = GetPos();
	int Scale = GetScale();
	int RightPadding = Scale / 2;
	int LeftPadding = (Scale % 2 == 1) ? RightPadding : RightPadding - 1;
	
	//���� �ε����� ����
	for (int y = Pos.Y - LeftPadding; y <= Pos.Y + RightPadding; y++)
	{
		for (int x = Pos.X - LeftPadding; x <= Pos.X + RightPadding; x++)
		{
			if (y == 0 || y == GetCore()->Screen.GetScreenY() - 1
				|| x == 0 || x == GetCore()->Screen.GetScreenX() - 1)
			{
				GetCore()->EngineEnd();
			}
		}
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
		CurPart->SetScale(FrontPart->GetScale());

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
	//�ٵ������ ������ �̵�

	for (int y = Pos.Y - LeftPadding; y <= Pos.Y + RightPadding; y++)
	{
		for (int x = Pos.X - LeftPadding; x <= Pos.X + RightPadding; x++)
		{
			if (y == CurBody->GetPos().Y && x==CurBody->GetPos().X)
			{
				CurRemain--;
				if (CurRemain == 0)
				{
					int CurScale = GetScale();
					this->SetScale(CurScale + 1);
					CurRemain = SizeUpCount;

					if (this->GetScale() == 4)
					{
						GetCore()->EngineEnd();
					}
				}

				Part* CurNode = this;
				while (CurNode->Back)
				{
					CurNode = CurNode->Back;
				}

				CurNode->Back = CurBody;
				CurBody->Front = CurNode;
				CurBody->SetPos(CurNode->PrevPosition);
				CurBody->SetScale(this->GetScale());

				BodyManager::ResetBody();
			}
		}
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

