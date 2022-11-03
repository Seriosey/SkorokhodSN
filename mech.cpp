#pragma once
#include "mech.hpp"


vector <Bonus*> bonuses;

int score{ 0 };

void testCollisionPB(Paddle& mPaddle, Ball& mBall)
{
    if (!isIntersecting(mPaddle, mBall)) return;

    mBall.velocity.y = -ballVelocity;
    if (mBall.x() < mPaddle.x())
        mBall.velocity.x = -ballVelocity;
    else
        mBall.velocity.x = ballVelocity;
}

void testCollisionBB(Brick& mBrick, Ball& mBall, Paddle& mPaddle, RenderWindow& window)
{
    if (!isIntersecting(mBrick, mBall)) return;
    mBrick.hardness -= 1;
   if (mBrick.hardness == 0) 
    mBrick.destroy();
    score += 1;
    float mx = mBrick.x();
    float my = mBrick.y();

    switch (mBrick.bonus) {
    case 's': {
        ballVelocity *= 1.02;
        break;}
    case 'l': {
        Bonus* tmpBonus = CreateBonuses(mx, my, &mPaddle, &mBall, &window);
        bonuses.push_back(tmpBonus);

        break;}
    case 'u':
        mBrick.destroyed = false;
        break;
    }

    float overlapLeft{ mBall.right() - mBrick.left() };
    float overlapRight{ mBrick.right() - mBall.left() };
    float overlapTop{ mBall.bottom() - mBrick.top() };
    float overlapBottom{ mBrick.bottom() - mBall.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if (abs(minOverlapX) < abs(minOverlapY))
        mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
    else
        mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}

bool IsTaken(Bonus* bonus, Paddle* paddle, Time gameTime) {
    if (!isIntersecting(*bonus, *paddle)) {
        return false;
    }
    else {
        bonus->GetBonusClock().restart().asSeconds();
        bonus->SetActivity(true);
        return true;
    }
}
//if (isIntersecting(*bonus, *paddle))
