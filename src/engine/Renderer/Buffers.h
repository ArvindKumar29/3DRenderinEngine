#pragma once
#include "Vertex.h"
#include <vulkan/vulkan_raii.hpp>

namespace VKRENDERER
{
	struct vertexBuffer
	{
		
		std::vector<Vertex> VB = {
			{ { -0.5f, 0.5f, 0.0f },{ 1.0f, 0.0f, 0.0f } }, 
			{ { 0.5f,  0.5f, 0.0f },{ 0.0f, 1.0f, 0.0f } }, 
			{ { -0.5f, -0.5f, 0.0f },{ 0.0f, 0.0f, 1.0f } },
			{ { 0.5f, -0.5f, 0.0f },{ 1.0f, 0.0f, 0.0f } }
		};

		
		vk::raii::Buffer buffer = nullptr;
		vk::raii::DeviceMemory bufferMemory = nullptr;

		void createVertexBuffer(vk::raii::Device& ld, vk::raii::PhysicalDevice& pd)
		{
			vk::DeviceSize bufferSize = sizeof(VB[0]) * VB.size();

			vk::BufferCreateInfo bufferInfo = vk::BufferCreateInfo()
				.setSize(bufferSize)
				.setUsage(vk::BufferUsageFlagBits::eVertexBuffer)
				.setSharingMode(vk::SharingMode::eExclusive);
			buffer = vk::raii::Buffer(ld, bufferInfo);

			vk::MemoryRequirements memReq = buffer.getMemoryRequirements();
			vk::PhysicalDeviceMemoryProperties memProp = pd.getMemoryProperties();
			vk::MemoryPropertyFlags requiredProps = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;

			uint32_t memoryTypeIndex = 0;
			for (uint32_t i = 0; i < memProp.memoryTypeCount; i++)
			{
				if ((memReq.memoryTypeBits & (1 << i)) && ((memProp.memoryTypes[i].propertyFlags & requiredProps) == requiredProps))
				{
					memoryTypeIndex = i;
					break;
				}
			}

			vk::MemoryAllocateInfo allocInfo = vk::MemoryAllocateInfo()
				.setAllocationSize(memReq.size)
				.setMemoryTypeIndex(memoryTypeIndex);

			bufferMemory = vk::raii::DeviceMemory(ld, allocInfo);
			buffer.bindMemory(*bufferMemory, 0);

			void* data = bufferMemory.mapMemory(0, bufferSize);
			memcpy(data, VB.data(), static_cast<size_t>(bufferSize));
			bufferMemory.unmapMemory();
		}
	};

	struct indexBuffer
	{
		std::vector<uint32_t> IB = {0, 1, 2, 2, 1, 3};
		vk::raii::Buffer buffer = nullptr;
		vk::raii::DeviceMemory bufferMemory = nullptr;

		void createIndexBuffer(vk::raii::Device& ld, vk::raii::PhysicalDevice& pd)
		{
			vk::DeviceSize bufferSize = sizeof(IB[0]) * IB.size();

			vk::BufferCreateInfo bufferInfo = vk::BufferCreateInfo()
				.setSize(bufferSize)
				.setUsage(vk::BufferUsageFlagBits::eIndexBuffer)
				.setSharingMode(vk::SharingMode::eExclusive);
			buffer = vk::raii::Buffer(ld, bufferInfo);

			vk::MemoryRequirements memReq = buffer.getMemoryRequirements();
			vk::PhysicalDeviceMemoryProperties memProp = pd.getMemoryProperties();
			vk::MemoryPropertyFlags requiredProps = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;

			uint32_t memoryTypeIndex = 0;
			for (uint32_t i = 0; i < memProp.memoryTypeCount; i++)
			{
				if ((memReq.memoryTypeBits & (1 << i)) && ((memProp.memoryTypes[i].propertyFlags & requiredProps) == requiredProps))
				{
					memoryTypeIndex = i;
					break;
				}
			}

			vk::MemoryAllocateInfo allocInfo = vk::MemoryAllocateInfo()
				.setAllocationSize(memReq.size)
				.setMemoryTypeIndex(memoryTypeIndex);

			bufferMemory = vk::raii::DeviceMemory(ld, allocInfo);
			buffer.bindMemory(*bufferMemory, 0);

			void* data = bufferMemory.mapMemory(0, bufferSize);
			memcpy(data, IB.data(), static_cast<size_t>(bufferSize));
			bufferMemory.unmapMemory();
		}
	};
}