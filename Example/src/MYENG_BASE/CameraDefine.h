#pragma once

#ifndef DEF_CAMERA
#define DEF_CAMERA

enum E_CAMERA_MOVEMENT
{
	E_CAMERA_FORWARD = 0
	, E_CAMERA_BACKWARD
	, E_CAMERA_LEFT
	, E_CAMERA_RIGHT
	, E_CAMERA_BOTTOM
	, E_CAMERA_TOP
	, E_CAMERA_NUM
};

enum E_CAMERA_MODE
{
	E_MODE_SIMPLE = 0
	, E_MODE_FPS
	, E_MODE_MODELER	
	, E_MODE_NUM
};

#endif // !DEF_CAMERA