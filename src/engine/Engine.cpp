#include "Engine.h"


namespace VKRENDERER
{
	Engine::~Engine()
	{
		
		device.logicalDevice.waitIdle();

		cmdPool.cmdBuffer = nullptr;
		cmdPool.cmdPool = nullptr;

		pipeline.imageAvailableSemaphores = nullptr;
		pipeline.renderFinishedSemaphore = nullptr;
		pipeline.renderFence = nullptr;

		pipeline.graphicsPipeline = nullptr;
		pipeline.graphicsPipeLineLayout = nullptr;

		window.swapChainImageViews.clear();
		window.swapChain = nullptr;

		device.graphicsQueue = nullptr;
		device.logicalDevice = nullptr;
		device.physicalDevice = nullptr;

		vulkanInstance.instance = nullptr;

		if (m_window)
		{
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}
		glfwTerminate();
	}

	void Engine::init()
	{
		// Creating Window
		uint32_t width = 1920, height = 1080;
		const char* title = "Rendering Engine";
		//spdlog::info("Initializing the rendering engine...");
		m_window = window.initWindow(width, height, title);
		//spdlog::info("GLFW Window Created ... {}, {}, {}", width, height, title);

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

		pipeline.createGraphicsPipeline(device.logicalDevice, window.swapChainSurfaceFormat.format);
		m_GraphicsPipeline = &pipeline.graphicsPipeline;

		cmdPool.createCommandPool(device.logicalDevice, device.graphicsQueueIndex);
		cmdPool.creatCommandBuffer(device.logicalDevice);
		//vk::ImageView imageView = window.swapChainImageViews[0];
		//cmdPool.recordCommandBuffer(device.logicalDevice, imageView, window.swapChainExtent, *m_GraphicsPipeline);
		m_cmdBuffer = &cmdPool.cmdBuffer;
		m_cmdPool = &cmdPool.cmdPool;
		
		pipeline.createSyncObjects(device.logicalDevice);

		spdlog::info("Rendering engine initialized successfully with window, instance, context, surface, Graphics Queue, Image views and Physical and Logical Devices and swapchain...");
	}
	

	void Engine::run()
	{
		init();
		while (!glfwWindowShouldClose(m_window)) 
		{
			glfwPollEvents();
			renderFrame();
		}

		device.logicalDevice.waitIdle();

		window.swapChainImageViews.clear();
		window.swapChain = nullptr;
	}

	void Engine::renderFrame()
	{
		device.logicalDevice.waitForFences(*pipeline.renderFence, vk::True, UINT64_MAX);

		auto [result, imageIndex] = window.swapChain.acquireNextImage(UINT64_MAX, *pipeline.imageAvailableSemaphores, nullptr);

		device.logicalDevice.resetFences(*pipeline.renderFence);

		cmdPool.cmdBuffer.reset();
		vk::CommandBufferBeginInfo beginInfo{};
		cmdPool.cmdBuffer.begin(beginInfo);

		window.transitionImageLayout(cmdPool.cmdBuffer, imageIndex, vk::ImageLayout::eUndefined, vk::ImageLayout::eAttachmentOptimal, vk::AccessFlags2(), vk::AccessFlagBits2::eColorAttachmentWrite, vk::PipelineStageFlagBits2::eTopOfPipe, vk::PipelineStageFlagBits2::eColorAttachmentOutput);
		cmdPool.recordCommandBuffer(device.logicalDevice, window.swapChainImageViews[imageIndex], window.swapChainExtent, pipeline.graphicsPipeline);
		window.transitionImageLayout(cmdPool.cmdBuffer, imageIndex, vk::ImageLayout::eColorAttachmentOptimal, vk::ImageLayout::ePresentSrcKHR, vk::AccessFlagBits2::eColorAttachmentWrite, vk::AccessFlags2(), vk::PipelineStageFlagBits2::eColorAttachmentOutput, vk::PipelineStageFlagBits2::eBottomOfPipe);

		cmdPool.cmdBuffer.end();

		vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };

		vk::SubmitInfo submitInfo = vk::SubmitInfo()
			.setWaitSemaphores(*pipeline.imageAvailableSemaphores)
			.setWaitDstStageMask(waitStages)
			.setCommandBuffers(*cmdPool.cmdBuffer)
			.setSignalSemaphores(*pipeline.renderFinishedSemaphore);
		device.graphicsQueue.submit(submitInfo, *pipeline.renderFence);

		vk::PresentInfoKHR presentInfo = vk::PresentInfoKHR()
			.setWaitSemaphores(*pipeline.renderFinishedSemaphore)
			.setSwapchains(*window.swapChain)
			.setImageIndices(imageIndex);
		auto presentResult = device.graphicsQueue.presentKHR(presentInfo);
	}
}