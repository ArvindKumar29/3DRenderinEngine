#pragma once
//#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#include <math.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan_raii.hpp>
#include <spdlog/spdlog.h>

namespace VKRENDERER
{
	class Window
	{
		vk::SurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<vk::SurfaceFormatKHR> const &availableFormats);
		vk::PresentModeKHR choosePresentMode(std::vector<vk::PresentModeKHR> const& availablePresentModes);
		vk::Extent2D chooseSwapExtent(vk::SurfaceCapabilitiesKHR const &capabilities, GLFWwindow* window);
		uint32_t chooseSwapMinImageCount(vk::SurfaceCapabilitiesKHR const &capabilities);

		std::vector<vk::Image>           swapChainImages;
		vk::SurfaceFormatKHR             swapChainSurfaceFormat;
		vk::Extent2D                     swapChainExtent;
		std::vector<vk::raii::ImageView> swapChainImageViews;

	public:
		GLFWwindow* initWindow(uint32_t width, uint32_t height, const char* title);
		void initSurface(vk::raii::Instance& instance, GLFWwindow* window);
		void createSwapChain(vk::raii::PhysicalDevice& pd, vk::raii::Device& ld);
		void createImageViews(vk::raii::Device& ld);
	
		GLFWwindow* window;
		vk::raii::SurfaceKHR surface = nullptr;
		vk::raii::SwapchainKHR swapChain = nullptr;
	};
}
