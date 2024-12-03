#include "Barrel.h"

Barrel::Barrel(const Board* org_board, Board* curr_board, Coordinates _pos) : Entity(org_board, curr_board, _pos, BARREL) {};

void Barrel::move() { // @ decide what happends if barrel is off bound

    if (fall_count >= 8) {
        explode = true;
    }

    char bellow_barrel = curr_board->get_char(pos.x, pos.y + 1);

    if (falling) {

        if (is_floor(bellow_barrel)) {

            falling = false;
            dir.y = 0;
            fall_count = 0;

            if (explode) {

                erase();

                return;
            }

            floor_switch(bellow_barrel);
        }

        else {
			dir.y = 1;
			fall_count++;   
        }
    }

    else {

		last_dx = dir.x;

        if (is_floor(bellow_barrel)) {

            floor_switch(bellow_barrel);
        }

        else {

            dir.y = 1;
            dir.x = 0;
            falling = true;
            fall_count++;
        }
      
    }

    step(70);
}

void Barrel::floor_switch(char bellow_barrel) {

    switch (bellow_barrel) {

    case FLOOR_L:
        dir.x = -1;
        break;

    case FLOOR_R:
        dir.x = 1;
        break;

    case FLOOR:
        dir.x = last_dx;
    default:
        break;
    }
}

