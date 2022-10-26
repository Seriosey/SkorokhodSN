#include "game.h"
using namespace sf;

void Game::Draw() {
	window->clear();
	field.printField(window);

	window->display();
}

void Game::Update(int elapsed) {
	Event event;
	while (window->pollEvent(event)) {
		switch (event.type) {
		case Event::Closed:
			window->close();
			break;
		case Event::MouseButtonReleased:
			Moving(event);
			field.rebuild();
			break;
		}
	}
}

void Game::Run() {
	Clock clc;
	field.buildGrid();

	while (window->isOpen()) {
		int elapsed = clc.restart().asMilliseconds();
		Update(elapsed);

		Draw();
	}
}

void Game::SelectFirstGem1(Event event) {
	if (event.mouseButton.button == Mouse::Left) {
		
		Vector2i localPositionFirstGem = Mouse::getPosition();
		float x_size = 80, y_size = 80;

		FirstGem.setX(static_cast<int>(event.mouseButton.x / x_size));
		FirstGem.setY( static_cast<int>(event.mouseButton.y / y_size));

		isPicked = true;
	}
}

void Game::SelectSecondGem1(Event event) {
	if (event.mouseButton.button == Mouse::Left) {
		
		Vector2i localPositionFirstGem = Mouse::getPosition();
		float x_size = 80, y_size = 80;

		SecondGem.setX (static_cast<int>(event.mouseButton.x / x_size));
		SecondGem.setY ( static_cast<int>(event.mouseButton.y / y_size));

		Combination();

		isPicked = false;
		
	}
	if (event.mouseButton.button == Mouse::Right) {
		isPicked = false;
	}
}



void Game::Combination() {
	if (isNeighbours(FirstGem, SecondGem)) {
		field.GemsSwap(FirstGem, SecondGem);
		field.RemoveIdenticalNeighbors(FirstGem, SecondGem);
	}
}

void Game::Moving(Event event) {
	if (!isPicked) {
		SelectFirstGem1(event);
	}
	else {
		SelectSecondGem1(event);
	}
}

bool Game::isNeighbours(gem FirstGem, gem SecondGem) {
	return (abs(FirstGem.x - SecondGem.x) + abs(FirstGem.y - SecondGem.y)) == 1;
}