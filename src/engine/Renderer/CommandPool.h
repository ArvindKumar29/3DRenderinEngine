#pragma once
#include <vulkan/vulkan_raii.hpp>
#include <spdlog/spdlog.h>

namespace VKRENDERER
{
	class CommandPool
	{
	public:
		vk::raii::CommandPool cmdPool = nullptr;
		vk::raii::CommandBuffer cmdBuffer = nullptr;

		void createCommandPool(vk::raii::Device& ld, uint32_t queueIndex);
		void creatCommandBuffer(vk::raii::Device& ld);
		void recordCommandBuffer(vk::raii::Device& ld, vk::ImageView imageView, vk::Extent2D extent, vk::raii::Pipeline& pipeline);
	};
}