#include <windows.h>
#include <dwmapi.h>
#include <stdio.h>

#pragma comment(lib, "dwmapi.lib")

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Application entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    const wchar_t CLASS_NAME[] = L"Green Title Bar Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        L"Window with Green Title Bar",   // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    HWND hButton = CreateWindow(
        WC_BUTTON,             // Use standard button class
        L"Windows 7 Button",   // Button text
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // Standard button styles
        10, 40, 150, 30,       // Position and size
        hwnd,            // Parent window
        NULL,      // Button ID
        hInstance,             // Application instance
        NULL                   // No additional data
    );

    HWND hComboBox = CreateWindow(
        WC_COMBOBOX,           // Standard ComboBox class
        L"",                   // No text
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, // ComboBox styles
        10, 80, 150, 200,      // Position and size
        hwnd,            // Parent window
        NULL,       // ComboBox ID
        hInstance,             // Application instance
        NULL                   // No additional data
    );

    // For progress bars, sliders, etc.
    HWND hProgress = CreateWindow(
        PROGRESS_CLASS,        // Progress bar class
        L"",                   // No text
        WS_CHILD | WS_VISIBLE, // Standard styles
        10, 120, 150, 20,       // Position and size
        hwnd,            // Parent window
        NULL,    // Control ID
        hInstance,             // Application instance
        NULL                   // No additional data
    );

    if (hwnd == NULL) {
        return 0;
    }

    // Make sure DWM composition is enabled (should be by default on modern Windows)
    BOOL enabled = FALSE;
    DwmIsCompositionEnabled(&enabled);
    if (!enabled) {
        MessageBox(NULL, L"DWM composition is not enabled!", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Configure the title bar to be Green
    COLORREF titleBarColor = RGB(20, 100, 0); // Green

    // Set the title bar color
    DwmSetWindowAttribute(
        hwnd,
        DWMWA_CAPTION_COLOR,
        &titleBarColor,
        sizeof(titleBarColor)
    );

    // Make the window visible
    ShowWindow(hwnd, nCmdShow);

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

		HBRUSH hBrush = CreateSolidBrush(RGB(20, 100, 0));

        FillRect(hdc, &ps.rcPaint, hBrush);

        // Draw some text in the client area
        SetTextColor(hdc, RGB(255, 255, 255));
        SetBkMode(hdc, TRANSPARENT);
        TextOut(hdc, 20, 20, L"Window with a green title bar using DWM!", 40);

        EndPaint(hwnd, &ps);
        return 0;
    }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}