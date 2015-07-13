#include "application.h"

#include <thread>
#include <iostream>
#include <conio.h>

int main() {
	application* app = new application();
	app->run();

	delete app;
	std::cout << "\nPress any key to exit...";
	_getch();
	return 0;
}