#include <iostream>
#include <SFML/Graphics.hpp>
#include "headers/Game.h"
#include "headers/consts.h"

const int WINDOW_WIDTH = 550;
const int WINDOW_HEIGHT = 800;
const int GOAL_WIDTH = 110*1.3;
const int GOAL_HEIGHT = 44;
const char* TITLE = "FootLan2k17";
const double UPDATE_TIME = 0.005;

int main(int argc, char *argv[])
{
	Game game;
	game.run();

	return 0;
}
