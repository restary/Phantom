#pragma once

#include <memory.h>

// Macros for easy reading
#define implements : public


template<typename T>
inline void ZeroInstance(T* instance)
{
    memset(instance, 0, sizeof(T));
}

template<class T>
inline void SafeRelease(T **ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != nullptr) {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = nullptr;
    }
}
