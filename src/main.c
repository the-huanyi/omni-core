#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE

#include <cglm/cglm.h> //math

#include <stdint.h>
#include <stdio.h>
#include "main.h"

void om_run(){
	om_initVulkan();
	om_mainLoop();
	om_cleanup();
}

void om_initVulkan(){

}
void om_mainLoop(){

}
void om_cleanup(){
}

int main() {
		
}
