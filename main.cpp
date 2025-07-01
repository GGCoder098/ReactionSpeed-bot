#include <windows.h>
#include <iostream>
#include <thread>
using namespace std;
// Low-level mouse procedure
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_LBUTTONDOWN) {
        // Get the cursor position
        POINT p;
        GetCursorPos(&p);

        // Get the device context for the screen
        HDC hdcScreen = GetDC(NULL);

        // Get the pixel color at the cursor position
        COLORREF color = GetPixel(hdcScreen, p.x, p.y);

        // Release device context
        ReleaseDC(NULL, hdcScreen);

        // Extract RGB values
        int red = GetRValue(color);
        int green = GetGValue(color);
        int blue = GetBValue(color);

        // Print info
        std::cout << "Clicked at (" << p.x << ", " << p.y << "): ";
        std::cout << "R=" << red << ", G=" << green << ", B=" << blue << std::endl;
    }

    // Call the next hook in the chain
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int getPixel() {
    // Set the low-level mouse hook
    HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);

    if (!mouseHook) {
        std::cerr << "Failed to install mouse hook!" << std::endl;
        return 1;
    }

    std::cout << "Click anywhere on the screen to get pixel color. Press Ctrl+C to exit.\n";

    // Message loop to keep the hook running
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Unhook when done (never reached here unless message loop ends)
    UnhookWindowsHookEx(mouseHook);

    return 0;
}


void click() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    // Sleep(30);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}




int main() {
    // Coordinates of the pixel (for example, 100, 200)
    // while (true) {
    //     getPixel();
    // }
    int x = 1101;
    int y = 392;

    int r = 75;
    int g = 219;
    int b = 106;
    // Get the device context of the entire screen
    HDC hdcScreen = GetDC(NULL);

    // Get the color of the pixel at (x, y)
    // COLORREF color = GetPixel(hdcScreen, x, y);

    // Release the device context
    // ReleaseDC(NULL, hdcScreen);

    // Extract RGB values
    // int red = GetRValue(color);
    // int green = GetGValue(color);
    // int blue = GetBValue(color);

    while (true) {
        if (GetAsyncKeyState('X') & 0x8000) {
            break;
        }
        // cout << "Waiting for X key to be pressed" << endl;
    }
    // click();
    while (true) {
        COLORREF color = GetPixel(hdcScreen, x, y);
        if (GetRValue(color) ==r && GetGValue(color) == g && GetBValue(color) == b) {
            // click();
            // cout << "Clicked" << endl;
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(100);
        }
        // Check for 'C' key to stop
        // if (GetAsyncKeyState('C') & 0x8000) {
        //     // cout << "stopped" << endl;
        //     break;
        // }
    }
    ReleaseDC(NULL, hdcScreen);
    return 0;
}
