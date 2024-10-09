#pragma once
#include <Windows.h>
#include "DataLoader.h"
#include "Transformation.h"

extern Camera camera;
extern Light light;
extern int WindowWidth, WindowHeight;
extern int VNUM, SNUM;
extern vertex_position VertexBuffer[50000];    // ���㻺��
extern screen_position VertexBuffer_t[50000];  // ���㻺��
extern Indexbuffer IndexBuffer[50000];         // ��������

// ��Ϣ������
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// VB -> VB_t
void Calculate_Transformation(bool);

// Debug���
void OutputDebugPrintf(const char* strOutputString, ...);
