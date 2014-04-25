#pragma once

#include <windows.h>

// 동적 할당한 포인터를 해제할 때 사용.
template<typename T>
void SafeDelete(T& pointer)
{
	if (pointer)
	{
		delete [] pointer;
		pointer = NULL;
	}
}

// 문자열을 복사할때 매번 dest 의 크기를 잡고 복사하기 싫어서 
// src 의 길이를 확인하고 알아서 dest에 메모리를 확보하고 복사.
template<typename Char>
void strAlloc(Char** dst, const Char* src)
{
	int len = 0;
	while (src[len++]);
	
	// 이미 dst 에 데이터가 있다면..
	if (*dst)
		// 지워주고.
		SafeDelete(*dst);

	// src 만큼 메모리 할당한 다음.
	*dst = new Char[len];
	len = 0;
	// 하나씩 복사...
	while ((*dst)[len++] = src[len]);
}

// 싱글톤 패턴을 템플릿으로 만든것.
// Cls의 기본생성자,기본소멸자는 protected 이하일테니...
// getReference 에서 생성가능하도록 하려면...
// 상속받은 클래스에서 반드시 singleton<Cls>를 friend 해야 한다.
template<typename Cls>
class singleton
{
protected :
	singleton(){}
	virtual ~singleton(){}

public :
	static Cls& getReference(void)
	{
		static Cls inst;
		return inst;
	}
};

template<typename ReturnType, typename Class, typename FunctionPointer>
class Callable
{
public :
	Callable(FunctionPointer a):func(a){}

	// argument 4
	template<typename Derived,
			typename Arg1, 
			typename Arg2, 
			typename Arg3, 
			typename Arg4>
	ReturnType operator ()(Derived* pObj, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4)
	{
		return (get_pointer(pObj)->*func)(a1, a2, a3, a4);
	}
	// argument 3
	template<typename Derived,
			typename Arg1, 
			typename Arg2, 
			typename Arg3>
	ReturnType operator ()(Derived* pObj, Arg1 a1, Arg2 a2, Arg3 a3)
	{
		return (get_pointer(pObj)->*func)(a1, a2, a3);
	}
	// argument 2
	template<typename Derived,
			typename Arg1, 
			typename Arg2>
	ReturnType operator ()(Derived* pObj, Arg1 a1, Arg2 a2)
	{
		return (get_pointer(pObj)->*func)(a1, a2);
	}
	// argument 1
	template<typename Derived,
			typename Arg1>
	ReturnType operator ()(Derived* pObj, Arg1 a1)
	{
		return (get_pointer(pObj)->*func)(a1);
	}
	// argument 0
	template<typename Derived>
	ReturnType operator ()(Derived* pObj)
	{
		return (get_pointer(pObj)->*func)();
	}

	template<typename Derived>
	Class* get_pointer(Derived* obj)
	{
		return dynamic_cast<Class*>(obj);
	}
private :
	FunctionPointer func;
};

// SelectObject API 사용시 반환타입을 형변환해야하는데
// 매번 하는것이 귀찮고, 에러 보는 것도 싫어서 작성.
template<typename T>
T Select(HDC hdc, T GDI_Object)
{
	return T(::SelectObject(hdc, GDI_Object));
}

// 16진수를 뜻하는 문자를 숫자로 변환하여 반환.
template<typename T>
int c2d(const T c)
{
	if (c >= '0' && c <= '9')
		return int(c-'0');
	else if (c >= 'a' && c <= 'f')
		return int(c-'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return int(c-'A' + 10);

	return 0;
}