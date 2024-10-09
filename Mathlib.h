#pragma once
#include <math.h>

// ��ά�ռ��/����
typedef struct vertex_position {
	float x, y, z;
} vec3d;

float dot_product(vec3d&, vec3d&);

// ��ά�ռ�ƽ��
struct Plane {
    float A, B, C, D;
};

Plane ComputePlane(vertex_position&, vertex_position&, vertex_position&);
vec3d Cal_n(vec3d);

// ��Ļ����ϵ
typedef struct screen_position {
    int x, y;
    float z;
};

bool InTriangle(int x, int y, screen_position& p1, screen_position& p2, screen_position& p3);
float DepthInterpolation(screen_position&, screen_position&, screen_position&, float, float);

// ��������ṹ
typedef struct Indexbuffer {
    int a, b, c;
};

int MIN(int a, int b, int c);
int MAX(int a, int b, int c);
