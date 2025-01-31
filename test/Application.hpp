#pragma once

#include <Vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <GLM/glm.hpp>

#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <optional>
#include <set>
#include <limits>
#include <algorithm>

class Application{
public:
	Application();
	virtual ~Application();
	void run();
    void cleanup();

protected:
	struct QueueFamilyIndices{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		inline bool isComplete() const{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
	struct SwapChainSupportDetails{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

    void initVulkan();
    void mainLoop();

	void initWindow();
	void createInstance();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createGraphicsPipeline();

	bool checkValidationLayerSupport();
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	GLFWwindow* window = nullptr;
	VkInstance instance = nullptr;
    VkDebugUtilsMessengerEXT debugMessenger = nullptr;
	VkSurfaceKHR surface = nullptr;
	VkPhysicalDevice physicalDevice = nullptr;
	VkDevice device = nullptr;
	VkQueue graphicsQueue = nullptr;
	VkQueue presentQueue = nullptr;
	VkSwapchainKHR swapChain = nullptr;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat = VK_FORMAT_UNDEFINED;
	VkExtent2D swapChainExtent = {};

	const uint32_t window_width = 1280;
	const uint32_t window_height = 720;
	const char* application_title = "Vulkan test window";
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

    std::vector<const char*> getRequiredExtensions() const;

    void setupDebugMessenger();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	static void glfwErrorCallback(int error_code, const char* description);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
};