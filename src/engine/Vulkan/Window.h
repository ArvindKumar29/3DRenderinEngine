#pragma once
//#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan_raii.hpp>
#include <spdlog/spdlog.h>

namespace VKRENDERER
{
	class Window
	{
	public:
		GLFWwindow* initWindow(uint32_t width, uint32_t height, const char* title);
		void initSurface(vk::raii::Instance& instance, GLFWwindow* window);
	
		vk::raii::SurfaceKHR surface = nullptr;
	};
}
