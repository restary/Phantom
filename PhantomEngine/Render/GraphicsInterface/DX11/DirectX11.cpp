//
// Created by Joker on 8/20/2018.
//

#include "DirectX11.hpp"
#include "Debug.hpp"


struct VERTEX {
    Vector3 Position;
    Vector4 Color;
};


namespace PhantomEngine::Render
{
    GraphicsInterface* g_pGraphicsInterface = new DirectX11();

    void DirectX11::Initialize(const RenderSettings *settings)
    {
        GraphicsInterface::Initialize(settings);

        Debug::Log("Initialize DX 11...");
        CreateGraphicsResources();
        Debug::Log("Initialize complete");
    }

    void DirectX11::CreateRenderTarget()
    {
        HRESULT hr;
        ID3D11Texture2D *pBackBuffer;

        // Get back buffer
        hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
        if (!SUCCEEDED(hr)) {
            return;
        }

        // Create render target view pointing at back buffer to display
        hr = m_pD3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
        if (!SUCCEEDED(hr)) {
            return;
        }
        pBackBuffer->Release();

        // Bind view
        m_pD3dDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
    }

    void DirectX11::SetViewPort()
    {
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width = m_Settings.windowSize.x;
        viewport.Height = m_Settings.windowSize.y;

        m_pD3dDeviceContext->RSSetViewports(1, &viewport);
    }

    void DirectX11::InitPipeline()
    {
        ID3DBlob *vs, *ps;

        // Load and compile shader files
        D3DReadFileToBlob(L"simple.vso", &vs);
        D3DReadFileToBlob(L"simple.pso", &ps);

        // Create shader instance
        m_pD3dDevice->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &m_pVertexShader);
        m_pD3dDevice->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, &m_pPixelShader);

        // Set shader
        m_pD3dDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
        m_pD3dDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

        // Create shader input data layout
        D3D11_INPUT_ELEMENT_DESC ied[] =
                {
                        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
                };
        m_pD3dDevice->CreateInputLayout(ied, 2, vs->GetBufferPointer(), vs->GetBufferSize(), &m_pInputLayout);
        m_pD3dDeviceContext->IASetInputLayout(m_pInputLayout);

        vs->Release();
        ps->Release();
    }

    void DirectX11::InitGraphics()
    {
        // Triangle data(Position and color)
        VERTEX triangle[] = {
                // Position                   Color
                { Vector3( 0.0f, 0.5f, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f) },
                { Vector3( 0.5f,-0.5f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f) },
                { Vector3(-0.5f,-0.5f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f) },
        };

        // Create vertex buffer
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));

        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.ByteWidth = sizeof(VERTEX) * 3;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        m_pD3dDevice->CreateBuffer(&bd, nullptr, &m_pVertexBuffer);

        // copy the vertices into the buffer
        D3D11_MAPPED_SUBRESOURCE ms;
        m_pD3dDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
        memcpy(ms.pData, triangle, bd.ByteWidth);
        m_pD3dDeviceContext->Unmap(m_pVertexBuffer, 0);
    }


    HRESULT DirectX11::CreateGraphicsResources()
    {
        HRESULT hr = S_OK;

        if (m_pSwapChain != nullptr) return hr;

        // Create swap chain
        DXGI_SWAP_CHAIN_DESC scd;
        ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

        scd.BufferCount = 1;
        scd.BufferDesc.Width = m_Settings.windowSize.x;
        scd.BufferDesc.Height = m_Settings.windowSize.y;
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        scd.BufferDesc.RefreshRate.Numerator = 60;
        scd.BufferDesc.RefreshRate.Denominator = 1;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scd.OutputWindow = m_Settings.hwnd;
        scd.SampleDesc.Count = 4;
        scd.Windowed = TRUE;
        scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        const D3D_FEATURE_LEVEL featureLevels[] = {
                D3D_FEATURE_LEVEL_11_1,
                D3D_FEATURE_LEVEL_11_0,
                D3D_FEATURE_LEVEL_10_1,
                D3D_FEATURE_LEVEL_10_0,
                D3D_FEATURE_LEVEL_9_3,
                D3D_FEATURE_LEVEL_9_2,
                D3D_FEATURE_LEVEL_9_1,
        };
        D3D_FEATURE_LEVEL featureLevelSupported;

        hr = D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                0,
                featureLevels,
                _countof(featureLevels),
                D3D11_SDK_VERSION,
                &scd,
                &m_pSwapChain,
                &m_pD3dDevice,
                &featureLevelSupported,
                &m_pD3dDeviceContext);

        if (hr == SEC_E_OK) {
            CreateRenderTarget();
            SetViewPort();
//            InitPipeline();
//            InitGraphics();
        }

        return hr;
    }


    void DirectX11::Release()
    {
        SafeRelease(&m_pInputLayout);
        SafeRelease(&m_pVertexShader);
        SafeRelease(&m_pPixelShader);
        SafeRelease(&m_pVertexBuffer);
        SafeRelease(&m_pSwapChain);
        SafeRelease(&m_pRenderTargetView);
        SafeRelease(&m_pD3dDevice);
        SafeRelease(&m_pD3dDeviceContext);
    }

    void DirectX11::Render()
    {
        const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
        m_pD3dDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);

        UINT stride = sizeof(VERTEX);
        UINT offset = 0;

        m_pD3dDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

        m_pD3dDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        m_pD3dDeviceContext->Draw(3, 0);


        m_pSwapChain->Present(0, 0);
    }
}