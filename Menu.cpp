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
		for (int i = 0; i < Screen_dim::Y - 1; i++)
		{
			std::cout << pause_layout[i] << std::endl;
		}
		std::cout << pause_layout[Screen_dim::Y - 1];
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
			if (_kbhit()) { // Check if a key is pressed (again to make it run faster between two "sleep")
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

int Menu::choseLevel()
{
	gotoxy(0, 0);
	for (int i = 0; i < Screen_dim::Y - 1; i++)
	{
		std::cout << level_layout[i] << std::endl;
	}
	std::cout << level_layout[Screen_dim::Y - 1];

	while (true)//Wait for level selection
	{
		if (_kbhit()) { // Check if a key is pressed
			char key = _getch(); // Get the key input
			switch (key) {
			case EASY:
				return EASY;
			case MEDIUM:
				return MEDIUM;
			case HARD:
				return HARD;
			}
		}
	}
}

void Menu::printExitLayOut()
{
	gotoxy(0, 0);
	for (int i = 0; i < Screen_dim::Y - 1; i++)
	{
		std::cout << ExitGame_layout[i] << std::endl;
	}
	std::cout << ExitGame_layout[Screen_dim::Y - 1];
}

void Menu::printTryAgainLayOut()
{
	gotoxy(0, 0);
	for (int i = 0; i < Screen_dim::Y - 1; i++)
	{
		std::cout << tryAgain_layout[i] << std::endl;
	}
	std::cout << tryAgain_layout[Screen_dim::Y - 1];

	while (true)//Wait for key press
	{
		if (_kbhit())  // Check if a key is pressed
			break;

		gotoxy(27, 23);
		std::cout << "Press any key to continue";

		Sleep(700);
		if (_kbhit()) { // Check if a key is pressed (again to make it run faster between two "sleep")
			break;
		}
		gotoxy(27, 23);
		std::cout << "                         ";
		Sleep(300);

	}
}

void Menu::printFailLayOut()
{
	gotoxy(0, 0);
	for (int i = 0; i < Screen_dim::Y - 1; i++)
	{
		std::cout << Fail_layout[i] << std::endl;
	}
	std::cout << Fail_layout[Screen_dim::Y - 1];
}

void Menu::printSuccessLayOut()
{
	gotoxy(0, 0);
	for (int i = 0; i < Screen_dim::Y - 1; i++)
	{
		std::cout << success_layout[i] << std::endl;
	}
	std::cout << success_layout[Screen_dim::Y - 1];
}
