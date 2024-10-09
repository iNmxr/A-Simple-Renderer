#pragma once;
#include "Mathlib.h"

typedef struct OrthBox {
	float l, r, b, t, f, n;
};

typedef struct PspcBox {
	float Znear, Zfar, Viewtheta, Aspect; // Aspect: �ݺ��W/H
};

class Camera {
public:
	vertex_position p;	// �ռ�����ϵXYZ�У��������ά����
	vec3d u, v, n;		// �ռ�����ϵXYZ�У�����ķ�������
	OrthBox ob;			// �������ϵuvn�У���ͶӰ�۲���
	PspcBox pb;			// �������ϵuvn�У�͸��ͶӰ�۲���

	Camera();
	void LookDown();
};

class Light {
public:
	vec3d n;

	Light();
};