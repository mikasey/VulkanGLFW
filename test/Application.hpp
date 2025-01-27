#pragma once

#include <Vulkan/vulkan.h>
// #define GLFW_INCLUDE_VULKAN // do not see any practical reason for it, normal vulkan header looks cooler
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include <sstream>		// formating
#include <iostream>		// console logging
#include <vector>
#include <stdexcept>	// exeptions
#include <cstdlib>		// EXIT_SUCCESS, EXIT_FAILURE and precise types



class Application{
public:
	Application();
	virtual ~Application();
	void run();

protected:
    void initVulkan();
    void mainLoop();
    void cleanup();

	void initWindow();
	void createInstance();

	bool checkValidationLayerSupport();

	GLFWwindow* window = nullptr;
	VkInstance instance = nullptr;
    VkDebugUtilsMessengerEXT debugMessenger = nullptr;

	const uint32_t window_width = 1280;
	const uint32_t window_height = 720;
	const char* application_title = "Vulkan test window";
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
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