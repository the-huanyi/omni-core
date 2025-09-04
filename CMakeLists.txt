cmake_minimum_required( VERSION 3.20 )
project (omni LANGUAGES C)

add_subdirectory(vendor/glfw)
#add_subdirectory(vendor/glm)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.c")
file(GLOB_RECURSE HDR CONFIGURE_DEPENDS "src/include/*.h")

add_executable(core ${SRC} ${HDR})
target_link_libraries	(core PUBLIC glfw ${Vulkan_LIBRARIES})
target_link_directories	(core PUBLIC "vendor/cglm/include")
target_include_directories(core PRIVATE "src/include/" "vendor/cglm/include/" ${Vulkan_INCLUDE_DIRS})

#add_custom_target(shaders ALL COMMAND bash "../src/build_shaders.sh" COMMENT "Building Shaders")
