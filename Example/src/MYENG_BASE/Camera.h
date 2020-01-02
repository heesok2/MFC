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
		glm::vec3 GetEyePos() { return m_aCameraPos; }
		glm::vec3 GetEyeDir() { return m_aCameraDir; }
		glm::vec3 GetEyeUp() { return m_aCameraUp; }
		glm::vec3 GetEyeRight() { return m_aCameraRight; }
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();

	public:
		void SetViewSize(CRect& rect);
		void SetViewCenter(glm::vec3& vPosition);
		void SetCameraPosition(glm::vec3& vPosition);
		void SetMousePosition(CPoint& point);

		void OnKeyboardDown(E_CAMERA_MOVEMENT eMovement, float deltaTime);
		void OnMouseMove(CPoint point);

	protected:
		void UpdateCameraVectors(float fOffsetX, float fOffsetY);

	protected:
		E_CAMERA_MODE m_eMode;

		CRect m_Viewport;
		CPoint m_MousePoint; // Mouse Move

		glm::vec3 m_aCameraPos;
		glm::vec3 m_aCameraDir;
		glm::vec3 m_aCameraUp;
		glm::vec3 m_aCameraRight;
		glm::vec3 m_aWorldUp;
		glm::vec3 m_aWorldCenter;

		float m_fYaw;
		float m_fPitch;
		float m_fMovementSpeed;
		float m_fMouseSensitivity;

	};
}