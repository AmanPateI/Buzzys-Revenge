/*
Author: Aman Patel
Class: ECE 4122
Last Date Modified: 10/26/2021

Description: Buzzy's Revenge game
*/

/*
 * File:   collision.cpp
 * Author: Nick (original version), ahnonay (SFML2 compatibility)
 */

 // Included important C++ libraries here
#include <sstream>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>    
#include <array>        
#include <random>      
#include <chrono>      
#include <unordered_map>
#include <cmath>
#include <any>
#include "Collision.hpp" 


 // Make code easier to type with "using namespace"
using namespace sf;
const double PI = std::atan(1.0) * 4;

// Where is the player/branch? 
// Left or Right
enum class side { LEFT, RIGHT, NONE };



int main()
{
	//screen resolution
	VideoMode vm(1920, 1080);

	// default in screen mode can change it to full screen mode
	RenderWindow gameWindow(vm, "Buzzy's Revenge", Style::Default);

	// background texture 
	Texture textureBackground;

	// loading the image 
	textureBackground.loadFromFile("graphics/background.png");


	Sprite background;


	background.setTexture(textureBackground);

	//creating map sprites for tiger & bulldog 

	std::unordered_map<std::string, sf::Sprite> evilTiger;
	std::unordered_map<std::string, sf::Sprite> evilBulldog;


	background.setPosition(0, 0);

	// mascot key values
	std::array<String, 5> tigerLocation{ "Chicken","Mouse","Pig","Tiger"
		, "Dog" };
	std::array<String, 5> bulldogLocation{ "Sheep", "Frog",
		"Bunny", "Unicorn", "BullDog" };

	//mascot locations
	std::array<int, 5> locations{ 950,825,700,575,450 };

	// mouse
	Texture textureMouse;
	textureMouse.loadFromFile("graphics/mouse.png");
	Sprite spriteMouse;
	spriteMouse.setTexture(textureMouse);
	evilTiger["Mouse"] = spriteMouse;

	//Tiger
	Texture textureTiger;
	textureTiger.loadFromFile("graphics/tiger.png");
	Sprite spriteTiger;
	//Setting up Tiger texture
	spriteTiger.setTexture(textureTiger);
	evilTiger["Tiger"] = spriteTiger;

	// Frog
	Texture textureFrog;
	textureFrog.loadFromFile("graphics/frog.png");
	Sprite spriteFrog;
	//Setting frog texture
	spriteFrog.setTexture(textureFrog);
	evilBulldog["Frog"] = spriteFrog;

	//dog
	Texture textureDog;
	textureDog.loadFromFile("graphics/dog.png");
	Sprite spriteDog;
	spriteDog.setTexture(textureDog);
	evilTiger["Dog"] = spriteDog;

	//chicken
	Texture textureChicken;
	textureChicken.loadFromFile("graphics/chicken.png");
	Sprite spriteChicken;
	//Setting chicken texture
	spriteChicken.setTexture(textureChicken);
	evilTiger["Chicken"] = spriteChicken;

	// pig
	Texture texturePig;
	texturePig.loadFromFile("graphics/pig.png");
	Sprite spritePig;
	spritePig.setTexture(texturePig);
	evilTiger["Pig"] = spritePig;

	//bulldog
	Texture textureBullDog;
	textureBullDog.loadFromFile("graphics/Georgia_Bulldogs_logo_dog_g.png");
	Sprite spriteBullDog;
	//Setting bulldog texture
	spriteBullDog.setTexture(textureBullDog);
	evilBulldog["BullDog"] = spriteBullDog;

	//bunny
	Texture textureBunny;
	textureBunny.loadFromFile("graphics/bunny.png");
	Sprite spriteBunny;
	//Setting bunny texture
	spriteBunny.setTexture(textureBunny);
	evilBulldog["Bunny"] = spriteBunny;

	//the sheep
	Texture textureSheep;
	textureSheep.loadFromFile("graphics/sheep.png");
	Sprite spriteSheep;
	//Setting sheep texture
	spriteSheep.setTexture(textureSheep);
	evilBulldog["Sheep"] = spriteSheep;

	//unicorn
	Texture textureUnicorn;
	textureUnicorn.loadFromFile("graphics/angry_unicorn.png");
	Sprite spriteUnicorn;
	spriteUnicorn.setTexture(textureUnicorn);
	evilBulldog["Unicorn"] = spriteUnicorn;

	//bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/insect.png");
	Sprite spriteBee;
	//Setting bee texture
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(1675, 250);
	spriteBee.scale(-1, 1);
	bool spriteBeeHit = false;

	//load in font from provided file
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//randomize evil mascot locations in respective coloumn
	shuffle(tigerLocation.begin(), tigerLocation.end(), std::default_random_engine(time(NULL)));
	shuffle(bulldogLocation.begin(), bulldogLocation.end(), std::default_random_engine(time(NULL)));

	int j = 0;
	for (auto i : tigerLocation) {

		evilTiger[i].setPosition(1675, locations[j]);
		j++;
	}
	j = 0;
	for (auto i : bulldogLocation) {
		evilBulldog[i].setPosition(1820, locations[j]);
		j++;
	}

	// Game Clock
	Clock clock;

	bool paused = true;
	int score = 5;

	// text for the start screen
	sf::Text pressEnterToStartGame;
	sf::Text pressUpandDowntoAim;
	sf::Text BuzzsRevenge;
	sf::Text escapteToExit;
	sf::Text scoreText;
	sf::Text powerBar;
	sf::Text Lives;
	sf::Text pressSpaceToPowerUp;
	sf::Text Name;
	sf::Text realScore;

	/* assigning the fonst to all the writings int he start screeen
	*/
	BuzzsRevenge.setFont(font);
	Lives.setFont(font);
	scoreText.setFont(font);
	// To check if Up and Down rotate 
	powerBar.setFont(font);
	pressUpandDowntoAim.setFont(font);
	//Game controls
	escapteToExit.setFont(font);
	pressEnterToStartGame.setFont(font);
	pressSpaceToPowerUp.setFont(font);
	realScore.setFont(font);
	Name.setFont(font);

	// Assign the messages
	Lives.setString("Lives");
	BuzzsRevenge.setString("Buzzy's Revenge");
	scoreText.setString("Score:");
	pressEnterToStartGame.setString("Press Enter to Restart Game!");
	pressUpandDowntoAim.setString("Press Up/Down arrow to aim");
	pressSpaceToPowerUp.setString("Press Space to Powerup");
	Name.setString("Created by\nAman Patel");
	powerBar.setString("Power");
	escapteToExit.setString("Press ESC to exit");
	// Set text size
	Lives.setCharacterSize(50);
	BuzzsRevenge.setCharacterSize(100);
	Name.setCharacterSize(25);
	pressEnterToStartGame.setCharacterSize(75);
	escapteToExit.setCharacterSize(75);
	realScore.setCharacterSize(50);
	pressSpaceToPowerUp.setCharacterSize(75);
	scoreText.setCharacterSize(50);
	pressUpandDowntoAim.setCharacterSize(75);
	powerBar.setCharacterSize(50);

	// Font Colors
	escapteToExit.setFillColor(Color::White);
	pressSpaceToPowerUp.setFillColor(Color::White);
	Name.setFillColor(Color::White);
	Lives.setFillColor(Color::White);
	BuzzsRevenge.setFillColor(Color::Red);
	scoreText.setFillColor(Color::White);
	realScore.setFillColor(Color::White);
	pressUpandDowntoAim.setFillColor(Color::White);
	powerBar.setFillColor(Color::White);

	// Text Positions
	FloatRect textRect = pressUpandDowntoAim.getLocalBounds();
	// Message coordinates

	pressSpaceToPowerUp.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	Name.setOrigin(textRect.left +
		textRect.width / 1.5f,
		textRect.top +
		textRect.height / 1.5f);

	escapteToExit.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	BuzzsRevenge.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top + 1.0f +
		textRect.height / 2.0f);

	pressUpandDowntoAim.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);


	//locations for each text messages
	pressUpandDowntoAim.setPosition(1920 / 2.0f, 550); // 540
	BuzzsRevenge.setPosition(1920 / 2.0f + 150, 200);
	pressSpaceToPowerUp.setPosition(1920 / 2.0f + 150, 1080 / 1.7f); //
	escapteToExit.setPosition(1920 / 2.0f + 170, 1080 / 2.5f);
	pressEnterToStartGame.setPosition(1920 / 2.0f - 600, 300);
	Lives.setPosition(20, 200);
	scoreText.setPosition(1600, 30);
	Name.setPosition(1920 / 1.1f, 1080 / 1.1f);
	powerBar.setPosition(20, 980);

	//Textures for graphics
	Texture graphicsLives;
	graphicsLives.loadFromFile("graphics/buzzylife.png");
	//Number of Lives
	int lives = 5;
	//Sprite buzzy array of 5
	Sprite buzzyLives[5];
	buzzyLives[0].setTexture(graphicsLives);
	buzzyLives[1].setTexture(graphicsLives);
	buzzyLives[2].setTexture(graphicsLives);
	buzzyLives[3].setTexture(graphicsLives);
	buzzyLives[4].setTexture(graphicsLives);
	//Position of Lives Spirtes
	buzzyLives[0].setPosition(155, 30);
	buzzyLives[1].setPosition(255, 30);
	buzzyLives[2].setPosition(355, 30);
	buzzyLives[3].setPosition(455, 30);
	buzzyLives[4].setPosition(555, 30);

	// Texture for PLayers Buzz Spirte
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/buzzy life.png");
	Sprite Buzzy;
	Buzzy.setTexture(texturePlayer);
	Buzzy.setPosition(20, 720);
	// Player controls
	bool input = false;
	// Fire sound
	SoundBuffer buzzLaunch;
	buzzLaunch.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(buzzLaunch);
	//Death sound
	SoundBuffer deathSound;
	deathSound.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathSound);

	// Projectile motion parameters
	float initialAngle = 0;
	float g = -9.8;
	double V_initalY = 0;
	double airTime = 0;
	double beeTime = 0;
	double V_initial = 0;
	double V_initalX = 0;
	double velocityAmount = 1;
	double xprev = 0;
	double yperv = 0;
	float speedOfBee = 0.0f;

	// Spirte status
	bool tigerStatus = false;
	bool restart = false;
	bool bulldogStatus = false;
	bool buzzyStatus = false;
	bool beeStatus = false;
	bool squirelStatus = false;
	bool powerStatus = false;
	bool bulldogHit = true;
	bool unicornStatus = false;
	bool tigerHit = true;

	//Power Bar control
	RectangleShape powerBar;
	float pbWidth = 30;
	float pbHeight = 85;
	powerBar.setSize(Vector2f(pbWidth, pbHeight));
	powerBar.setFillColor(Color::Red);
	powerBar.setPosition(200, 980);
	float timeStart = 1.0f;
	float powerBarWidthPerSecond = pbWidth / (4.0 - timeStart);
	//Game control
	while (gameWindow.isOpen())
	{
		//Create event for the game
		Event event;
		while (gameWindow.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{

				input = true;
			}

		}
		// escape key causes exit
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			gameWindow.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			score = 0;
			lives = 5;
			input = true;
		}
		// When input is read
		if (input)
		{
			//Arrow keys control Buzz's angle
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				Buzzy.rotate(0.5);
				initialAngle = Buzzy.getRotation();
			}
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				Buzzy.rotate(-0.5);
				initialAngle = Buzzy.getRotation();
			}
			//Power bar Strength
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				if (timeStart < 40) {
					timeStart += 0.005;
					velocityAmount += 0.0002;
				}
				else {
					timeStart = 40;
					velocityAmount = 4;
				}
			}
			// Releasing the space bar launches BUzzy
			if (event.type == sf::Event::KeyReleased && event.key.code == Keyboard::Space)
			{
				// update the columns
				buzzyStatus = true;
				timeStart = 1;
				input = false;
				velocityAmount = 1;
				chop.play();
			}
		}
		if (!paused)
		{
			// Measure the current time
			Time dt = clock.restart();

			// Set powerbar during pause
			powerBar.setSize(Vector2f(powerBarWidthPerSecond * timeStart * 100, pbHeight));

			// removing Bee sprite while paused
			if (!beeStatus)
			{
				srand((int)time(0) * 10);
				speedOfBee = (rand() % 200) + 200;
				srand((int)time(0) * 10);
				float height = (rand() % 500);
				spriteBee.setPosition(2000, height);
				beeStatus = true;
			}
			else
			{
				// Move the bee
				beeTime += dt.asSeconds();
				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(speedOfBee * dt.asSeconds()),
					spriteBee.getPosition().y + 0.05 * cos(beeTime * velocityAmount));

				// Event where the bee reaches end of screen
				if (spriteBee.getPosition().x < -100 && spriteBeeHit == false)
				{
					beeStatus = false;
				}
			}
			// Reset back to original location according to current status
			if (!buzzyStatus) {
				V_initial = velocityAmount * 400;
				airTime = 0;
				Buzzy.setPosition(20, 720);
				Buzzy.setRotation(initialAngle);
				V_initalX = V_initial * cos(initialAngle * PI / 180) * 100;
				V_initalY = V_initial * sin(initialAngle * PI / 180);
			}
			// reset BUzzy after successful hit
			else if (buzzyStatus && squirelStatus) {
				Buzzy.move(0, 1000 * dt.asSeconds());
				Buzzy.rotate(0.1);
				if (Buzzy.getPosition().y > 1150) {
					squirelStatus = false;
					buzzyStatus = false;
				}
			}
			else {
				airTime += dt.asSeconds();
				xprev = Buzzy.getPosition().x;
				yperv = Buzzy.getPosition().y;
				Buzzy.move((V_initalX * airTime), V_initalY * airTime - 0.5 * g * airTime * airTime);

				Buzzy.setRotation((atan2(Buzzy.getPosition().y - yperv, Buzzy.getPosition().x - xprev) * 180 / PI));
				//event for pixel collsion
				if (Collision::collisionEvent(Buzzy, spriteBee)) {
					spriteBee.setPosition(2000, 2000);
					score += 75;
					spriteBeeHit = true;
					buzzyStatus = false;
				}
				// left column control
				if (tigerHit) {
					for (int i = 0; i < 5; i++) {
						if (Collision::collisionEvent(Buzzy, evilTiger[tigerLocation[i]])) {
							if (std::string(tigerLocation[i]) == "Tiger") {
								buzzyStatus = false;
								tigerStatus = true;
								score += 25;
								tigerHit = false;

							}
							else {
								squirelStatus = true;
								lives--;
							}
						}
					}
				}
				// right column control
				if (bulldogHit) {
					for (int i = 0; i < 5; i++) {
						if (Collision::collisionEvent(Buzzy, evilBulldog[bulldogLocation[i]])) {
							if (std::string(bulldogLocation[i]) == "Unicorn") {
								buzzyStatus = false;
								unicornStatus = true;
								lives++;
							}
							else  if (std::string(bulldogLocation[i]) == "BullDog") {
								buzzyStatus = false;
								bulldogStatus = true;
								score += 25;
								bulldogHit = false;
							}
							else {
								squirelStatus = true;
								lives--;
							}
						}
					}
				}
				// event if Buzzy is out of window bounds ( miss )
				if ((Buzzy.getPosition().x > 1920 || Buzzy.getPosition().x < 0) ||
					(Buzzy.getPosition().y > 1080))
				{
					buzzyStatus = false;
					lives--;
				}

			}

			// Event for Tiger hit
			if (tigerStatus) {
				for (auto i : tigerLocation) {
					evilTiger[i].setPosition(
						evilTiger[i].getPosition().x,
						evilTiger[i].getPosition().y + (1000 * dt.asSeconds())
					);
					evilTiger[i].rotate(0.1);
				}
				if (evilTiger[tigerLocation[4]].getPosition().y > 1200)
				{
					bulldogHit = true;
					tigerStatus = false;
				}
			}
			// event for bulldog hit
			if (bulldogStatus) {
				for (auto i : bulldogLocation) {
					evilBulldog[i].setPosition(
						evilBulldog[i].getPosition().x,
						evilBulldog[i].getPosition().y + (1000 * dt.asSeconds())
					);
					//hit animation
					evilBulldog[i].rotate(0.1);
				}
				if (evilBulldog[bulldogLocation[4]].getPosition().y > 1200)
				{
					bulldogStatus = false;
					restart = true;
				}
			}
			if (unicornStatus) {
				evilBulldog["Unicorn"].move(0, (1100 - evilBulldog["Unicorn"].getPosition().y));
				int x = 0;
				for (int i = 0; i < 5; i++) {
					if (std::string(bulldogLocation[i]) == "Unicorn") {
						x = i;
					}
				}
				int j = 4;
				for (int i = 4; i >= 0; i--) {
					if (i != x) {
						j--;
						evilBulldog[bulldogLocation[i]].setPosition(1820, locations[j]);
					}
				}
				unicornStatus = false;

			}
			// restart the game and reset game conditions
			if (restart) {
				int j = 0;
				shuffle(tigerLocation.begin(), tigerLocation.end(), std::default_random_engine(time(NULL)));
				shuffle(bulldogLocation.begin(), bulldogLocation.end(), std::default_random_engine(time(NULL)));
				for (auto i : tigerLocation) {

					evilTiger[i].setPosition(1675, locations[j]);
					evilTiger[i].setRotation(0);
					j++;
				}
				j = 0;
				for (auto i : bulldogLocation) {
					evilBulldog[i].setPosition(1820, locations[j]);
					evilBulldog[i].setRotation(0);
					j++;
				}

				tigerHit = true;
				if (!(lives > 0)) {
					lives = 5;
					score = 0;
					//end game 
				}
				restart = false;
				spriteBeeHit = false;
			}
			std::stringstream scoreString;
			scoreString << "Score = " << score;
			scoreText.setString(scoreString.str());
		}
		// Load the game
		gameWindow.clear();
		gameWindow.draw(background);
		gameWindow.draw(Buzzy);
		// Load the lvies
		gameWindow.draw(Lives);
		// Load bee sprite
		gameWindow.draw(spriteBee);
		//Load the score
		gameWindow.draw(scoreText);
		//Load Power Bar
		gameWindow.draw(powerBar);
		for (auto i : bulldogLocation) {
			//Bulldog column
			gameWindow.draw(evilBulldog[i]);
		}
		for (auto i : tigerLocation) {
			//Tiger column
			gameWindow.draw(evilTiger[i]);
		}
		if (paused)
		{
			// Press Escape to exit
			gameWindow.draw(escapteToExit);
			// Press space to power up
			gameWindow.draw(pressSpaceToPowerUp);
			//Reset game menu
			gameWindow.draw(pressEnterToStartGame);
			gameWindow.draw(Name);
			gameWindow.draw(pressUpandDowntoAim);
			gameWindow.draw(BuzzsRevenge);

		}
		// Lives control
		if (lives > 0 && lives < 6) {
			for (int i = 0; i < lives; i++) {
				gameWindow.draw(buzzyLives[i]);
			}
		}
		// Game over control
		else if (lives < 1) {
			restart = true;
			death.play();
		}
		else
		{
			lives = 5;
		}
		// display game
		gameWindow.display();
	}
	return 0;
}
