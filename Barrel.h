#pragma once

#include <iostream>
#include "Board.h"
#include "Config.h"
#include "Utils.h"
#include "Entity.h"

class Barrel : public Entity {


    bool falling = false;

    int fall_count = 0;

    bool explode = false;

    void floor_switch(char bellow_barrel);

public:

    Barrel(const Board* org_board, Board* curr_board, Coordinates _pos); // Initialize curr_board

    void move(); // Moves Barrel based on key press

};
