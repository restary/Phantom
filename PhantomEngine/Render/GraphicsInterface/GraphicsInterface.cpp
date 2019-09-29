//
// Created by Joker on 8/20/2018.
//

#include "GraphicsInterface.hpp"


namespace PhantomEngine::Render
{
    void GraphicsInterface::Initialize(const RenderSettings *settings)
    {
        m_Settings = *settings;
    }
}