#pragma once

#include "CameraDefine.h"

namespace mygl
{
	class AFX_EXT_CLASS CCamera
	{
	public:
		CCamera();
		virtual ~CCamera();

	public:
		glm::ivec4 GetViewport();
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();		

	public:
		void SetViewport(int width, int height);
		void SetViewCenter(glm::vec3& vPosition);
		void SetCameraPosition(glm::vec3& vPosition);
		void SetMousePosition(CPoint& point);

		void OnKeyboardDown(E_CAMERA_MOVEMENT eMovement, float deltaTime);
		void OnMouseMove(CPoint point);

	protected:
		void UpdateCameraVectors(float fOffsetX, float fOffsetY);

	protected:
		float m_fYaw;
		float m_fPitch;
		float m_fMovementSpeed;
		float m_fMouseSensitivity;
		CPoint m_MousePoint; // Mouse Move

		E_CAMERA_MODE m_eMode;
		glm::vec3 m_aCameraPos;
		glm::vec3 m_aCameraDir;
		glm::vec3 m_aCameraUp;
		glm::vec3 m_aCameraRight;
		glm::vec3 m_aWorldUp;
		glm::vec3 m_aWorldCenter;

		glm::ivec4 m_aViewport;
	};
}