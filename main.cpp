#include <windows.h>

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Set black background
            SetBkColor(hdc, RGB(0, 0, 0));
            SetTextColor(hdc, RGB(255, 255, 255));
            
            // Draw white border
            RECT rect;
            GetClientRect(hwnd, &rect);
            FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 255, 255)));
            
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_CTLCOLORSTATIC: {
            // Make all text white with black background
            HDC hdcStatic = (HDC)wParam;
            SetTextColor(hdcStatic, RGB(255, 255, 255));
            SetBkColor(hdcStatic, RGB(0, 0, 0));
            return (LRESULT)GetStockObject(BLACK_BRUSH);
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register window class
    const char CLASS_NAME[] = "FluxusWindow";
    
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClassA(&wc);
    
    // Create window with black background
    HWND hwnd = CreateWindowExA(
        0, CLASS_NAME, "Fluxus v1 | Free",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL, NULL, hInstance, NULL
    );
    
    if (hwnd == NULL) {
        return 0;
    }
    
    // Create some sample text
    CreateWindowA("STATIC", "Welcome to Fluxus v1",
                  WS_VISIBLE | WS_CHILD | SS_CENTER,
                  20, 50, 360, 30,
                  hwnd, NULL, NULL, NULL);
    
    CreateWindowA("STATIC", "Status: Ready",
                  WS_VISIBLE | WS_CHILD | SS_CENTER,
                  20, 100, 360, 20,
                  hwnd, NULL, NULL, NULL);
    
    CreateWindowA("BUTTON", "Click Here",
                  WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                  140, 150, 120, 40,
                  hwnd, (HMENU)1, NULL, NULL);
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}
