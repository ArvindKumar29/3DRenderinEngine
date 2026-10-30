#pragma once
#include <vulkan/vulkan_raii.hpp>
#include "ValidationLayers.h"
#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"

namespace VKRENDERER
{
	class Instance
	{
		void createInstance(vk::raii::Context& ctx);
	public:

		void init(vk::raii::Context& ctx);
		std::vector<char const*> getRequiredExtensions();
		vk::raii::Instance instance = nullptr;

	private:
		std::vector<char const*> requiredLayers;
		ValidationLayers validationLayers;
	};
}