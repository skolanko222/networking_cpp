#pragma once
#include "NetBase.hpp"

namespace net
{
	template <typename T>
	struct header
	{
		uint32_t size = 0;
		
		T id{}; 
	};


}