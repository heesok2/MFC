#pragma once

namespace mygl
{
	class AFX_EXT_CLASS CPrimitiveBase
	{
	protected:
		typedef struct tagPimitive
		{
			UINT uiVAO;
			UINT uiCount;

			tagPimitive(UINT _uiVAO = 0, UINT _uiCount = 0)
				: uiVAO(_uiVAO), uiCount(_uiCount)
			{
			}

		} TPrimitive;

	public:
		CPrimitiveBase();
		virtual ~CPrimitiveBase();

	public:
		virtual UINT GetRenderType() = 0;
		virtual BOOL GLPrepare(CView* pView) = 0;

	public:
		void GLDraw();

	protected:
		UINT CreateVBO(std::vector<float>& aBuffer);
		UINT CreateEBO(std::vector<UINT>& aBufferIndex);
		UINT CreateVAO(UINT uiVBO, UINT uiEBO, UINT uiCount
					   , UINT uiVertexCount, UINT uiVertexOffset
					   , UINT uiNormalCount, UINT uiNormalOffset
					   , UINT uiTexcelCount, UINT uiTexcelOffset);

		UINT CreateTex2D(UINT uiInternal, UINT uiWidth, UINT uiHeight,
						 UINT uiFormat, UINT uiType, const BYTE* pBuffer);

	protected:
		std::vector<TPrimitive> m_aVAO;
		std::vector<UINT> m_aVBO;
		std::vector<UINT> m_aEBO;

	};
}


