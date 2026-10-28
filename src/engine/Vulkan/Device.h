#pragma once
#include <vulkan/vulkan_raii.hpp>
//#include "engine/Engine.h"

namespace VKRENDERER
{
	class Device
	{
		bool isDeviceSuitable(vk::raii::PhysicalDevice& const pd, vk::raii::SurfaceKHR& surface, std::vector<char const*> requiredDeviceExtensions);
	public:
		void getPhysicalDevice(vk::raii::Instance& instance, vk::raii::SurfaceKHR& surface, std::vector<char const*> requiredDeviceExtensions);
		
		vk::raii::PhysicalDevice physicalDevice = nullptr;
	
	
	private:
	};
}