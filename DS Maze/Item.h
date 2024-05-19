#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding random number generator
#include <sstream>

using namespace std;
using namespace sf;
class Item {
public:
    Item(string name, int value) : name(name), value(value) {}

    string getName() const {
        return name;
    }

    int getValue() const {
        return value;
    }

    virtual int use(int) = 0; // Make it a pure virtual function to make Item an abstract class

private:
    string name;
    int value;
};

class Weapon : public Item {
public:
    struct Type {
        static const string Sword;
    };

    struct Rarity {
        static const string Normal;
        static const string Rare;
    };

    Weapon(string name, int value, int damage, string type, string rarity) : Item(name, value), damage(damage), type(type), rarity(rarity) {}

    int getDamage() const {
        return damage;
    }

    string getType() const {
        return type;
    }

    string getRarity() const {
        return rarity;
    }

    int getActualDamage() const {
        return (rarity == Rarity::Rare) ? damage * 4 : damage;
    }

private:
    int damage;
    string type;
    string rarity;
};

const string Weapon::Type::Sword = "Sword";

const string Weapon::Rarity::Normal = "Normal";
const string Weapon::Rarity::Rare = "Rare";

class Potion : public Item {
public:
    Potion(string name, int value, int effect) : Item(name, value), effect(effect) {}

    int getEffect() const {
        return effect;
    }

    virtual int use(int) = 0; // Make it a pure virtual function to make Potion an abstract class

protected:
    int updateEffect(int& value) const {
        value += getEffect();

        return value;
    }

    int effect;
};

class RedPotion : public Potion {
public:
    RedPotion() : Potion("Small Red", 25, 50) {} // Small Red Potion heals 50 HP

    int use(int health)  override {
        cout << "Using Small Red Potion..." << endl;
        // Add healing logic here to heal 50 HP

        int maxHp = 100; // Assuming max HP is 200
        updateEffect(hp);
        if (health > maxHp) {
            health = maxHp;
        }
        else {
            health += 10;
        }
        cout << "Healed " << getEffect() << " HP" << endl;
        return health;
    }

private:
    int hp = 100; // Mutable to allow modification inside const member function
};

class LargeRedPotion : public Potion {
public:
    LargeRedPotion() : Potion("Large Red", 50, 100) {} // Large Red Potion heals 100 HP

    int use(int health)  override {
        cout << "Using Large Red Potion..." << endl;
        // Add healing logic here to heal 100 HP
        int maxHp = 100; // Assuming max HP is 200
        updateEffect(hp);
        if (health > maxHp) {
            health = maxHp;
        }
        else {
            health += 20;
        }
        cout << "Healed " << getEffect() << " HP" << endl;
        return health;
    }

private:
    int hp = 100; // Mutable to allow modification inside const member function
};

class YellowPotion : public Potion {
public:
    YellowPotion() : Potion("Small Yellow", 25, 2) {} // Small Yellow Potion doubles attack

    int use(int a)  override {
        cout << "Using Small Yellow Potion..." << endl;
        // Add attack doubling logic here
        updateEffect(attack);
        cout << "Attack doubled to " << getEffect() << endl;

        return a;
    }

private:
    int attack = 2; // Mutable to allow modification inside const member function
};

class LargeYellowPotion : public Potion {
public:
    LargeYellowPotion() : Potion("Large Yellow", 50, 4) {} // Large Yellow Potion quadruples attack

    int use(int a)  override {
        cout << "Using Large Yellow Potion..." << endl;
        // Add attack quadrupling logic here
        updateEffect(attack);
        cout << "Attack quadrupled to " << getEffect() << endl;

        return a;
    }

private:
    int attack = 2; // Mutable to allow modification inside const member function
};

// AVL Node
template<typename T>
class AVLNode {
public:
    T data;
    int height;
    AVLNode<T>* left;
    AVLNode<T>* right;

    AVLNode(T value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

// AVL Tree
template<typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    // Get height of a node
    int getHeight(AVLNode<T>* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Update height of a node
    void updateHeight(AVLNode<T>* node) {
        if (node != nullptr)
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    // Get balance factor of a node
    int getBalanceFactor(AVLNode<T>* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Rotate right
    AVLNode<T>* rotateRight(AVLNode<T>* node) {
        AVLNode<T>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    // Rotate left
    AVLNode<T>* rotateLeft(AVLNode<T>* node) {
        AVLNode<T>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    // Balance the AVL tree
    AVLNode<T>* balance(AVLNode<T>* node) {
        updateHeight(node);
        int balanceFactor = getBalanceFactor(node);

        // Left heavy
        if (balanceFactor > 1) {
            // Left Right Case
            if (getBalanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        // Right heavy
        else if (balanceFactor < -1) {
            // Right Left Case
            if (getBalanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    // Insert a node into the AVL tree
    AVLNode<T>* insert(AVLNode<T>* node, T value) {
        if (node == nullptr)
            return new AVLNode<T>(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else
            return node; // Duplicate values not allowed

        return balance(node);
    }

    // Remove a node from the AVL tree
    AVLNode<T>* remove(AVLNode<T>* node, T value) {
        if (node == nullptr)
            return nullptr;

        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                AVLNode<T>* temp = (node->left == nullptr) ? node->right : node->left;
                delete node;
                return temp;
            }
            else {
                AVLNode<T>* successor = findMin(node->right);
                node->data = successor->data;
                node->right = remove(node->right, successor->data);
            }
        }
        return balance(node);
    }

    // Find the minimum node in the AVL tree
    AVLNode<T>* findMin(AVLNode<T>* node) {
        if (node == nullptr)
            return nullptr;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Delete the entire AVL tree
    void clear(AVLNode<T>* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    AVLNode<T>* search(AVLNode<T>* node, T value) {
        if (node == nullptr || node->data == value)
            return node;

        if (value < node->data)
            return search(node->left, value);
        else
            return search(node->right, value);
    }

public:
    AVLTree() : root(nullptr) {}

    // Insert a value into the AVL tree
    void insert(T value) {
        root = insert(root, value);
    }

    // Remove a value from the AVL tree
    void remove(T value) {
        root = remove(root, value);
    }

    // Check if a value exists in the AVL tree
    bool contains(T value) {
        AVLNode<T>* current = root;
        while (current != nullptr) {
            if (value < current->data)
                current = current->left;
            else if (value > current->data)
                current = current->right;
            else
                return true;
        }
        return false;
    }

    // Clear the AVL tree
    void clear() {
        clear(root);
        root = nullptr;
    }
    bool contain(T value) {
        return search(root, value) != nullptr;
    }
    ~AVLTree() {
        clear();
    }
};
class Inventory {
private:
    AVLTree<Item*> items;
    Weapon* selectedWeapon;
    Potion* selectedPotion;
    int redPotionCount;
    int yellowPotionCount;
    bool flag; // Flag to indicate whether to search for red potions or yellow potions

public:
    Inventory() : selectedWeapon(nullptr), selectedPotion(nullptr), redPotionCount(0), yellowPotionCount(0), flag(true) {}

    void addDefaultRedPotions(int count)
    {
        for (int i = 0; i < count; ++i)
        {
            addItem(new RedPotion());
        }
    }

    // Add an item to the inventory
    void addItem(Item* item) {
        if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
            if (!items.contains(weapon)) {
                items.insert(weapon);
            }
        }
        else if (RedPotion* potion = dynamic_cast<RedPotion*>(item)) {
            redPotionCount++;
        }
        else if (YellowPotion* potion = dynamic_cast<YellowPotion*>(item)) {
            yellowPotionCount++;
        }
    }

    // Remove an item from the inventory
    void removeItem(Item* item) {
        if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
            items.remove(weapon);
            if (selectedWeapon == weapon) {
                selectedWeapon = nullptr;
            }
        }
        else if (RedPotion* potion = dynamic_cast<RedPotion*>(item)) {
            if (redPotionCount > 0) {
                redPotionCount--;
            }
            if (selectedPotion == potion) {
                selectedPotion = nullptr;
            }
        }
        else if (YellowPotion* potion = dynamic_cast<YellowPotion*>(item)) {
            if (yellowPotionCount > 0) {
                yellowPotionCount--;
            }
            if (selectedPotion == potion) {
                selectedPotion = nullptr;
            }
        }
    }

    // Check if an item is in the inventory
    bool containsItem(Item* item) {
        if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
            return items.contains(weapon);
        }
        else if (RedPotion* potion = dynamic_cast<RedPotion*>(item)) {
            return redPotionCount > 0;
        }
        else if (YellowPotion* potion = dynamic_cast<YellowPotion*>(item)) {
            return yellowPotionCount > 0;
        }
        return false;
    }

    // Select a weapon from the inventory
    void selectWeapon(Weapon* weapon) {
        if (containsItem(weapon)) {
            selectedWeapon = weapon;
        }
    }

    // Select a potion from the inventory based on the search flag
    void selectPotion(bool searchRed) {
        flag = searchRed;
        if (flag) {
            if (containsItem(new RedPotion())) {
                selectedPotion = new RedPotion();
            }
            else {
                selectedPotion = nullptr;
            }
        }
        else {
            if (containsItem(new YellowPotion())) {
                selectedPotion = new YellowPotion();
            }
            else {
                selectedPotion = nullptr;
            }
        }
    }

    // Use the selected potion
    int useSelectedPotion(int health) {
        int healh;
        if (selectedPotion != nullptr) {
            healh = selectedPotion->use(health);
            removeItem(selectedPotion); // Remove used potion from inventory
        }
        return healh;
    }

    // Get the selected weapon
    Weapon* getSelectedWeapon() const {
        return selectedWeapon;
    }

    // Get the selected potion
    Potion* getSelectedPotion() const {
        return selectedPotion;
    }

    // Clear the inventory
    void clear() {
        items.clear();
        redPotionCount = 0;
        yellowPotionCount = 0;
        selectedWeapon = nullptr;
        selectedPotion = nullptr;
    }

};