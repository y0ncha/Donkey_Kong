#pragma once

#include <iostream>
#include "Config.h"

#include  "Utils.h" > <

// The Board class represents the game board and its functionalities
class Board {

    char layout[MAX_Y][MAX_X + 1] = {
        // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
          "             LIVES: <3  <3  <3        LEVEL 1        POINTS : 00                ",// 0
          "================================================================================",// 1
          "                                                                                ",// 2
          "                                   $                                            ",// 3
          "     =============              =======                                         ",// 4
          "        H                        H       ======                         =====   ",// 5    
          "        H                        H &      H                                H    ",// 6 
		  "==================>====== ================== ========<<<===<<<================  ",// 7
          "                                     H                                  H       ",// 8
          "                                     H                                  H       ",// 9
          "                        =<<<==========             ======== ================    ",// 10
          "                                                               H                ",// 11
          "                                     =======>>>======          H                ",// 12
          "      ===============>>>             H             H           H                ",// 13
          "                   H                 H         ===========   ==========         ",// 14
          "                   H                 H                   H         H            ",// 15
          "                   H                 H                   H         H            ",// 16
          "                   H       =================<<<================    H            ",// 17
          "                   H        H                                      H            ",// 18
          "                   H        H                           ==================      ",// 19
          "                 =====<<<>>>====                                                ",// 20
          "                              H               ========                          ",// 21
          "                              H                                                 ",// 22
          "                              H                                =======          ",// 23
          "=======>>>==========================================================<<<=========" // 24
    };

public:

    void print() const; // Prints the board on the console

    char get_char(Coordinates coord) const; // Retrieves the character from the board at given coordinates
    char get_char(int x, int y) const; // Retrieves the character from the board at given coordinates

	void set_char(Coordinates coord, char ch); // Sets the character at the given coordinates
	void set_char(int x, int y , char ch); // Sets the character at the given coordinates

    bool is_floor(Coordinates coord) const; // Checks if the character at the given coordinates is a floor element

    void burn(); // Sets the game board on fire (implementation pending) @ implement

    void clear(); // Clears the game board (implementation pending) @ implement
  
	bool path_clear(Coordinates coord) const; // Checks if the path is clear
	bool path_clear(int x, int y) const; // Checks if the path is clear
};
