/*
坐标体系规范：
一、空间坐标系 X-Y-Z (float)
	右手系：
	Y轴为竖直向上方向

二、相机坐标系 u-v-n (float)
	右手系，
	相机位于坐标原点：
	n轴为相机朝向的反方向(即眼睛是看向-n方向的)
	屏幕的水平方向与u轴平行
	屏幕的垂直方向与v轴平行

三、规范坐标系 x_n-y_n-z_n (float)
	左手系，
	规范化立方体的坐标系：
	z_n轴为穿过屏幕向内的方向
	x_n轴与相机系u轴(屏幕的水平方向)平行且同向
	y_n轴与相机系v轴(屏幕的垂直方向)平行且同向

四、窗口坐标系 x-y-z (float)
	左手系，
	以窗口左下角为原点：
	顶点z值一定为正，且值越大表示离屏幕越远
	x轴向右为正向(窗口水平方向，与x_n轴同向)
	y轴向上为正向(窗口垂直方向，与y_n轴同向)

五、显示坐标系 px-py (int)
	以窗口左上角为原点：
	第一个坐标为水平坐标，向右为正向(与x轴相同)
	第二个坐标为竖直坐标，向下为正向(与y轴相反)

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