#include <Windows.h>
#include "WindowProcess.h"

// 窗口尺寸
int WindowWidth = 640;
int WindowHeight = 480;

// 摄像机、光源
Camera camera;
Light light;

int VNUM, SNUM; // 顶点数量、三角面数量
vertex_position VertexBuffer[50000];    // 顶点缓存(raw)
screen_position VertexBuffer_t[50000];  // 顶点缓存(after transformation)
Indexbuffer IndexBuffer[50000];         // 索引缓存

// WinMain主函数
int WINAPI WinMain(
    HINSTANCE hinstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    // 注册窗口
    WNDCLASSEX wd{};
    wd.cbSize = sizeof(WNDCLASSEX);
    wd.lpfnWndProc = MainWndProc;
    wd.hInstance = hinstance;
    wd.lpszClassName = L"Z_Buffer";

    RegisterClassEx(&wd);

    // 创建窗口
    HWND hwd;
    hwd = CreateWindowEx(
        NULL,                       // 扩展窗口样式，默认为0
        wd.lpszClassName,           // 窗口类的名字，必须是已经register过的类名
        L"z_buffer",                // 窗口栏实际显示的标题
        WS_OVERLAPPEDWINDOW,        // 窗口样式，最小化最大化关闭等
        CW_USEDEFAULT,              // 初始位置的 x 坐标
        CW_USEDEFAULT,              // 初始位置的 y 坐标
        WindowWidth,                // 宽度
        WindowHeight,               // 高度
        NULL,                       // 父窗口句柄，默认为0
        NULL,                       // 无需添加菜单，默认为0
        hinstance,                  // 应用程序实例句柄
        NULL                        // 额外参数，默认为0
    );

    // 显示窗口
    ShowWindow(hwd, nCmdShow); // SW_NORMAL

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
