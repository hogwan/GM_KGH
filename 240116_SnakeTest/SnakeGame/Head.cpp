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

	AddPos(Dir);

	if (GetPos().X == 0 || GetPos().X == GetCore()->Screen.GetScreenX() - 1
		|| GetPos().Y == 0 || GetPos().Y == GetCore()->Screen.GetScreenY() - 1)
	{
		GetCore()->EngineEnd();
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

