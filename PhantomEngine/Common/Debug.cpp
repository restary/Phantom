//
// Created by Joker on 8/17/2018.
//

#include "Debug.hpp"

#include <iostream>

using namespace std;


namespace PhantomEngine
{
    void Debug::Log(const char* msg)
    {
        cout << "[TRACE] : " << msg << endl;
    }


    void Debug::Warn(const char* msg)
    {
        cout << "[WARN] : " << msg << endl;
    }


    void Debug::Error(const char* msg)
    {

        cout << "[ERROR] : " << msg << endl;
    }
}