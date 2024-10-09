#pragma once;
#include "Mathlib.h"

typedef struct OrthBox {
	float l, r, b, t, f, n;
};

typedef struct PspcBox {
	float Znear, Zfar, Viewtheta, Aspect; // Aspect: 纵横比W/H
};

class Camera {
public:
	vertex_position p;	// 空间坐标系XYZ中，相机的三维坐标
	vec3d u, v, n;		// 空间坐标系XYZ中，相机的方向向量
	OrthBox ob;			// 相机坐标系uvn中，正投影观察体
	PspcBox pb;			// 相机坐标系uvn中，透视投影观察体

	Camera();
	void LookDown();
};

class Light {
public:
	vec3d n;

	Light();
};