//
// Created by Joker on 8/20/2018.
//

#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <Common/Define.hpp>
#include <Math.hpp>
#include "../GraphicsInterface.hpp"

using namespace PhantomEngine::Math;


namespace PhantomEngine::Render
{
    class DirectX11 implements GraphicsInterface
    {
    public:
        void CreateRenderTarget();
        void SetViewPort();
        void InitPipeline();
        void InitGraphics();
        HRESULT CreateGraphicsResources();

        void Initialize(const RenderSettings* settings) override ;
        void Render() override ;
        void Release() override ;
    private:
        ID3D11Device*           m_pD3dDevice        = nullptr;
        ID3D11DeviceContext*    m_pD3dDeviceContext = nullptr;

        ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
        IDXGISwapChain*         m_pSwapChain        = nullptr;


        ID3D11Buffer*           m_pVertexBuffer     = nullptr;
        ID3D11InputLayout*      m_pInputLayout      = nullptr;


        ID3D11VertexShader*     m_pVertexShader     = nullptr;
        ID3D11PixelShader*      m_pPixelShader      = nullptr;
    };
}



