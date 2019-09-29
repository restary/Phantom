#include "Value.hpp"

using namespace std;

namespace PhantomEngine
{
    void DataTypes::Data::operator=(std::string s)
    {
        if (s.length() < ShortString::MAX_SIZE) {
            shortString.type = SHORT_STRING;
            memcpy(shortString.content, s.c_str(), s.length());
        }
        else {
            string.type = STRING;
            // TODO memory management
            //string.data.pointer = s.c_str();
        }
    }

    template<>
    Field<int>::Field(string fieldName)
    {
        name = fieldName;
        value = 0;
    }
}