#pragma once
#include "playground.h"
#include "gems.h"
#include "game.h"
#include "SFML\Graphics.hpp"
#include <iostream>
#include <time.h>
#include <cmath>
using namespace sf;

class Game {
public:
	void Run();

	Game() {
		window = new RenderWindow(VideoMode(WindowWidth, WindowHeight), "GEMS" );
		isPicked = false;
		FirstGemX = FirstGemY = SecondGemX = SecondGemY = 0;
	}
	gem FirstGem;
	gem SecondGem;
	Field field;

private: 
	RenderWindow* window;
	bool isPicked;
	int FirstGemX, FirstGemY, SecondGemX, SecondGemY;

	void Draw();
	void Update(int elapsed);
	void SelectFirstGem1(Event event);
	void SelectSecondGem1(Event event);
	void Combination();
	void Moving(Event event);
	bool isNeighbours(gem FirstGem, gem SecondGem);

};
