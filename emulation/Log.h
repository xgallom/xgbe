//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_LOG_H
#define XGBE_LOG_H

#include <iostream>
#include "Arguments.h"

namespace Log {
	template<typename ... Args>
	inline void info(Args ... args) noexcept
	{
		if(ApplicationConfig.logDebug)
			(std::cout << ... << args);
	}

	template<typename ... Args>
	inline void error(Args ... args) noexcept
	{
		(std::cerr << ... << args);
	}
}

#endif //XGBE_LOG_H
