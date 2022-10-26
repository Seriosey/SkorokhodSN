#pragma once
//#include "bonuce.hpp"
//#include "ball.hpp"
#include"mech.hpp"
//#include"paddle.hpp"


Bonus::Bonus(float x, float y) {
	shape.setPosition(x, y);
	shape.setSize({ bonusWidth, bonusHeight });
	shape.setOrigin(bonusWidth / 2.f, bonusHeight / 2.f);
	shape.setFillColor(Color::Magenta);
	block_pos_x = x;
	block_pos_y = y;
}

void Bonus::update() {
	Vector2f velo = { 0.f, 5.f };
	shape.move(velo);
}

void Bonus::BonusCheck(Paddle* paddle, Ball* ball, RenderWindow* window, Time gameClock) {

	if (IsActive() == false) {
		return;
	}
	if (GetType() == "newBlockBonus") {
		BonusActivate();
		return;
	}
	if (GetBonusClock().getElapsedTime() < oneBonusTime) {
		BonusActivate();
	}
	if (GetBonusClock().getElapsedTime() > oneBonusTime) {
		SetActivity(false);
		BonusDeactivate();
	}
}

SizeIncreaseBonus::SizeIncreaseBonus(float _x, float _y, Paddle* _paddle) : Bonus(_x, _y) {
	SetType("sizeIncreaseBonus");
	paddle = _paddle;
}

void SizeIncreaseBonus::BonusDeactivate() {
	paddle->shape.setSize({ paddleWidth, paddleHeight });
	paddle->shape.setOrigin(paddle->shape.getSize().x / 2.f, paddleHeight / 2.f);
};

void SizeIncreaseBonus::BonusActivate() {
	paddle->shape.setSize({ paddleWidth * 3, paddleHeight });
	paddle->shape.setSize({ paddleWidth * 3, paddleHeight });
	paddle->shape.setOrigin(paddle->shape.getSize().x / 2.f, paddleHeight / 2.f);
};

SpeedUpBonus::SpeedUpBonus(float _x, float _y, Ball* _ball) : Bonus(_x, _y) {
	SetType(type);
	type = "speedUpBonus";
	ball = _ball;
}

void SpeedUpBonus::BonusActivate(){
	ballVelocity *= 1.3;
	ball->update();
};
void SpeedUpBonus::BonusDeactivate() {
	ballVelocity /= 1.3;
	ball->update();
};

SafeBottomBonus::SafeBottomBonus(float _x, float _y, RenderWindow* _window, Ball* _ball) : Bonus(_x, _y) {
	SetType("safeBottomBonus");
	window = _window;
	ball = _ball;
}
void SafeBottomBonus::BonusActivate() {
	RectangleShape shape;
	shape.setPosition(0, windowHeight - 5);
	shape.setFillColor(Color::Yellow);
	shape.setSize({ windowWidth, 5 });
	window->draw(shape);
	if (ball->bottom() >= windowHeight-5) {
		SetActivity(false);
	}
};

StickCarriageBonus::StickCarriageBonus(float _x, float _y, Paddle* _paddle, Ball* _ball) : Bonus(_x, _y) {
	SetType("stickCarriageBonus");
	paddle = _paddle;
	ball = _ball;
}

void StickCarriageBonus::BonusActivate() {
	if ((ball->right() >= paddle->left() && ball->left() <= paddle->right() && ball->bottom() >= paddle->top() && ball->top() <= paddle->bottom()) == false) {
		return;
	}
	ball->setVelocity(0);
	ball->setVelocity(paddle->GetVelocity());

	float xPlace = ball->x() - paddle->x();
	if (xPlace > 0) {
		ball->shape.setPosition({ paddle->x() + xPlace, windowHeight - 50 - paddleHeight });
	}
	if (xPlace < 0) {
		ball->shape.setPosition({ paddle->x() - xPlace, windowHeight - 50 - paddleHeight });
	}
	if (xPlace == 0) {
		ball->shape.setPosition({ paddle->x(), windowHeight - 50 - paddleHeight });
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) || ball->right() >= windowWidth) {
		ball->setVelocity(-paddleVelocity);

	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) || ball->left() <= 0) {
		ball->setVelocity(paddleVelocity);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
		SetActivity(false);
	}
};

ChangeWayBonus::ChangeWayBonus(float _x, float _y, Ball* _ball) : Bonus(_x, _y) {
	SetType("changeWayBonus");
	ball = _ball;
	SetRandTime();
}

void ChangeWayBonus::BonusActivate() {
	int changeOption = rand() % 3;
	ball->shape.setFillColor(Color::Green);
	if ((int)GetBonusClock().getElapsedTime().asSeconds() == randTime) {
		cout << changeOption << endl;
		if (changeOption == 0) {
			ball->setVelocityX(-ball->getVelocityX());
			ball->setVelocityY(-ball->getVelocityY());

		}
		if (changeOption == 1) {
			ball->setVelocityX(ball->getVelocityX());
			ball->setVelocityY(-ball->getVelocityY());

		}
		if (changeOption == 2) {
			ball->setVelocityX(-ball->getVelocityX());
			ball->setVelocityY(ball->getVelocityY());
		}
		SetActivity(false);
		BonusDeactivate();
	}
};
void ChangeWayBonus::BonusDeactivate() {
	ball->shape.setFillColor(Color::White);
};

NewBlockBonus::NewBlockBonus(float _x, float _y, Ball* _ball, RenderWindow* _window, Paddle* _paddle) : Bonus(_x, _y) {
	SetType("newBlockBonus");
	ball = _ball;
	window = _window;
	paddle = _paddle;
	block = new MovingBlock(windowWidth / 2, windowHeight / 4 + (rand() % (windowHeight / 2) + 70));
	block->shape.setFillColor(Color::Green);
}
void NewBlockBonus::BonusActivate() {
	window->draw(block->shape);
	block->update();
	testCollisionBB(*block, *ball, *paddle, *window);
	if (block->hardness == 0) {
		block->destroyed = true;
		SetActivity(false);
	}
	//score += 1;
}
Bonus* CreateBonuses(float mx, float my, Paddle* paddle, Ball* ball, RenderWindow* window) {
	//vector <Bonus*> bonuses;
	int tmp = rand() % 5;
	if (tmp == 0) {
		Bonus* bonus = new SizeIncreaseBonus{ mx, my, paddle };
		bonuses.push_back(bonus);
		return bonus;
	}
	if (tmp == 1) {
		Bonus* bonus = new SpeedUpBonus{ mx, my, ball };
		bonuses.push_back(bonus);
		return bonus;
	}
	if (tmp == 2) {
		Bonus* bonus = new SafeBottomBonus{ mx, my, window, ball };
		bonuses.push_back(bonus);
		return bonus;
	}
	if (tmp == 3) {
		Bonus* bonus = new StickCarriageBonus{ mx, my, paddle, ball };
		bonuses.push_back(bonus);
		return bonus;
	}
	if (tmp == 4) {
		Bonus* bonus = new ChangeWayBonus{ mx, my, ball };
		bonuses.push_back(bonus);
		return bonus;
	}
	if (tmp == 5) {
		Bonus* bonus = new NewBlockBonus{ mx, my, ball, window, paddle };
		bonuses.push_back(bonus);
		return bonus;
	}
}