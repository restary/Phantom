//
// Created by Joker on 8/28/2018.
//

#include "RenderSystem.hpp"


namespace PhantomEngine::Render
{
    void RenderSystem::Initialize(const RenderSettings* settings)
    {
        m_Settings = *settings;
        g_pGraphicsInterface->Initialize(settings);
    }

    void RenderSystem::Render()
    {
        g_pGraphicsInterface->Render();
    }
}