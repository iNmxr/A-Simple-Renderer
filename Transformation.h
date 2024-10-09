/*
������ϵ�淶��
һ���ռ�����ϵ X-Y-Z (float)
	����ϵ��
	Y��Ϊ��ֱ���Ϸ���

�����������ϵ u-v-n (float)
	����ϵ��
	���λ������ԭ�㣺
	n��Ϊ�������ķ�����(���۾��ǿ���-n�����)
	��Ļ��ˮƽ������u��ƽ��
	��Ļ�Ĵ�ֱ������v��ƽ��

�����淶����ϵ x_n-y_n-z_n (float)
	����ϵ��
	�淶�������������ϵ��
	z_n��Ϊ������Ļ���ڵķ���
	x_n�������ϵu��(��Ļ��ˮƽ����)ƽ����ͬ��
	y_n�������ϵv��(��Ļ�Ĵ�ֱ����)ƽ����ͬ��

�ġ���������ϵ x-y-z (float)
	����ϵ��
	�Դ������½�Ϊԭ�㣺
	����zֵһ��Ϊ������ֵԽ���ʾ����ĻԽԶ
	x������Ϊ����(����ˮƽ������x_n��ͬ��)
	y������Ϊ����(���ڴ�ֱ������y_n��ͬ��)

�塢��ʾ����ϵ px-py (int)
	�Դ������Ͻ�Ϊԭ�㣺
	��һ������Ϊˮƽ���꣬����Ϊ����(��x����ͬ)
	�ڶ�������Ϊ��ֱ���꣬����Ϊ����(��y���෴)

*/
#pragma once
#include <Windows.h>
#include "Mathlib.h"
#include "Camera.h"

vertex_position Camera_Transformation(vertex_position&, Camera&);

vertex_position Projection_Transformation_Orthogonal(vertex_position& vp, Camera& ca);

vertex_position Projection_Transformation_Perspective(vertex_position& vp, Camera& ca);

vertex_position Viewport_Transformation(vertex_position& vp, float width, float height);

vertex_position Transformation(vertex_position& vp, Camera& ca, float w, float h, bool B);

POINT CalScreenPosition(vertex_position& vp, int);