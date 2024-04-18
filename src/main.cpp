#include <iostream>
#include "../inc/game.h"

/**
 * The main function of the program. It prompts the user for their name, creates a Player object
 * with the given name and initial health and damage values, creates a Dungeon object, and creates a
 * Game object with the Player and Dungeon objects as parameters. The program then prints a
 * welcome message to the user and enters a loop where it calls the initiateRoomSequence function
 * of the Game object until the game is over.
 *
 * @return int The exit status of the program.
 *
 * @throws None
 */
int main()
{
    std::string name;
    std::cout << "Welcome to the dungeon! What is your name?" << std::endl;
    std::cin >> name;

    Player player = Player(name, 100, 10);
    Dungeon dungeon;
    Game game = Game(&player, &dungeon);

    std::cout << "Good luck, " << name << std::endl;

    while (!game.isGameOver)
    {
        game.initiateRoomSequence();
    }
}