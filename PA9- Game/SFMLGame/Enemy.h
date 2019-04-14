#pragma once
#include "visualObj.h"

class Enemy : public visualObj {
public:
	Enemy();
	~Enemy();
	void draw(sf::RenderWindow & window);
	void AiUpdate();
	void enemyAi1();
	void moveUpdate();
	void border();
	void checkCollision(visualObj *star);
	bool isCollision(visualObj *star);
	void death();
	void respawn();
	void spawn();
	int rand_int(int min, int quantity);
private:
	int health;
	bool dead;
	int collisionTimer;
	int respawnTimer;
	double x;
	double y;
};