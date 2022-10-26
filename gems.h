#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <vector>
using namespace sf;
constexpr unsigned int WindowWidth{800}, WindowHeight{800};


class gem {
public:
	int x;
	int y;
	void setX(int _x) {x = _x;}
	void setY(int _y) { y = _y; }
	int getX() { return x; }
	int getY() { return y; }

	gem(Color color) {
		gem_color = color;
	}
	gem() {};
	int GetSizeGem() {
		return gem_size;
	}
	void printGem(gem Gem, RenderWindow* window);
	Color GetColor() {
		return gem_color;
	}
	void SetColor(Color color) {
		gem_color = color;
	}
	

private:
	int gem_size = 80;
	Color gem_color;
};

