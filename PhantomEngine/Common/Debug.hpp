//
// Created by Joker on 8/17/2018.
//

#pragma once


namespace PhantomEngine
{
    class Debug
    {
    public:
        static void Log(const char* msg);
        static void Warn(const char* msg);
        static void Error(const char* msg);
    };
}


