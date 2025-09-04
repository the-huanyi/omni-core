cmake_minimum_required( VERSION 3.20 )
project (omni LANGUAGES C)

add_subdirectory(vendor/glfw)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.c")
file(GLOB_RECURSE HDR CONFIGURE_DEPENDS "src/include/*.h")

add_executable(core ${SRC} ${HDR})
target_include_directories(core PRIVATE "src/include/")
