#include "Star.h"
#include "Engine.h"

Star::Star() {
	isThrown = false;
}

Star::~Star() {

}

void Star::throwStar(visualObj *player, bool isPlayer) {
	int x = player->getPosition().x;
	int y = player->getPosition().y;
	int showStar = getHeight();
	if (isPlayer == false)
		showStar = 0;				//Spanws at Enemy's position hidden under them
	setPosition(x, y - showStar);	//Spawns at Player's position, in front of the player
}

void Star::draw(sf::RenderWindow & window) {
	visualObj::draw(window);
}

void Star::moveUpdate(visualObj *player, bool isPlayer) {
	if (isThrown == false)
		throwStar(player, isPlayer);	//Spawns at Player's position
	else if (getPosition().y < (-1) * getHeight() || getPosition().y > SCREEN_Y) {	///If Star goes off screen
		setRotation(0);			//Star rotation resets
		setPosition(-20, -20);	//Is places off screen
		isThrown = false;		//Throw is off, player can throw more stars
	}
	else {							///Star is moved upwards towards enemies' side
		rotate(.5);	//Rotates star as it moves
		if (isPlayer)
			move(0, -.5);		//Player's star moved upwards
		else
			move(0, .3);		//Enemies' stars move downwards slower
	}
}

void Star::eventUpdate(sf::Event event) {
	if (event.type == sf::Event::KeyPressed)	///Keyboard Commands
		if (event.key.code == sf::Keyboard::X)		//X = Throw Attack
			isThrown = true;
	if (event.type == sf::Event::JoystickButtonPressed)		///Controller Action Buttons
		if (event.joystickButton.button == 2)					//X = Throw Attack
			isThrown = true;
}

void Star::eventAiUpdate(sf::Event event) {
	int rand = rand_int(0, 3);	///Enemy has 1/3 random chance to throw enemy star
	if (rand == true)
		isThrown = true;	//Randomly throws
}

int Star::rand_int(int min, int quantity) {
	return rand() % quantity + min;
}