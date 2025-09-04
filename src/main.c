#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include <cglm/cglm.h> //math

#include <stdint.h>
#include <stdio.h>

int main() {
	glfwInit();
	
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window",nullptr, nullptr);
	
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,nullptr);
	
	printf("%d\n", extensionCount);
	

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
