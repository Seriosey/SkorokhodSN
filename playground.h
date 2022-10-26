#pragma once
#include <vector>
#include <iostream>
//#include "game.h"
#include "gems.h"
#include "SFML\Graphics.hpp"



class Field {
public:
	void buildGrid();
	void printField(sf::RenderWindow* window);
	void GemsSwap(gem FirstGem, gem SecondGem);
	void RemoveIdenticalNeighbors(gem FirstGem, gem SecondGem);
	void removeGem(int x, int y, int from_x, int to_x, int from_y, int to_y);
	void rebuild();
	bool GemIsEmpty(int i, int j) {
		if (grid[i][j].GetColor() == sf::Color::Black)
			return true;
		else
			return false;
	}
	int GemAmount() {
		return GemsInRow;
	}
	void SetColorToOneGem(int x, int y);
private:
	std::vector< std::vector<gem>> grid;
	std::vector<gem> gems;
	std::vector<sf::Color> colors = { sf::Color::Yellow, sf::Color::Blue, sf::Color::White, sf::Color::Green, sf::Color::Magenta, sf::Color::Cyan };
	int gem_size = 80;
	int WindowWidth = 800;
	int WindowHeight = 800;
	int GemsInRow = WindowWidth / gem_size;
	int GemsInColumn = WindowHeight / gem_size;
};
