#include "gems.h"
using namespace sf;

void gem::printGem(gem Gem, RenderWindow* window) {
	ConvexShape convex;
	int x = Gem.getX();
	int y = Gem.getY();
	convex.setPointCount(4);
	convex.setPoint(0, Vector2f(static_cast<float>(x), static_cast<float>(y)));
	convex.setPoint(1, Vector2f(static_cast<float>(x) + 80, static_cast<float>(y)));
	convex.setPoint(2, Vector2f(static_cast<float>(x) + 80, static_cast<float>(y) + 80));
	convex.setPoint(3, Vector2f(static_cast<float>(x), static_cast<float>(y) + 80));
	convex.setFillColor(gem::gem_color);

	window->draw(convex);
}