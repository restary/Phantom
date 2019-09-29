//
// Created by Joker on 8/28/2018.
//

#pragma once


namespace PhantomEngine::Math
{
    struct Vector2
    {
        float x, y;

        Vector2() : x(0.0f), y(0.0f) {}

        Vector2(float x, float y)
        {
            this->x = x;
            this->y = y;
        }
    };
}

