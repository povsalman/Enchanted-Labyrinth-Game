//#pragma once
//
//#include"SFML/graphics.hpp"
//#include<stack>
//#include <ctime>
//#include<iostream>
//using namespace std;
//
//stack <pair <int, int >> CellStack;
//sf::Texture wallTexture;
//sf::Texture pathTexture;
//sf::Texture solve;
//
//struct Cell {
//	bool isWall = true;
//	bool visitedByPlayer = false;
//	bool visited = false;
//};
//
//struct Position {
//	int x;
//	int y;
//};
//
//Cell cell[110][72];
//sf::RectangleShape rect[110][72];
//sf::RectangleShape border[4];
//int nCells, mCells, endX, endY;
//Position initialPos, finalPos;
//
//Position CurrentCell;
//
///////
//
//
//int GetNeighbour(int X,int Y)
//{
//	int east, west, north, south,dice;
//	Y + 2 <mCells && !cell[X][Y+2].visited ? east = 1 : east = 10;
//	Y - 2 >=0 && !cell[X][Y-2].visited ? west = 2 : west = 10;
//	X - 2 >=0 && !cell[X - 2][Y].visited ? north = 3 : north = 10;
//	X + 2 < nCells && !cell[X + 2][Y].visited ? south = 4 : south = 10;
//	if (east == 10 && west == 10 && north == 10 && south == 10)
//		return 0;
//	while (1){
//		dice = (rand() % 4) + 1;
//		if (dice == east)
//			return 1;
//		else if (dice == west)
//			return 2;
//		else if (dice == north)
//			return 3;
//		else if (dice == south)
//			return 4;
//	}
//
//
//}
////::::::::::::::::::::::::::::::::AlGORITHM:::::::::::::::::::::::::::::::::
//void initialize()
//{
//	
//	CurrentCell.x = 0;
//	CurrentCell.y = 0;
//	cell[CurrentCell.x][CurrentCell.y].visited = true;
//	cell[CurrentCell.x][CurrentCell.y].isWall = false;
//	CellStack.push(make_pair(CurrentCell.x, CurrentCell.y));
//
//}
//void GenerateMaze(){
//	initialize();
//	while (1)
//	{
//		int neighbour = GetNeighbour(CurrentCell.x,CurrentCell.y);
//
//		if (neighbour == 1)
//	    {
//			cell[CurrentCell.x][CurrentCell.y + 1].isWall = false;
//			cell[CurrentCell.x][CurrentCell.y + 2].isWall = false;
//			cell[CurrentCell.x][CurrentCell.y + 2].visited = true;
//			CellStack.push(make_pair(CurrentCell.x, CurrentCell.y+2));
//			CurrentCell.y += 2;
//   		}
//		else if (neighbour == 2)
//		{
//			cell[CurrentCell.x][CurrentCell.y - 1].isWall = false;
//			cell[CurrentCell.x][CurrentCell.y - 2].isWall = false;
//			cell[CurrentCell.x][CurrentCell.y - 2].visited = true;
//			CellStack.push(make_pair(CurrentCell.x, CurrentCell.y - 2));
//			CurrentCell.y -= 2;
//		}
//		else if (neighbour == 3)
//		{
//			cell[CurrentCell.x-1][CurrentCell.y].isWall = false;
//			cell[CurrentCell.x-2][CurrentCell.y].isWall = false;
//			cell[CurrentCell.x-2][CurrentCell.y].visited = true;
//			CellStack.push(make_pair(CurrentCell.x-2, CurrentCell.y));
//			CurrentCell.x -= 2;
//		}
//		else if (neighbour == 4)
//		{
//			cell[CurrentCell.x + 1][CurrentCell.y].isWall = false;
//			cell[CurrentCell.x + 2][CurrentCell.y].isWall = false;
//			cell[CurrentCell.x + 2][CurrentCell.y].visited = true;
//			CellStack.push(make_pair(CurrentCell.x + 2, CurrentCell.y));
//			CurrentCell.x += 2;
//		}
//
//		else if (CurrentCell.x == 0 && CurrentCell.y == 0)
//		{
//			break;
//		}
//
//		else
//		{
//			CellStack.pop();
//			CurrentCell.x = CellStack.top().first;
//			CurrentCell.y = CellStack.top().second;
//		
//		}
//		  
//	}
//}
////::::::::::::::::::::::::::::::::::::::solution:::::::::::::::::::::::::::::::::::::::::::::::::::
//
//int maze[128][72];
//bool wasHere[128][72];
//bool correctPath[128][72];
//int startX = 0, startY = 0;
//
//void IniSolution()
//{
//	for (int i = 0; i < nCells; i++)
//	{
//		for (int j = 0; j < mCells; j++)
//		{
//			wasHere[i][j] = false;
//			correctPath[i][j] = false;
//			cell[i][j].isWall ? maze[i][j] = 2 : maze[i][j] = 1;
//		}
//	}
//
//}
//
//bool recursiveSolve(int x, int y)
//{
//	if (x == endX&&y == endY)
//		return true;
//	if (maze[x][y] == 2 || wasHere[x][y])
//		return false;
//	wasHere[x][y] = true;
//	if (x != 0)
//	if (recursiveSolve(x - 1, y)) { 
//		correctPath[x][y] = true; 
//		return true;
//	}
//	if (x != nCells - 1) 
//	if (recursiveSolve(x + 1, y)) { 
//		correctPath[x][y] = true;
//		return true;
//	}
//	if (y != 0)  
//	if (recursiveSolve(x, y - 1)) { 
//		correctPath[x][y] = true;
//		return true;
//	}
//	if (y != mCells - 1) 
//	if (recursiveSolve(x, y + 1)) { 
//		correctPath[x][y] = true;
//		return true;
//	}
//	return false;
//}
//void GetSolution()
//{
//	IniSolution();
//	recursiveSolve(startX, startY);
//}
//
//void clearMaze()
//{
//	for (int i = 0; i < nCells; i++)
//	for (int j = 0; j < mCells; j++)
//	{
//		cell[i][j].visitedByPlayer = false;
//		cell[i][j].isWall = true;
//		cell[i][j].visited = false;
//		maze[i][j]=0;
//		rect[i][j].setFillColor(sf::Color::White);
//		correctPath[i][j] = false;
//		startX = 0;
//		startY = 0;
//		endX = 0;
//		endY = 0;
//	}
//}

#pragma once

#include"SFML/graphics.hpp"
#include<stack>
#include <ctime>
#include<iostream>

//#ifndef PLAYER_H
//#define PLAYER_H

using namespace std;

// Stack to keep track of visited cells during maze generation
stack<pair<int, int>> CellStack;

// Texture for walls and paths in the maze
sf::Texture wallTexture;
sf::Texture pathTexture;
sf::Texture solve; // Texture for indicating the solution path

// Structure representing a cell in the maze
struct Cell {
    bool isWall = true; // Flag indicating whether the cell is a wall or a path
    bool visitedByPlayer = false; // Flag indicating whether the cell has been visited by the player
    bool visited = false; // Flag indicating whether the cell has been visited during maze generation
};

// 2D array representing the maze grid
Cell cell[110][72];

// 2D array representing the graphical representation of the maze cells
sf::RectangleShape rect[110][72];

// Array of rectangles representing the border of the maze
sf::RectangleShape border[4];

// Dimensions of the maze grid and endpoints
int nCells, mCells; // Number of cells in the maze grid
int endX, endY; // Endpoints of the maze

// Position of the initial and final cells
struct Position {
    int x;
    int y;
};

Position initialPos; // Initial position of the maze
Position finalPos; // Final position of the maze

// Current cell being processed during maze generation
Position CurrentCell;


//::::::::: For Solution :::::::::

// Define a 2D array to represent the maze
int maze[128][72];
// Array to keep track of visited cells during maze solving
bool wasHere[128][72];
// Array to mark cells that are part of the correct path through the maze
bool correctPath[128][72];
// Starting position of the maze solver algorithm
int startX = 0, startY = 0;


// In 'maze':
// - Each element represents a cell in the maze.
// - '0' typically indicates a wall, and '1' indicates an open path.
// - Simple representation of maze layout using integers.

// In 'cell':
// - Each element represents a cell in the maze.
// - Uses a custom structure 'Cell' to store detailed information about each cell.
// - Provides more detailed information about each cell's state and properties.



// Function to get a random neighbor of a cell during maze generation
int GetNeighbour(int X, int Y) {
    // Define possible directions for neighboring cells
    int east, west, north, south, dice;

    // Check if neighboring cells are within bounds and unvisited
    Y + 2 < mCells && !cell[X][Y + 2].visited ? east = 1 : east = 10;
    Y - 2 >= 0 && !cell[X][Y - 2].visited ? west = 2 : west = 10;
    X - 2 >= 0 && !cell[X - 2][Y].visited ? north = 3 : north = 10;
    X + 2 < nCells && !cell[X + 2][Y].visited ? south = 4 : south = 10;

    // If no unvisited neighbors are available, return 0
    if (east == 10 && west == 10 && north == 10 && south == 10)
        return 0;

    // Randomly select one of the unvisited neighbors
    while (1) {
        dice = (rand() % 4) + 1;
        if (dice == east)
            return 1;
        else if (dice == west)
            return 2;
        else if (dice == north)
            return 3;
        else if (dice == south)
            return 4;
    }
}

// Function to initialize maze generation
void initialize() {
    // Start maze generation from a random cell
    CurrentCell.x = 0;
    CurrentCell.y = 0;
    cell[CurrentCell.x][CurrentCell.y].visited = true;
    cell[CurrentCell.x][CurrentCell.y].isWall = false;
    CellStack.push(make_pair(CurrentCell.x, CurrentCell.y));
}

// Function to generate the maze using backtracking algorithm + called repeatedly but will run only once and will return back for next time as case is handled in else if
void GenerateMaze() {

    //// Generate maze only if it hasn't been generated yet
    //static bool isinitialized = false;
    //if (!isinitialized) {
    //    initialize();
    //    isinitialized = true;
    //}

    initialize(); // Initialize maze generation using a random cell

    while (1) {
        // Get a random unvisited neighbor of the current cell
        int neighbour = GetNeighbour(CurrentCell.x, CurrentCell.y);

        // Based on the neighbor direction, create a path by removing walls
        if (neighbour == 1) {
            cell[CurrentCell.x][CurrentCell.y + 1].isWall = false;
            cell[CurrentCell.x][CurrentCell.y + 2].isWall = false;
            cell[CurrentCell.x][CurrentCell.y + 2].visited = true;
            CellStack.push(make_pair(CurrentCell.x, CurrentCell.y + 2));
            CurrentCell.y += 2;
        }
        else if (neighbour == 2) {
            cell[CurrentCell.x][CurrentCell.y - 1].isWall = false;
            cell[CurrentCell.x][CurrentCell.y - 2].isWall = false;
            cell[CurrentCell.x][CurrentCell.y - 2].visited = true;
            CellStack.push(make_pair(CurrentCell.x, CurrentCell.y - 2));
            CurrentCell.y -= 2;
        }
        else if (neighbour == 3) {
            cell[CurrentCell.x - 1][CurrentCell.y].isWall = false;
            cell[CurrentCell.x - 2][CurrentCell.y].isWall = false;
            cell[CurrentCell.x - 2][CurrentCell.y].visited = true;
            CellStack.push(make_pair(CurrentCell.x - 2, CurrentCell.y));
            CurrentCell.x -= 2;
        }
        else if (neighbour == 4) {
            cell[CurrentCell.x + 1][CurrentCell.y].isWall = false;
            cell[CurrentCell.x + 2][CurrentCell.y].isWall = false;
            cell[CurrentCell.x + 2][CurrentCell.y].visited = true;
            CellStack.push(make_pair(CurrentCell.x + 2, CurrentCell.y));
            CurrentCell.x += 2;
        }
        // If no unvisited neighbors are available, backtrack
        else if (CurrentCell.x == 0 && CurrentCell.y == 0) {
            break;
        }
        else {
            CellStack.pop(); // Backtrack
            CurrentCell.x = CellStack.top().first;
            CurrentCell.y = CellStack.top().second;
        }
    }

    return;
}

// Function to initialize the solution grid for maze solving
void IniSolution() {
    for (int i = 0; i < nCells; i++) {
        for (int j = 0; j < mCells; j++) {
            // Reset solution grid and maze visualization
            wasHere[i][j] = false;
            correctPath[i][j] = false;
            cell[i][j].isWall ? maze[i][j] = 2 : maze[i][j] = 1;
        }
    }
}

// Recursive function to find a solution to the maze and store it in correctPath[x][y]
bool recursiveSolve(int x, int y) {
    // Base case: Reached the endpoint
    if (x == endX && y == endY)
        return true;
    // If the current cell is a wall or has already been visited, return false
    if (maze[x][y] == 2 || wasHere[x][y])
        return false;
    // Mark the current cell as visited
    wasHere[x][y] = true;
    // Recursively explore neighboring cells
    if (x != 0 && recursiveSolve(x - 1, y)) {
        correctPath[x][y] = true;
        return true;
    }
    if (x != nCells - 1 && recursiveSolve(x + 1, y)) {
        correctPath[x][y] = true;
        return true;
    }
    if (y != 0 && recursiveSolve(x, y - 1)) {
        correctPath[x][y] = true;
        return true;
    }
    if (y != mCells - 1 && recursiveSolve(x, y + 1)) {
        correctPath[x][y] = true;
        return true;
    }
    return false;
}

// Function to clear the maze and solution grid and reset values and clean cyan/red trails
void clearMaze() {
    for (int i = 0; i < nCells; i++) {
        for (int j = 0; j < mCells; j++) {
            cell[i][j].visited = false;
            cell[i][j].isWall = true;
            cell[i][j].visitedByPlayer = false;

            maze[i][j] = 0;
            rect[i][j].setFillColor(sf::Color::White);
            correctPath[i][j] = false;
            startX = 0;
            startY = 0;
            endX = 0;
            endY = 0;
        }
    }
    // Clear the cell stack used during maze generation
    while (!CellStack.empty())
        CellStack.pop();
}

// Called by Load() function
// Get solution for the maze ready and update it based on player's current position and its visited paths BUT doesnt draw it yet
void GetSolution()
{
	IniSolution();                       // Function to initialize the solution grid for maze solving
	recursiveSolve(startX, startY);      // Recursive function to find a solution to the maze and store it in correctPath[x][y] + not displayed yet (done by DrawSolution())
}

///// Enemy logic


//
//// Initialize enemy sprite and position
//sf::Sprite enemySprite;
//sf::Vector2f enemyPosition;
//
//int cellWidth = 10;
//int cellHeight = 10;
//
//// Function to initialize enemy at a random position within the maze
//void initializeEnemy() {
//    // Generate random position within the maze boundary that is not a wall and not occupied by the player
//    do {
//        int randomX = rand() % nCells;
//        int randomY = rand() % mCells;
//        if (!cell[randomX][randomY].isWall && !(randomX == playerPosition.x && randomY == playerPosition.y)) {
//            enemyPosition.x = randomX * cellWidth;  // Assuming cellWidth is the width of each cell in pixels
//            enemyPosition.y = randomY * cellHeight; // Assuming cellHeight is the height of each cell in pixels
//            enemySprite.setPosition(enemyPosition);
//            break;
//        }
//    } while (true);
//}
//
//
//// Function to update enemy movement
//void updateEnemy() {
//    // Determine movement direction based on neighboring cells
//    // Example: Check if cell to the right is a path, if so, move right
//    int cellX = (enemyPosition.x + cellWidth / 2) / cellWidth; // Calculate cell index based on enemy position
//    int cellY = (enemyPosition.y + cellHeight / 2) / cellHeight;
//
//    if (cellX >= 0 && cellX < nCells && cellY >= 0 && cellY < mCells) {
//        if (!cell[cellX + 1][cellY].isWall) {
//            // Move right
//            enemyPosition.x += cellWidth;
//        }
//        else if (!cell[cellX - 1][cellY].isWall) {
//            // Move left
//            enemyPosition.x -= cellWidth;
//        }
//        else if (!cell[cellX][cellY + 1].isWall) {
//            // Move down
//            enemyPosition.y += cellHeight;
//        }
//        else if (!cell[cellX][cellY - 1].isWall) {
//            // Move up
//            enemyPosition.y -= cellHeight;
//        }
//    }
//
//    // Update enemy sprite position
//    enemySprite.setPosition(enemyPosition);
//
//    // Check for collision with player
//    if (enemySprite.getGlobalBounds().intersects(player.getGlobalBounds())) {
//        // Handle collision with player (e.g., trigger game over)
//    }
//}


//#endif