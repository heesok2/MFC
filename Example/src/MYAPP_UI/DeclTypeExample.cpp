#include "pch.h"
#include "DeclTypeExample.h"

#include "..\MYENG_LIB\StringLib.h"

inline void PrintMsg(std::string str)
{
	auto cstr = mylib::CStringLib::STR2CSTR(str);
	TRACE(_T("%s\n"), cstr.GetBuffer());
};

template <typename T>
void func(T p)
{
	std::string typeT = typeid(T).name();
	std::string typeP = typeid(p).name();
	PrintMsg(typeT);
	PrintMsg(typeP);
};

template <typename T>
void func_const_ref(const T& p)
{
	std::string typeT = typeid(T).name();
	std::string typeP = typeid(p).name();
	PrintMsg(typeT);
	PrintMsg(typeP);
};

template <typename T>
void func_ref(T& p)
{
	std::string typeT = typeid(T).name();
	std::string typeP = typeid(p).name();
	PrintMsg(typeT);
	PrintMsg(typeP);
};

template <typename T>
void func_ptr(T* p)
{
	std::string typeT = typeid(T).name();
	std::string typeP = typeid(p).name();
	PrintMsg(typeT);
	PrintMsg(typeP);
};

template <typename T>
void func_rval(T&& p)
{
	std::string typeT = typeid(T).name();
	std::string typeP = typeid(p).name();
	PrintMsg(typeT);
	PrintMsg(typeP);
};

template <typename T, std::size_t N>
constexpr void func_array_num(const T(&)[N]) noexcept
{
	std::string str = std::to_string(N);
	PrintMsg(str);
}

void func_exam(int, double)
{

}

template <typename T>
void func_init_list(std::initializer_list<T> p)
{
	std::string typeT = typeid(T).name();
	std::string typeP = typeid(p).name();
	PrintMsg(typeT);
	PrintMsg(typeP);
}

void template_decltype()
{
	// type deduction 

	int x = 0;
	const int cx = x;
	const int& rx = x;
	const int* px = &x;
	const TCHAR* const ptr = _T("TCHAR");
	const TCHAR arr[] = _T("TCHAR");
	const TCHAR* ptr_arr = arr;

	func_const_ref(x); // template(int), parameter(const int&)
	func_const_ref(cx); // template(int), parameter(const int&)
	func_const_ref(rx); // template(int), parameter(const int&)

	func_ref(x); // template(int), parameter(int&)
	func_ref(cx); // template(const int), parameter(const int&)
	func_ref(rx); // (const int), parameter(const int&)

	func_ptr(&x); // template(int), parameter(int*)
	func_ptr(px); // template(const int), parameter(const int*)

	func_rval(x); // template(int&), parameter(int&)
	func_rval(cx); // template(const int&), parameter(const int&)
	func_rval(rx); // template(const int&), parameter(const int&)
	func_rval(27); // template(int), parameter(int&&)

	func(x); // template(int), parameter(int)
	func(cx); // template(int), parameter(int)
	func(rx); // template(int), parameter(int)
	func(ptr); // template(const TCHAR*), parameter(const TCHAR*)
	func(arr); // template(const TCHAR*), parameter(const TCHAR*)
	func(ptr_arr); // template(const TCHAR*), parameter(const TCHAR*)
	func_array_num(arr);

	func(func_exam); // template(void (*)(int, double)), parameter(void (*)(int, double))
	func_ref(func_exam); // template(void (*)(int, double)), parameter(void &)(int, double))

}

void auto_decltype()
{
	auto x = 27; // int 
	const auto cx = x; // const int 
	const auto& rx = x; // const int&
	const TCHAR ptr[] = _T("TCHAR");

	auto&& rval_lval = x; // int&
	auto&& rval_clval = cx; // const int&
	auto&& rval_rval = 27; // int&&

	auto arr = ptr; // TCHAR*
	auto& arr_ref = ptr; // TCHAR (*)[6]

	auto fp = func_exam; // void (*)(int, double)
	auto& fp_ref = func_exam; // void (&)(int, double)
	
	func(x);
	func(cx);
	func(rx);
	func(ptr);
	func(rval_lval); 
	func(rval_clval);
	func(rval_rval);
	func(arr);
	func(arr_ref);
	func(fp); 
	func(fp_ref);

	func_init_list({1, 2, 3});
}