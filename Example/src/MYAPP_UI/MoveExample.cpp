#include "pch.h"
#include "MoveExample.h"

class CMoveExample
{

};


template <typename T>
typename std::remove_reference<T>::type&&
move_vc11(T&& param)
{
	using ret_type = typename std::remove_reference<T>&&;
	return static_cast<ret_type>(param);
}

template <typename T>
decltype(auto)
move_vc14(T&& param)
{
	using ret_type = std::remove_reference_t<T>&&;
	return static_cast<ret_type>(param);
}

void MoveExample()
{
	auto&& move = move_vc11(CMoveExample());

	auto lambda_time_log = [](auto&& func, auto&&... args)
	{
		// log start

		std::forward<decltype(func)>(func)
			(std::forward<decltype(args)>(args)...);

		// log end 
	};
}
