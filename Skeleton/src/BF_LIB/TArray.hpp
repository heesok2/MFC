#pragma once

#include "TShortStr.h"

//이 클래스는 copy/new가 필요한 자료구조를 담지 않기 위해 만든 것임. 주의.(속도 문제 때문)

//#define TARRAY_COPYELEMENTS(dst, src, size)	if(TypeNeedCopyConstruct) CopyElements((dst), (src), (size)); else memcpy( (dst), (src), (size) * sizeof(Type) )
#define TARRAY_COPYELEMENTS(dst, src, size)	memcpy( (dst), (src), (size) * sizeof(Type) )
template <class Type>//, BOOL TypeNeedCopyConstruct = TRUE>
class TArray	
{
public:
	TArray() : m_aData(NULL), m_nSize(0) {}

	TArray(int size) : m_aData(NULL), m_nSize(0)
	{
		this->SetSize(size);
	}

	TArray(int size, Type Val) : m_aData(NULL), m_nSize(0)
	{
		this->SetSize(size);
		for(int i=0; i<size; i++)
			(*this)[i] = Val;
	}

	TArray(const TArray<Type>& src) : m_aData(NULL), m_nSize(0)
	{		
		if (src.m_nSize)
		{
			m_aData = (Type*)malloc(src.m_nSize * sizeof(Type));
			memset((void*)m_aData, 0, (size_t)src.m_nSize * sizeof(Type));

			TARRAY_COPYELEMENTS(m_aData, src.m_aData, src.m_nSize);

			m_nSize = src.m_nSize;
		}
	}

	~TArray() { RemoveAll(); }

	TArray<Type>& operator=(const TArray<Type>& src)
	{
		if( &src.m_aData == &m_aData )
			return *this;

		if(m_aData)free(m_aData);
		m_aData = (Type*)malloc(src.m_nSize * sizeof(Type));
		memset((void*)m_aData, 0, (size_t)src.m_nSize * sizeof(Type));

		TARRAY_COPYELEMENTS(m_aData, src.m_aData, src.m_nSize);		

		m_nSize = src.m_nSize;
		return *this;
	}

	// Operations

	long GetSize() const { return m_nSize; }
	long GetCount() const { return m_nSize; }
	void Copy(const TArray<Type>& src)
	{
		if( &src.m_aData == &m_aData )
			return;
		if(m_aData)free(m_aData);		
		m_aData = (Type*)malloc(src.m_nSize * sizeof(Type));

		TARRAY_COPYELEMENTS(m_aData, src.m_aData, src.m_nSize);

		m_nSize = src.m_nSize;
	}

	void Append(const TArray<Type>& src)
	{
		if(src.IsEmpty())
			return;

		long nPrevSize = m_nSize;
		reSize(m_nSize + src.m_nSize);

		TARRAY_COPYELEMENTS(m_aData + nPrevSize, src.m_aData, src.m_nSize);
	}

	const Type& operator[](long nIndex) const
	{
		ASSERT( nIndex >= 0 && nIndex < m_nSize);
		return m_aData[nIndex];
	}

	Type& operator[](long nIndex)

	{
		ASSERT( nIndex >= 0 && nIndex < m_nSize);
		return m_aData[nIndex];
	}

	void SetSize(const long nSize)
	{
		if( nSize != m_nSize ) 
		{
			if(m_aData) free(m_aData);
			if(nSize > 0)
			{
				m_nSize = nSize;		
				m_aData = (Type*)malloc(m_nSize*sizeof(Type));
				memset((void*)m_aData, 0, (size_t)m_nSize * sizeof(Type));
			}
			else {
				m_nSize = 0;
				m_aData = NULL;
			}
		}
	}

	void RemoveAll()
	{
		if( m_aData ){
			free(m_aData);
			m_aData = NULL;
		}
		m_nSize = 0;
	}

	BOOL IsEmpty() const
	{
		return (m_nSize==0);
	}

	void reSize(const long nSize) // resize the array but maintain data
	{
		TArray<Type> arTmp;
		// 		if(m_nSize >= nSize) 좀 느려도... 메모리 쳐먹는거 생각해서 요래 하자...(버퍼처럼 쓰고 싶을 때...)
		// 		{
		// 			m_nSize = nSize;
		// //			return;	// return으로 떼우지 말고 실제 array도 줄여주지 않으면 안된다.
		// 		}

		if( nSize != m_nSize ) 
		{
			arTmp.SetSize(m_nSize);
			TARRAY_COPYELEMENTS(arTmp.m_aData, m_aData, m_nSize);
			if(m_aData) free(m_aData);
			if(nSize > 0)
			{
				m_nSize = nSize;		
				m_aData = (Type*)malloc(m_nSize*sizeof(Type));
				memset((void*)m_aData, 0, (size_t)m_nSize * sizeof(Type));

				if (m_nSize > arTmp.m_nSize)
					TARRAY_COPYELEMENTS(m_aData, arTmp.m_aData, arTmp.m_nSize);
				else
					TARRAY_COPYELEMENTS(m_aData, arTmp.m_aData, m_nSize);
			}
			else {
				m_nSize = 0;
				m_aData = NULL;
			}
		}		
	}

	Type* GetData() const { return m_aData; }

protected:

	Type*	m_aData;
	long	m_nSize;
};

typedef TArray<BOOL>				TArrayB;
typedef TArray<unsigned char>		TArrayub;
typedef TArray<long>				TArrayl;
typedef TArray<int>					TArrayi;
typedef TArray<ULONG>				TArrayul;
typedef TArray<float>				TArrayf;
typedef TArray<double>				TArrayd;
typedef TArray<TKey>				TArrayK;
typedef TArray<TIterator>			TArrayITR;		// Iterator Array
typedef TArray<TShortStr>			TArraySStr;
typedef TArray<TStr>				TArrayStr;
typedef TArray<TLongStr>			TArrayLStr;
typedef TArray<HCADItem>			TArrayHCADItem;
typedef TArray<THCADItem>			TArrayTHCADItem;
typedef TArray<TElemSide>			TArrayTElemSide;
typedef TArray<char>				TArrayc;
typedef TArray<int>					TArrayi;
typedef TArray<UINT>				TArrayui;
typedef TArray<COLORREF>			TArrayColor;

typedef TArray<TVector2l>			TArrayVec2l;
typedef TArray<TVector2f>			TArrayVec2f;
typedef TArray<TVector2d>			TArrayVec2d;

typedef TArray<TVector3b>			TArrayVec3b;
typedef TArray<TVector3l>			TArrayVec3l;
typedef TArray<TVector3f>			TArrayVec3f;
typedef TArray<TVector3d>			TArrayVec3d;
typedef TArray<TVector3i>			TArrayVec3i;

typedef TArray<TVector4b>			TArrayVec4b;
typedef TArray<TVector4l>			TArrayVec4l;
typedef TArray<TVector4f>			TArrayVec4f;
typedef TArray<TVector4d>			TArrayVec4d;

typedef TArray<TMatrix3l>			TArrayMat3l;
typedef TArray<TMatrix3f>			TArrayMat3f;
typedef TArray<TMatrix3d>			TArrayMat3d;

typedef TArray<TMatrix4l>			TArrayMat4l;
typedef TArray<TMatrix4f>			TArrayMat4f;
typedef TArray<TMatrix4d>			TArrayMat4d;

typedef TArray<TSpheref>			TArraySpheref;
typedef TArray<TSphered>			TArraySphered;

// Part of Array ( no allocation, just referencing )
template <class Type>
struct TArrPart {
	Type*	aData;
	long	idxStart;
	long	nSize;

	struct TArrPart() 
	{
		aData = NULL;
		idxStart = 0;
		nSize = 0;
	}

	Type* GetArray() { return &(aData[idxStart]); }
	long GetSize() { return nSize; }
};

typedef TArrPart<long>			TArrPartl;
typedef TArrPart<float>			TArrPartf;
typedef TArrPart<double>		TArrPartd;
typedef TArrPart<TKey>			TArrPartK;
typedef TArrPart<TIterator>		TArrPartITR;	// Iterator Array

typedef TArrPart<TVector2l>		TArrPartVec2l;
typedef TArrPart<TVector2f>		TArrPartVec2f;
typedef TArrPart<TVector2d>		TArrPartVec2d;

typedef TArrPart<TVector3l>		TArrPartVec3l;
typedef TArrPart<TVector3f>		TArrPartVec3f;
typedef TArrPart<TVector3d>		TArrPartVec3d;

typedef TArrPart<TVector4l>		TArrPartVec4l;
typedef TArrPart<TVector4f>		TArrPartVec4f;
typedef TArrPart<TVector4d>		TArrPartVec4d;

typedef TArrPart<TMatrix3l>		TArrPartMat3l;
typedef TArrPart<TMatrix3f>		TArrPartMat3f;
typedef TArrPart<TMatrix3d>		TArrPartMat3d;

typedef TArrPart<TMatrix4l>		TArrPartMat4l;
typedef TArrPart<TMatrix4f>		TArrPartMat4f;
typedef TArrPart<TMatrix4d>		TArrPartMat4d;