#pragma once

#include <cassert>
#include <windows.h>

#pragma warning( disable : 4312 )
#pragma warning( disable : 4311 )

// 객체를 singleton으로 만들어주는 클래스

template <typename T>class Singleton
{
private:
	static T* ms_Singleton;
protected:
public:
	Singleton()
	{
		assert(!ms_Singleton);
		int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
		ms_Singleton = (T*)((int)this + offset);
	}
	~Singleton()
	{
		assert(ms_Singleton);
		ms_Singleton = NULL;
	}
	static T* GetSingleton() {return T::ms_Singleton;}
	static void SetSingleton(T* pSingleton) { ms_Singleton = pSingleton;}
};

template <typename T> T* Singleton<T>::ms_Singleton = 0;