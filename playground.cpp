#include "playground.h"
#include "game.h"

void Field::buildGrid() {
	srand(static_cast<int>(time(0)));
	for (int i = 0; i < GemsInRow; i++) {
		std::vector <gem> temporary_vector;
		for (int j = 0; j < GemsInColumn; j++) {
			
			switch (static_cast<int>(rand() / (static_cast<double>(RAND_MAX) + 1.0) * 6)) {
			case 0:
				temporary_vector.push_back(sf::Color::Yellow);
				break;
			case 1:
				temporary_vector.push_back(sf::Color::Blue);
				break;
			case 2:
				temporary_vector.push_back(sf::Color::Red);
				break;
			case 3:
				temporary_vector.push_back(sf::Color::Green);
				break;
			case 4:
				temporary_vector.push_back(sf::Color::Magenta);
				break;
			case 5:
				temporary_vector.push_back(sf::Color::Cyan);
				break;
			}
		}
		grid.push_back(temporary_vector);
		temporary_vector.clear();
	}
}

void Field::printField(sf::RenderWindow* window) {
	int x, y;
	for (int i = 0; i < GemsInRow; i++) {
		for (int j = 0; j < GemsInColumn; j++) {
			x = gem_size * i;
			y = gem_size * j;
			gem Gem;
			Gem.setX(x);
			Gem.setY(y);
			grid[i][j].printGem(Gem, window);
		}
	}
}

void Field::GemsSwap(gem FirstGem, gem SecondGem) {
	sf::Color color_1, color_2;

	color_1 = grid[FirstGem.x][FirstGem.y].GetColor();
	color_2 = grid[SecondGem.x][SecondGem.y].GetColor();

	grid[FirstGem.x][FirstGem.y].SetColor(color_2);
	grid[SecondGem.x][SecondGem.y].SetColor(color_1);
}

void Field::RemoveIdenticalNeighbors(gem FirstGem, gem SecondGem) {
	sf::Color Color1 = grid[FirstGem.x][FirstGem.y].GetColor(), Color2 = grid[SecondGem.x][SecondGem.y].GetColor();
	int left1, right1, up1, down1; // number 1 matching item
	int left2, right2, up2, down2;
	left1 = right1 = up1 = down1 = left2 = right2 = up2 = down2 = 0;

	int i = FirstGem.x;
	int j = FirstGem.y;

	while (i >= 0) {
		if (grid[i][FirstGem.y].GetColor() == Color1) {
			left1 = i;
			i--;
		}
		else {
			left1 = i + 1;
			break;
		}
	}
	i = FirstGem.x;
	while (i < 10) {
		if (grid[i][FirstGem.y].GetColor() == Color1) {
			right1 = i;
			i++;
		}
		else {
			right1 = i - 1;
			break;
		}
	}
	while (j >= 0) {
		if (grid[FirstGem.x][j].GetColor() == Color1) {
			up1 = j;
			j--;
		}
		else {
			up1 = j + 1;
			break;
		}
	}
	j = FirstGem.y;
	while (j < 10) {
		if (grid[FirstGem.x][j].GetColor() == Color1) {
			down1 = j;
			j++;
		}
		else {
			down1 = j - 1;
			break;
		}
	}

	i = SecondGem.x;
	while (i >= 0) {
		if (grid[i][SecondGem.y].GetColor() == Color2) {
			left2 = i;
			i--;
		}
		else {
			left2 = i + 1;
			break;
		}
	}
	i = SecondGem.x;
	while (i < 10) {
		if (grid[i][SecondGem.y].GetColor() == Color2) {
			right2 = i;
			i++;
		}
		else {
			right2 = i - 1;
			break;
		}
	}
	j = SecondGem.y;
	while (j >= 0) {
		if (grid[SecondGem.x][j].GetColor() == Color2) {
			up2 = j;
			j--;
		}
		else {
			up2 = j + 1;
			break;
		}
	}
	j = SecondGem.y;
	while (j < 10) {
		if (grid[SecondGem.x][j].GetColor() == Color2) {
			down2 = j;
			j++;
		}
		else {
			down2 = j - 1;
			break;
		}
	}
	if ((abs(left1 - right1) + abs(up1 - down1)) > 1)
		removeGem(FirstGem.x, FirstGem.y, left1, right1, up1, down1);

	if ((abs(left2 - right2) + abs(up2 - down2)) > 1)
		removeGem(SecondGem.x, SecondGem.y, left2, right2, up2, down2);

}

void Field::removeGem(int x, int y, int from_x, int to_x, int from_y, int to_y) {
	for (int i = from_x; i <= to_x; i++) {
		grid[i][y].SetColor(sf::Color::Black);
	}
	for (int j = from_y; j <= to_y; j++) {
		grid[x][j].SetColor(sf::Color::Black);
	}
}

void Field::rebuild() {
	int t = 0;
	gem firstGem, secondGem;
	for (int i = 0; i < GemsInRow; i++) {
		int tt = 0;
		for (int j = GemsInColumn - 1; j > 0; j--) {
			if (grid[i][j].GetColor() == sf::Color::Black) {
				tt++;
				for (int k = j; k > 0; k--) {
					
					firstGem.setX(i);
					firstGem.setY(k);
					secondGem.setX(i);
					secondGem.setY(k-1);
					GemsSwap(firstGem, secondGem);
				}
			}
		}
		if (t < tt)
			t = tt;
	}
	while (t > 0) {
		for (int i = 0; i < GemsInRow; i++) {
			for (int j = GemsInColumn - 1; j > 0; j--) {
				if (grid[i][j].GetColor() == sf::Color::Black) {
					t = j;
					for (int k = j; k > 0; k--) {
						firstGem.setX(i);
						firstGem.setY(k);
						secondGem.setX(i);
						secondGem.setY(k - 1);
						GemsSwap(firstGem, secondGem);
					}
				}
			}
		}
		t--;
	}

	for (int i = 0; i < GemsInRow; i++) {
		for (int j = 0; j < GemsInColumn; j++) {
			if (grid[i][j].GetColor() == sf::Color::Black) {
				switch (static_cast<int>(rand() / (static_cast<double>(RAND_MAX) + 1.0) * 6)) {
				case 0:
					grid[i][j].SetColor(sf::Color::Yellow);
					break;
				case 1:
					grid[i][j].SetColor(sf::Color::Blue);
					break;
				case 2:
					grid[i][j].SetColor(sf::Color::White);
					break;
				case 3:
					grid[i][j].SetColor(sf::Color::Green);
					break;
				case 4:
					grid[i][j].SetColor(sf::Color::Magenta);
					break;
				case 5:
					grid[i][j].SetColor(sf::Color::Cyan);
					break;
				}
			}
		}
	}
}

void Field::SetColorToOneGem(int x, int y) {
	switch (static_cast<int>(rand() / (static_cast<double>(RAND_MAX) + 1.0) * 6)) {
	case 0:
		grid[x][y].SetColor(sf::Color::Yellow);
		break;
	case 1:
		grid[x][y].SetColor(sf::Color::Blue);
		break;
	case 2:
		grid[x][y].SetColor(sf::Color::White);
		break;
	case 3:
		grid[x][y].SetColor(sf::Color::Green);
		break;
	case 4:
		grid[x][y].SetColor(sf::Color::Magenta);
		break;
	case 5:
		grid[x][y].SetColor(sf::Color::Cyan);
		break;
	}
}