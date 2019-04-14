/*******************************************************************************************
* Programmers: Cong Trinh, Gabe Berbig, Hansel Cheong, Pedro Teodoro
* Contributions:
*	Cong Trinh: Almost All Code including Ai, Ui, movements, collisions & engine (Not exaggerating...),
*				w/ Classes & Sprites: Screen Menus, Game Over Screen & Characters Textures
*	Gabe Berbig: Menu UI & Menu
*	Hansel Cheong: Background & Music (Music wouldn't work anymore last minute)
*	Pedro: Text Font..
*	
* Class: CptS 122, Spring 2016
* Programming Assignment: PA9 Game: Shogun Master Kanako
* Date: April 14, 2016
* Description: This program runs a ninja-themed game in SFML. The goal of the game is to survive
*			as long as possible. Throw stars at enemies to kill them, and dash to dodge enemy
*			projectiles. Enemies respawn randomly at random times after death. The player only
*			has 3 lives. Have Fun~
*******************************************************************************************/
#include "Engine.h"

int main() {
	Game app;
	app.run();
	return 0;
}