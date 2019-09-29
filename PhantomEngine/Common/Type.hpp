#pragma once

#include <map>
#include <string>
#include "SerializableObject.hpp"

using namespace std;


namespace PhantomEngine
{
    class Type
    {
    public:
        Type(string name, CreateInstanceFunc createFunc);

        const string GetName() const { return m_ClassName; }

        static SerializableObject* CreateInstance(string className);
    private:
        string                    m_ClassName;
        CreateInstanceFunc        m_CreateInstanceFunc;

        static map<string, Type*> s_TypeMap;
    };
}