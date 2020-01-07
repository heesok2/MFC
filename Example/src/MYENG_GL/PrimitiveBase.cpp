#include "pch.h"
#include "PrimitiveBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mygl;

CPrimitiveBase::CPrimitiveBase()
{
}

CPrimitiveBase::~CPrimitiveBase()
{
}

void CPrimitiveBase::GLDraw()
{
	for (auto& primitive : m_aVAO)
	{
		glBindVertexArray(primitive.uiVAO);

		glDrawElements(GL_TRIANGLES, primitive.uiCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
}

UINT CPrimitiveBase::CreateVBO(std::vector<float>& aBuffer)
{
	UINT uiVBO = 0;

	glGenBuffers(1, &uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * aBuffer.size(), &(aBuffer[0]), GL_STATIC_DRAW);

	return uiVBO;
}

UINT CPrimitiveBase::CreateEBO(std::vector<UINT>& aBufferIndex)
{
	UINT uiEBO;

	glGenBuffers(1, &uiEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT)* aBufferIndex.size(), &(aBufferIndex[0]), GL_STATIC_DRAW);

	return uiEBO;
}

UINT CPrimitiveBase::CreateVAO(UINT uiVBO, UINT uiEBO, UINT uiTexCount, UINT* pTex
							   , UINT uiCount
							   , UINT uiVertexCount, UINT uiVertexOffset
							   , UINT uiNormalCount, UINT uiNormalOffset
							   , UINT uiTexcelCount, UINT uiTexcelOffset)
{
	UINT uiVAO;

	glGenVertexArrays(1, &uiVAO);
	glBindVertexArray(uiVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);

		glVertexAttribPointer(0, uiVertexCount, GL_FLOAT, GL_FALSE, 0, (void*)uiVertexOffset);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, uiNormalCount, GL_FLOAT, GL_FALSE, 0, (void*)uiNormalOffset);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, uiTexcelCount, GL_FLOAT, GL_FALSE, 0, (void*)uiTexcelOffset);
		glEnableVertexAttribArray(2);
	}
	glBindVertexArray(0);

	if (uiVAO > 0)
		m_aVAO.push_back(TPrimitive(uiVAO, uiCount));

	return uiVAO;
}

UINT CPrimitiveBase::CreateTex2D(UINT uiInternal, UINT uiWidth, UINT uiHeight, UINT uiFormat, UINT uiType, const BYTE * pBuffer)
{
	UINT uiTex2D = 0;

	glGenTextures(1, &uiTex2D);
	glBindTexture(GL_TEXTURE_2D, uiTex2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, uiInternal, uiWidth, uiHeight, 0, uiFormat, uiType, pBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return uiTex2D;
}
