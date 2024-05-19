#pragma once

#include "UserInterface.h"
#include "Menu.h"
#include <stdlib.h>

int scoreflag; // Flag to track if the score has been updated
char scor[20]; // Array to store the score as a string

// Create instance of Menu class
//Menu m;

// Load function to initialize game + called repeatedly by startGame case 1
void Load()
{
    // Generate a random maze using back tracking algo + run only once and will return back for next time as case is handled in else if
    GenerateMaze();

    // Initialize drawing i.e set up maze graph with path and wall textures  + called repeatedly and drawn everytime
    DrawInitialize();
    // Get solution for the maze ready and update it based on player's current position and its visited paths BUT doesnt draw it yet
    GetSolution();

    return;
}

// Main game loop
void startGame(sf::RenderWindow& myWindow, Menu& m)
{
    switch (GameState)
    {
        // If game state is 0 (Menu)
        case 0: 
        {
            // Run menu
            m.runMenu(myWindow);
            return;
            break;
        }

        case 1: // Start mode + constantly run case 
        {
            // Load game (GenerateMaze only called once but other two are repeatedly called ), (maze generate + maze graph set + solution generated but not drawn)
            Load();

            // player input is handled + player position is updated based on arrow keys + final dot reached is checked
            playermovement();
            enemymovement();

            // Display side menu (cases handled for name, mute, pause, giveup, home)
            SideMenu(myWindow);

            // Draw maze if not paused clicked also when name input is done
            if (sideMenuState != 2 && sideMenuState) {
                //draws player sprite + makes trail of player(cyan) + makes final dot (blue) + draws borders
                DrawMaze(myWindow);
            }
            // Set score flag to 1 meaning level started
            scoreflag = 1;
            break;
        }

        case 3: // Successfully completed level (GameState was checked and updated in playermovement())
        {
            // Display side menu (cases handled for name, mute, pause, giveup, home)
            SideMenu(myWindow);

            // Draw "Solved" box
            myWindow.draw(solvedButton);

            // Get mouse position
            sf::Vector2i mousePos = sf::Mouse::getPosition(myWindow);

            // Update total score if score flag is set (successfully completion of level will set it to 1)
            if (scoreflag) {
                totalScore += score;
                scoreflag = 0;
            }

            // Level complete score show

            // Convert total score to string
            _itoa_s(totalScore, scor, score);
            // Set score text
            _score.setString(scor);
            // Convert string score to integer
            int new_score = stoi(scor);
            // Update total score
            totalScore = new_score;
            _score.setPosition(590, 335);
            // Draw score
            myWindow.draw(_score);

            // If ">>" button is clicked, reset game
            if (mousePos.x >= 531 && mousePos.x <= 586 && mousePos.y >= 390 && mousePos.y <= 436 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                // Function to clear the maze and solution grid and reset values and clean cyan/red trails
                clearMaze();
                // Set game state to 1 (Play mode)
                GameState = 1;
                // initiate level again and the cells and graph location based on difficulty. Also set initial position for player
                LevelInitiate();
            }
            break;
        }

        // when give up is clicked in SideMenu();
        case 4: // Drawing maze and solution
        {
            // Display side menu
            SideMenu(myWindow);
            // Draw maze
            DrawMaze(myWindow);
            // Draw solution
            DrawSolution(myWindow);
            break;
        }
    }

    return;
}
