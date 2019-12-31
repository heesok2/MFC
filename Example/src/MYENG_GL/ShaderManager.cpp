#include "pch.h"
#include "resource.h"
#include "ShaderManager.h"
#include "ShaderDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mygl;

CShaderManager::CShaderManager()
{
}


CShaderManager::~CShaderManager()
{
}

BOOL CShaderManager::IsValid(UINT uiType)
{
	auto itr = m_mBuild.find(uiType);
	return itr != m_mBuild.end();
}

CShader & CShaderManager::GetAt(UINT uiType)
{
	auto itr = m_mBuild.find(uiType);
	if (itr == m_mBuild.end())
	{
		ASSERT(g_warning);
		m_mBuild[uiType] = CShader();
	}

	return m_mBuild[uiType];
}

void CShaderManager::GLVersion()
{
	char* strSLVersion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	//���� ����ũž ������ ��ȭ�Ǹ鼭 �׷��� �ڿ��� ������� ���� �Ҵ�޴� ����� �ٲ������ ���δ�.
	//�Ʒ��� ���� Shader Version�� ȣ������ ���� ��찡 ���ܼ� ����ó�� �߰�
	if (strSLVersion)
	{

	}
	else
	{
	}
}

void CShaderManager::GLCreate()
{
	for (UINT indx = E_SHADER_SCENE; indx < E_SHADER_NUM; ++indx)
	{
		GLCreate(indx);
	}
}

void CShaderManager::GLCreate(UINT uiType)
{
	auto itrFind = m_mBuild.find(uiType);
	if (m_mBuild.end() != itrFind)
		return;

	CShader shader;
	shader.GLCreate();

	switch (uiType)
	{
	case E_SHADER_SCENE:
		{
			shader.GLAttachShader(GL_VERTEX_SHADER, IDR_SCENE_VERT);
			shader.GLAttachShader(GL_FRAGMENT_SHADER, IDR_SCENE_FRAG);
		}
		break;
	case E_SHADER_PHONG:
		{
			shader.GLAttachShader(GL_VERTEX_SHADER, IDR_PHONG_VERT);
			shader.GLAttachShader(GL_FRAGMENT_SHADER, IDR_DIRECTIONAL_FRAG);
			shader.GLAttachShader(GL_FRAGMENT_SHADER, IDR_PHONG_FRAG);
		}
		break;
	default:
		{
			ASSERT(g_warning);
		}
		break;
	}

	shader.GLLinkShader();
	m_mBuild[uiType] = shader;
}

void CShaderManager::GLDelete()
{
	auto itr = m_mBuild.begin();
	while (itr == m_mBuild.end())
	{
		itr->second.GLDelete();
		itr++;
	}
}