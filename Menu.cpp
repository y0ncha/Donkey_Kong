#include "Menu.h"

void Menu::print(Menu_types type) const {

	gotoxy(0, 0);
	if (type == START_MENU)
	{
		for (int i = 0; i < Screen_dim::Y - 1; i++)
		{
			std::cout << main_layout[i] << std::endl;
		}
		std::cout << main_layout[Screen_dim::Y - 1];
	}
	else//PAUSE_MENU
	{
		std::cout << "#####change this####" << std::endl;
	}
}

void Menu::keys(Menu_types type) const
{
	gotoxy(0, 0);
	for (int i = 0; i < Screen_dim::Y - 1; i++)
	{
		std::cout << keys_layout[i] << std::endl;
	}
	std::cout << main_layout[Screen_dim::Y - 1];

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

int Menu::run(Menu_types type) const {
	this->print(type);

	while (true) {
		if (_kbhit()) { // Check if a key is pressed
			char key = _getch(); // Get the key input
			if (key == START || key == EXIT)
				return key; // Return the key value (START or EXIT)
			else if (key == KEYS)
				this->keys(type);
		}
	}
}