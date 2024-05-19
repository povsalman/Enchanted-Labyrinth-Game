#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include"Highscore.h"
#include"player.h"

using namespace std;

class Menu {
private:
    sf::Font arialFont;
    sf::Font minecraftFont;
    sf::Text title;
    sf::Text menuOptions[5];
    int selectedItemIndex;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music backgroundMusic; // Background music

public:
    const static int NewGame = 0;
    const static int Difficulty = 1;
    const static int Highscore = 2;
    const static int Instructions = 3;
    const static int Exit = 4;

    Menu() {};

    Menu(float width, float height) {
        // Load Arial font
        if (!arialFont.loadFromFile("Menu/arial.ttf")) {
            cerr << "Error loading Arial font" << endl;
        }

        // Load Minecraft font
        if (!minecraftFont.loadFromFile("Menu/minecraft.ttf")) {
            cerr << "Error loading Minecraft font" << endl;
        }

        if (!backgroundTexture.loadFromFile("Menu/MainMenu01.png")) {
            cerr << "Error loading background texture" << endl;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(width / backgroundSprite.getLocalBounds().width, height / backgroundSprite.getLocalBounds().height);

        // Load background music
        if (!backgroundMusic.openFromFile("Menu/yt1s.com-Bigbys-Apartment-Theme.ogg")) {
            cerr << "Error loading background music" << endl;
        }
        backgroundMusic.setLoop(true); // Make the music loop

        // Calculate vertical spacing between menu options
        float verticalSpacing = (height * 0.8f) / 5;

        // Set up title
        title.setFont(minecraftFont); // Set font to Minecraft font
        title.setString("Arcadia");
        title.setCharacterSize(70); // Larger size for the title
        title.setFillColor(sf::Color::Green);
        title.setPosition(sf::Vector2f(width / 2 - title.getLocalBounds().width / 2, height / 5));

        // Set up menu options
        for (int i = 0; i < 5; ++i) {
            menuOptions[i].setFont(minecraftFont); // Set font to Arial font
            menuOptions[i].setFillColor(sf::Color::White);
        }

        menuOptions[NewGame].setFillColor(sf::Color::Red);
        menuOptions[NewGame].setString("New Game");
        menuOptions[NewGame].setPosition(sf::Vector2f(width / 2 - menuOptions[NewGame].getLocalBounds().width / 2, height / 2 - verticalSpacing * 1));

        menuOptions[Difficulty].setString("Difficulty");
        menuOptions[Difficulty].setPosition(sf::Vector2f(width / 2 - menuOptions[Difficulty].getLocalBounds().width / 2, height / 2 - verticalSpacing * 0.5));

        menuOptions[Highscore].setString("Highscore");
        menuOptions[Highscore].setPosition(sf::Vector2f(width / 2 - menuOptions[Highscore].getLocalBounds().width / 2, height / 2 ));

        menuOptions[Instructions].setString("Instructions");
        menuOptions[Instructions].setPosition(sf::Vector2f(width / 2 - menuOptions[Instructions].getLocalBounds().width / 2, height / 2 + verticalSpacing * 0.5));

        menuOptions[Exit].setString("Exit");
        menuOptions[Exit].setPosition(sf::Vector2f(width / 2 - menuOptions[Exit].getLocalBounds().width / 2, height / 2 + verticalSpacing * 1));

        selectedItemIndex = NewGame;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(backgroundSprite);
        window.draw(title); // Draw the title
        for (int i = 0; i < 5; i++) {
            window.draw(menuOptions[i]);
        }
    }

    void MoveUp() {
        if (selectedItemIndex - 1 >= 0) {
            menuOptions[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex--;
            menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    void MoveDown() {
        if (selectedItemIndex + 1 < 5) {
            menuOptions[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex++;
            menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    int GetPressedItem() {
        return selectedItemIndex;
    }

    void PlayBackgroundMusic() {
        backgroundMusic.play();
    }

    void showInstructions(sf::RenderWindow& window) {
        // Instruction title text
        sf::Text instructionTitle;
        instructionTitle.setFont(minecraftFont);
        instructionTitle.setString("Instructions");
        instructionTitle.setCharacterSize(48); // Larger size for the title
        instructionTitle.setFillColor(sf::Color::Green); // Set color to green
        instructionTitle.setPosition(window.getSize().x / 2.0f - instructionTitle.getLocalBounds().width / 2, window.getSize().y / 8.0f);

        // Instructions text
        sf::Text instructions;
        instructions.setFont(minecraftFont);
        instructions.setString(
            "- Use arrow keys to navigate the maze.\n"
            "- Press 'A' to attack.\n"
            "- Press 'S' to use an item.\n"
            "- Press 'D' to flee.\n"
            "- Press 'Esc' to return to the main menu.");
        instructions.setCharacterSize(36); // Increased font size
        instructions.setFillColor(sf::Color::Blue);

        // Center the text on the screen
        sf::FloatRect textRect = instructions.getLocalBounds();
        instructions.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        instructions.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

        while (window.isOpen()) {
            window.clear();
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        return; // Return to the main menu
                        break;
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }
            window.draw(backgroundSprite);
            window.draw(instructionTitle); // Draw the instruction title
            window.draw(instructions);
            window.display();
        }
    }


    void ShowHighscore(sf::RenderWindow& window) {
        // Title text
        sf::Text highscoreTitle;
        highscoreTitle.setFont(minecraftFont);
        highscoreTitle.setString("Highscores");
        highscoreTitle.setCharacterSize(48); // Larger size for the title
        highscoreTitle.setFillColor(sf::Color::Green); // Set color to green
        highscoreTitle.setPosition(window.getSize().x / 2.0f - highscoreTitle.getLocalBounds().width / 2, window.getSize().y / 8.0f);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.clear();
                        return;
                        break;
                    case sf::Event::Closed:
                        window.close();
                        break;
                    }
                }
                window.clear();

                // Draw background
                window.draw(backgroundSprite);

                // Draw title
                window.draw(highscoreTitle);

                // Load and display highscores
                _score.setPosition(380, 230); //reset score position for level end score
                loadHighscores();
                window.draw(_score);
                window.display();
            }
        }
    }


    void SelectDifficulty(sf::RenderWindow& window) {
        int selectedItemIndex = 0; // Initially select the first difficulty option
        sf::Text title;
        sf::Text Difficulty[4]; // Array to store difficulty options

        // Set up title
        title.setFont(minecraftFont); // Set font to Minecraft font
        title.setString("Choose Difficulty");
        title.setCharacterSize(48); // Larger size for the title
        title.setFillColor(sf::Color::Green); // Set color to green
        title.setPosition(window.getSize().x / 2.0f - title.getLocalBounds().width / 2, window.getSize().y / 8.0f);

        // Set up difficulty options
        for (int i = 0; i < 4; ++i) {
            Difficulty[i].setFont(minecraftFont); // Set font to Minecraft font
            Difficulty[i].setCharacterSize(36); // Set font size
            Difficulty[i].setFillColor(sf::Color::White); // Set initial color
            Difficulty[i].setString(""); // Set the string for now, to be updated later
        }

        // Update difficulty option strings
        Difficulty[0].setString("Easy");
        Difficulty[1].setString("Normal");
        Difficulty[2].setString("Hard");
        Difficulty[3].setString("Nightmare");

        // Calculate vertical position for difficulty options
        float verticalSpacing = (window.getSize().y * 0.8f) / 7;
        float verticalCenter = window.getSize().y / 2.0f;

        // Set initial positions for difficulty options
        for (int i = 0; i < 4; ++i) {
            Difficulty[i].setPosition(sf::Vector2f(window.getSize().x / 2.0f - Difficulty[i].getLocalBounds().width / 2, verticalCenter - verticalSpacing * 1.5 + i * verticalSpacing));
        }

        // Highlight the initially selected difficulty option
        Difficulty[selectedItemIndex].setFillColor(sf::Color::Red);

        while (window.isOpen()) {
            window.clear();
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selectedItemIndex > 0) {
                            Difficulty[selectedItemIndex].setFillColor(sf::Color::White); // Set the previously selected difficulty option to white
                            selectedItemIndex--; // Move to the previous difficulty option
                            Difficulty[selectedItemIndex].setFillColor(sf::Color::Red); // Highlight the new selected difficulty option
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (selectedItemIndex < 3) {
                            Difficulty[selectedItemIndex].setFillColor(sf::Color::White); // Set the previously selected difficulty option to white
                            selectedItemIndex++; // Move to the next difficulty option
                            Difficulty[selectedItemIndex].setFillColor(sf::Color::Red); // Highlight the new selected difficulty option
                        }
                        break;
                    case sf::Keyboard::Enter:
                        switch (selectedItemIndex) {
                        case 0:
                            cout << "Easy selected" << endl;
                            GameLevel = 1;
                            break;
                        case 1:
                            cout << "Normal selected" << endl;
                            GameLevel = 2;
                            break;
                        case 2:
                            cout << "Hard selected" << endl;
                            GameLevel = 3;
                            break;
                        case 3:
                            cout << "Nightmare selected" << endl;
                            GameLevel = 4;
                            break;
                        }
                        break;
                    case sf::Keyboard::Escape:
                        return; // Return to the main menu
                        break;
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }

            window.clear();
            window.draw(backgroundSprite);
            // Draw difficulty options
            for (int i = 0; i < 4; ++i) {
                window.draw(Difficulty[i]);
            }
            // Draw title
            window.draw(title);
            window.display();
        }
    }

    void runMenu(sf::RenderWindow& window) {

        //sf::RenderWindow window(sf::VideoMode(1280, 800), "Menu");
        Menu menu(window.getSize().x, window.getSize().y);

        menu.PlayBackgroundMusic(); // Play background music

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem()) {
                        case Menu::NewGame:
                            cout << "New Game selected" << endl;
                            GameState = 1;
                            LevelInitiate();        // initiate level cells and graph location based on difficulty. Also set initial position for player
                            return;                 // go back to main.cpp
                            break;
                        case Menu::Highscore:
                            cout << "Highscore selected" << endl;
                            menu.ShowHighscore(window);
                            break;
                        case Menu::Instructions:
                            cout << "Instructions selected" << endl;
                            menu.showInstructions(window);
                            break;
                        case Menu::Difficulty:
                            cout << "Difficulty selected" << endl;
                            menu.SelectDifficulty(window);
                            break;
                        case Menu::Exit:
                            window.close();
                            return;
                            break;
                        }
                        break;
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }
            window.clear();

            menu.draw(window);
            window.display();
        }

        return;
    }

};
