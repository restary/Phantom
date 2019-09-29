
#include "Type.hpp"
#include <string>
#include <map>

using namespace std;


namespace PhantomEngine
{
    map<string, Type*> Type::s_TypeMap;


    Type::Type(string name, CreateInstanceFunc createFunc)
        : m_ClassName(name), m_CreateInstanceFunc(createFunc)
    {
        if (s_TypeMap.find(name) == s_TypeMap.end()) {
            s_TypeMap.insert(map<string, Type*>::value_type(name, this));
        }
    }

    SerializableObject* Type::CreateInstance(string className)
    {
        SerializableObject* obj = nullptr;
        auto iter = s_TypeMap.find(className);
        if (iter != s_TypeMap.end()) {
            obj = iter->second->m_CreateInstanceFunc();
        }

        return obj;
    }
}
