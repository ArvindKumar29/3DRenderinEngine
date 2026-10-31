#include "ValidationLayers.h"

namespace VKRENDERER
{
	ValidationLayers::ValidationLayers(){}
	ValidationLayers::~ValidationLayers(){}

	void ValidationLayers::getRequiredValidationLayers(std::vector<char const*>& requiredLayers, vk::raii::Context& ctx)
	{
		if (enableValidationLayers)
		{
			requiredLayers.assign(validationLayers.begin(), validationLayers.end());
		}

		auto layerProperties = ctx.enumerateInstanceLayerProperties();
		auto unsupportedLayerIt = std::ranges::find_if(requiredLayers,
			[&layerProperties](auto const& requiredLayer) {
				return std::ranges::none_of(layerProperties,
					[requiredLayer](auto const& layerProperty) { return strcmp(layerProperty.layerName, requiredLayer) == 0; });
			});
		if (unsupportedLayerIt != requiredLayers.end())
		{
			throw std::runtime_error("Required layer not supported: " + std::string(*unsupportedLayerIt));
		}
	}
}