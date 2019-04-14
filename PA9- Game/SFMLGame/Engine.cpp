#include "Engine.h"
Game::Game() {
	srand((unsigned int)time(NULL));
	gameStart = false;
}

Game::~Game() {
}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Shogun-Master Makano");
	///Visual Objects Initilized
	Player *player = new Player();
	Star *star = new Star();
	Enemy enemy[MAX_ENEMIES];
	Star enemyStar[MAX_ENEMIES];
	visualObj background, gameOverScreen, startScreen;
	///Sprites/Images loaded
	background.load("sprites/background.png");
	gameOverScreen.load("sprites/gameOverScreen.png");
	startScreen.load("sprites/startScreen.png");
	player->load("sprites/player.png");
	star->load("sprites/star.png");
	///Sets origins & positions
	background.setOrigin(0, 0);
	startScreen.setOrigin(0, 0);
	gameOverScreen.setPosition(0, -300);
	player->setPosition(500, 630);
	for (int x = 0; x < MAX_ENEMIES; x++) {	///Loads multipy enemies & sprites w/ Ai
		enemy[x].load("sprites/enemy.png");		//Loads Enemy Sprites
		enemy[x].spawn();						//Spawns a new enemy randomly on the map
		enemyStar[x].load("sprites/star.png");	//Loads Star Sprite
		enemyStar[x].setColor(200, 0, 0);		//Makes Star Red to distinguish as enemy projectiles
	}
	///Loop to run game
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {	///Event Updates
			///If any key is pressed, game starts
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickMoved)
				gameStart = true;	//Starts the Game
			check_closeWindows(event, window);		//Closes Game Events
			if (player->checkGameOver() == false) {		///Player can not move if game is over
				player->eventUpdate(event);			//Updates Character Events
				star->eventUpdate(event);			//Updates Star Events
			} else	///Game Over
				gameOverMenu(event, window, (Player*)player, (visualObj)gameOverScreen);
		}
		///If game is over, player stops moving & projectiles stop
		if (player->checkGameOver() == false) {
			for (int x = 0; x < MAX_ENEMIES; x++)
				enemyStar[x].eventAiUpdate(event);
			moveUpdate((Player*)player, enemy, (Star*)star);	//Movement Updates
			///Enemies don't attack when game has not started
			if (gameStart == true)
				for (int x = 0; x < MAX_ENEMIES; x++) {
					enemy[x].checkCollision(star);
					enemyStar[x].moveUpdate(&enemy[x], false);
					player->checkCollision((Star*)&enemyStar[x]);
				}
		}
		///Places game over menu on screen if game is over or restarted
		if (player->checkGameOver() == true)
			gameOverScreen.setPosition(500, 300);
		else
			gameOverScreen.setPosition(0, -400);
		///Displays everything
		window.clear();				//Clears Window

		background.draw(window);	//Displays Background
		star->draw(window);			//Displays player's star
		player->draw(window);		//Displays Player
		for (int x = 0; x < MAX_ENEMIES; x++) {///Runs through all enemies
			enemyStar[x].draw(window);
			enemy[x].draw(window);	//Displays Enemies
		}
		if (gameStart == false)
			startScreen.draw(window);
		gameOverScreen.draw(window);
		window.display();			//Displays Window to Screen
	}
}

void Game::moveUpdate(Player *player, Enemy enemy[], Star *star) {
	player->moveUpdate();						//Player's Movements
	for (int x = 0; x < MAX_ENEMIES; x++)	///Spawns total enemies
		enemy[x].moveUpdate();
	star->moveUpdate((Player*)player, true);			//Stars Movement
}

void Game::check_closeWindows(sf::Event event, sf::RenderWindow &window) {
	if (event.type == sf::Event::Closed)
		window.close();									//Closes Window
	if (event.type == sf::Event::KeyPressed)			///If Keyboard is Pressed
		if (event.key.code == sf::Keyboard::Escape)	///Press Esc on Keyboard to Exit
			window.close();								//Closes Window
	if (event.type == sf::Event::JoystickButtonPressed)	///If Controller is Pressed
		if (event.joystickButton.button == 6)		///Press Back on Controller to Exit
			window.close();								//Closes Window
}

int Game::rand_int(int min, int quantity) {
	return rand() % quantity + min;
}

void Game::gameOverMenu(sf::Event event, sf::RenderWindow &window, Player *player, visualObj gameOverScreen) {
	if (event.type == sf::Event::KeyPressed) {	///Keyboard Commands
		if (event.key.code == sf::Keyboard::S) {	///Pressed S on Keyboard
			player->revive();							//Revives Player
			gameStart = false;							//Restarts Game
			return;										//Break
		}
		if (event.key.code == sf::Keyboard::A)		///Pressed A on Keyboard
			window.close();
	}
	if (event.type == sf::Event::JoystickButtonPressed) {	///Controller Action Buttons
		if (event.joystickButton.button == 3) {		///Pressed Y on Xbox Controller
			player->revive();							//Revives Player
			gameStart = false;							//Restarts Game
			return;										//Break
		}
		if (event.joystickButton.button == 1)		///Pressed B on Xbox Controller
			window.close();
	}
}