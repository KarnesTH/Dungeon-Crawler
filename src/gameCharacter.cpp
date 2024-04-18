#include "../inc/gameCharacter.h"

/**
 * Initializes a GameCharacter with the specified name, health, and damage values.
 *
 * @param _name the name of the GameCharacter
 * @param _health the initial health of the GameCharacter
 * @param _damage the damage value of the GameCharacter
 *
 * @return None
 *
 * @throws None
 */
GameCharacter::GameCharacter(std::string _name, int _health, int _damage)
{
    name = _name;
    maxHealth = _health;
    currentHealth = _health;
    damage = _damage;
}

/**
 * Decreases the current health of the GameCharacter by the specified amount.
 *
 * @param amount the amount of damage to take
 *
 * @throws None
 */
void GameCharacter::takeDamage(int amount)
{
    currentHealth -= amount;
}

/**
 * Checks if the GameCharacter is alive.
 *
 * @return true if the GameCharacter is alive, false otherwise
 */
bool GameCharacter::checkIsAlive()
{
    return currentHealth > 0;
}

/**
 * Retrieves the name of the GameCharacter.
 *
 * @return the name of the GameCharacter
 *
 * @throws None
 */
std::string GameCharacter::getName()
{
    return name;
}

/**
 * Retrieves the health of the GameCharacter.
 *
 * @return the health of the GameCharacter
 */
int GameCharacter::getHealth()
{
    return currentHealth;
}

/**
 * Retrieves the damage value of the GameCharacter.
 *
 * @return the damage value of the GameCharacter
 */
int GameCharacter::getDamage()
{
    return damage;
}