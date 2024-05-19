#pragma once

#include "gameHeader.h"
#include "enem.h"
#include "Max.h"

sf::Font font;

void displayCombatMessage(sf::RenderWindow& window, const std::string& attacker, const std::string& action, int damage)
{
	std::ostringstream oss;
	oss << attacker << " " << action << " and dealt " << damage << " damage.";

	sf::Text text(oss.str(), font, 16);
	text.setFillColor(sf::Color::White);
	text.setPosition(10, 10); // Adjust position as needed

	window.draw(text);
}

class Combat {
public:
	Combat(sf::RenderWindow& window, Player& player, Enem* isenemy, bool bob) :
		window(window), player(player), enemy(isenemy), combatBackgroundTexture(),
		combatBackgroundSprite(), combatFont(), combatText(), combatMenuFont(),
		combatMenuText(), shakeClock(), shakeDuration(sf::seconds(0.5f)),
		shakeDistance(5.0f), isPlayerShaking(false), isEnemyShaking(false) {
		if (bob) {
			// Load combat background
			if (!combatBackgroundTexture.loadFromFile("MENU/Images/Backgrounds/Finale.jpg")) {
				std::cerr << "Failed to load combat background texture!" << std::endl;
			}

			// Load the music file
			if (!music.openFromFile("MENU/Music/Boss.ogg")) {
				// Failed to load music file
				std::cerr << "Failed to load Music!" << std::endl;
			}
			// Set the music to loop
			music.setLoop(true);

			// Set Scale of the Image
			combatBackgroundSprite.setScale(1.65, 1.4);

			combatBackgroundSprite.setTexture(combatBackgroundTexture);
			//combatBackgroundSprite.setTextureRect(portionRect);

			// Move combat background sprite a little to the bottom
			combatBackgroundSprite.setPosition(0, 30); // Adjust as needed
		}
		else {
			// Load combat background
			if (!combatBackgroundTexture.loadFromFile("MENU/Images/Backgrounds/NewRuins.png")) {
				std::cerr << "Failed to load combat background texture!" << std::endl;
			}
			// Load the music file
			if (!music.openFromFile("MENU/Music/Combat-Theme.ogg")) {
				// Failed to load music file
				std::cerr << "Failed to load Music!" << std::endl;
			}
			// Set the music to loop
			music.setLoop(true);

			// Set Texture
			combatBackgroundSprite.setTexture(combatBackgroundTexture);

			// Move combat background sprite a little to the bottom
			combatBackgroundSprite.setPosition(0, 30); // Adjust as needed
		}
	}

	void displayInstructions(sf::RenderWindow& window) {
		// Load font
		sf::Font font;
		if (!font.loadFromFile("MENU/Fonts/Pearlesce-aYpgJ.ttf")) {
			std::cerr << "Failed to load font!" << std::endl;
			return;
		}

		// Create text object
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(67);
		text.setFillColor(sf::Color::Blue);
		text.setString("Press \"A\" for attack, \"S\" to use items, \"D\" to flee");
		text.setPosition(70, 650);

		// Display text
		window.draw(text);
	}

	void displayFailure(RenderWindow& window, string sent) {
		cout << sent << endl;
		Font font;
		if (!font.loadFromFile("MENU/Fonts/Guardians.ttf")) {
			std::cerr << "Failed to load font!" << std::endl;
			return;
		}

		Text text;
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Red);
		text.setString(sent);
		text.setPosition(600 - text.getLocalBounds().width / 2, 400 - text.getLocalBounds().height / 2);

		window.draw(text);
	}

	void stringTexter(RenderWindow& window, string sent) {
		Font font;
		if (!font.loadFromFile("MENU/Fonts/Pearlesce-aYpgJ.ttf")) {
			std::cerr << "Failed to load font!" << std::endl;
			return;
		}

		Text text;
		text.setFont(font);
		text.setCharacterSize(67);
		text.setFillColor(sf::Color::Blue);
		text.setString(sent);
		text.setPosition(70, 650);

		// Display text
		window.draw(text);

	}

	void startCombat(sf::RenderWindow& window, Player& player, Enem* isenemy, const sf::Vector2f& initialEnemyPosition, const sf::Vector2f& initialEnemyScale, bool bob) {
		
		//////////
		if (bob) {
			// Load combat background
			if (!combatBackgroundTexture.loadFromFile("MENU/Images/Backgrounds/Finale.jpg")) {
				std::cerr << "Failed to load combat background texture!" << std::endl;
			}

			// Load the music file
			if (!music.openFromFile("MENU/Music/Boss.ogg")) {
				// Failed to load music file
				std::cerr << "Failed to load Music!" << std::endl;
			}
			// Set the music to loop
			music.setLoop(true);

			// Set Scale of the Image
			combatBackgroundSprite.setScale(1.65, 1.4);

			combatBackgroundSprite.setTexture(combatBackgroundTexture);
			//combatBackgroundSprite.setTextureRect(portionRect);

			// Move combat background sprite a little to the bottom
			combatBackgroundSprite.setPosition(0, 30); // Adjust as needed
		}
		else {
			// Load combat background
			if (!combatBackgroundTexture.loadFromFile("MENU/Images/Backgrounds/NewRuins.png")) {
				std::cerr << "Failed to load combat background texture!" << std::endl;
			}
			// Load the music file
			if (!music.openFromFile("MENU/Music/Combat-Theme.ogg")) {
				// Failed to load music file
				std::cerr << "Failed to load Music!" << std::endl;
			}
			// Set the music to loop
			music.setLoop(true);

			// Set Texture
			combatBackgroundSprite.setTexture(combatBackgroundTexture);

			// Move combat background sprite a little to the bottom
			combatBackgroundSprite.setPosition(0, 30); // Adjust as needed
		}
		
		
		
		////////
		
		enemy = isenemy; // Assign the enemy

		// Set initial position and scale for the enemy sprite
		enemy->sprite.setPosition(initialEnemyPosition);
		enemy->sprite.setScale(initialEnemyScale);

		sf::Clock playerClock;
		sf::Clock enemyClock;
		Clock turnClock;
		sf::Clock defeatClock; // Clock to track defeat message display time

		bool playerAnimationStarted = false;
		bool enemyAnimationStarted = false;
		bool attacking = false;

		bool displayPlayerDefeatMessage = false;
		bool displayEnemyDefeatMessage = false;

		int playerFrames = 0;
		int enemyFrames = 0;

		// Create text objects for defeat messages
		sf::Text playerDefeatText;
		playerDefeatText.setFont(font);
		playerDefeatText.setCharacterSize(24);
		playerDefeatText.setFillColor(sf::Color::Red);
		playerDefeatText.setString("Player Defeated!");
		playerDefeatText.setPosition(440, 340);

		sf::Text enemyDefeatText;
		enemyDefeatText.setFont(font);
		enemyDefeatText.setCharacterSize(24);
		enemyDefeatText.setFillColor(sf::Color::White);
		enemyDefeatText.setString("Enemy Defeated!");
		enemyDefeatText.setPosition(440, 340);

		bool fee = false;
		bool enemyTurn = false;
		// Play the music
		music.play();
		while (window.isOpen()) {
			// Load textbox texture
			if (!TBText.loadFromFile("MENU/Images/TextBox/TextBox1.png")) {
				std::cerr << "Failed to load textbox texture!" << std::endl;
			}

			TBSprite.setTexture(TBText);
			// Set position and scale for the textbox sprite
			TBSprite.setScale(1.0f / 1.5f, 1.0f / 1.5f); // Scale down to one-third of its size
			TBSprite.setPosition(20.0f, window.getSize().y - TBSprite.getGlobalBounds().height - 20.0f); // Position at the bottom left

			// Process events
			sf::Event event;
			while (window.pollEvent(event)) {

				enemyTurn = false;

				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (event.type == sf::Event::KeyPressed) {
					if (!attacking && event.key.code == sf::Keyboard::A) {
						fee = false;
						playerAnimationStarted = true;
						enemyAnimationStarted = false;
						attacking = true;
						playerFrames = 0;
						cout << "player" << endl;
						playerAttack();
						//enemyTurn = true;
					}
					else if (!attacking && event.key.code == Keyboard::D) {
						flee(window, bob);
						fee = true;
						playerAnimationStarted = false;
						enemyAnimationStarted = false;
						attacking = true;
					}
					else if (event.key.code == Keyboard::S) {
						useItem(window);
						playerAnimationStarted = false;
						enemyAnimationStarted = false;
						attacking = true;
					}
				}


				// Check for defeated entities and handle shaking and removal
				if (!player.isAlive()) {
					shakePlayer();
					displayPlayerDefeatMessage = true; // Player defeated, set flag to display defeat message
					//defeatClock.restart(); // Restart clock for defeat message display
				}

				if (!enemy->isAlive()) {
					shakeEnemy();
					displayEnemyDefeatMessage = true; // Enemy defeated, set flag to display defeat message
					//defeatClock.restart(); // Restart clock for defeat message display
					//return;
				}
			}


			// Get the current mouse position relative to the window
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			// Print the coordinates
			cout << "(" << mousePos.x << "," << mousePos.y << ")" << endl;


			// Set player sprite position to bottom right of the window
			player.sprite.setPosition(780, 270);
			player.sprite.setScale(4, 4);

			window.clear();

			// Draw combat background
			window.draw(combatBackgroundSprite);

			// Draw player sprite if alive
			if (player.isAlive()) {
				window.draw(player.sprite);
			}

			// Draw enemy sprite if alive
			if (enemy->isAlive()) {
				window.draw(enemy->sprite);
			}

			window.draw(TBSprite);

			// Play player animation if A key is pressed
			if (attacking && playerAnimationStarted && !enemyAnimationStarted) {
				if (playerClock.getElapsedTime().asSeconds() > 0.1f) {
					if (player.rectsprite.left + player.rectsprite.width >= 660) {
						// Reset animation
						player.rectsprite.left = 0;
						playerAnimationStarted = false;
						enemyAnimationStarted = false;

					}
					else {
						player.rectsprite.left += player.rectsprite.width;
						playerFrames++;
					}
					player.sprite.setTextureRect(player.rectsprite);
					playerClock.restart();
				}
			}

			else if (attacking && !playerAnimationStarted && !enemyAnimationStarted && !displayEnemyDefeatMessage) {

				stringTexter(window, enemy->getName() + " attacks! ");
				if (turnClock.getElapsedTime().asSeconds() > 2.15f) {
					enemyAnimationStarted = true;
					turnClock.restart();
				}
			}

			// Play enemy animation
			else if (attacking && !playerAnimationStarted && enemyAnimationStarted) {
				if (enemyClock.getElapsedTime().asSeconds() > 0.1f) {
					if (enemy->rectsprite.left + enemy->rectsprite.width >= enemy->val) {
						// Reset animation
						enemy->rectsprite.left = 0;
						enemyAnimationStarted = false;
						enemyTurn = false;
						attacking = false;
					}
					else {
						enemy->rectsprite.left += enemy->rectsprite.width;
						enemyFrames++;
					}
					enemy->sprite.setTextureRect(enemy->rectsprite);
					enemyClock.restart();
				}
				//enemyAttack();
			}


			// Clear the window
			// Draw combat text and menu
			//window.draw(combatText);
			if (fee && attacking) {
				if (turnClock.getElapsedTime().asSeconds() > 2.15f) {
					attacking = false;
					playerAnimationStarted = false;
					enemyAnimationStarted = false;
					fee = false;
					turnClock.restart();
				}
				else flee(window, bob);
				if (turnClock.getElapsedTime().asSeconds() > 2.15f) {
					enemyAnimationStarted = true;
					turnClock.restart();
				}
				//displayInstructions(window);
			}
			if (!attacking && !playerAnimationStarted && !enemyAnimationStarted) {
				displayInstructions(window);
			}
			// Display defeat messages if applicable
			if (displayPlayerDefeatMessage) {
				window.draw(playerDefeatText);
				if (defeatClock.getElapsedTime().asSeconds() >= 5.0f) {
					displayPlayerDefeatMessage = false; // Hide defeat message after 5 seconds
					defeatClock.restart(); // Restart clock for defeat message display
				}
			}

			if (enemy->getHealth() == 0 || enemy->getHealth() < 0 && displayEnemyDefeatMessage) {

				displayFailure(window, "Enemy Defeated!");
				if (turnClock.getElapsedTime().asSeconds() > 2.5f) {
					turnClock.restart();
					break;
				}
			}
			else if (player.getHealth() == 0 || player.getHealth() < 0 && displayPlayerDefeatMessage) {
				displayFailure(window, "Game Over :(");
				if (turnClock.getElapsedTime().asSeconds() > 3.5f) {
					turnClock.restart();
					break;
				}
			}

			// Display the window
			window.display();
		}
		return;
	}

private:
	sf::RenderWindow& window;
	Player& player;
	Enem* enemy;
	sf::Texture combatBackgroundTexture;
	sf::Sprite combatBackgroundSprite;
	Texture TBText;
	Sprite TBSprite;
	sf::Font combatFont;
	sf::Text combatText;
	sf::Font combatMenuFont;
	sf::Text combatMenuText;
	sf::Music music;

	sf::Clock shakeClock;
	sf::Time shakeDuration;
	float shakeDistance;
	bool isPlayerShaking;
	bool isEnemyShaking;

	sf::Vector2f enemyPosition; // Position of the enemy sprite
	sf::IntRect enemyAnimationRect; // Animation rect for the enemy sprite



	void playerAttack() {
		int playerDamage = player.getAttackDamage();
		enemy->takeDamage(playerDamage);
		combatText.setString(player.getName() + " attacks " + enemy->getName() + " for " + std::to_string(playerDamage) + " damage!");
		if (!enemy->isAlive()) {
			combatText.setString(enemy->getName() + " has been defeated!");
			cout << "Enemy has been defeated!" << endl;
		}
		cout << enemy->getHealth() << endl;
	}

	void enemyAttack() {
		int enemyDamage = enemy->attack();
		player.takeDamage(enemyDamage);
		combatText.setString(enemy->getName() + " attacks " + player.getName() + " for " + std::to_string(enemyDamage) + " damage!");
		if (!player.isAlive()) {
			combatText.setString(player.getName() + " has been defeated!");
		}
		cout << player.getHealth() << endl;
	}

	void shakePlayer() {
		if (!isPlayerShaking) {
			isPlayerShaking = true;
			shakeClock.restart();
		}

		if (shakeClock.getElapsedTime() < shakeDuration) {
			float shakeTime = shakeClock.getElapsedTime().asSeconds();
			float offsetX = std::sin(shakeTime * 50) * shakeDistance;
			float offsetY = std::cos(shakeTime * 50) * shakeDistance;
			player.sprite.setPosition(player.sprite.getPosition().x + offsetX, player.sprite.getPosition().y + offsetY);
		}
		else {
			// Reset player sprite position
			player.sprite.setPosition(780, 270);
			isPlayerShaking = false; // Reset shaking flag
		}
	}

	void shakeEnemy() {
		if (!isEnemyShaking) {
			isEnemyShaking = true;
			shakeClock.restart();
		}

		if (shakeClock.getElapsedTime() < shakeDuration) {
			float shakeTime = shakeClock.getElapsedTime().asSeconds();
			float offsetX = std::sin(shakeTime * 50) * shakeDistance;
			float offsetY = std::cos(shakeTime * 50) * shakeDistance;
			enemy->sprite.setPosition(enemy->sprite.getPosition().x + offsetX, enemy->sprite.getPosition().y + offsetY);
		}
		else {
			// Reset enemy sprite position
			enemy->sprite.setPosition(90, 30);
			isEnemyShaking = false; // Reset shaking flag
		}
	}



	// Player uses an item
	void useItem(RenderWindow& window) {
		// Implement item usage logic
		cout << player.getHealth() << endl;
		player.storage.selectPotion(true);
		player.setHealth(player.storage.useSelectedPotion(player.getHealth()));
		//Clock turnClock;
		displayFailure(window, "Item successfully used, new health: ");
		cout << player.getHealth() << endl;
	}

	// Player attempts to flee from combat
	void flee(RenderWindow& window, bool bob) {
		// Generate random number between 1 and 100
		int chanceToFlee = rand() % 100 + 1;

		if (bob) {
			chanceToFlee = 25;
		}

		// Check if player successfully flees
		if (chanceToFlee <= 5) {
			// Player successfully flees
			// Close combat window and resume game state
			window.close();
			// Implement game state resumption
		}
		else {
			// Player fails to flee
			// Display combat text
			/*combatText.setString("You failed to flee!");*/
			displayFailure(window, "You failed to flee!");

		}

	}
};