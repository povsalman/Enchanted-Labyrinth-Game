#pragma once

#include"gameHeader.h"

// Resource Directory for easy path:
//constexpr char RESOURCE_DIR[] = "resources/";


// Parent Enem Class
class Enem {
public:
    Enem(std::string name, int health, int attackDamage, int defense, const std::string& texturePath, const sf::IntRect& rectsprite, const sf::Vector2f& initialPosition, const sf::Vector2f& initialScale) :
        name(name), health(health), maxHealth(health), attackDamage(attackDamage), defense(defense) {
        if (!texture.loadFromFile(texturePath)) {
            std::cerr << "Failed to load Enem texture: " << texturePath << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(rectsprite);
        sprite.setPosition(initialPosition);
        sprite.setScale(initialScale);
    }


    // Getter methods
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getAttackDamage() const { return attackDamage; }
    int getDefense() const { return defense; }

    // Setter methods
    void setName(std::string newName) { name = newName; }
    void setHealth(int newHealth) { health = newHealth; }
    void setMaxHealth(int newMaxHealth) { maxHealth = newMaxHealth; }
    void setAttackDamage(int newAttackDamage) { attackDamage = newAttackDamage; }
    void setDefense(int newDefense) { defense = newDefense; }

    // Other methods
    void takeDamage(int damage) {
        int actualDamage = damage - defense;
        if (actualDamage < 0) {
            actualDamage = 0; // Ensure damage is non-negative
            defense -= damage; // break shield
        }
        health -= actualDamage;
    }

    bool isAlive() const {
        return health > 0;
    }

    // Virtual method for attacking
    virtual int attack() const = 0;

    sf::Sprite sprite;
    sf::IntRect rectsprite;
    sf::Texture texture;
    int val = 0;

protected:
    std::string name;
    int health;
    int maxHealth;
    int attackDamage;
    int defense;

};


// Enem Type 1: 30, 5, 2,
class Goblin : public Enem {
public:
    Goblin() : Enem("Goblin", 15, 5, 4, "MENU/Images/Enemies/Goblincropped.png", sf::IntRect(0, 0, 50, 80), sf::Vector2f(90, 30), sf::Vector2f(6, 6)) {
        //// Assign values to private members in the constructor
        rectsprite = sf::IntRect(0, 0, 50, 80);
        sprite = sf::Sprite(texture, rectsprite);
        val = 150;
    }

    // Override the attack method
    int attack() const override {
        // Implement dark dwarf-specific attack behavior here
        return attackDamage;
    }


};


// Enem Type 2: 80, 15, 8,
class DarkDwarf : public Enem {
public:
    DarkDwarf() : Enem("Dark Dwarf", 10, 15, 8, "MENU/Images/Enemies/DarkDwarfcropped.png", sf::IntRect(0, 0, 80, 100), sf::Vector2f(60, 0), sf::Vector2f(5, 5)) {

        rectsprite = sf::IntRect(0, 0, 80, 100);
        sprite = sf::Sprite(texture, rectsprite);
        val = 199;

    }

    // Override the attack method
    int attack() const override {
        // Implement dark dwarf-specific attack behavior here
        return attackDamage;
    }



};

// Enem Type 3: 30, 20, 3,
class GiantBat : public Enem {
public:
    GiantBat() : Enem("Giant Bat", 10, 20, 3, "MENU/Images/Enemies/GiantBatcropped2.png", sf::IntRect(0, 0, 66, 74), sf::Vector2f(100, 60), sf::Vector2f(4.5, 4.5)) {

        rectsprite = sf::IntRect(0, 0, 66, 74);
        sprite = sf::Sprite(texture, rectsprite);

        val = 190;
    }

    // Override the attack method
    int attack() const override {
        // Implement giant bat-specific attack behavior here
        return attackDamage;
    }


};

// Enem Type 4: 100, 25, 15,
class EvilMage : public Enem {
public:
    EvilMage() : Enem("Evil Mage", 10, 25, 3, "MENU/Images/Enemies/DarkMagecropped2.png", sf::IntRect(0, 0, 80, 95), sf::Vector2f(90, 30), sf::Vector2f(5, 5)) {

        rectsprite = sf::IntRect(0, 0, 80, 95);
        sprite = sf::Sprite(texture, rectsprite);

        val = 320;

    }

    // Override the attack method
    int attack() const override {
        // Implement evil mage-specific attack behavior here
        return attackDamage;
    }

};

class Kane : public Enem {
public:
    Kane() : Enem("Kane. ", 100, 20, 15, "MENU/Images/Enemies/BossKanecropped.png", sf::IntRect(-8, 0, 90, 95), sf::Vector2f(140, 180), sf::Vector2f(4.5, 4.5)) {

        rectsprite = sf::IntRect(-8, 0, 90, 95);
        sprite = sf::Sprite(texture, rectsprite);

        val = 360;

    }

    // Override the attack method
    int attack() const override {
        // Implement evil mage-specific attack behavior here
        return attackDamage;
    }

};