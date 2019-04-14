#include "Player.h"
#include "Engine.h"

Player::Player() {
	health = 3;
	dead = false;
	collisionTimer = 0;
	dashTimer = 0;
	x = 0;
	y = 0;
}

Player::~Player() {
}

void Player::draw(sf::RenderWindow & window) {
	visualObj::draw(window);
}

void Player::eventUpdate(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {	///Keyboard Commands
		if (event.key.code == sf::Keyboard::Up)		// Move Up
			x = 0, y = -P_SPD;
		if (event.key.code == sf::Keyboard::Down)	// Move Down
			x = 0, y = P_SPD;
		if (event.key.code == sf::Keyboard::Right)	// Move Right
			x = P_SPD, y = 0;
		if (event.key.code == sf::Keyboard::Left)	// Move Left
			x = -P_SPD, y = 0;
		if (event.key.code == sf::Keyboard::Z)		//X = Dash
			activateDash();
	}
	else if (event.type == sf::Event::JoystickMoved) {										///Controller Directionals
		if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100)	//Up
			x = 0, y = -P_SPD;
		if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100)	//Down
			x = 0, y = P_SPD;
		if (event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100)	//Right
			x = P_SPD, y = 0;
		if (event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100)	//Left
			x = -P_SPD, y = 0;
	}
	if (event.type == sf::Event::JoystickButtonPressed) {	///Controller Action Buttons
		if (event.joystickButton.button == 0)					//A = Dash
			activateDash();
	}
}

void Player::moveUpdate() {
	if (dashTimer != 0) {	///Player's speed increases for dash
		move(x * 3, y * 3);		//Moves 3x fast
		dashTimer--;			//Dash timer count down
	} else					///Moves normally
		move(x, y);				//Moves at normal speed
	border();					//Makes sure player stays within games border
}

void Player::activateDash() {
	dashTimer = DASH_TIME;	//Dash timer is set, player dashes in this time
}

void Player::border() {
	if (getPosition().x >= SCREEN_X - getWidth()/2)			///If Player goes off screen, spawns on the other side
		setPosition(SCREEN_X - getWidth()/2, getPosition().y);			//Right Border
	if (getPosition().x <= getWidth() / 2)
		setPosition(getWidth()/2, getPosition().y);						//left Border
	if (getPosition().y < 520 + getHeight() / 2)
		setPosition(getPosition().x, 520 + getHeight() / 2);			//Top Border
	if (getPosition().y >= SCREEN_Y - getHeight()/2 - 30)
		setPosition(getPosition().x, SCREEN_Y - getHeight()/2 - 30);	//Bottom Border
}

bool Player::isCollision(visualObj *star) {
	///Works as collision box, creates a rectangular region to detect collision
	int top = getPosition().x + getWidth() / 2 + star->getWidth() / 2;
	int bottom = getPosition().x - getWidth() / 2 - star->getWidth() / 2;
	int right = getPosition().y + getHeight() / 2 + star->getHeight() / 2;
	int left = getPosition().y - getHeight() / 2 + star->getHeight() / 2;

	if ((bottom < star->getPosition().x && star->getPosition().x < top))		//Checks Top & Bottom Collision Box
		if ((left < star->getPosition().y && star->getPosition().y < right))	//Checks Left & Right Collision Box
			return true;
	return false;
}

void Player::checkCollision(visualObj *star) {
	bool interact = isCollision(star);		//Checks if player interacted with star
	int healthColor = (105 + health * 50);	//Sets current color for player based on health

	if (interact == true) {
		if (collisionTimer == 0)	///If timer is not set yet
			health--;		//Loses health
		if (health == 0) {	///Player runs out of health
			x = 0, y = 0;	//Player stops moving after death
			dead = true;	//Declared dead
		}
		setColor(255, 0, 0);	//Collision with enemy star [Damage taken, changes Red]
		collisionTimer = 400;	//Timer for player to stay red from damage
	}
	if (collisionTimer > 0)						///If collision is currently counting down
		collisionTimer--;							//Collision Timer counts down
	else if (collisionTimer == 0)				///If collision timer hits 0
		setColor(255, healthColor, healthColor);	//Changes enemy's color back after certain period of time
}

bool Player::checkGameOver() {
	if (health == 0) {
		setColor(0, 0, 0);	///Sets enemy as black, indicating dead
		return true;
	}
	return false;
}

void Player::revive() {	///Revives Player
	dead = false;	//Declared revived
	health = 3;		//Given full health
	setPosition(500, 630);	//Set at center of screen
}