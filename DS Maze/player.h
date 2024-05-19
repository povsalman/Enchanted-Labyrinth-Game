#pragma once

#include"UserInterface.h"
#include"Enemy.h"
#include"Controller.h"
#include"Combat.h"
#include <SFML/Graphics.hpp>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()


Position playerPosition;
Position enemyPosition;

int GameState = 0;
int GameLevel = 1;
int score;

int X, Y;

sf::Sprite player;
sf::Sprite enemy;

// for player

void move_east()
{
	playerPosition.x += 10;
	player.setTextureRect(sf::IntRect(0, 90, 30, 30)); // Set texture rectangle for right movement
	player.setPosition(playerPosition.x, playerPosition.y);
}

void move_west()
{
	playerPosition.x -= 10;
	player.setTextureRect(sf::IntRect(0, 60, 30, 30)); // Set texture rectangle for left movement
	player.setPosition(playerPosition.x, playerPosition.y);
}

void move_north()
{
	playerPosition.y -= 10;
	player.setTextureRect(sf::IntRect(0, 30, 30, 30)); // Set texture rectangle for up movement
	player.setPosition(playerPosition.x, playerPosition.y);
}

void move_south()
{
	playerPosition.y += 10;
	player.setTextureRect(sf::IntRect(0, 0, 30, 30)); // Set texture rectangle for down movement
	player.setPosition(playerPosition.x, playerPosition.y);
}

// for enemy

void emove_east()
{
	enemyPosition.x += 10;
	//player.setTextureRect(sf::IntRect(0, 90, 30, 30)); // Set texture rectangle for right movement
	enemy.setPosition(enemyPosition.x, enemyPosition.y);
}

void emove_west()
{
	enemyPosition.x -= 10;
	//player.setTextureRect(sf::IntRect(0, 60, 30, 30)); // Set texture rectangle for left movement
	enemy.setPosition(enemyPosition.x, enemyPosition.y);
}

void emove_north()
{
	enemyPosition.y -= 10;
	//player.setTextureRect(sf::IntRect(0, 30, 30, 30)); // Set texture rectangle for up movement
	enemy.setPosition(enemyPosition.x, enemyPosition.y);
}

void emove_south()
{
	enemyPosition.y += 10;
	//player.setTextureRect(sf::IntRect(0, 0, 30, 30)); // Set texture rectangle for down movement
	enemy.setPosition(enemyPosition.x, enemyPosition.y);
}


void playcombatanimation() {
	RenderWindow window(VideoMode(1200, 800), "Combat Screen", Style::Close);
	Player Slayer;
	Texture TBText;
	Sprite TBSprite;

	// Create enemies with different initial positions and scales
	Goblin goblin;
	DarkDwarf darkDwarf;
	GiantBat giantBat;
	EvilMage evilMage;
	Kane Boss;

	bool bob = false;
	//Combat chaos(window, Slayer, &Boss); // Initialize Combat object with player
	Combat chaos1(window, Slayer, &goblin, bob); // Initialize Combat object with player
	Combat chaos2(window, Slayer, &darkDwarf, bob); // Initialize Combat object with player
	Combat chaos3(window, Slayer, &giantBat, bob); // Initialize Combat object with player
	Combat chaos4(window, Slayer, &evilMage, bob); // Initialize Combat object with player
	Combat chaos5(window, Slayer, &Boss, bob); // Initialize Combat object with player

	// Combat loop for Goblin
	//chaos.startCombat(window, Slayer, &Boss, sf::Vector2f(140, 180), sf::Vector2f(4.5, 4.5));
	chaos1.startCombat(window, Slayer, &goblin, sf::Vector2f(60, 0), sf::Vector2f(5, 5), bob);

	 //Progress to next enemy if Goblin is defeated
	//if (!goblin.isAlive()) {
		chaos2.startCombat(window, Slayer, &darkDwarf, sf::Vector2f(60, 0), sf::Vector2f(5, 5), bob);
		// Combat loop for Dark Dwarf
	//}

	// Repeat for the remaining enemies
	//if (!darkDwarf.isAlive()) {
		// Combat loop for Giant Bat
		chaos3.startCombat(window, Slayer, &giantBat, sf::Vector2f(100, 60), sf::Vector2f(4.5, 4.5), bob);
	//}

	//if (!giantBat.isAlive()) {
		// Combat loop for Evil Mage
		chaos4.startCombat(window, Slayer, &evilMage, sf::Vector2f(90, 30), sf::Vector2f(5, 5), bob);
	//}
	//if (!evilMage.isAlive()) {
		bob = true;
		chaos5.startCombat(window, Slayer, &Boss, sf::Vector2f(90, 30), sf::Vector2f(5, 5), bob);
	//}
	return;
}

void LevelInitiate()
{
	// Declare variables for calculating differences in positions
	int diffX, diffY;

	// Define the scale factor for the player sprite (adjust as needed)
	float playerScaleFactor = 0.5;
	player.setScale(playerScaleFactor, playerScaleFactor);

	// Define the scale factor for the enemy sprite (adjust as needed)
	float enemyScaleFactor = 0.5;
	enemy.setScale(enemyScaleFactor, enemyScaleFactor);

	/*enemy.setColor(sf::Color::Red);*/

	// Check the game level and set parameters accordingly
	if (GameLevel == 1)
	{
		// Set the number of cells for the maze
		mCells = 40;		//increases vertically	(rows)
		nCells = 40;		//increases horizontally (columns)
		// Set the initial score
		score = 10;
	}
	else if (GameLevel == 2)
	{
		mCells = 50;
		nCells = 50;
		score = 20;
	}
	else if (GameLevel == 3)
	{
		mCells = 60;
		nCells = 80;
		score = 40;
	}
	else if (GameLevel == 4)
	{
		mCells = 60;
		nCells = 100;
		score = 50;
	}

	// Calculate the end position of the maze finish dot wali
	endY = mCells - 2;
	endX = nCells - 2;

	// Calculate the initial position of the maze graph
	initialPos.x = ((1100 - (nCells * 10)) / 2) + 10;
	initialPos.y = ((720 - (mCells * 10)) / 2) + 10;

	// Calculate the final position of the maze graph
	finalPos.x = (initialPos.x + nCells * 10) + 10;
	finalPos.y = (initialPos.y + mCells * 10) + 10;

	// Set the initial position of the player using graph position
	playerPosition.x = initialPos.x;
	playerPosition.y = initialPos.y;

	// Set the initial position of the enemy
	enemyPosition.x = endX;
	enemyPosition.y = endY - 30;


	/////////////

	X = 0;
	Y = 0;

	/*eX = 0;
	eY = 0;*/


	// Calculate differences in positions (graph)
	diffX = finalPos.x - initialPos.x;
	diffY = finalPos.y - initialPos.y;

	// Define colors for the maze borders
	int r = 0, g = 0, b = 0;

	// Set positions and sizes for maze borders
	// Border 0
	border[0].setPosition(initialPos.x - 10, initialPos.y - 10);
	border[0].setSize(sf::Vector2f((float)(diffX), 10.0f));
	border[0].setFillColor(sf::Color::Color(r, g, b));

	// Border 1
	border[1].setPosition(finalPos.x - 20, initialPos.y);
	border[1].setSize(sf::Vector2f(10.0f, (float)diffY - 10));
	border[1].setFillColor(sf::Color::Color(r, g, b));

	// Border 2
	border[2].setPosition(initialPos.x - 10, initialPos.y);
	border[2].setSize(sf::Vector2f(10.0f, (float)(diffY - 10)));
	border[2].setFillColor(sf::Color::Color(r, g, b));

	// Border 3
	border[3].setPosition(initialPos.x - 10, initialPos.y + diffY - 20);
	border[3].setSize(sf::Vector2f((float)(diffX), 10.0f));
	border[3].setFillColor(sf::Color::Color(r, g, b));

}

int WaysFound(int x, int y)
{
	int ways = 0;
	if (y && !cell[x][y - 1].isWall)
		ways++;
	if (x &&!cell[x - 1][y].isWall)
		ways++;
	if (!cell[x][y + 1].isWall)
		ways++;
	if (y >= 0 && !cell[x + 1][y].isWall)
		ways++;
	return ways;
}

// player input is handled + final dot reached is checked
void playermovement()
{
	// final dot reached
	if(cell[endX][endY].visitedByPlayer)
	{
		playcombatanimation();
		GameState = 3;
		clearMaze();
	}

	cell[X][Y].visitedByPlayer = true;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		while (Y && !cell[X][Y - 1].isWall)
		{
			move_north();
			Y--;
			cell[X][Y].visitedByPlayer = true;
			if (WaysFound(X, Y) > 2)
				break;
		}
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{

		while (!cell[X][Y + 1].isWall)
		{
			move_south();
			Y++;
			cell[X][Y].visitedByPlayer = true;
			if (WaysFound(X, Y) > 2)
				break;
		}
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		while (!cell[X + 1][Y].isWall)
		{
			move_east();
			X++;
			cell[X][Y].visitedByPlayer = true;
			if (WaysFound(X, Y) > 2)
				break;
		}
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		while (X && !cell[X - 1][Y].isWall)
		{
			move_west();
			X--;
			cell[X][Y].visitedByPlayer = true;
			if (WaysFound(X, Y) > 2)
				break;
		}
	}

}

int eX, eY; // Enemy position variables



void enemymovement() {
	// Check the direction of the enemy's movement

	// Initialize enemy position
	/*eX = enemyPosition.x;
	eY = enemyPosition.y;*/

	if (eX < X) {
		// Move the enemy towards the right until a wall is reached
		while (eX < X && !cell[eX + 1][eY].isWall) {
			emove_east();
			eX++;
		}
	}
	else if (eX > X) {
		// Move the enemy towards the left until a wall is reached
		while (eX > X && !cell[eX - 1][eY].isWall) {
			emove_west();
			eX--;
		}
	}
	else if (eY < Y) {
		// Move the enemy upwards until a wall is reached
		while (eY < Y && !cell[eX][eY + 1].isWall) {
			emove_south();
			eY++;
		}
	}
	else if (eY > Y) {
		// Move the enemy downwards until a wall is reached
		while (eY > Y && !cell[eX][eY - 1].isWall) {
			emove_north();
			eY--;
		}
	}
}



//void enemymovement() {
//
//	srand(time(0));
//	// Generate a random direction for the enemy to move
//	int direction = rand() % 4; // 0: up, 1: down, 2: left, 3: right
//
//	// Check if the movement is valid based on the maze structure
//	if (direction == 0 && enemyPosition.y > 0 && !cell[enemyPosition.x][enemyPosition.y - 1].isWall) {
//		emove_north();
//	}
//	else if (direction == 1 && enemyPosition.y < (mCells - 1) * 10 && !cell[enemyPosition.x][enemyPosition.y + 1].isWall) {
//		emove_south();
//	}
//	else if (direction == 2 && enemyPosition.x > 0 && !cell[enemyPosition.x - 1][enemyPosition.y].isWall) {
//		emove_west();
//	}
//	else if (direction == 3 && enemyPosition.x < (nCells - 1) * 10 && !cell[enemyPosition.x + 1][enemyPosition.y].isWall) {
//		emove_east();
//	}
//	return;
//
//}


