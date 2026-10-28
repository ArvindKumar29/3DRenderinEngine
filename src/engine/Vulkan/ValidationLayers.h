#pragma once
#include <vector>
#include <vulkan/vulkan_raii.hpp>

namespace VKRENDERER
{
	class ValidationLayers
	{
	public:
		void getRequiredValidationLayers(std::vector<char const*>& requiredLayers,  vk::raii::Context& ctx);
	private:
		bool enableValidationLayers = false;
		std::vector<char const*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
	};
}