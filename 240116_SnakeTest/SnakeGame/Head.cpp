#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"
#include <vector>

// 
// 1. 내가 특정 방향으로 진행했다면 다음 입력때는 그 반대방향으로는 갈수가 없다.
//    내가 이동하는 방향의 반대방향으로는 가면 안된다.
// 2. 내가 이동을 해서 CurBody를 획득했다면 그 다음부터 그 바디는 나를 따라와야 한다.


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
	
	//벽에 부딪히면 죽음
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
	//바디들이 헤드를 따라다니는 로직
	Part* CurPart = this->Back;
	while (CurPart)
	{
		//프론트의 이전위치를 기억해서 이동
		Part* FrontPart = CurPart->Front;
		CurPart->PrevPosition = CurPart->GetPos();
		CurPart->SetPos(FrontPart->PrevPosition);
		CurPart->SetScale(FrontPart->GetScale());

		//바디들을 바디벡터에 넣음
		int2 CurPosition = CurPart->GetPos();
		MyBodyPositionVector.push_back(CurPosition);

		CurPart = CurPart->Back;
	}

	//자기 바디 물면 종료
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
		MsgBoxAssert("먹을수 있는 바디가 존재하지 않습니다.");
		return;
	}

	Body* CurBody = BodyManager::GetCurBody();

	std::list<ConsoleObject*> AllList = GetCore()->GetUpdateGroup();
	//바디먹으면 꼬리로 이동

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

