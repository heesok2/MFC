#pragma once

class CDocBase;
class CMYPackageStream
{
public:
	CMYPackageStream();
	~CMYPackageStream();

public:
	static BOOL New(CDocBase* pDoc);
	static BOOL Open(CDocBase* pDoc);
	static BOOL Save(CDocBase* pDoc);
	static BOOL Close(CDocBase* pDoc);

};

