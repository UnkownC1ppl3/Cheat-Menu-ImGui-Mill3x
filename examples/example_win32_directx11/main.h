#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_freetype.h"

#include "custom_widgets.hpp"

#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

#include <d3d11.h>
#include <tchar.h>

#include "font.h"
#include "image.h"

static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;

bool dark = true;

char field[45] = { "" };

int page = 0;

static float tab_alpha = 0.f; /* */ static float tab_add; /* */ static int active_tab = 0;

int key, m;

bool checkbox_on = true;
bool checkbox_off = false;

static int slider_int = 50;
static float slider_float = 0.5f;

static int select1 = 0;
const char* items[3]{ "Selected", "Nope", "what :/ a y?" };

static int bullet_select = 0;
const char* bullet[2]{ "Disabled", "Enabled" };

static int sound_select = 0;
const char* sound[2]{ "Disabled", "Enabled" };

static int style_select = 0;
const char* stylee[2]{ "Flat", "Back" };

static int style2_select = 0;
const char* stylee2[2]{ "Textured", "3D Mode" };

static bool multi_num[5] = { false, true, true, true, false };
const char* multi_items[5] = { "One", "Two", "Three", "Four", "Five" };

float knob = 1.f;

float col[4] = { 118 / 255.f, 187 / 255.f, 117 / 255.f, 0.5f };

namespace font
{
    ImFont* icomoon_logo = nullptr;
    ImFont* icomoon_page = nullptr;
    ImFont* inter_semibold = nullptr;
    ImFont* icon_notify = nullptr;
}

namespace texture
{
    ID3D11ShaderResourceView* preview_slow = nullptr;
}

int rotation_start_index;
void ImRotateStart()
{
    rotation_start_index = ImGui::GetWindowDrawList()->VtxBuffer.Size;
}

ImVec2 ImRotationCenter()
{
    ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX);

    const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
    for (int i = rotation_start_index; i < buf.Size; i++)
        l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

    return ImVec2((l.x + u.x) / 2, (l.y + u.y) / 2);
}

void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter())
{
    float s = sin(rad), c = cos(rad);
    center = ImRotate(center, s, c) - center;

    auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
    for (int i = rotation_start_index; i < buf.Size; i++)
        buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
}