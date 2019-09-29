//
// Created by Joker on 8/14/2018.
//

#pragma once


namespace PhantomEngine::Math
{
    struct Vector4
    {
        float x, y, z, w;

        Vector4(float x, float y, float z, float w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
    };
}
