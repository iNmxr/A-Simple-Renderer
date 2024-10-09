#include "Transformation.h"

// �ռ�����ϵX-Y-Z => �������ϵu-v-n (����P242)
vertex_position Camera_Transformation(vertex_position& vp, Camera& ca) {
	float u = dot_product(vp, ca.u) - dot_product(ca.p, ca.u);
	float v = dot_product(vp, ca.v) - dot_product(ca.p, ca.v);
	float n = dot_product(vp, ca.n) - dot_product(ca.p, ca.n);
	return { u, v, n };
}

// �������ϵu-v-n => �淶����ϵx_n-y_n-z_n (����P246)
vertex_position Projection_Transformation_Orthogonal(vertex_position& vp, Camera& ca) {
	float x_n = vp.x * 2 / (ca.ob.r - ca.ob.l) - (ca.ob.r + ca.ob.l) / (ca.ob.r - ca.ob.l);
	float y_n = vp.y * 2 / (ca.ob.t - ca.ob.b) - (ca.ob.t + ca.ob.b) / (ca.ob.t - ca.ob.b);
	float z_n = vp.z * 2 / (ca.ob.f - ca.ob.n) - (ca.ob.f + ca.ob.n) / (ca.ob.f - ca.ob.n);
	return { x_n, y_n, z_n };
}

// �������ϵu-v-n => �淶����ϵx_n-y_n-z_n (����P261)
vertex_position Projection_Transformation_Perspective(vertex_position& vp, Camera& ca) {
#define b ca.pb
	float x_n = -vp.x / tan(b.Viewtheta / 2.0) / b.Aspect;
	float y_n = -vp.y / tan(b.Viewtheta / 2.0);
	float z_n = -vp.z * (b.Znear + b.Zfar) / (b.Znear - b.Zfar) + 2 * b.Znear * b.Zfar / (b.Znear - b.Zfar);
	return { x_n / vp.z, y_n / vp.z, z_n / vp.z };
}

// �淶����ϵx_n-y_n-z_n => ��������ϵx-y-z (����P261)
vertex_position Viewport_Transformation(vertex_position& vp, float width, float height) {
	float r = 0.5 * 0.8 * (width < height ? width : height);
	float x = vp.x * r + width / 2;
	float y = vp.y * r + height / 2;
	float z = 0.5 * vp.z + 0.5;
	return { x, y, z };
}

vertex_position Transformation(vertex_position& vp, Camera& ca, float w, float h, bool B) {
	vertex_position vp_t = Camera_Transformation(vp, ca);
	if (B) { // True��Ϊ͸��ͶӰ
		if (vp_t.z > ca.pb.Znear || vp_t.z < ca.pb.Zfar) // �����۲��巶Χ
			return { -1, -1 };
		vp_t = Projection_Transformation_Perspective(vp_t, ca);
	}
	else {  // Flase��Ϊ����ͶӰ
		if (vp_t.z > ca.ob.n || vp_t.z < ca.ob.f) // �����۲��巶Χ
			return { -1, -1 };
		vp_t = Projection_Transformation_Orthogonal(vp_t, ca);
	}
	return Viewport_Transformation(vp_t, w, h);
}

// �ռ�����ϵX-Y-Z => ��ʾ����ϵpx-py
POINT CalScreenPosition(vertex_position& vp, int height) {
	return { (int)floor(vp.x), (int)(height - floor(vp.y)) };
}