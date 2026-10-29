#include "Engine.h"


namespace VKRENDERER
{
	void Engine::init()
	{
		// Creating Window
		uint32_t width = 1920, height = 1080;
		const char* title = "Rendering Engine";
		//spdlog::info("Initializing the rendering engine...");
		m_window = window.initWindow(width, height, title);
		spdlog::info("GLFW Window Created ... {}, {}, {}", width, height, title);

		// Creating Vulkan Instance and Setting up Validation Layers
		vulkanInstance.init(ctx);
		//spdlog::info("Vulkan Instance for rendering engine initialized...");
		
		// Creating surface for rendering
		window.initSurface(vulkanInstance.instance, m_window);
		m_Surface = &window.surface;

		// choosing appropriate physical device...
		device.getPhysicalDevice(vulkanInstance.instance, window.surface, deviceExtensions);
		pd = device.physicalDevice;
		vk::PhysicalDeviceProperties pdProperties = pd.getProperties();
		//spdlog::info("Physical Device selection done!!!", pdProperties.deviceName.data());
		spdlog::info("Selected Device Info:");
		spdlog::info("Name: {}", pdProperties.deviceName.data());
		spdlog::info("Type: {}", pdProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu);
		spdlog::info("Vulkan API Version: {}.{}.{}",
			VK_VERSION_MAJOR(pdProperties.apiVersion),
			VK_VERSION_MINOR(pdProperties.apiVersion),
			VK_VERSION_PATCH(pdProperties.apiVersion));

		//spdlog::info("Creating Logical Device...");
		device.createLogicalDevice(deviceExtensions);
		window.createSwapChain(device.physicalDevice, device.logicalDevice);
		m_SwapChain = &window.swapChain;
		//spdlog::info("Swapchain Created for the Engine...");

		window.createImageViews(device.logicalDevice);

		spdlog::info("Rendering engine initialized successfully with window, instance, context, surface, Graphics Queue, Image views and Physical and Logical Devices and swapchain...");
	}
	

	void Engine::run()
	{
		init();
		while (!glfwWindowShouldClose(m_window)) 
		{
			glfwPollEvents();
		}
	}
}