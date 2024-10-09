#include <Windows.h>
#include "WindowProcess.h"

// ���ڳߴ�
int WindowWidth = 1640;
int WindowHeight = 1480;

// ���������Դ
Camera camera;
Light light;

int VNUM, SNUM; // ��������������������
vertex_position VertexBuffer[50000];    // ���㻺��(raw)
screen_position VertexBuffer_t[50000];  // ���㻺��(after transformation)
Indexbuffer IndexBuffer[50000];         // ��������

// WinMain������
int WINAPI WinMain(
    HINSTANCE hinstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    // ע�ᴰ��
    WNDCLASSEX wd{};
    wd.cbSize = sizeof(WNDCLASSEX);
    wd.lpfnWndProc = MainWndProc;
    wd.hInstance = hinstance;
    wd.lpszClassName = L"Z_Buffer";

    RegisterClassEx(&wd);

    // ��������
    HWND hwd;
    hwd = CreateWindowEx(
        NULL,                       // ��չ������ʽ��Ĭ��Ϊ0
        wd.lpszClassName,           // ����������֣��������Ѿ�register��������
        L"z_buffer",                // ������ʵ����ʾ�ı���
        WS_OVERLAPPEDWINDOW,        // ������ʽ����С����󻯹رյ�
        CW_USEDEFAULT,              // ��ʼλ�õ� x ����
        CW_USEDEFAULT,              // ��ʼλ�õ� y ����
        WindowWidth,                // ���
        WindowHeight,               // �߶�
        NULL,                       // �����ھ����Ĭ��Ϊ0
        NULL,                       // ������Ӳ˵���Ĭ��Ϊ0
        hinstance,                  // Ӧ�ó���ʵ�����
        NULL                        // ���������Ĭ��Ϊ0
    );

    // ��ʾ����
    ShowWindow(hwd, nCmdShow); // SW_NORMAL

    // ��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
