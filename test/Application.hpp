#pragma once

#include <Vulkan/vulkan.h>
#include <GLM/glm.hpp>
#include <GLFW/glfw3.h>

#include <iostream> // console logging
#include <stdexcept> // exeptions
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE macros



class Application{
public:
	Application();
	virtual ~Application();
	void run();

protected:
    void initVulkan();
    void mainLoop();
    void cleanup();
};

