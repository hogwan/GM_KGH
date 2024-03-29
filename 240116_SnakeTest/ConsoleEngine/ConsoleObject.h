#pragma once
#include "ConsoleMath.h"
#include "ConsoleUpdater.h"

// 전방선언 
class ConsoleObject : public ConsoleUpdater
{
	friend class EngineCore;

public:
	ConsoleObject();
	ConsoleObject(const int2& _StartPos, char _RenderChar);
	// 소멸자 virtual 
	virtual ~ConsoleObject();

	int2 GetPos() const;
	int GetScale() const;
	char GetRenderChar() const;

	virtual void SetRenderChar(char _Ch);

	inline void SetPos(const int2& _Pos)
	{
		Pos = _Pos;
	}

	inline void AddPos(const int2& _Dir)
	{
		Pos += _Dir;
	}
	inline void SetScale(const int _Scale)
	{
		Scale = _Scale;
	}
	//inline void SetBufferSize(const int )

	template<typename EnumType>
	ConsoleObject* Collision(EnumType _UpdateOrder)
	{
		return Collision(static_cast<int>(_UpdateOrder));
	}

	// 나랑 충돌한 오브젝트
	ConsoleObject* Collision(int _UpdateOrder);

protected:

private:

	int2 Pos = { 0, 0 };
	int Scale = 1;
	char RenderChar = '@';
};


