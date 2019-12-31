#pragma once

namespace Assimp
{
	class Importer;
}

class CDocBase;
class AFX_EXT_CLASS CAssimpFile
{
public:
	CAssimpFile(CDocBase* pDoc);
	~CAssimpFile();

public:
	BOOL Open(CString& strFilePath);
	BOOL Load();

protected:
	CDocBase* m_pMyDoc;

	CString m_strFilePath;
	std::shared_ptr<Assimp::Importer> m_pFile;

};