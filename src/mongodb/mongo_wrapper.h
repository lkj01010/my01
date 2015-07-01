#pragma once
#include "common.h"

namespace my{
	class mongo_wrapper : public singleton<mongo_wrapper>
	{
	public:
		mongo_wrapper();
		~mongo_wrapper();
	};
}

