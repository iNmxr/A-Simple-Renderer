#include "Camera.h"

Camera::Camera() {
	p = { 150,250,170 };
	n = { 0.6,0.529,0.6 };
	u = { 0.70710678,0,-0.70710678 };
	v = { -0.374,0.8486,-0.374 };
	ob = { -100,100,-100,100,-500,-20 };
	pb = { -20,-500,3.14159 / 4,1 };
}
/*
Camera::Camera() {
	p = { 150,0,170 };
	n = { 0.70710678,0,0.70710678 };
	u = { 0.70710678,0,-0.70710678 };
	v = { 0,1,0 };
	ob = { -100,100,-100,100,-500,-20 };
	pb = { -20,-500,3.14159 / 3,1 };
}
*/
/*
Camera::Camera() {
	p = { 0,0,300 };
	n = { 0,0,1 };
	u = { 1,0,0 };
	v = { 0,1,0 };
	ob = { -100,100,-100,100,-500,-20 };
	pb = { -20,-500,3.14159 / 6,1 };
}
*/
void Camera::LookDown() {
#define fai 3.1415926/12
	// 实现起来太费劲，用到：罗德里格向量旋转公式
}

Light::Light() {
	n = { -0.3, -0.5, -0.8124 };
}