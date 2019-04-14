#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "Player.h"
#include "Enemy.h"
#include "Star.h"

#define SCREEN_X 1000	//Size of Memory, can be changed
#define SCREEN_Y 800	//Size of Memory, can be changed
#define MAX_ENEMIES 5
#define DASH_TIME 250	//Speed of Player Attack
#define P_SPD .2		//Player's Speed
#define E_SPD .15		//Player's Speed

class Game {
public:
	Game();
	~Game();
	void run();
	int rand_int(int min, int quantity);
	void moveUpdate(Player *player, Enemy enemy[], Star *star);
	void check_closeWindows(sf::Event event, sf::RenderWindow &window);
	void gameOverMenu(sf::Event event, sf::RenderWindow &window, Player *player, visualObj gameOverScreen);
private:
	bool gameStart;
};