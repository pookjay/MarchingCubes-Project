#pragma once

#include "Mesh.h"

#include "Utility/Camera.h"

inline Camera camera;

class Application {

public:

	// Initializes GLFW, GLEW, and creates the window
	Application();

	// Runs the game loop
	void RunLoop();

	// Updates the game state every frame
	void Update();

	// @brief Sets the screen size
	// @param width is the new width of the screen
	// @param height is the new height of the screen
	void SetScreenSize(const unsigned int width, const unsigned int height);

	Camera& GetCameraReference() { return camera; };

private:

	struct GLFWwindow* window;

	int WIDTH = 1920, HEIGHT = 1080;

	Mesh* mesh;

	

};

void MouseCallback(GLFWwindow* window, double xpos, double ypos);

void ResizeWindowCallback(GLFWwindow* window, int width, int height);