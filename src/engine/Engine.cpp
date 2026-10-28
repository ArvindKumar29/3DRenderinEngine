#include "Engine.h"


namespace VKRENDERER
{
	void Engine::init()
	{
		// Creating Window
		uint32_t width = 1920, height = 1080;
		const char* title = "Rendering Engine";
		spdlog::info("Initializing the rendering engine...");
		m_window = window.initWindow(width, height, title);
		spdlog::info("GLFW Window Created ...");

		// Creating Vulkan Instance and Setting up Validation Layers
		vulkanInstance.init(ctx);
		spdlog::info("Vulkan Instance for rendering engine initialized...");
		
		// Creating surface for rendering
		window.initSurface(vulkanInstance.instance, m_window);
		m_Surface = &window.surface;
		spdlog::info("Rendering engine initialized successfully with window, instance, context and surface.");

		// choosing appropriate physical device...
		device.getPhysicalDevice(vulkanInstance.instance, window.surface, deviceExtensions);
		pd = device.physicalDevice;
		spdlog::info("Physical Device selection done!!!");
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