/**
 * Fluxus v1 | Free
 * Black-themed UI – edit this file on GitHub to update the app.
 */

#include <windows.h>

// Function to set black background for controls
HBRUSH hBrushBlack = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));

            // Title label (centered)
            CreateWindowA("STATIC", "Fluxus v1 | Free",
                          WS_VISIBLE | WS_CHILD | SS_CENTER,
                          0, 30, 400, 40,
                          hwnd, NULL, GetModuleHandleA(NULL), NULL);

            // A simple button
            CreateWindowA("BUTTON", "Click Me",
                          WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                          150, 150, 100, 40,
                          hwnd, (HMENU)1, GetModuleHandleA(NULL), NULL);
            break;
        }
        case WM_CTLCOLORSTATIC: {
            // White text on black background
            SetTextColor((HDC)wParam, RGB(255, 255, 255));
            SetBkColor((HDC)wParam, RGB(0, 0, 0));
            return (LRESULT)hBrushBlack;
        }
        case WM_CTLCOLORBTN: {
            // Buttons also black background
            SetBkColor((HDC)wParam, RGB(0, 0, 0));
            return (LRESULT)hBrushBlack;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == 1) {
                MessageBoxA(hwnd, "Hello from GitHub-updated UI!", "Fluxus", MB_OK);
            }
            break;
        }
        case WM_ERASEBKGND: {
            // Fill entire background black
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect((HDC)wParam, &rc, hBrushBlack);
            return 1;
        }
        case WM_DESTROY: {
            if (hBrushBlack) DeleteObject(hBrushBlack);
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register window class
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "FluxusMainWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL; // We handle background ourselves
    RegisterClassA(&wc);

    // Create window
    HWND hwnd = CreateWindowExA(
        0, "FluxusMainWindow", "Fluxus v1 | Free",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 1;

    // Center the window
    RECT rc;
    GetClientRect(hwnd, &rc);
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    SetWindowPos(hwnd, NULL, (screenWidth - width) / 2, (screenHeight - height) / 2, 0, 0, SWP_NOSIZE);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
