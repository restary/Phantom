#pragma once

#include "Define.hpp"
#include "SerializableObject.hpp"
#include "Type.hpp"


namespace PhantomEngine
{
    class Component implements SerializableObject
    {
        RTTI_DECLARE(PhantomEngine::Component)
    };
}