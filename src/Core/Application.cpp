#include "Application.h"
#include <iostream>

#include <GLFW/glfw3.h>

Application::Application()
{
	// Initialize GLFW

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window Creation
	window = glfwCreateWindow(WIDTH, HEIGHT, "Marching Cubes", NULL, NULL);

	// Checks if window was successfully created
	// Shuts down if there was a problem
	if (window == NULL)
	{
		std::cout << "Failed to create a window! \nShutting down..." << std::endl;
		glfwTerminate();

		throw std::runtime_error("Failed to create a window!");
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetFramebufferSizeCallback(window, ResizeWindowCallback);

	// Initialize GLEW

	glfwInit();

	// Set GLEW settings
	glClearColor(0, 0.7, 0.9, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

}

void Application::RunLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Update();

		glfwSwapBuffers(window);
	}
}

void Application::Update()
{
}

void Application::SetScreenSize(const unsigned int width, const unsigned int height)
{
	WIDTH = width;
	HEIGHT = height;

	//Utility::perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 10000.0f);
	glViewport(0, 0, width, height);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	//game->GetPlayerReference()->GetCameraReference().mouse_callback(window, xpos, ypos);
}

void ResizeWindowCallback(GLFWwindow* window, int width, int height)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	app->SetScreenSize(width, height);
}

