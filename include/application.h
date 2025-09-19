#pragma once
#include <GLFW/glfw3.h>

class Application
{

public:
	Application(void) = delete;
	Application(int width, int height, const char* title)
		: width(width), height(height), title(title), window(nullptr)
	{ }

	~Application(void);

	bool init(void);
	void run(void);

private:
	int width;
	int height;
	const char* title;
	GLFWwindow* window;

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

};