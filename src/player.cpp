#include "../inc/player.h"

Player::Player(std::string _name, int _health, int _damage) : GameCharacter(_name, _health, _damage) {}

/**
 * Updates the player's health by adding the specified amount. If the resulting health exceeds the maximum health, it is capped at the maximum health value.
 *
 * @param amount the amount to heal the player by
 *
 * @return void
 *
 * @throws None
 */
void Player::heal(int amount)
{
    currentHealth += amount;
    if (currentHealth > maxHealth)
    {
        currentHealth = maxHealth;
    }
}

/**
 * Moves the player to a new room.
 *
 * @param newRoom The room to move the player to.
 *
 * @return void
 *
 * @throws None
 */
void Player::moveToRoom(room *newRoom)
{
    previousRoom = currentRoom;
    currentRoom = newRoom;
}

/**
 * Updates the player's current and previous room pointers to simulate a retreat action.
 *
 * @param None
 *
 * @return void
 *
 * @throws None
 */
void Player::retreat()
{
    room *tempRoom = currentRoom;
    currentRoom = previousRoom;
    previousRoom = tempRoom;
}

/**
 * Updates the player's damage and health based on the item picked up.
 *
 * @param item the item to be picked up
 *
 * @return void
 *
 * @throws None
 */
void Player::pickUpItem(item item)
{
    damage += item.damage;
    heal(item.health);
}