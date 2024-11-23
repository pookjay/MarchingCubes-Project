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
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)

FetchContent_Declare(
    GLEW
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
    GIT_TAG master # Change to the latest stable version
    )

    # Force GLEW to build in Release mode
# Populate GLEW and set it to build only in Release mode
FetchContent_GetProperties(GLEW)
if (NOT glew_POPULATED)
    FetchContent_Populate(GLEW)
    
    # Create a custom build directory for GLEW in Release mode
    set(GLEW_RELEASE_BUILD_DIR ${glew_BINARY_DIR})
    file(MAKE_DIRECTORY ${GLEW_RELEASE_BUILD_DIR})
    
    # Configure GLEW explicitly for Release
    execute_process(COMMAND ${CMAKE_COMMAND} -S ${glew_SOURCE_DIR} -B ${GLEW_RELEASE_BUILD_DIR} -DCMAKE_BUILD_TYPE=Release)
    
    # Build GLEW in Release mode
    execute_process(COMMAND ${CMAKE_COMMAND} --build ${GLEW_RELEASE_BUILD_DIR} --config Release)
endif()

add_library(GLEW_STATIC STATIC IMPORTED)
set_target_properties(GLEW_STATIC PROPERTIES
    IMPORTED_LOCATION ${GLEW_RELEASE_BUILD_DIR}/lib/Release/glew.lib
    INTERFACE_INCLUDE_DIRECTORIES ${glew_SOURCE_DIR}/include
)
#FetchContent_MakeAvailable(GLEW)

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


file(GLOB SHADER_VERT_SOURCES "${CMAKE_SOURCE_DIR}/resources/shaders/*.vert")
file(GLOB SHADER_FRAG_SOURCES "${CMAKE_SOURCE_DIR}/resources/shaders/*.frag")

file(GLOB TEXTURE_SOURCES "${CMAKE_SOURCE_DIR}/resources/textures/spritesheet/*.png")


#file(COPY ${SHADER_VERT_SOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)
#file(COPY ${SHADER_FRAG_SOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)

if(CMAKE_CONFIGURATION_TYPES) # Multi-config generator
    # Multi-config generators (Visual Studio, Xcode)
    foreach(config ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${config} CONFIG_UPPER)
        file(COPY ${SHADER_VERT_SOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER}}/shaders)
        file(COPY ${SHADER_FRAG_SOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER}}/shaders)

        message(STATUS "Copying shaders and textures to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER}} for ${config} configuration.")
    endforeach()
else() # Single-config generator
    # Single-config generators (Makefiles, Ninja)
    file(COPY ${SHADER_VERT_SOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)
    file(COPY ${SHADER_FRAG_SOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)
    message(STATUS "Copying shaders to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders for ${CMAKE_BUILD_TYPE}.")
endif()

file(COPY ${SHADER_VERT_SOURCES} DESTINATION ${CMAKE_BINARY_DIR}/shaders)
file(COPY ${SHADER_FRAG_SOURCES} DESTINATION ${CMAKE_BINARY_DIR}/shaders)




