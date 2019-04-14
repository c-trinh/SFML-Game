#pragma once
#include "visualObj.h"

class Player: public visualObj {
public:
	Player();
	~Player();
	void draw(sf::RenderWindow & window);
	void eventUpdate(sf::Event event);
	void moveUpdate();
	void activateDash();
	void border();
	bool isCollision(visualObj *star);
	void checkCollision(visualObj *star);
	bool checkGameOver();
	void revive();
private:
	int health;
	bool dead;
	int collisionTimer;
	int respawnTimer;
	int dashTimer;
	double x;
	double y;
};

