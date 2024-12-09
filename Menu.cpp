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
	else//PAUSE_MENU
	{
		std::cout << "#####change this####" << std::endl;
	}
}

void Menu::ShowKeys(MENU_TYPES type) const
{
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++)
	{
		std::cout << KeysLayout[i] << std::endl;
	}
	std::cout << MenuLayout[MAX_Y - 1];

	while (true)//Wait for ESC
	{
		if (_kbhit()) { // Check if a key is pressed
			char key = _getch(); // Get the key input

			if (key == ESC) {
				this->print(type);
				break;
			}
		}
			gotoxy(26, 22);
			std::cout << "Press ESC to return to menu";

			Sleep(700);
			if (_kbhit()) { // Check if a key is pressed (again to make it run faster between two "seep")
				char key = _getch(); // Get the key input

				if (key == ESC) {
					this->print(type);
					break;
				}
			}
			gotoxy(26, 22);
			std::cout << "                           ";
			Sleep(300);
		
	}
}

int Menu::run(MENU_TYPES type) const {
	this->print(type);

	while (true) {
		if (_kbhit()) { // Check if a key is pressed
			char key = _getch(); // Get the key input
			if (key == START || key == EXIT)
				return key; // Return the key value (START or EXIT)
			else if (key == KEYS)
				this->ShowKeys(type);
		}
	}
}