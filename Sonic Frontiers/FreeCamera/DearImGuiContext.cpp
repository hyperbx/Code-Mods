#pragma region Context Initialisation

bool m_Initialised = false;

static ID3D11Device* m_pDevice;
static ID3D11DeviceContext* m_pDeviceContext;
static ID3D11RenderTargetView* m_pRenderTargetView;
static ID3D11Texture2D* m_pBackBuffer;

void CreateBackBuffer(IDXGISwapChain* in_pThis)
{
    // TODO: fix scaling.
    in_pThis->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
    m_pDevice->CreateRenderTargetView(m_pBackBuffer, nullptr, &m_pRenderTargetView);
    m_pBackBuffer->Release();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HOOK(LRESULT, __fastcall, WndProcHook, m_SigWndProcHook(), HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, Msg, wParam, lParam))
        return true;

    return originalWndProcHook(hWnd, Msg, wParam, lParam);
}

VTABLE_HOOK(HRESULT, WINAPI, IDXGISwapChain, Present, UINT SyncInterval, UINT Flags)
{
    if (!m_Initialised)
    {
        This->GetDevice(__uuidof(ID3D11Device), (void**)&m_pDevice);
        {
            m_pDevice->GetImmediateContext(&m_pDeviceContext);
        }

        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        {
            This->GetDesc(&swapChainDesc);
        }

        HWND windowHandle = swapChainDesc.OutputWindow;

        IMGUI_CHECKVERSION();

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        {
            io.Fonts->AddFontDefault();

            io.ImeWindowHandle = windowHandle;
        }

        ImGui::StyleColorsDark();

        CreateBackBuffer(This);

        ImGui_ImplDX11_Init(m_pDevice, m_pDeviceContext);
        ImGui_ImplWin32_Init(windowHandle);

        m_Initialised = true;
    }

    DearImGuiContext::Update();

    m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

    if (DearImGuiContext::IsVisible)
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return originalIDXGISwapChainPresent(This, SyncInterval, Flags);
}

VTABLE_HOOK(HRESULT, WINAPI, IDXGISwapChain, ResizeBuffers, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    CreateBackBuffer(This);

    return originalIDXGISwapChainResizeBuffers(This, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HOOK(void*, __fastcall, SwapChainHook, m_SigSwapChainHook(), void* in_pThis, IDXGISwapChain* in_pSwapChain)
{
    INSTALL_VTABLE_HOOK(IDXGISwapChain, in_pSwapChain, Present, 8);
    INSTALL_VTABLE_HOOK(IDXGISwapChain, in_pSwapChain, ResizeBuffers, 13);

    return originalSwapChainHook(in_pThis, in_pSwapChain);
}

HOOK(int64_t, __fastcall, MouseHookUpdate, 0x140E2B6C0, int64_t a1, float a2)
{
    if (GetAsyncKeyState(VK_TAB) & 1)
        ShowCursor(DearImGuiContext::IsMouseCursorVisible = !DearImGuiContext::IsMouseCursorVisible);

    return DearImGuiContext::IsMouseCursorVisible ? *(uint32_t*)(a1 + 136) : originalMouseHookUpdate(a1, a2);
}

#pragma endregion

void DearImGuiContext::Update()
{
    // TODO: fix this for unfocusing window.
    if (GetAsyncKeyState(VK_ESCAPE) & 1)
        DearImGuiContext::IsVisible = !DearImGuiContext::IsVisible;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();
    {
        // NOTICE: update stuff here.
        Camera::UpdateImGui();
    }
    ImGui::EndFrame();

    ImGui::Render();
}

void DearImGuiContext::Install()
{
    INSTALL_HOOK(WndProcHook);
    INSTALL_HOOK(SwapChainHook);
    INSTALL_HOOK(MouseHookUpdate);
}