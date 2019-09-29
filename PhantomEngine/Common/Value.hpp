#pragma once
#include <iostream>
#include <string>
#include <Define.hpp>

using namespace std;

namespace PhantomEngine
{
    namespace DataTypes
    {
        static const uint8_t    UNDEFINED = 255;
        static const uint8_t      INTEGER = 0;
        static const uint8_t        FLOAT = 1;
        static const uint8_t      VECTOR2 = 2;
        static const uint8_t      VECTOR3 = 3;
        static const uint8_t SHORT_STRING = 4;
        static const uint8_t       STRING = 5;
        static const uint8_t       OBJECT = 6;
        static const uint8_t        ARRAY = 7;

        union DataPointer
        {
            void*    pointer;
            uint32_t offset;
        };

        struct Integer
        {
            int64_t value;
            uint8_t reserved[7];
            uint8_t type;
        };

        struct Float
        {
            float   value;
            uint8_t reserved[11];
            uint8_t type;
        };

        struct Vector2
        {
            float   x;
            float   y;
            uint8_t reserved[7];
            uint8_t type;
        };

        struct Vector3
        {
            float   x;
            float   y;
            float   z;
            uint8_t reserved[3];
            uint8_t type;
        };

        struct ShortString
        {
            const static uint32_t MAX_SIZE = 14;

            char    content[MAX_SIZE];
            uint8_t length;
            uint8_t type;
        };

        struct String
        {
            DataPointer data;
            uint32_t    size;
            uint8_t     reserved[3];
            uint8_t     type;
        };

        struct Object
        {
            DataPointer data;
            uint32_t    size;
            uint8_t     reserved[3];
            uint8_t     type;
        };

        struct Array
        {
            DataPointer data;
            uint32_t    size;
            uint8_t     reserved[3];
            uint8_t     type;
        };

        union Data 
        {
            Integer     integer;
            Float       number;
            Vector2     vector2;
            Vector3     vector3;
            ShortString shortString;
            String      string;
            Object      object;
            Array       array;

            void operator=(int i) { integer.type = INTEGER; integer.value = i; }
            void operator=(float f) { number.type = FLOAT; number.value = f; }
            void operator=(Vector2 v2) { vector2 = v2; }
            void operator=(Vector3 v3) { vector3 = v3; }
            void operator=(std::string s);

            uint8_t GetType() { return integer.type; }
            bool IsReference() { return integer.type > SHORT_STRING; }
        };
    }

    template<typename T>
    struct Value
    {
        uint8_t GetType() { return DataTypes::UNDEFINED; }
    };


    template<>
    struct Value<int>
    {
        Value() { data = 0; }
        uint8_t GetType() { return DataTypes::INTEGER; }
        void operator=(int i) { data = i; }
    private:
        DataTypes::Data data;
    };

    template<>
    struct Value<float>
    {
        Value() { data = 0.0f; }
        uint8_t GetType() { return DataTypes::FLOAT; }
        void operator=(float f) { data = f; }
    private:
        DataTypes::Data data;
    };

    template<>
    struct Value<string>
    {
        Value() { data = ""; }
        uint8_t GetType() { return DataTypes::FLOAT; }
        void operator=(string s) { data = s; }
    private:
        DataTypes::Data data;
    };


    template<typename T>
    struct Field
    {
        Value<string> name;
        Value<T>      value;

        Field(std::string fieldName);
    };
}