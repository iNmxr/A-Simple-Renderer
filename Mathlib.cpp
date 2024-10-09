#include "Mathlib.h"

int MIN(int a, int b, int c) {
    int minab = a <= b ? a : b;
    return minab <= c ? minab : c;
}

int MAX(int a, int b, int c) {
    int maxab = a >= b ? a : b;
    return maxab >= c ? maxab : c;
}

float dot_product(vec3d& v1, vec3d& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3d Cal_n(vec3d v) {
    float s = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return{ v.x / s, v.y / s, v.z / s };
}

Plane ComputePlane(vertex_position& p1, vertex_position& p2, vertex_position& p3) {
    float A = (p2.y - p1.y) * (p3.z - p1.z) - (p3.y - p1.y) * (p2.z - p1.z);
    float B = (p2.z - p1.z) * (p3.x - p1.x) - (p3.z - p1.z) * (p2.x - p1.x);
    float C = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    float D = -A * p1.x - B * p1.y - C * p1.z;
    return { A, B, C, D };
}

bool InTriangle(int x, int y, screen_position& p1, screen_position& p2, screen_position& p3) {
    // 计算叉积
    int c1 = (p1.x - x) * (p2.y - y) - (p1.y - y) * (p2.x - x);
    int c2 = (p2.x - x) * (p3.y - y) - (p2.y - y) * (p3.x - x);
    int c3 = (p3.x - x) * (p1.y - y) - (p3.y - y) * (p1.x - x);
    // 检查符号
    if (c1 < 0 && c2 < 0 && c3 < 0 || c1>0 && c2>0 && c3>0)
        return 1;
    else
        return 0;
}

float DepthInterpolation(screen_position& p1, screen_position& p2, screen_position& p3, float x, float y) {
    // 求平面方程
    float A = (p2.y - p1.y) * (p3.z - p1.z) - (p3.y - p1.y) * (p2.z - p1.z);
    float B = (p2.z - p1.z) * (p3.x - p1.x) - (p3.z - p1.z) * (p2.x - p1.x);
    float C = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    float D = -A * p1.x - B * p1.y - C * p1.z;
    // 求深度值
    return -(A * x + B * y + D) / C;
}
