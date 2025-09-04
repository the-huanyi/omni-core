#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include <cglm/cglm.h> //math

#include <stdint.h>
#include <stdio.h>
#include "main.h"


GLFWwindow* window;
VkInstance instance;
const uint32_t WIDTH=800;
const uint32_t HEIGHT=600;

void om_initWindow(){
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
	window=glfwCreateWindow(WIDTH,HEIGHT,"Vulkan", nullptr, nullptr);

}

void om_initVulkan(){
	om_createInstance();
}

int om_createInstance(){
	// CREATING INSTANCE STRUCTS:
	VkApplicationInfo appInfo;
	appInfo.sType=VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName= "Hello triangle";
	appInfo.applicationVersion= VK_MAKE_VERSION(0,0,1);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion= VK_MAKE_VERSION(0,0,1);
	appInfo.apiVersion= VK_API_VERSION_1_0;
	
	VkInstanceCreateInfo createInfo;
	createInfo.sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo= &appInfo;
	
	//EXTENSIONS:
	uint32_t glfwExtensionCount=0;
	const char** glfwExtensions; //pointer to pointer where GLFW will tell what extensions it needs! platform indepent fuck yeah dude
	glfwExtensions= glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	createInfo.enabledExtensionCount= glfwExtensionCount;
	createInfo.ppEnabledExtensionNames= glfwExtensions;

	createInfo.enabledLayerCount= 0;
	VkResult result= vkCreateInstance(&createInfo, nullptr, &instance);
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS){
		printf("sis..we failed to create instance, womp womp\n");
		return 1;
	};
	return 0;

}

void om_mainLoop(){
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
	}
}

void om_cleanup(){
	glfwDestroyWindow(window);
	glfwTerminate();
}

void om_run(){
	om_initWindow();
	om_initVulkan();
	om_mainLoop();
	om_cleanup();
}

int main() {
	om_run();
}
