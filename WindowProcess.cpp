#include "WindowProcess.h"

// 窗口回调函数（用来接收并处理发送给特定窗口的消息的函数）
LRESULT CALLBACK MainWndProc(
    HWND hwnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{
    switch (uMsg)
    {
    case WM_CREATE:
        // Initialize the window. 
        Loader();
        OutputDebugPrintf("VNUM=%d, SNUM=%d\n", VNUM, SNUM);

        return 0;

    case WM_PAINT:
        // Paint the window's client area. 
    {
        // 初始化
        Calculate_Transformation(1);

        // Begin painting
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Set the background color to black
        RECT rc;
        GetClientRect(hwnd, &rc);
        FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));

        // 遍历每个像素
        int r = 0.5 * 0.8 * (WindowWidth < WindowHeight ? WindowWidth : WindowHeight);
        int DrawLeftBound = WindowWidth / 2 - r;
        int DrawRightBound = DrawLeftBound + 2 * r;
        int DrawUpBound = WindowHeight / 2 + r;
        int DrawBottomBound = DrawUpBound - 2 * r;

        for (int n = DrawUpBound; n >= DrawBottomBound; n--) {
            for (int m = DrawLeftBound; m <= DrawRightBound; m++) {
                // 与各个三角形求交
                int MinID = -1;
                float MinT = 2;
                for (int i = 0; i < SNUM; i++) {
                    screen_position triA = VertexBuffer_t[IndexBuffer[i].a];
                    screen_position triB = VertexBuffer_t[IndexBuffer[i].b];
                    screen_position triC = VertexBuffer_t[IndexBuffer[i].c];
                    // 检查是否在三角面内
                    if (!InTriangle(m, n, triA, triB, triC)) continue;
                    float ti = DepthInterpolation(triA, triB, triC, m, n);
                    if (ti < 0 || ti > 1) continue;
                    if (ti < MinT)
                        MinID = i, MinT = ti;
                }
                if (MinID != -1) {
                    // 着色
                    Plane P = ComputePlane(
                        VertexBuffer[IndexBuffer[MinID].a],
                        VertexBuffer[IndexBuffer[MinID].b],
                        VertexBuffer[IndexBuffer[MinID].c]);
                    vec3d N = Cal_n({ P.A, P.B, P.C });
                    float lamda = abs(dot_product(N, light.n));
                    int Color = (int)floor(255 * lamda);
                    // int Color = 100;
                    SetPixel(hdc, m, WindowHeight - n, RGB(Color, Color, Color));
                }
            }
        }

        // End painting
        EndPaint(hwnd, &ps);

        return 0;
    }

    case WM_SIZE:
        // Set the size and position of the window. 
    {
        WindowWidth = LOWORD(lParam);
        WindowHeight = HIWORD(lParam);
        OutputDebugPrintf("W:%d H:%d\n", WindowWidth, WindowHeight);
        InvalidateRect(hwnd, NULL, TRUE); // Redraw the window

        return 0;
    }

    case WM_KEYDOWN:
        // Handle key presses to move the triangle
    {
        switch (wParam)
        {
        case VK_UP:
            camera.p.y += 5;
            break;
        case VK_DOWN:
            camera.p.y -= 5;
            break;
        case VK_LEFT:
            camera.p.x -= 5;
            break;
        case VK_RIGHT:
            camera.p.x += 5;
            break;
        }
        InvalidateRect(hwnd, NULL, TRUE); // Redraw the window

        return 0;
    }

    case WM_DESTROY:
        // Clean up window-specific data objects.
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void Calculate_Transformation(bool _b) {
    // 对每个空间点进行坐标变换，转换到屏幕坐标系
    for (int i = 0; i < VNUM; i++) {
        vertex_position vp = Transformation(VertexBuffer[i], camera, WindowWidth, WindowHeight, _b);
        VertexBuffer_t[i] = { (int)floor(vp.x),(int)floor(vp.y),vp.z };
    }
}

void OutputDebugPrintf(const char* strOutputString, ...)
{
#define PUT_PUT_DEBUG_BUF_LEN   1024
    char strBuffer[PUT_PUT_DEBUG_BUF_LEN] = { 0 };
    va_list vlArgs;
    va_start(vlArgs, strOutputString);
    _vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);  //_vsnprintf_s  _vsnprintf
    //vsprintf(strBuffer,strOutputString,vlArgs);
    va_end(vlArgs);
    OutputDebugStringA(strBuffer);  //OutputDebugString
}