#include "stdafx.h"
#include "ZipLib.h"
#include "StringLib.h"

#include <zip.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mylib;

mylib::CZipLib::CZipLib()
{
}

mylib::CZipLib::~CZipLib()
{
}

void mylib::CZipLib::Example()
{
	CString ProgramPath;
	::GetModuleFileName(NULL, ProgramPath.GetBuffer(_MAX_PATH), _MAX_PATH);
	ProgramPath.ReleaseBuffer();

	int nFind = ProgramPath.ReverseFind('\\');
	if (nFind == -1)
	{
		ASSERT(g_warning);
		return;
	}

	ProgramPath = ProgramPath.Left(nFind + 1);

	CString zippath = ProgramPath + _T("..\\..\\..\\..\\file\\achive.zip");

	std::string output_filename = CStringLib::CSTR2STR(zippath);
	int errorp;
	zip_t *zipper = zip_open(output_filename.c_str(), ZIP_CREATE | ZIP_EXCL, &errorp);
	if (zipper == nullptr) {
		zip_error_t ziperror;
		zip_error_init_with_code(&ziperror, errorp);
		throw std::runtime_error("Failed to open output file " + output_filename + ": " + zip_error_strerror(&ziperror));
	}

	CString filepath = ProgramPath + _T("..\\..\\..\\..\\file\\reference.md");
	std::string fullname = CStringLib::CSTR2STR(filepath);

	CString dirpath = ProgramPath + _T("..\\..\\..\\..\\file");
	std::string startdir = CStringLib::CSTR2STR(dirpath);

	try
	{
		zip_source_t *source = zip_source_file(zipper, fullname.c_str(), 0, 0);
		if (source == nullptr) {
			throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(zipper)));
		}
		if (zip_file_add(zipper, fullname.substr(startdir.length() + 1).c_str(), source, ZIP_FL_ENC_UTF_8) < 0) {
			zip_source_free(source);
			throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(zipper)));
		}
	}
	catch (...) {
		zip_close(zipper);
		throw;
	}

	zip_close(zipper);
}
