#pragma once

#include <string>

using namespace std;


namespace PhantomEngine
{
    class Type;
    class SerializableObject;

    typedef SerializableObject* (*CreateInstanceFunc)(void);

/*
* Use this inside class declaration
* to declear static Type and CreateInstance function
*/
#define RTTI_DECLARE(className)                     \
protected:		                                    \
static Type* s_Type;                                \
public:                                             \
virtual Type* GetType() const { return s_Type; }    \
static SerializableObject* CreateObject();


/*
* Implement type and CreateInstance function
* NOTE : className should contain namespace
*/
#define RTTI_IMPLEMENT(className)                   \
SerializableObject* className::CreateObject()       \
{ return new className; }                           \
Type* className::s_Type = new Type((#className),    \
(CreateInstanceFunc)className::CreateObject);


    class SerializableObject
    {
        RTTI_DECLARE(PhantomEngine::SerializableObject)
    };
}

