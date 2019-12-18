#include "stdafx.h"
#include "MYZipLib.h"
#include <zlib/zlib.h>
#include <zlib/zip.h>

CMYZipLib::CMYZipLib()
{
}

CMYZipLib::~CMYZipLib()
{
}

void CMYZipLib::Example()
{
	CString ProgramPath;
	::GetModuleFileName(NULL, ProgramPath.GetBuffer(_MAX_PATH), _MAX_PATH);
	ProgramPath.ReleaseBuffer();

	int nFind = ProgramPath.ReverseFind('\\');
	if (nFind == -1)
	{
		ASSERT(0);
		return;
	}

	ProgramPath = ProgramPath.Left(nFind + 1);

	CString strZip = ProgramPath + _T("..\\..\\..\\..\\file\\Example23.zip");

	auto strZipPath = std::string(CT2CA(strZip.operator LPCWSTR()));

	auto zf = zipOpen(strZipPath.c_str(), APPEND_STATUS_CREATE);
	if (zf == NULL)
		return;

	bool _return = true;
	for (size_t i = 0; i < 1; i++)
	{
		CString strWrite = ProgramPath + _T("..\\..\\..\\..\\file\\Write.txt");
		auto strWritePath = std::wstring(strWrite.operator LPCWSTR());

		zip_fileinfo zfi = {0};
		std::wstring fileName = _T("Write.txt");

		char buffer[] = "TEST ZIP FILE 한글도 되나?";
		bool _return = true;
		if (S_OK == zipOpenNewFileInZip(zf, std::string(fileName.begin(), fileName.end()).c_str(), &zfi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION))
		{
			if (zipWriteInFileInZip(zf, &buffer[0], sizeof(buffer)))
				_return = false;

			if (zipCloseFileInZip(zf))
				_return = false;
		}

		zip_fileinfo zfi2 = {0};
		std::wstring fileName2 = _T("Dir\\Write2.txt");
		if (S_OK == zipOpenNewFileInZip(zf, std::string(fileName2.begin(), fileName2.end()).c_str(), &zfi2, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION))
		{
			if (zipWriteInFileInZip(zf, &buffer[0], sizeof(buffer)))
				_return = false;

			if (zipCloseFileInZip(zf))
				_return = false;
		}
		
	}

	zipClose(zf, NULL);
}
