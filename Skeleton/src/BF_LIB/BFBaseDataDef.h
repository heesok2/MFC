#pragma once

typedef long		TKey;
typedef DWORD_PTR	TIterator;
typedef int			HCADItem;	

#define _SAFE_DELETE(x)			{if(x){delete (x);(x)=NULL;}}
#define _SAFE_DELETE_ARRAY(x)	{if(x){delete [] (x);(x)=NULL;}}

#define VFPTR_SIZE sizeof(DWORD_PTR)

#define KEY_IS_VALID(x)			( (x) > 0 )
#define ITR_IS_VALID(x)			( (x) > 0 )

#define ITR_TO_IDX(x)			( *((ObjectParam*)(x)).idx )
#define ITR_TO_KEY(x)			( *((TKey*)((BYTE*)(x) + sizeof(ObjectParam) + VFPTR_SIZE)) )
#define ITR_TO_DATABASE(x)		( (CDataBase*)((BYTE*)(x) + sizeof(ObjectParam)) )
#define ITR_TO_DATA(T,x)		( (const T*)&((CDataLinker<T>::ObjectData*)(x)->data) )

//////////////////////////////////////////////////////////////////////////

#define DLINKER_HASH_SIZE 1000
#define DLINKER_HASH_INDX( key, hash_size ) ((key) % (hash_size))

#define __OBJ_PARAM_OFF__ 0x0000
#define __OBJ_PARAM_ON___ 0x0001

typedef struct tagObjectParam
{
	UINT idx : 29;
	UINT removed : 1;
	UINT modified : 1;
	UINT mark : 1;

	tagObjectParam() : idx(0), removed(0), modified(0), mark(0) {}

} ObjectParam, *LPObjectParam;
