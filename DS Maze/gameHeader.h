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

class Game {


public:

	// Constructors & Destructors
	Game();
	virtual ~Game();

	void update() {

	}

	void render() {

	}

	void startSomething() {

		// Window Stuff
		sf::RenderWindow window(sf::VideoMode(1080, 920), "Starting Window.", Style::Titlebar | Style::Close | Style::Resize);
		sf::CircleShape shape(100.f);
		Event ev;
		shape.setFillColor(sf::Color::Green);

		// Game Loop

		while (window.isOpen())
		{
			// Event Polling
			sf::Event event;
			while (window.pollEvent(ev))
			{
				switch (ev.type) {
					{
				case Event::Closed:
					window.close();
					break;
					}

				case Event::KeyPressed:
					if (ev.key.code == Keyboard::Escape)
						window.close();
					break;
				}



			}

			// Update

			//Render
			window.clear(Color::Transparent);  // Clear Old frame

			// Draw the game:

			window.draw(shape);


			window.display(); // Tell app that window is done drawing
		}


		// The End
	}


};