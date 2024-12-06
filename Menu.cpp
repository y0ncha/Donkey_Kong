#include "Menu.h"

Menu::Menu(){}

void Menu::print() const {
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++)
	{
		std::cout << MenuLayout[i] << std::endl;
	}
	std::cout << MenuLayout[MAX_Y - 1];
}

int Menu::run() const {
	this->print();

	while (true) {
		if (_kbhit()) { // Check if a key is pressed
			char key = _getch(); // Get the key input
			if (key == EXIT) 
				return EXIT;
			if (key == START)
				return START;
		}
	}
}