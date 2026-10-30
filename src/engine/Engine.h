#pragma once
#include "Vulkan/Instance.h"
#include "Vulkan/ValidationLayers.h"
#include "Vulkan/Window.h"
#include "Vulkan/Device.h"
#include "vulkan/vulkan.hpp"
#include "Renderer/Pipeline.h"
#include "Renderer/CommandPool.h"
#include <spdlog/spdlog.h>

namespace VKRENDERER
{
	class Engine
	{
	public:
		void run();
		~Engine();
	
	private:
		void init();
		void renderFrame();

		// Vulkan Core
		GLFWwindow* m_window;
		vk::raii::Context ctx;
		vk::raii::SurfaceKHR* m_Surface = nullptr;
		vk::raii::SwapchainKHR* m_SwapChain = nullptr;
		vk::raii::PhysicalDevice pd = nullptr;
		vk::raii::Pipeline* m_GraphicsPipeline = nullptr;
		vk::raii::CommandPool* m_cmdPool = nullptr;
		vk::raii::CommandBuffer* m_cmdBuffer = nullptr;
		Window window;
		ValidationLayers validationLayers;
		Instance vulkanInstance;
		Device device;

		// Renderer Stuff
		Pipeline pipeline;
		CommandPool cmdPool;

		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
	};
}
