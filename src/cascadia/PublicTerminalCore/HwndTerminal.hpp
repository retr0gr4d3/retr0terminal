#pragma once

#include "../../renderer/base/Renderer.hpp"
#include "../../renderer/dx/DxRenderer.hpp"
#include "../../cascadia/TerminalCore/Terminal.hpp"

extern "C" {
    __declspec(dllexport) HRESULT _stdcall CreateTerminal(HWND parentHwnd, _Out_ void** hwnd, _Out_ void** terminal);
    __declspec(dllexport) void _stdcall SendTerminalOutput(void* terminal, LPCWSTR data);
    __declspec(dllexport) void _stdcall RegisterScrollCallback(void* terminal, void __stdcall callback(int, int, int));
    __declspec(dllexport) HRESULT _stdcall TriggerResize(void* terminal, double width, double height, _Out_ int* charColumns, _Out_ int* charRows);
    __declspec(dllexport) void _stdcall DpiChanged(void* terminal, int newDpi);
    __declspec(dllexport) void _stdcall UserScroll(void* terminal, int viewTop);
    __declspec(dllexport) void _stdcall StartSelection(void* terminal, COORD cursorPosition, bool altPressed);
    __declspec(dllexport) void _stdcall MoveSelection(void* terminal, COORD cursorPosition);
    __declspec(dllexport) void _stdcall ClearSelection(void* terminal);

    enum CursorStyle
    {

    };
    struct TerminalSettings
    {
        COLORREF DefaultBackground;
        COLORREF DefaultForeground;
        CursorStyle CursorShape;
    };
    }

struct HwndTerminal {
public:
    HwndTerminal(HWND hwnd);
    HRESULT Initialize();
    void SendOutput(std::wstring_view data);
    HRESULT Refresh(double width, double height, _Out_ int* charColumns, _Out_ int* charRows);
    void RegisterScrollCallback(std::function<void (int, int, int)> callback);

private:
    HWND _hwnd;
    FontInfoDesired _desiredFont;
    FontInfo _actualFont;

    std::unique_ptr<::Microsoft::Terminal::Core::Terminal> _terminal;

    std::unique_ptr<::Microsoft::Console::Render::Renderer> _renderer;
    std::unique_ptr<::Microsoft::Console::Render::DxEngine> _renderEngine;

    friend HRESULT _stdcall CreateTerminal(HWND parentHwnd, _Out_ void** hwnd, _Out_ void** terminal);
    friend void _stdcall DpiChanged(void* terminal, int newDpi);
    friend void _stdcall UserScroll(void* terminal, int viewTop);
    friend void _stdcall StartSelection(void* terminal, COORD cursorPosition, bool altPressed);
    friend void _stdcall MoveSelection(void* terminal, COORD cursorPosition);
    friend void _stdcall ClearSelection(void* terminal);
    void _UpdateFont(int newDpi);
};
