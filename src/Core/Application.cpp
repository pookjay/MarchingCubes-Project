#include "Application.h"
#include <iostream>

#include <glew.h>
#include <GLFW/glfw3.h>

#include "Core/World.h"

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

	glewInit();

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

	World* world = new World();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Update();

		world->RenderWorld();

		glfwPollEvents();
		ProcessInput();

		glfwSwapBuffers(window);
	}
}

void Application::Update()
{
	camera.UpdateCamera();

}

void Application::ProcessInput()
{
	float CameraSpeed = 0.05f;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.cameraPosition.y += CameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.cameraPosition.y -= CameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.cameraPosition += CameraSpeed * camera.cameraForwardVector;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.cameraPosition -= CameraSpeed * camera.cameraForwardVector;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.cameraPosition -= CameraSpeed * glm::cross(camera.cameraForwardVector, camera.cameraUpVector);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.cameraPosition += CameraSpeed * glm::cross(camera.cameraForwardVector, camera.cameraUpVector);
	}
}

void Application::SetScreenSize(const unsigned int width, const unsigned int height)
{
	WIDTH = width;
	HEIGHT = height;

	Utility::perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 10000.0f);
	glViewport(0, 0, width, height);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	app->GetCameraReference().MouseCallback(window, xpos, ypos);
}

void ResizeWindowCallback(GLFWwindow* window, int width, int height)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	app->SetScreenSize(width, height);
}

