#include <Vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include <iostream>
#include <string>

#include <stdexcept>
#include <chrono>
#include <thread>
#include <array>
#include <numeric>
#include <functional>


namespace my_vk_test{

	void processEvents();

	int vulkan_test(){
		// GLFW stuff
		bool success = glfwInit();
		if(!success){
			throw std::runtime_error("Failed to initialize GLFW");
			return -1;
		}
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		GLFWwindow* window = glfwCreateWindow(1280, 720, "test", NULL, NULL);
		if(!window){
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window");
			return -2;
		}
		int monitors_count;
		GLFWmonitor** monitors = glfwGetMonitors(&monitors_count);
		if(monitors_count < 1){
			glfwDestroyWindow(window);
			glfwTerminate();
			throw std::runtime_error("No monitors found");
			return -3;
		}
		const GLFWvidmode* main_screen_mode = glfwGetVideoMode(monitors[0]);

		// Vulkan stuff
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::cout << extensionCount << " extensions supported\n";

		// GLM stuff
		glm::mat4 matrix;
		glm::vec4 vec;
		auto test = matrix * vec;

		// Time stuff
		auto frame_prev = std::chrono::steady_clock::time_point();
		auto frame_start = std::chrono::steady_clock::time_point();
		auto frame_count = 0ui64;
		int target_fps = main_screen_mode->refreshRate;
		std::array<double, 100> dt_stack = {0};
		std::chrono::steady_clock::duration interval = std::chrono::nanoseconds(1000000000 / target_fps);
		double delta_time;
		double avg_delta_time;
		char title[64];

		// Game loop stuff
		while(!glfwWindowShouldClose(window) && (frame_count < 10000)){
			// Self explanatory stuff
			processEvents();
			frame_count++;

			// FPS counting stuff
			{
				frame_prev = frame_start; frame_start = std::chrono::steady_clock::now();
				target_fps = glfwGetVideoMode(monitors[0])->refreshRate; // calculate corrent display number
				interval = std::chrono::nanoseconds(1000000000 / target_fps);
				delta_time = std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(frame_start - frame_prev).count();

				dt_stack[frame_count % dt_stack.size()] = delta_time;
				avg_delta_time = std::accumulate(dt_stack.begin(), dt_stack.end(), 0.0) / dt_stack.size();
				sprintf_s(title, "[test game] FPS = %.2f / %d", 1.0 / avg_delta_time * 1000000000., target_fps);
				glfwSetWindowTitle(window, title);
			}

			// Other logic here
			{
				//std::cout << "Whatever, bruh. ";
			}

			// Drawing here
			{
				//std::cout << "Drawing frame No " << frame_count << "\n";
			}

			// This is garbage solution that uses all of the cpu, need to find something better
			while((frame_start + interval) > std::chrono::steady_clock::now()) continue;
		}

		// cleanup stuff
		glfwDestroyWindow(window);
		glfwTerminate();

		return 0;
	}

	void processEvents(){
		glfwPollEvents();
	}
}