#include "Instance.h"

namespace VKRENDERER
{
	void Instance::init(vk::raii::Context& ctx)
	{
		//spdlog::info("Creating Vulkan Instance for the Renderer!!!");
		createInstance(ctx);
	}

	void Instance::createInstance(vk::raii::Context& ctx)
	{
		//spdlog::info("Creating Application Info struct for the instance!!!");
		vk::ApplicationInfo appInfo = vk::ApplicationInfo()
			.setPApplicationName("Vulkan Renderer")
			.setApplicationVersion(VK_MAKE_VERSION(1, 0, 0))
			.setPEngineName("Rendering Engine")
			.setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
			.setApiVersion(vk::ApiVersion14);

		uint32_t glfwExtensionCount = 0;
		auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		auto extensionProperties = ctx.enumerateInstanceExtensionProperties();

		for (uint32_t i = 0; i < glfwExtensionCount; ++i)
		{
			if (std::ranges::none_of(extensionProperties,
				[glfwExtension = glfwExtensions[i]](auto const& extensionProperty)
				{ return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }))
			{
				throw std::runtime_error("Required GLFW extension not supported: " + std::string(glfwExtensions[i]));
			}
		}

		// Get the required Validation Layers
		//spdlog::info("Getting required validation Layers!!!");
		validationLayers.getRequiredValidationLayers(requiredLayers, ctx);

		// Get the required Instance Extensions 
		//spdlog::info("Getting required Instance Extensions!!!");
		auto requiredExtensions = getRequiredExtensions();

		//auto extensionProperties = ctx.enumerateInstanceExtensionProperties();
		auto unsupportedPropertyIt =
			std::ranges::find_if(requiredExtensions,
				[&extensionProperties](auto const& requiredExtension) {
					return std::ranges::none_of(extensionProperties,
						[requiredExtension](auto const& extensionProperty) { return strcmp(extensionProperty.extensionName, requiredExtension) == 0; });
				});
		if (unsupportedPropertyIt != requiredExtensions.end())
		{
			throw std::runtime_error("Required extension not supported: " + std::string(*unsupportedPropertyIt));
		}

		//spdlog::info("Creating create info struct for instances!!!");
		vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo()
			.setPApplicationInfo(&appInfo)
			.setEnabledLayerCount(static_cast<uint32_t>(requiredLayers.size()))
			.setPpEnabledLayerNames(requiredLayers.data())
			.setEnabledExtensionCount(glfwExtensionCount)
			.setPpEnabledExtensionNames(glfwExtensions);

		instance = vk::raii::Instance(ctx, createInfo);
		//spdlog::info("Vulkan Instance created Successfully!!!");

	}

	std::vector<const char*> Instance::getRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		return extensions;
	}
}