#include <iostream>
#include <ConsoleEngine/EngineDebug.h>

class IntArray
{
    // private: 디폴트 접근제한 지정자
public:
    // 디폴트 생성자
    IntArray(int _Size)
    {
        ReSize(_Size);
    }

    // 디폴트 복사 생성자
    IntArray(const IntArray& _Other)
    {
        Copy(_Other);

        //NumValue = _Other.NumValue;
        //ArrPtr = _Other.ArrPtr;
    }
    // 디폴트 소멸자
    ~IntArray()
    {
        Release();
    }
    // 디폴트 대입연산자
    void operator=(const IntArray& _Other)
    {
        // 쉘로우 카피라고 부릅니다.
        // 이걸 얕은 복사라고 합니다.
        // 깊은 복사가 더 좋은 복사
        // 멍청한 일이 발생하는 경우가 있는데.
        // 얕은 복사 => 나빠 <= 아니다.
        // 참조만 복사하는 복사를 얕은 복사라고 합니다.
        // ArrPtr = _Other.ArrPtr;
        Copy(_Other);
    }

    int& operator[](int _Count)
    {
        return ArrPtr[_Count];
    }

    int Num()
    {
        return NumValue;
    }

    void Copy(const IntArray& _Other)
    {
        NumValue = _Other.NumValue;

        // 깊은 복사를 해줘야 합니다.
        ReSize(NumValue);
        for (int i = 0; i < NumValue; i++)
        {
            ArrPtr[i] = _Other.ArrPtr[i];
        }
    }

    void ReSize(int _Size)
    {
        if (0 >= _Size)
        {
            MsgBoxAssert("배열의 크기가 0일수 없습니다");
        }

        NumValue = _Size;

        if (nullptr != ArrPtr)
        {
            Release();
        }

        ArrPtr = new int[_Size];
        for (int i = 0; i < _Size/2; i++)
        {
            ArrPtr[i] = i;
        }
    }

    void Release()
    {
        if (nullptr != ArrPtr)
        {
            delete[] ArrPtr;
            ArrPtr = nullptr;
        }
    }

private:
    int NumValue = 0;
    int* ArrPtr = nullptr;
};


int main()
{
    LeckCheck;
    IntArray NewArray = IntArray(5);

    for (int i = 0; i < NewArray.Num(); i++)
    {
        NewArray[i] = i;
    }
    
    NewArray.ReSize(10);

    for (size_t i = 0; i < NewArray.Num(); i++)
    {
        std::cout << NewArray[i] << std::endl;
    }
    
}
