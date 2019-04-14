#pragma once
#include "visualObj.h"

class Star : public visualObj {
public:
	Star();
	~Star();
	void throwStar(visualObj *player, bool isPlayer);
	void draw(sf::RenderWindow & window);
	void eventUpdate(sf::Event event);
	void moveUpdate(visualObj *player, bool isPlayer);
	void eventAiUpdate(sf::Event event);
	int rand_int(int min, int quantity);
private:
	bool isThrown;
};