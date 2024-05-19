#pragma once
#include"gameHeader.h"
#include"Item.h"

class Player {
public:
    Player(std::string name = "Player", int health = 30, int attackDamage = 10, int defense = 5) :
        name(name), health(health), attackDamage(attackDamage), defense(defense) {
        if (!texture.loadFromFile("MENU/Images/Player/Maxcroppeduse.png")) {
            std::cerr << "Failed to load Player Texture!" << std::endl;
        }
        sprite.setTexture(texture);

        // Assign values to private members in the constructor
        rectsprite = sf::IntRect(0, 0, 110, 110);
        sprite = sf::Sprite(texture, rectsprite);
        storage.addDefaultRedPotions(2);
    }

    // Getter methods
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttackDamage() const { return attackDamage; }
    int getDefense() const { return defense; }

    // Setter methods
    void setName(std::string newName) { name = newName; }
    void setHealth(int newHealth) { health = newHealth; }
    void setAttackDamage(int newAttackDamage) { attackDamage = newAttackDamage; }
    void setDefense(int newDefense) { defense = newDefense; }

    // Other methods
    void takeDamage(int damage) {
        int actualDamage = damage - defense;
        if (actualDamage < 0) {
            actualDamage = 0; // Ensure damage is non-negative
        }
        health -= actualDamage;
    }

    bool isAlive() const {
        return health > 0;
    }

    //private:
    std::string name;
    int health;
    int attackDamage;
    int defense;
    sf::Sprite sprite;
    sf::IntRect rectsprite;
    sf::Texture texture;
    Inventory storage;
};
