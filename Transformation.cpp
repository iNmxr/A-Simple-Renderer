#include "Transformation.h"

// 空间右手系X-Y-Z => 相机右手系u-v-n (见书P242)
vertex_position Camera_Transformation(vertex_position& vp, Camera& ca) {
	float u = dot_product(vp, ca.u) - dot_product(ca.p, ca.u);
	float v = dot_product(vp, ca.v) - dot_product(ca.p, ca.v);
	float n = dot_product(vp, ca.n) - dot_product(ca.p, ca.n);
	return { u, v, n };
}

// 相机右手系u-v-n => 规范左手系x_n-y_n-z_n (见书P246)
vertex_position Projection_Transformation_Orthogonal(vertex_position& vp, Camera& ca) {
	float x_n = vp.x * 2 / (ca.ob.r - ca.ob.l) - (ca.ob.r + ca.ob.l) / (ca.ob.r - ca.ob.l);
	float y_n = vp.y * 2 / (ca.ob.t - ca.ob.b) - (ca.ob.t + ca.ob.b) / (ca.ob.t - ca.ob.b);
	float z_n = vp.z * 2 / (ca.ob.f - ca.ob.n) - (ca.ob.f + ca.ob.n) / (ca.ob.f - ca.ob.n);
	return { x_n, y_n, z_n };
}

// 相机右手系u-v-n => 规范左手系x_n-y_n-z_n (见书P261)
vertex_position Projection_Transformation_Perspective(vertex_position& vp, Camera& ca) {
#define b ca.pb
	float x_n = -vp.x / tan(b.Viewtheta / 2.0) / b.Aspect;
	float y_n = -vp.y / tan(b.Viewtheta / 2.0);
	float z_n = -vp.z * (b.Znear + b.Zfar) / (b.Znear - b.Zfar) + 2 * b.Znear * b.Zfar / (b.Znear - b.Zfar);
	return { x_n / vp.z, y_n / vp.z, z_n / vp.z };
}

// 规范左手系x_n-y_n-z_n => 窗口坐标系x-y-z (见书P261)
vertex_position Viewport_Transformation(vertex_position& vp, float width, float height) {
	float r = 0.5 * 0.8 * (width < height ? width : height);
	float x = vp.x * r + width / 2;
	float y = vp.y * r + height / 2;
	float z = 0.5 * vp.z + 0.5;
	return { x, y, z };
}

vertex_position Transformation(vertex_position& vp, Camera& ca, float w, float h, bool B) {
	vertex_position vp_t = Camera_Transformation(vp, ca);
	if (B) { // True则为透视投影
		if (vp_t.z > ca.pb.Znear || vp_t.z < ca.pb.Zfar) // 超出观察体范围
			return { -1, -1 };
		vp_t = Projection_Transformation_Perspective(vp_t, ca);
	}
	else {  // Flase则为正交投影
		if (vp_t.z > ca.ob.n || vp_t.z < ca.ob.f) // 超出观察体范围
			return { -1, -1 };
		vp_t = Projection_Transformation_Orthogonal(vp_t, ca);
	}
	return Viewport_Transformation(vp_t, w, h);
}

// 空间右手系X-Y-Z => 显示坐标系px-py
POINT CalScreenPosition(vertex_position& vp, int height) {
	return { (int)floor(vp.x), (int)(height - floor(vp.y)) };
}