#pragma once

#include"player.h"
#include"Highscore.h"
#include"Controller.h"

using namespace std;

sf::Event eve;

int totalScore;
int sideMenuState = 0;

sf::Text _score;
sf::Font score_font;

//sf::Text sidescore;
//sf::Font sidescore_font;

sf:: Text nameInputText;
sf::Font nameInputFont;

string input;//user name;
highscore* h = new highscore;

char inp;

sf::RectangleShape solvedButton(sf::Vector2f(400.0f, 220.0f));
sf::RectangleShape nameInput(sf::Vector2f(400.0f, 200.0f));
sf::RectangleShape giveup(sf::Vector2f(120.0f, 50.0f));

//textures:
sf::Texture sidemenu;
sf::Texture sidemenuMuted;
sf::Texture sidemenuPaused;
sf::Texture solveButtonTexture;
sf::Texture nameInputTexture;
sf::Texture GiveupTexture;
sf::Texture playerTexture;

//sprites:
sf::Sprite menu;
sf::Sprite side_menu;
sf::Sprite Muted;
sf::Sprite paused;
sf::Sprite highScoreSprite;


//sf::SoundBuffer buffer;
//sf::Sound sound;

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::MENU:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void MenuReady()
{ 
	//load texture:
	sidemenu.loadFromFile("MENU/sidemenu2.png");
	sidemenuMuted.loadFromFile("Menu/muted2.png");
	sidemenuPaused.loadFromFile("Menu/paused2.png");
	solveButtonTexture.loadFromFile("Textures/solvedButtonTexture.png");
	nameInputTexture.loadFromFile("Textures/name.png");
	GiveupTexture.loadFromFile("Textures/giveup.png");
	solvedButton.setPosition(355, 260);
	nameInput.setPosition(355, 260);
	playerTexture.loadFromFile("Textures/kanecyan.png");
	wallTexture.loadFromFile("Textures/wall.png");
	pathTexture.loadFromFile("Textures/path.png");
	solve.loadFromFile("Textures/solvepath.png");


	//load sprite:
	side_menu.setTexture(sidemenu);
	Muted.setTexture(sidemenuMuted);
	paused.setTexture(sidemenuPaused);
	solvedButton.setTexture(&solveButtonTexture);
	nameInput.setTexture(&nameInputTexture);
	giveup.setTexture(&GiveupTexture);
	score_font.loadFromFile("Menu/arial.ttf");
	//sidescore_font.loadFromFile("Menu/arial.ttf");
	player.setTexture(playerTexture);
	_score.setFont(score_font);
	_score.setPosition(590, 335);
	
	//sidescore.setFont(sidescore_font);
	//sidescore.setPosition(890, 335);
	
	nameInputFont.loadFromFile("Menu/arial.ttf");
	nameInputText.setFont(nameInputFont);
	nameInputText.setPosition(430, 370);
	giveup.setPosition(1132, 606);


	//sound:
	//buffer.loadFromFile("MENU/gta.wav");
	//sound.setBuffer(buffer);

}

//// show highscore menu ///

void loadHighscores() {

	ifstream highscoreFile("high.txt");
	string line;

	_score.setString(""); // Clear previous highscores

	while (getline(highscoreFile, line)) {
		_score.setString(_score.getString() + line + "\n");
	}

	highscoreFile.close();
}


//checking side panel controls

void SideMenu(sf::RenderWindow& myWindow)
{
	sf::Vector2i MousePosn = sf::Mouse::getPosition(myWindow);

	switch (sideMenuState)
	{
		case 0:			//Name input case
		{
			myWindow.draw(side_menu);
			myWindow.draw(nameInput);
			if (eve.TextEntered)
				if( eve.text.unicode > 64 && eve.text.unicode < 91 || eve.text.unicode>96 && eve.text.unicode < 123)
				input += eve.text.unicode;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace))
				{
					if (input.size() > 0)  input.resize(input.size() - 1);
				}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
			{
				sideMenuState = 1;		// Normal standard side menu
			}
			nameInputText.setString(input);
			myWindow.draw(nameInputText);

			break;
		}

		case 1:				// Normal standard side menu
		{
			myWindow.draw(side_menu);
			myWindow.draw(giveup);

			
			if (MousePosn.x >= 1141 && MousePosn.x <= 1235 && MousePosn.y >= 622 && MousePosn.y <= 654 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				GameState = 4; // give up clicked
			}

			if (MousePosn.x >= 1157 && MousePosn.x <= 1203 && MousePosn.y >= 252 && MousePosn.y <= 300 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sideMenuState = 2;//pause clicked
			}

			if (MousePosn.x >= 1157 && MousePosn.x <= 1203 && MousePosn.y >= 315 && MousePosn.y <= 362 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sideMenuState = 3; //mute clicked
				myWindow.draw(Muted);

			}
			if (MousePosn.x >= 1157 && MousePosn.x <= 1203 && MousePosn.y >= 377 && MousePosn.y <= 425 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sideMenuState = 4;	//goto main menu

				// add to highscore file first
				h->adding(input, to_string(totalScore));
			}
				  
			break;
		}

		//pause clicked
		case 2:
		{
			myWindow.draw(paused);
			myWindow.draw(giveup);

			if (MousePosn.x >= 1141 && MousePosn.x <= 1235 && MousePosn.y >= 622 && MousePosn.y <= 654 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				GameState = 4;	// give up clicked
			}

			if (MousePosn.x >= 546 && MousePosn.x <= 596 && MousePosn.y >= 345 && MousePosn.y <= 405 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sideMenuState = 1;	//resume is clicked
			}

			break;
		}

		//mute clicked
		case 3:
		{
			myWindow.draw(Muted);
			myWindow.draw(giveup);
			if (MousePosn.x >= 1141 && MousePosn.x <= 1235 && MousePosn.y >= 622 && MousePosn.y <= 654 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				GameState = 4;
			}

			if (MousePosn.x >= 1157 && MousePosn.x <= 1203 && MousePosn.y >= 315 && MousePosn.y <= 362 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				sideMenuState = 1;
				  
			break;
		}

		//goto main menu
		case 4:
		{
			GameState = 0;		//menu
			clearMaze();		//clean maze
			sideMenuState = 0;	//take name input for next time
			
			break;
		}

	}
}

// set up maze graph with path and wall textures + player sprite initial positions + called repeatedly by Load()
void DrawInitialize()
{
	int a, b, i, j;


	// Double the gap size between cells
	int gapSize = 20; 

	// Adjust the size and position of cells
	for (i = initialPos.x, a = 0; i < finalPos.x; i += gapSize, a++)
	{
		for (j = initialPos.y, b = 0; j < finalPos.y; j += gapSize, b++)
		{
			// Adjust the size of cells
			rect[a][b].setSize(sf::Vector2f(gapSize, gapSize));

			rect[a][b].setPosition(sf::Vector2f(i, j));
			if (cell[a][b].isWall)
				rect[a][b].setTexture(&wallTexture);
			else
				rect[a][b].setTexture(&pathTexture);

		}

	}
}

// Called by the main game loop repeatedly i.e startGame() in Controller.h
// draws player sprite + makes trail of player(cyan) + makes final dot (blue) + draws borders
void DrawMaze(sf::RenderWindow& myWindow)
{

	for (int i = 0; i < nCells; i++)
	{
		for (int j = 0; j < mCells; j++)
		{
			if (i == (playerPosition.x - initialPos.x) / 10 && j == (playerPosition.y - initialPos.y) / 10)
			{
				player.setPosition(playerPosition.x,playerPosition.y);
				myWindow.draw(player);
				
				

			}
			
			/*if (i == enemyPosition.x && j == (enemyPosition.y) )
			{
				enemy.setPosition(enemyPosition.x, enemyPosition.y);
				myWindow.draw(enemy);


			}*/


			else
			{ 
				myWindow.draw(rect[i][j]);					//draws the graphical grid of maze


				if (cell[i][j].visitedByPlayer)
					rect[i][j].setFillColor(sf::Color::Cyan);
				if (i ==endX && j == endY)
					rect[i][j].setFillColor(sf::Color::Blue);
				if (i == enemyPosition.x && j == enemyPosition.y)
				{
					rect[i][j].setFillColor(sf::Color::Magenta);
					//enemy.setPosition(enemyPosition.x, enemyPosition.y);
					//myWindow.draw(enemy);
				}

			}
		}
	}

	

	myWindow.draw(border[0]);
	myWindow.draw(border[1]);
	myWindow.draw(border[2]);
	myWindow.draw(border[3]);

	////////////


	 //Update and draw enemies
	// Example:
	//enemy.update();
	//if (enemy.checkCollision(player)) {
	//	// Handle collision with player sprite
	//}
	//myWindow.draw(enemy); // Assuming 'window' is your SFML render window


	/////////////


	// Update enemy movement
    //updateEnemy();



	//////////////


	
}

// Draw a red trail of the solution generated by 
void DrawSolution(sf::RenderWindow& myWindow)
{
	for (int i = 0; i < nCells; i++)
	{
		for (int j = 0; j < mCells; j++)
		{

			if (correctPath[i][j])
			{
				rect[i][j].setFillColor(sf::Color::Red);
				myWindow.draw(rect[i][j]);
			}

		}
	}
}
