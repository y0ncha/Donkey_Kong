#include "Menu.h"

Menu::Menu(){}

void Menu::print(MENU_TYPES type) const {
	gotoxy(0, 0);
	if (type == START_MENU)
	{
		for (int i = 0; i < MAX_Y - 1; i++)
		{
			std::cout << MenuLayout[i] << std::endl;
		}
		std::cout << MenuLayout[MAX_Y - 1];
	}
	else
	{
		std::cout << "#####change this####" << std::endl;
	}
}

void Menu::ShowKeys() const///######change this
{
	gotoxy(4, 12);
	std::cout << "1" << std::endl;
	Sleep(1000);
	gotoxy(4, 12);
	std::cout << " " << std::endl;
	Sleep(1000);
}

int Menu::run(MENU_TYPES type) const {
	this->print(type);

	while (true) {
		if (_kbhit()) { // Check if a key is pressed
			char key = _getch(); // Get the key input
			if (key == START || key == EXIT)
				return key; // Return the key value (START or EXIT)
			else if (key == KEYS)
				this->ShowKeys();
		}
	}
}