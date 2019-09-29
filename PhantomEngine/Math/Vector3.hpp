//
// Created by Joker on 8/14/2018.
//

#pragma once



namespace PhantomEngine::Math
{
    struct Vector3
    {
        float x, y, z;

        Vector3(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };
}
