#pragma once
#include <iostream>

namespace engine_core
{
	template<typename ...Args>
	void log(Args && ...args)
	{
		(std::cout << ... << args);
		std::cout << std::endl;
	}
}