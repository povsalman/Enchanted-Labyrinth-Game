#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include"Controller.h"
#include "Menu.h"


using namespace std;
int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Menu");
	MenuReady();
	Menu m;
	m.runMenu(window);

	srand(time(NULL));
	window.setFramerateLimit(10);
	while (window.isOpen())
	{
		while (window.pollEvent(eve))
		{
			switch (eve.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		startGame(window, m);				// main game loop
		window.display();

	}
}

