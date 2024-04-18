#include "../inc/game.h"
#include <iostream>

/**
 * Initializes a new game with the given player and dungeon.
 *
 * @param _player The player object to be used in the game.
 * @param _dungeon The dungeon object to be used in the game.
 *
 * @throws None
 */
Game::Game(Player *_player, Dungeon *_dungeon)
{
    player = _player;
    dungeon = _dungeon;
    isGameOver = false;

    dungeon->setUpDungeon();
    player->currentRoom = &dungeon->rooms[dungeon->rows - 1][dungeon->cols - 1];
}

/**
 * Initializes the room sequence for the game.
 *
 * This function checks the current room of the player and performs different actions based on the room's properties.
 * If the player is in the top-left corner of the dungeon and there are no enemies in the room, the game is over and a congratulatory message is displayed.
 * If there are enemies in the room, the `handleEnemyActions` function is called.
 * If there are items in the room, the `handleItemActions` function is called.
 * If there are no enemies or items in the room, the `handleMovementActions` function is called.
 *
 * @throws None
 */
void Game::initiateRoomSequence()
{
    room *room = player->currentRoom;

    if (room->row == 0 && room->col == 0 && room->enemies.empty())
    {
        std::cout << "Congratulations, you have reached the exit and are free of the dungeon! Farwell " << player->getName() << "!" << std::endl;
        isGameOver = true;
        return;
    }

    if (!room->enemies.empty())
    {
        handleEnemyActions();
    }
    else if (!room->items.empty())
    {
        handleItemActions();
    }
    else
    {
        handleMovementActions();
    }
}

/**
 * Prints a list of actions to the console.
 *
 * @param actions a vector of strings representing the actions to be printed
 *
 * @throws none
 */
void Game::printActions(std::vector<std::string> actions)
{
    for (int i = 0; i < actions.size(); i++)
    {
        std::cout << i + 1 << ". " << actions[i] << std::endl;
    }
}

/**
 * Retrieves a vector of strings representing the available movement actions for the current player's room.
 *
 * @return A vector of strings containing the movement actions.
 */
std::vector<std::string> Game::getMovementActions()
{
    std::vector<std::string> actions;

    room *currentRoom = player->currentRoom;
    if (currentRoom->col > 0)
    {
        actions.push_back("Move left");
    }
    if (currentRoom->row > 0)
    {
        actions.push_back("Move up");
    }
    if (currentRoom->col < (dungeon->cols - 1))
    {
        actions.push_back("Move right");
    }
    if (currentRoom->row < (dungeon->rows - 1))
    {
        actions.push_back("Move down");
    }

    return actions;
}

/**
 * Handles the movement actions for the game.
 *
 * @throws None
 */
void Game::handleMovementActions()
{
    std::cout << "Where do you want to go next?" << std::endl;
    std::vector<std::string> actions = getMovementActions();
    printActions(actions);

    int input;
    std::cin >> input;
    std::string chosenAction = actions[input - 1];

    int horizontalMovement = 0;
    int verticalMovement = 0;

    if (chosenAction == "Move left")
    {
        horizontalMovement = -1;
    }
    else if (chosenAction == "Move up")
    {
        verticalMovement = -1;
    }
    else if (chosenAction == "Move right")
    {
        horizontalMovement = 1;
    }
    else if (chosenAction == "Move down")
    {
        verticalMovement = 1;
    }

    room *newRoom = &dungeon->rooms[player->currentRoom->row + verticalMovement][player->currentRoom->col + horizontalMovement];
    player->moveToRoom(newRoom);

    std::cout << "You are now in room " << newRoom->row << " " << newRoom->col << std::endl;
}

/**
 * Handles the actions for the enemy in the current room.
 *
 * This function prompts the player to choose an action for the enemy in the current room. If the player chooses to engage the enemy, the `engageInCombat` function is called. Otherwise, the player's `retreat` function is called.
 *
 * @throws None
 */
void Game::handleEnemyActions()
{
    std::cout << "There is an enemy " << player->currentRoom->enemies[0].getName() << " in this room! What would you like to do?" << std::endl;
    std::vector<std::string> actions;
    actions.push_back("Engage enemy");
    actions.push_back("Retreat");
    printActions(actions);

    int input;
    std::cin >> input;
    if (input == 1)
    {
        engageInCombat();
    }
    else
    {
        player->retreat();
    }
}

/**
 * Engages in combat with the enemy in the current room.
 *
 * This function continuously takes damage from the enemy and the player takes damage from the enemy until one of them is defeated.
 * The combat ends when the enemy is defeated or the player retreats.
 *
 * @throws None
 */
void Game::engageInCombat()
{
    GameCharacter *enemy = &player->currentRoom->enemies[0];
    while (true)
    {
        enemy->takeDamage(player->getDamage());
        std::cout << "You strike the " << enemy->getName() << ", dealing " << player->getDamage() << " damage." << std::endl;
        if (!enemy->checkIsAlive())
        {
            std::cout << "You have defeated the " << enemy->getName() << "!" << std::endl;
            player->currentRoom->enemies.clear();
            return;
        }

        player->takeDamage(enemy->getDamage());
        std::cout << "You take " << enemy->getDamage() << " damage. You now have " << player->getHealth() << " health." << std::endl;
        if (!player->checkIsAlive())
        {
            isGameOver = true;
            std::cout << "You have been defeated! Better luck next time!" << std::endl;
            return;
        }

        std::cout << "Would you like to keep fighting or retreat?" << std::endl;
        std::vector<std::string> actions;
        actions.push_back("Keep fighting");
        actions.push_back("Retreat");
        printActions(actions);

        int input;
        std::cin >> input;
        if (input != 1)
        {
            player->retreat();
            return;
        }
    }
}

/**
 * Handles the actions for the item in the current room.
 *
 * This function prompts the player to choose an action for the item in the current room. If the player chooses to pick up the item, the `pickUpItem` function is called on the player object. Otherwise, the `handleMovementActions` function is called.
 *
 * @throws None
 */
void Game::handleItemActions()
{
    item item = player->currentRoom->items[0];
    std::cout << "You find a " << item.name << " in this room! What would you like to do?" << std::endl;
    std::vector<std::string> actions;
    actions.push_back("Pick up item");
    actions.push_back("Ignore item");
    printActions(actions);

    int input;
    std::cin >> input;
    if (input == 1)
    {
        player->pickUpItem(player->currentRoom->items[0]);
        std::cout << "You picked up a " << item.name << ". Your health is now " << player->getHealth() << " and your damage is now " << player->getDamage() << std::endl;
        player->currentRoom->items.clear();
    }
    else
    {
        handleMovementActions();
    }
}