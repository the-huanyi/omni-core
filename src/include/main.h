#include "dynam_array.h"

void om_initWindow();
int om_createInstance();

bool om_checkValidationLayerSupport();
dynamicArray* om_getRequiredExtensions();
static VKAPI_ATTR VkBool32 VKAPI_CALL debufCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

void om_initVulkan();
void om_mainLoop();
void om_cleanup();

void om_run();
int main();

