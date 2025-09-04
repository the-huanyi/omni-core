#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include <cglm/cglm.h> //math

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "main.h"
#include "dynam_array.h"


GLFWwindow* window;
VkInstance instance;
const uint32_t WIDTH=800;
const uint32_t HEIGHT=600;

const dynamicArray validationLayers= {
	.items={
		(void*)"VK_LAYER_KHRONOS_validation"
	}, .length=1
};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else 
	const bool enableValidationLayers = true;
#endif


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
	if (enableValidationLayers) {
		createInfo.enabledLayerCount=(uint32_t) validationLayers.length;
		createInfo.ppEnabledLayerNames=(const char * const*)&validationLayers.items;
	}else {
		createInfo.enabledLayerCount=0;
	}
	
	//GLFW EXTENSIONS:
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
	
	// EXTENSION LIST 
	dynamicArray requiredExtensions= {0}; //dynamic required array
	for(uint32_t i=0; i< glfwExtensionCount; i++) {
		sa_push_back(&requiredExtensions, (void*)glfwExtensions[i]);
	}
	sa_push_back(&requiredExtensions, VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

	createInfo.enabledExtensionCount=(uint32_t) requiredExtensions.length;
	createInfo.ppEnabledExtensionNames= (const char * const*) &requiredExtensions.items;

	if(enableValidationLayers && !om_checkValidationLayerSupport()){
		printf("validation layers requested but not available!\n");
		return 1;
	}

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS){
		printf("failed to create instance!\n");
		return 1;
	}	
	sa_free(&requiredExtensions); //frees memory of first 
	
	

}

bool om_checkValidationLayerSupport(){
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	dynamicArray availableLayers={.length=layerCount};
	vkEnumerateInstanceLayerProperties(&layerCount, (VkLayerProperties*) &availableLayers.items);
	for(uint32_t i=0; i<validationLayers.length; i++){
		const char* layerName=(char*) validationLayers.items[i];
		bool layerFound = false;

		for(uint32_t j=0; j< availableLayers.length; j++){
			VkLayerProperties* layerProperties=(VkLayerProperties*) &availableLayers.items[j];
			if(strcmp(layerName,layerProperties->layerName) ==0) {
				layerFound=true;
				break;
			}
		}
		if(!layerFound){
			sa_free(&availableLayers);
			return false;
		}
	}
	return true;
}


// GETS LIST OF ALL EXTENSIONS NEEDED, GLFW + EXTRA IF DEBUG
dynamicArray om_getRequiredExtensions(){
	uint32_t glfwExtensionCount=0;
	const char** glfwExtensions;
	glfwExtensions=
		glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	dynamicArray extensions={.length=glfwExtensionCount,.items=glfwExtensions };
	if (enableValidationLayers) 
	sa_push_back(&extensions, VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	return extensions;
}


void om_mainLoop(){
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
	}
}

void om_cleanup(){
	vkDestroyInstance(instance, nullptr);
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
