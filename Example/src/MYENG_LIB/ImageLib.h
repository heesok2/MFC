#pragma once

#ifndef DEF_IMGLOADER
#define DEF_IMGLOADER

#define MYIMG_RED 1
#define MYIMG_RGB 3
#define MYIMG_RGBA 4

namespace mylib
{
	class AFX_EXT_CLASS CImageLib
	{
	public:
		CImageLib();
		~CImageLib();

	public:
		BOOL Open(CString& strFilePath);

	public:
		const BYTE* GetBuffer() { return m_pBuffer; }
		const int GetWidth() { return m_nWidth; }
		const int GetHeight() { return m_nHeight; }
		const int GetByte() { return m_nBytes; }

	protected:
		CString m_strFilePath;
		BYTE* m_pBuffer;
		int m_nWidth;
		int m_nHeight;
		int m_nBytes;

	};
}

#endif // !DEF_IMGLOADER