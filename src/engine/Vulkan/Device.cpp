#include "Device.h"

namespace VKRENDERER
{
	bool Device::isDeviceSuitable(vk::raii::PhysicalDevice& const pd, vk::raii::SurfaceKHR& surface, std::vector<char const*> requiredDeviceExtensions)
	{
		// Check support of vulkan 1.3 or above
		bool supportVulkan_1_3 = pd.getProperties().apiVersion >= VK_API_VERSION_1_3;

		// Check queue family support for graphics and present
		auto queueFamilies = pd.getQueueFamilyProperties();
		uint32_t qfpIndex = 0;
		bool supportGraphicsAndPresent = std::ranges::any_of(queueFamilies,
			[&pd, &surface, &qfpIndex](auto const& qfp) {
				bool const suitable = (qfp.queueFlags & vk::QueueFlagBits::eGraphics) && (pd.getSurfaceSupportKHR(qfpIndex, *surface));
				qfpIndex++;
				return suitable;
			});
		
		// Check for all the physical Devices Extensions availability
		auto availableDeviceExtensions = pd.enumerateDeviceExtensionProperties();
		bool supportAllRequiredExtensions = std::ranges::all_of(requiredDeviceExtensions,
			[&availableDeviceExtensions](auto const& requiredDeviceExtensions) {
				return std::ranges::any_of(availableDeviceExtensions,
					[requiredDeviceExtensions](auto const& availableDeviceExtensions) {
						return strcmp(availableDeviceExtensions.extensionName, requiredDeviceExtensions) == 0; });
			});

		// Check for support of required features
		auto features = pd.template getFeatures2<vk::PhysicalDeviceFeatures2,
			vk::PhysicalDeviceVulkan11Features,
			vk::PhysicalDeviceVulkan13Features,
			vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>();
		
		bool supportRequiredFeatures = features.template get<vk::PhysicalDeviceVulkan11Features>().shaderDrawParameters &&
			features.template get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering &&
			features.template get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState;

		return supportVulkan_1_3 && supportGraphicsAndPresent && supportAllRequiredExtensions && supportRequiredFeatures;
	}

	void VKRENDERER::Device::getPhysicalDevice(vk::raii::Instance& instance, vk::raii::SurfaceKHR& surface, std::vector<char const*> requiredDeviceExtensions)
	{
		auto physicalDevices = instance.enumeratePhysicalDevices();

		auto const devIter = std::ranges::find_if(physicalDevices, [&](auto pd) { return isDeviceSuitable(pd, surface, requiredDeviceExtensions); });

		if (devIter == physicalDevices.end())
		{
			throw std::runtime_error("No GPUs with vulkan support found on system!!!");
		}

		physicalDevice = *devIter;
	}

}
