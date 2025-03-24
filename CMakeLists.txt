cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include("${CMAKE_TOOLCHAIN_FILE}")

project(gls-box)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/renderer/*.cpp" "src/platform/*.cpp")

# Define the executable target
add_executable(gls-box ${SOURCES})

# Link any necessary libraries here
target_link_libraries(gls-box PUBLIC
    glfw
    glad::glad
    glm::glm
    )

add_custom_command(
    TARGET gls-box POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:gls-box>/shaders
    COMMENT "Creating symlink to shaders directory in app directory"
)

# Create a soft link to the shaders directory in the build directory
execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders
)