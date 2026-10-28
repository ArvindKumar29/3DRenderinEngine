#include "Window.h"

namespace VKRENDERER
{
	GLFWwindow* Window::initWindow(uint32_t width, uint32_t height, const char* title)
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		return glfwCreateWindow(width, height, title, nullptr, nullptr);
	}


	void Window::initSurface(vk::raii::Instance& instance, GLFWwindow* window)
	{
		VkSurfaceKHR _surface;
		if (glfwCreateWindowSurface(*instance, window, nullptr, &_surface) != 0)
		{
			throw std::runtime_error("Failed to create window surface!!!");
		}
		surface = vk::raii::SurfaceKHR(instance, _surface);
		spdlog::info("Window Surface is Created successfully");
	}
}