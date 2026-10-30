#include "CommandPool.h"

namespace VKRENDERER
{
	void CommandPool::createCommandPool(vk::raii::Device& ld, uint32_t queueIndex)
	{
		vk::CommandPoolCreateInfo poolInfo = vk::CommandPoolCreateInfo()
			.setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer)
			.setQueueFamilyIndex(queueIndex);
		cmdPool = vk::raii::CommandPool(ld, poolInfo);
		//spdlog::info("Command Pool Created!!!");
	}

	void CommandPool::creatCommandBuffer(vk::raii::Device& ld)
	{
		vk::CommandBufferAllocateInfo  allocInfo = vk::CommandBufferAllocateInfo()
			.setCommandPool(cmdPool)
			.setLevel(vk::CommandBufferLevel::ePrimary)
			.setCommandBufferCount(1);
		cmdBuffer = std::move(vk::raii::CommandBuffers(ld, allocInfo).front());
		//spdlog::info("Command Buffer Created!!!");
	}

	void CommandPool::recordCommandBuffer(vk::raii::Device& ld, vk::ImageView imageView, vk::Extent2D extent, vk::raii::Pipeline& pipeline)
	{
		// Starting command buffer recording
		//vk::CommandBufferBeginInfo beginInfo{};
		//cmdBuffer.begin(beginInfo);

		// Clear screen and set clear color
		vk::ClearValue clearColor;
		clearColor.color = vk::ClearColorValue(std::array<float, 4>{0.05f, 0.05f, 0.05f, 1.0f});

		// Setting up dynamic rendering
		vk::RenderingAttachmentInfo colorAttachment = vk::RenderingAttachmentInfo()
			.setImageView(imageView)
			.setImageLayout(vk::ImageLayout::eColorAttachmentOptimal)
			.setLoadOp(vk::AttachmentLoadOp::eClear)
			.setStoreOp(vk::AttachmentStoreOp::eStore)
			.setClearValue(clearColor);

		vk::RenderingInfo renderingInfo = vk::RenderingInfo()
			.setRenderArea(vk::Rect2D(vk::Offset2D(0, 0), extent))
			.setLayerCount(1)
			.setColorAttachments(colorAttachment);

		cmdBuffer.beginRendering(renderingInfo);
		cmdBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, *pipeline);
	
		// Setting viewport and Scissors
		vk::Viewport viewport(0.0f, 0.0f, static_cast<float>(extent.width), static_cast<float>(extent.height), 0.0f, 1.0f);
		cmdBuffer.setViewport(0, viewport);
		vk::Rect2D scissor(vk::Offset2D(0, 0), extent);
		cmdBuffer.setScissor(0, scissor);
		
		// Final draw command
		cmdBuffer.draw(3, 1, 0, 0);

		cmdBuffer.endRendering();
		//cmdBuffer.end();

	}
}