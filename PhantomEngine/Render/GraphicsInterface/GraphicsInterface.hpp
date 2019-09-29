//
// Created by Joker on 8/20/2018.
//

#pragma once

#include "../RenderSettings.hpp"

namespace PhantomEngine::Render
{
    class GraphicsInterface
    {
    public:
        virtual void Initialize(const RenderSettings* settings);
        virtual void Render() = 0;
        virtual void Release() = 0;

    protected:
        RenderSettings m_Settings;
    };


    extern GraphicsInterface* g_pGraphicsInterface;
}