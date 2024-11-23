cmake_minimum_required(VERSION 3.16)
project(MarchingCubes)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)

message(STATUS ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src include)

 # OpenGL
 find_package(OpenGL REQUIRED)
 target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

 # FetchContent for External Libraries
include(FetchContent)

# GLEW

set(GLEW_BUILD_DEMOS OFF CACHE BOOL "Disable GLEW demos" FORCE )
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "Build the shared glew library" FORCE )

FetchContent_Declare(
    GLEW
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
    GIT_TAG master # Change to the latest stable version
    )

FetchContent_MakeAvailable(GLEW)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)
target_include_directories(${PROJECT_NAME} PRIVATE ${glew_SOURCE_DIR}/include/GL)
target_link_libraries(${PROJECT_NAME} PRIVATE ${glew_BINARY_DIR}/lib/Release/glew.lib)

    
# GLFW

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE )
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE )
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE )

FetchContent_Declare(
    GLFW
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8 # Change to the latest stable version
)


FetchContent_MakeAvailable(GLFW)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# GLM
FetchContent_Declare(
    GLM
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8 # Change to the latest stable version
)
FetchContent_MakeAvailable(GLM)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)


