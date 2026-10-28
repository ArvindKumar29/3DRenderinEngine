#pragma once
#include "Vulkan/Instance.h"
#include "Vulkan/ValidationLayers.h"
#include "Vulkan/Window.h"
#include "Vulkan/Device.h"
#include "vulkan/vulkan.hpp"
#include <spdlog/spdlog.h>

namespace VKRENDERER
{
	class Engine
	{
	public:
		void run();
		
	
	private:
		void init();

		GLFWwindow* m_window;
		vk::raii::Context ctx;
		vk::raii::SurfaceKHR* m_Surface = nullptr;
		vk::raii::PhysicalDevice pd = nullptr;
		Window window;
		ValidationLayers validationLayers;
		Instance vulkanInstance;
		Device device;

		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
	};
}
