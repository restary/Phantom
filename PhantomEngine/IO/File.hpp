//
// Created by Joker on 8/14/2018.
//

#pragma once


namespace PhantomEngine::IO
{
    // File operations
    class File
    {
    public:
        static char* ReadAllText(const char* path);
    };
}
