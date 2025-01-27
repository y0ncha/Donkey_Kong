#pragma once
#include "Board.h"
#include "Coord.h"
#include "Point.h"
#include "Config.h"

// Forward declaration of the handle_err function
void handle_err(const std::string& message, const char* file, int line);

/**
 * @class Entity
 * Represents a generic game entity with position, movement, and rendering capabilities.
 */
class Entity {

public:

	// Virtual destructor for the Entity class
	virtual ~Entity() = default;

    // Virtual method to move the Entity
    virtual void move() = 0;

	// Draws the entity at its current position
    void set(size_t i = 0) const;

    // Erases the entity from its current position
    void vanish() const;

    // Getter for the char behind the entity
    char behind_ch() const;

    // Getter for the entity's icon
    char next_ch() const;

    // Checks the character beneath the entity
    char beneath_ch() const;

    // Checks the character above the entity
    char above_ch() const;

	// Getter for the char to the left of the entity
	char left_ch() const;
    
	// Getter for the char to the right of the entity
	char right_ch() const;

    // Method to get the destination position of the entity
    Coordinates get_dest() const;

    // Getter for the entity's position
    Coordinates get_pos() const { return point.pos; }

    // Getter for the entity's direction
    Coordinates get_dir() const { return dir; }

	// Getter for the entity's horizontal direction
	int get_dx() const { return dir.x; }

	// Getter for the entity's vertical direction
	int get_dy() const { return dir.y; }

    // Checks if the entity is off the ground
    bool off_ground() const;

    // Checks if the entity is on the ground
    bool on_ground() const;

	// Getter for the last horizontal direction
    int get_lastdx() const;

    // Method to set the position of the entity
    void reset();

    // Inverts the direction of the entity
    void invert_dir();

    // Setter for the board pointer
    bool set_board(const Board* pBoard);

protected:

	// Constructor for the Entity class (abstract class)
    Entity(const Board* pBoard, char ch, Coordinates init_pos, Coordinates dir = { 0, 0 });

    // Pointer to the original game board
    const Board* board;

    // Setter for the entity's direction using dx and dy values
    bool set_dir(int dx, int dy);
    bool set_dir(Coordinates coord);

	// Getter for the last horizontal direction
    void set_last_dx(int dx);

	// Setter for the entity's dx and dy values
	bool set_dy(int dy);
	bool set_dx(int dx);

	// Setter for the entity's icon
    bool set_icon(Board::Icon icon); 

    // Setter for the entity's position using x and y coordinates
    Coordinates set_pos(int _x, int _y) const;
    Coordinates set_pos(Coordinates coord) const;

    // Moves the entity by one step with an optional delay
    void step();

    // Virtual method to handle collisions with other entities or obstacles
    virtual char handle_collision() = 0;

    // Virtual method to update the entity's direction
    virtual bool update_dir(char key = static_cast<char>(Ctrl::DEF)) = 0;

    // Virtual method to handle the direction change when the entity is on different types of floors
    virtual void handle_falling() = 0;

private:

    // Point representation of the entity
    Point point;

    // Last horizontal direction
    int last_dx = 0;

    // Direction of the entity
    Coordinates dir;
};
