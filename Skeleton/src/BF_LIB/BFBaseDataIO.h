#pragma once

#include "BFBaseDataDef.h"

//////////////////////////////////////////////////////////////////////////

#define DATA_STR_SIZE 20

enum DATA_IO_TYPE
{
	DATA_IO_EMPTY = 0,
	DATA_IO_UNKNOWN,
	DATA_IO_SKIP,
	DATA_IO_FIXD,
	DATA_IO_ITER,
	DATA_IO_STRT,
	DATA_IO_ARRY,
};

struct DATA_IO
{
	TCHAR szName[DATA_STR_SIZE];

	UINT uiDataType;
	UINT uiDataOffset;
	UINT uiDataSize;

	UINT uiArrType;
	UINT uiArrSize;

	const DATA_IO* pStructIO;
};

#define BEGIN_DATA_IO( _define )\
	static _define& GSD() { static _define _instance; return _instance; }\
	static const DATA_IO* GetDataIO() { static const DATA_IO _io_instance[] = {

#define DATA_IO_LAST() { _T(""), DATA_IO_EMPTY, 0, 0, DATA_IO_EMPTY, 0, nullptr } };
#define END_DATA_IO() return _io_instance; }

#define DATA_IO_DEFN_FIXD( _name, _define, _type, _data ) { _T(#_name), DATA_IO_FIXD, offsetof(_define, _data), sizeof(_type), DATA_IO_EMPTY, 0, nullptr }
#define DATA_IO_DEFN_ITER( _name, _define, _type, _data ) { _T(#_name), DATA_IO_ITER, offsetof(_define, _data), sizeof(_type), DATA_IO_EMPTY, 0, nullptr }
#define DATA_IO_DEFN_STRT( _name, _define, _type, _data ) { _T(#_name), DATA_IO_STRT, offsetof(_define, _data), sizeof(_type), DATA_IO_EMPTY, 0, _type::GetDataIO() }
#define DATA_IO_ARRY_FIXD( _name, _define, _type, _data, _arr_type ) { _T(#_name), DATA_IO_ARRY, offsetof(_define, _data), sizeof(_type), DATA_IO_FIXD, sizeof(_arr_type), nullptr }
#define DATA_IO_ARRY_ITER( _name, _define, _type, _data, _arr_type ) { _T(#_name), DATA_IO_ARRY, offsetof(_define, _data), sizeof(_type), DATA_IO_ITER, sizeof(_arr_type), nullptr }
#define DATA_IO_ARRY_STRT( _name, _define, _type, _data, _arr_type ) { _T(#_name), DATA_IO_ARRY, offsetof(_define, _data), sizeof(_type), DATA_IO_STRT, sizeof(_arr_type), _arr_type::GetDataIO() }
