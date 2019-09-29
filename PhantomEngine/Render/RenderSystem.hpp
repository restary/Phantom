//
// Created by Joker on 8/28/2018.
//

#pragma once

#include "GraphicsInterface/GraphicsInterface.hpp"


namespace PhantomEngine::Render
{
    class RenderSystem
    {
    public:
        void Initialize(const RenderSettings* settings);
        void Render();

    private:
        RenderSettings m_Settings;
    };
}