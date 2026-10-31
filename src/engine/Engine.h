#pragma once
#include "vulkan/vlk.h"

namespace VKRENDERER
{
	class Engine
	{
		vlk vulkanContext;
	public:
		Engine();
		~Engine();
	};
}