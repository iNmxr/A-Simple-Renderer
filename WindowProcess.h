#pragma once
#include <Windows.h>
#include "DataLoader.h"
#include "Transformation.h"

extern Camera camera;
extern Light light;
extern int WindowWidth, WindowHeight;
extern int VNUM, SNUM;
extern vertex_position VertexBuffer[50000];    // 顶点缓存
extern screen_position VertexBuffer_t[50000];  // 顶点缓存
extern Indexbuffer IndexBuffer[50000];         // 索引缓存

// 消息处理函数
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// VB -> VB_t
void Calculate_Transformation(bool);

// Debug输出
void OutputDebugPrintf(const char* strOutputString, ...);
