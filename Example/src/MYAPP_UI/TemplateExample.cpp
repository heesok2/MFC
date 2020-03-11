#include "pch.h"
#include "TemplateExample.h"
#include <mutex>
#include <list>
#include <tuple>

#pragma warning(disable:4189)

int FuncInt(std::shared_ptr<CTemplateExample>)
{
	return 0;
}

double FuncDouble(std::unique_ptr<CTemplateExample>)
{
	return 0.0;
}

bool FuncBool(CTemplateExample *)
{
	return false;
}

template <typename _func, typename _mutex, typename _pointer>
auto LockAndCall_vc11(_func func, _mutex& mu, _pointer pt)
-> decltype(func(pt))
{
	using MuGuard = std::lock_guard<_mutex>;
	MuGuard gd(mu);
	return func(pt);
};

template <typename _func, typename _mutex, typename _pointer>
decltype(auto) LockAndCall_vc14(_func func, _mutex& mu, _pointer pt)
{
	using MuGuard = std::lock_guard<_mutex>;
	MuGuard gd(mu);
	return func(pt);
};

void TemplateExample()
{
	std::mutex muInt, muDouble, muBool;

	using MuGuard = std::lock_guard<std::mutex>;
	{
		MuGuard gd(muInt);
		auto result = FuncInt(0);
	}

	{
		MuGuard gd(muDouble);
		auto result = FuncDouble(NULL);
	}

	{
		MuGuard gd(muBool);
		auto result = FuncBool(nullptr);
	}

	{
		// LockAndCall_vc11(FuncInt, muInt, 0); -> Error 
		// LockAndCall_vc11(FuncDouble, muInt, NULL); -> Error 
		LockAndCall_vc11(FuncBool, muInt, nullptr);
	}

	{
		// LockAndCall_vc14(FuncInt, muInt, 0); -> Error 
		// LockAndCall_vc14(FuncDouble, muInt, NULL); -> Error 
		LockAndCall_vc14(FuncBool, muInt, nullptr);
	}

	{
		typedef void(*fpt_def)(int);
		using fpt_using = void(*)(int);
	}
}

template <typename T>
using alias_list = std::list<T, CAliasTemplate<T>>;

template <typename T>
struct alias_t
{
	typedef std::list<T, CAliasTemplate<T>> type;
};

template <typename T>
class CAliasClient
{
	alias_list<T> alias_name;
	typename alias_t<T>::type alias_struct;
};

template <typename T>
using my_remove_const_t = typename std::remove_const<T>::type;

template <typename T>
using my_remove_reference_t = typename std::remove_reference<T>::type;

enum e_tuple_index
{
	e_tuple_name
	, e_tuple_email
	, e_tuple_req
};

enum class ec_tuple_index
{
	ec_tuple_name
	, ec_tuple_email
	, ec_tuple_req
};

template <typename E>
constexpr typename std::underlying_type<E>::type 
toUType_vc11(E enumerator) noexcept
{
	return static_cast<typename std::underlying_type<E>::type>(enumerator);
}

template <typename E>
constexpr std::underlying_type_t<E>
toUType_vc14(E enumerator) noexcept
{
	return static_cast<std::underlying_type_t<E>>(enumerator);
}

template <typename E>
constexpr auto toUType_vc14_auto(E enumerator) noexcept
{
	return static_cast<std::underlying_type_t<E>>(enumerator);
}

void AliasExample()
{
	enum enum_alias
	{
		enum_alias_color = 0
		, enum_alias_normal
		, enum_alias_tanget
	};

	enum class e_alias
	{
		e_alias_color = 0
		, e_alias_normal
		, e_alias_tangent
	};

	// auto enum_alias_color = 0; -> Error
	auto e_alias_color = 0;

	e_alias alias_type = e_alias::e_alias_color;


	using user_info = std::tuple<std::string, std::string, std::size_t>;
	user_info uinfo;
	
	auto val = std::get<1>(uinfo);
	auto val_e = std::get<e_tuple_email>(uinfo);
	auto val_ec = std::get<static_cast<std::size_t>(ec_tuple_index::ec_tuple_email)>(uinfo);

	auto val_vc11 = std::get<toUType_vc11(e_tuple_email)>(uinfo);
	auto val_vc14 = std::get<toUType_vc14(ec_tuple_index::ec_tuple_email)>(uinfo);
	auto val_vc14_auto = std::get<toUType_vc14_auto(ec_tuple_index::ec_tuple_email)>(uinfo);
}

