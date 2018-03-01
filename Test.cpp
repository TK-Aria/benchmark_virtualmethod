// Test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <chrono>
#include <stddef.h>
#include <functional>

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


#ifdef _CustomMemoryAlloc_

#elseifdef _CustomMemoryAlloc2_

#else // _defaultMemoryAlloc_

// default allocator
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
//#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif // MemoryAlloc_

namespace RewriteFramework
{

	namespace Utility {
	
		template<class X>inline X* _RewMemoryAlloc(void){
			#ifdef _CustomMemoryAlloc_

			#elseifdef _CustomMemoryAlloc2_

			#else // _defaultMemoryAlloc_
				return new X;
			#endif // MemoryAlloc_
		}

		template<class X>inline X* _RewMemoryAllocArray(unsigned int size = 1) {
			#ifdef _CustomMemoryAlloc_

			#elseifdef _CustomMemoryAlloc2_

			#else // _defaultMemoryAlloc_
				return new X[size];
			#endif // MemoryAlloc_
		}

		#define ReAlloc(type) (RewriteFramework::Utility::_RewMemoryAlloc<type>())
		#define ReAllocArray(type,size) (RewriteFramework::Utility::_RewMemoryAlloc<type>(size))

	};

};

namespace Debug {

	template<class X = std::chrono::microseconds>inline double ProfileMethod(std::function<void(void)> pFunc) {

		auto start = std::chrono::system_clock::now();
		pFunc();
		auto end = std::chrono::system_clock::now();

		return std::chrono::duration_cast<X>(end - start).count();
	}

	template<class X,class Y = std::chrono::microseconds>inline double ProfileMethod(X* instance, void (X::*pFunc)(void)) {

		auto start = std::chrono::system_clock::now();
		(instance->*pFunc)();
		auto end = std::chrono::system_clock::now();

		return std::chrono::duration_cast<Y>(end - start).count();
	}

	/*template<class X,class Y>inline double ProfileMethod( X (*pFunc)(Y) ){

	auto start = std::chrono::system_clock::now();
	pFunc();
	auto end = std::chrono::system_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	}*/

};

class AllocatorObjectInterface
{
protected:
	AllocatorObjectInterface() {}

};

// Class AllocatorObject Using AllocatorObject
template<class X> class AllocatorObject : public AllocatorObjectInterface
{
protected:
	AllocatorObject() {}						// AllocatorObject Constructor
public:
	//static X& Create(char* c = __FILE__, int s = __LINE__) { auto instance = new X(_NORMAL_BLOCK,c,s); return *instance; }	// AllocatorObject Create Instance Class
	static X& Create(char* c = __FILE__, int s = __LINE__) { auto instance = new X; return *instance; }	// AllocatorObject Create Instance Class
	~AllocatorObject() {}					// AllocatorObject Destructor

	inline X& AllocatorObject<X>::operator + () const { return *objectInstance; }

private:

	// Member Variable
	X* objectInstance;

};

struct Test
{
	int n;
};

//void* MemoryArrocation()

/*
template<class X> _memory_allocation_(int size = 1)
{
	
}
*/

class VirtualTest
{
public:
	virtual void Execute() {};
};

class VirtualTestInheritance : public VirtualTest
{
public:
	virtual void Execute(void) override;
};


void VirtualTestInheritance::Execute(void)
{
	int sum = 1 + 2 + 3;
}



class VirtualTestInheritance2 : public VirtualTest
{
public:
	virtual void Execute(void) override {
		int sum = 1 + 2 + 3;
	}
};

class VirtualTestInheritance3 : public VirtualTest
{
public:
	virtual void Execute(void) override {
		int sum = 1 + 2 + 3;
	}
};

class FakeVirtualTest
{
public:
	FakeVirtualTest(std::function<void(void)> method)
		: virtualMethod(method){}
	inline void Execute() { virtualMethod(); }
protected:
	std::function<void(void)> virtualMethod;

};

class FakeVirtualTestPointer
{
public:
	FakeVirtualTestPointer(void(*method)(void))
		: virtualMethod(method) {}
	inline void Execute() { virtualMethod(); }
protected:
	void(*virtualMethod)(void);

};

inline void testMethod()
{

	int sum = 1 + 2 + 3;

}

int main()
{

	Test test;
	offsetof(Test,n);

	auto king = ReAlloc(Test);

	auto sample = AllocatorObject<Test>::Create();

	double test1, test2, test3, test4, test5,test6;

	VirtualTestInheritance vi;
	FakeVirtualTest vi2([](){
		int sum = 1 + 2 + 3;
	});

	test1 = Debug::ProfileMethod([&]() {
		
		for (int index = 0; index < 10000000; index++) {
			vi.Execute();
		}
	});

	auto testLambda = []() {int sum = 1 + 2 + 3; };
	test2 = Debug::ProfileMethod([&]() {
		
		for (int index = 0; index < 10000000; index++) {
			//vi.Execute();
			testLambda();
		}
	});

	test3 = Debug::ProfileMethod([&]() {

		for (int index = 0; index < 10000000; index++) {
			vi2.Execute();
		}
	});

	test4 = Debug::ProfileMethod([&]() {

		for (int index = 0; index < 10000000; index++) {
			testMethod();
		}
	});

	std::function<void(void)> testMethod2 = []() { int sum = 1 + 2 + 3; };
	test5 = Debug::ProfileMethod([&]() {

		for (int index = 0; index < 10000000; index++) {
			testMethod2();
		}
	});


	FakeVirtualTestPointer vi3([]() {
		int sum = 1 + 2 + 3;
	});
	test6 = Debug::ProfileMethod([&]() {

		for (int index = 0; index < 10000000; index++) {
			vi3.Execute();
		}
	});

	printf(" 1 仮想関数 : %f \n 2 ラムダ式 : %f \n 3 疑似仮想 : %f \n 4 関数 : %f \n 5 stdfunc : %f \n 6 疑似仮想ポインタ : %f",test1,test2,test3,test4,test5,test6);
	getchar();

    return 0;
}

