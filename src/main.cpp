#include <iostream>
#include "application.h"

int main(void)
{
	Application app(800, 800, "Mandelbrot");
	if (!app.init())
	{
		std::cerr << "Unable to initialize application." << std::endl;
		return EXIT_FAILURE;
	}

	app.run();
	return 0;
}