#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
#include<iostream>
#include<vector>
#include<string>
//#include "ball.hpp"
//#include "paddle.hpp"
//#include "Interaction.hpp"
//#include "blocks.hpp"
//#include"Player.hpp"
//#include "bonuce.hpp"
//#include "window.hpp"
#include "mech.hpp"

using namespace std;
using namespace sf;

//int score{ 0 };

int main()
{
    // Loot loot(windowWidth / 2, windowHeight/2);
    Ball ball{ windowWidth / 2, windowHeight / 2 };
    Paddle paddle{ windowWidth / 2, windowHeight - 50 };
    vector<Brick> bricks;
   // vector <Bonus*> bonuses;
    vector <Bonus*> activeBonuses;
    srand(time(0));
    Clock gameClock;


    for (int iX{ 0 }; iX < countBlocksX; ++iX)
        for (int iY{ 0 }; iY < countBlocksY; ++iY)
            bricks.emplace_back(
                (iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));

    RenderWindow window(VideoMode(800, 600), "Arkanoid ");
    window.setFramerateLimit(60);

    while (true)
    {
        window.clear(Color::Black);

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            cout << "Score is " << score << endl; break;
        }

        ball.update();
        paddle.update();
        //loot.update();
        testCollisionPB(paddle, ball);
        for (auto& brick : bricks) testCollisionBB(brick, ball, paddle, window);
        bricks.erase(remove_if(begin(bricks), end(bricks),
           [](const Brick& mBrick)
           {
                return mBrick.destroyed;
           }),
            end(bricks));

        window.draw(ball.shape);
        window.draw(paddle.shape);

        for (auto& brick : bricks) window.draw(brick.shape);
        for (int i = 0; i < bonuses.size(); i++) {
            window.draw(bonuses.at(i)->shape);
            bonuses.at(i)->update();
            if (IsTaken(bonuses.at(i) , &paddle, gameClock.getElapsedTime()) == true) {
                bonuses.at(i)->shape.setFillColor({ 0, 0, 0, 0 });
                activeBonuses.push_back(bonuses.at(i));
                bonuses.erase(bonuses.begin() + i);
                continue;
            }
            if (IsTaken(bonuses.at(i), &paddle, gameClock.getElapsedTime()) == false && bonuses.at(i)->y() >= windowHeight) {
                bonuses.erase(bonuses.begin() + i);
            }
        }
        if (ball.bottom() >= windowHeight) {
            for (int i = 0; i < activeBonuses.size(); i++) {
                if (activeBonuses.at(i)->GetType() == "safeBottomBonus") {
                    score += 1;
                    
                }
            }
        }
        for (int i = 0; i < activeBonuses.size(); i++) {
            activeBonuses.at(i)->BonusCheck(&paddle, &ball, &window, gameClock.getElapsedTime());
            if (activeBonuses.at(i)->IsActive() == false) {
                activeBonuses.erase(activeBonuses.begin() + i);
            }
        }
        window.display();
    }

    return 0;
}