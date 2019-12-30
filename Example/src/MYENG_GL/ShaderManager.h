#pragma once

#include "Shader.h"

namespace mygl
{
	class AFX_EXT_CLASS CShaderManager
	{
	public:
		CShaderManager();
		virtual ~CShaderManager();

	public:
		BOOL IsValid(UINT uiType);
		CShader& GetAt(UINT uiType);

		void GLVersion();
		void GLCreate();
		void GLDelete();

	protected:
		void GLCreate(UINT uiType);

	protected:
		std::map<UINT, CShader> m_mBuild;

	};
}