#include "visualObj.h"

visualObj::visualObj() {
	srand((unsigned int)time(NULL));
}

void visualObj::load(std::string filename) {
	if (texture.loadFromFile(filename) == false) {	//Loads game texture
		filename = "";
		isLoaded = false;
	} else {
		filename = filename;
		sprite.setTexture(texture);	//Sets as sprite
		isLoaded = true;
	}
	sprite.setOrigin(getWidth() / 2, getHeight() / 2);	//Sets origin of sprite to be the center
}

void visualObj::draw(sf::RenderWindow & window) {
	if (isLoaded)
		window.draw(sprite);
}

void visualObj::setOrigin(int x, int y) {
	sprite.setOrigin(x, y);			//Lets manual origin set
}

void visualObj::setPosition(double x, double y) {
	if (isLoaded)
		sprite.setPosition(x, y);	//Manual positionset
}

void visualObj::setColor(int r, int b, int g) {
	sprite.setColor(sf::Color(r, b, g));	//Manual color set
}

void visualObj::move(double x, double y) {
	if (isLoaded)
		sprite.move(x, y);	//Manually moves sprite
}

void visualObj::rotate(double rot) {
	if (isLoaded)
		sprite.rotate(rot);	//Manually rotates sprite
}

void visualObj::setRotation(double rot) {
	if (isLoaded)
		sprite.setRotation(rot);	//Sets rotation manually
}

sf::Sprite visualObj::getSprite() {
	return sprite;					//Returns sprite if needed
}

sf::Vector2f visualObj::getPosition() {
	return sprite.getPosition();	//Manually gets position
}

double visualObj::getHeight() {
	return sprite.getGlobalBounds().height;	//Gets height of sprite
}

double visualObj::getWidth() {
	return sprite.getGlobalBounds().width;	//Gets width of sprite
}