#include <iostream>
#include <glad/glad.h>
#include "application.h"

Application::~Application(void)
{
	if (window)
		glfwDestroyWindow(window);
	glfwTerminate();
}

bool Application::init(void)
{
	if (!glfwInit()) 
	{ 
		std::cerr << "Unable to initialize GLFW." << std::endl;
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Unable to initialize GLFW window." << std::endl;
		return false;
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Unable to initialize GLAD." << std::endl;
		return false;
	}

	glViewport(0, 0, width, height);
	
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, Application::framebufferSizeCallback);

	return true;
}

void Application::run(void)
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glfwSwapBuffers(window);
	}
}

void Application::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Application* app = (Application*)glfwGetWindowUserPointer(window);
	app->width = width;
	app->height = height;
	glViewport(0, 0, width, height);
}