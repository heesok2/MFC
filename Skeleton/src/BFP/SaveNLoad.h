#pragma once

class CBFPDoc;
class CSaveNLoad
{
public:
	static CSaveNLoad& Instance();

public:
	CSaveNLoad(void);
	virtual ~CSaveNLoad(void);

public:
	BOOL New( CBFPDoc* pDoc );
	BOOL Close( CBFPDoc* pDoc );
	BOOL Save( CBFPDoc* pDoc, LPCTSTR lpszPathName );
	BOOL Load( CBFPDoc* pDoc, LPCTSTR lpszPathName );
};