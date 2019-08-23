#pragma once

#pragma pack(push, 4)

template <class Type>
struct tagTVector2 {
	Type vec[2]; 
	tagTVector2<Type>(const Type& v0 = 0.f, const Type& v1 = 0.f)
	{
		vec[0] = v0;
		vec[1] = v1;
	}
	tagTVector2<Type>(const Type v[2])
	{
		vec[0] = v[0];
		vec[1] = v[1];
	}
	tagTVector2<Type>& operator=(const tagTVector2<Type> &src)
	{		
		vec[0] = src.vec[0];
		vec[1] = src.vec[1];
		return *this;
	}
	tagTVector2<Type>& operator+=(const tagTVector2<Type> &src)
	{		
		vec[0] += src.vec[0];
		vec[1] += src.vec[1];
		return *this;
	}	
	tagTVector2<Type>& operator-=(const tagTVector2<Type> &src)
	{		
		vec[0] -= src.vec[0];
		vec[1] -= src.vec[1];
		return *this;
	}	
	tagTVector2<Type> operator+(const tagTVector2<Type> &src) const
	{		
		tagTVector2<Type> tmp = *this;
		tmp+=src;
		return tmp;
	}

	tagTVector2<Type> operator-(const tagTVector2<Type> &src) const
	{		
		tagTVector2<Type> tmp = *this;
		tmp-=src;
		return tmp;
	}
	void Set(const Type& src)
	{
		vec[0] = src;
		vec[1] = src;
	}
};

typedef tagTVector2<long>		TVector2l;
typedef tagTVector2<float>		TVector2f;
typedef tagTVector2<double>		TVector2d;

template <class Type>
struct tagTVector3 {
	Type vec[3]; 
	tagTVector3<Type>(const Type& v0 = 0.f, const Type& v1 = 0.f, const Type& v2 = 0.f)
	{
		vec[0] = v0;
		vec[1] = v1;
		vec[2] = v2;
	}

	tagTVector3<Type>(const Type v[3])
	{
		vec[0] = v[0];
		vec[1] = v[1];
		vec[2] = v[2];
	}

	template<class Type0>
	tagTVector3<Type>& operator=(const tagTVector3<Type0> &src)
	{		
		vec[0] = Type(src.vec[0]);
		vec[1] = Type(src.vec[1]);
		vec[2] = Type(src.vec[2]);
		return *this;
	}

	template<class Type0>
	tagTVector3<Type>& operator+=(const tagTVector3<Type0> &src)
	{		
		vec[0] += Type(src.vec[0]);
		vec[1] += Type(src.vec[1]);
		vec[2] += Type(src.vec[2]);
		return *this;
	}	

	template<class Type0>
	tagTVector3<Type>& operator-=(const tagTVector3<Type0> &src)
	{		
		vec[0] -= Type(src.vec[0]);
		vec[1] -= Type(src.vec[1]);
		vec[2] -= Type(src.vec[2]);
		return *this;
	}

	template<class Type>
	tagTVector3<Type>& operator*=(const Type &src)
	{		
		vec[0] *= src;
		vec[1] *= src;
		vec[2] *= src;
		return *this;
	}

	template<class Type0>
	tagTVector3<Type> operator+(const tagTVector3<Type0> &src) const
	{		
		tagTVector3<Type> tmp = *this;
		tmp+=src;
		return tmp;
	}

	template<class Type0>
	tagTVector3<Type> operator-(const tagTVector3<Type0> &src) const
	{		
		tagTVector3<Type> tmp = *this;
		tmp-=src;
		return tmp;
	}

	void Set(const Type& src)
	{
		vec[0] = src;
		vec[1] = src;
		vec[2] = src;
	}

	Type Distance() const
	{
		Type dist = 0;
		for( int i=0 ; i<3 ; i++ )
		{
			dist += (vec[i]*vec[i]);
		}
		return sqrt(dist);
	}

	Type Normalize()
	{
		Type dist = Distance();
		if( fabs(dist) < 1.0e-12 )	return 0;

		for(int i=0 ; i<3 ; i++ )
			vec[i] /= dist;

		return dist;
	}

	Type Dot( const tagTVector3<Type> &src )
	{
		Type dotProd = 0;
		for(int i=0 ; i<3 ; i++ )
			dotProd += vec[i]*src.vec[i];

		return dotProd;
	}

	void Inverse()
	{
		for (int i=0 ; i<3 ; ++i )
		{
			this->vec[i] = -this->vec[i];
		}
	}
};

typedef tagTVector3<BYTE>		TVector3b;
typedef tagTVector3<long>		TVector3l;
typedef tagTVector3<int>		TVector3i;
typedef tagTVector3<float>		TVector3f;
typedef tagTVector3<double>		TVector3d;

template <class Type>
struct tagTVector4 {
	Type vec[4]; 
	tagTVector4<Type>(const Type& v0 = 0., const Type& v1 = 0., const Type& v2 = 0., const Type& v3 = 0.)
	{
		vec[0] = v0;
		vec[1] = v1;
		vec[2] = v2;
		vec[3] = v3;
	}
	tagTVector4<Type>(const Type v[4])
	{
		vec[0] = v[0];
		vec[1] = v[1];
		vec[2] = v[2];
		vec[3] = v[3];
	}
	tagTVector4<Type>& operator=(const tagTVector4<Type> &src)
	{		
		vec[0] = src.vec[0];
		vec[1] = src.vec[1];
		vec[2] = src.vec[2];
		vec[3] = src.vec[3];
		return *this;
	}
	tagTVector4<Type>& operator+=(const tagTVector4<Type> &src)
	{		
		vec[0] += src.vec[0];
		vec[1] += src.vec[1];
		vec[2] += src.vec[2];
		vec[3] += src.vec[3];
		return *this;
	}	

	void Set(const Type& src)
	{
		vec[0] = src;
		vec[1] = src;
		vec[2] = src;
		vec[3] = src;
	}
};

typedef tagTVector4<BYTE>		TVector4b;
typedef tagTVector4<long>		TVector4l;
typedef tagTVector4<float>		TVector4f;
typedef tagTVector4<double>		TVector4d;

// Matrix 
template <class Type>
union tagTMatrix3 {
	Type mat[3][3];
	Type _mat[9];

	void Init()
	{
		memset( mat, 0, sizeof(Type) * 9);
		mat[0][0] = Type(1.f);	mat[1][1] = Type(1.f);	mat[2][2]	= Type(1.f);
	}

	template<class Type0>
	tagTMatrix3<Type>& operator=(const tagTMatrix3<Type0> &src)
	{		
		Set(src.mat);
		return *this;
	}

	template<class Type0>
	void Get(Type0 dst[3][3]) const
	{
		dst[0][0] = Type0(mat[0][0]);	dst[0][1] = Type0(mat[0][1]);	dst[0][2] = Type0(mat[0][2]);
		dst[1][0] = Type0(mat[1][0]);	dst[1][1] = Type0(mat[1][1]);	dst[1][2] = Type0(mat[1][2]);
		dst[2][0] = Type0(mat[2][0]);	dst[2][1] = Type0(mat[2][1]);	dst[2][2] = Type0(mat[2][2]);
	}

	template<class Type0>
	void Set(const Type0 src[3][3])
	{
		mat[0][0] = Type(src[0][0]);	mat[0][1] = Type(src[0][1]);	mat[0][2] = Type(src[0][2]);
		mat[1][0] = Type(src[1][0]);	mat[1][1] = Type(src[1][1]);	mat[1][2] = Type(src[1][2]);
		mat[2][0] = Type(src[2][0]);	mat[2][1] = Type(src[2][1]);	mat[2][2] = Type(src[2][2]);		
	}
};

typedef tagTMatrix3<long>		TMatrix3l;
typedef tagTMatrix3<float>		TMatrix3f;
typedef tagTMatrix3<double>		TMatrix3d;

template <class Type>
union tagTMatrix4 {
	Type mat[4][4];
	Type _mat[16];

	void Init()
	{
		memset( mat, 0, sizeof(Type) * 16);
		mat[0][0] = Type(1.f);	mat[1][1] = Type(1.f);	mat[2][2]	= Type(1.f);	mat[3][3]	= Type(1.f);
	}

	template<class Type0>
	tagTMatrix4<Type>& operator=(const tagTMatrix4<Type0> &src)
	{		
		Set(src.mat);
		return *this;
	}

	template<class Type0>
	void Get(Type0 dst[4][4]) const
	{
		dst[0][0] = Type0(mat[0][0]);	dst[0][1] = Type0(mat[0][1]);	dst[0][2] = Type0(mat[0][2]);	dst[0][3] = Type0(mat[0][3]);
		dst[1][0] = Type0(mat[1][0]);	dst[1][1] = Type0(mat[1][1]);	dst[1][2] = Type0(mat[1][2]);	dst[1][3] = Type0(mat[1][3]);
		dst[2][0] = Type0(mat[2][0]);	dst[2][1] = Type0(mat[2][1]);	dst[2][2] = Type0(mat[2][2]);	dst[2][3] = Type0(mat[2][3]);
		dst[3][0] = Type0(mat[3][0]);	dst[3][1] = Type0(mat[3][1]);	dst[3][2] = Type0(mat[3][2]);	dst[3][3] = Type0(mat[3][3]);
	}

	template<class Type0>
	void Set(const Type0 src[4][4])
	{
		mat[0][0] = Type(src[0][0]);	mat[0][1] = Type(src[0][1]);	mat[0][2] = Type(src[0][2]);	mat[0][3] = Type(src[0][3]);
		mat[1][0] = Type(src[1][0]);	mat[1][1] = Type(src[1][1]);	mat[1][2] = Type(src[1][2]);	mat[1][3] = Type(src[1][3]);
		mat[2][0] = Type(src[2][0]);	mat[2][1] = Type(src[2][1]);	mat[2][2] = Type(src[2][2]);	mat[2][3] = Type(src[2][3]);
		mat[3][0] = Type(src[3][0]);	mat[3][1] = Type(src[3][1]);	mat[3][2] = Type(src[3][2]);	mat[3][3] = Type(src[3][3]);	
	}
};

typedef tagTMatrix4<long>		TMatrix4l;
typedef tagTMatrix4<float>		TMatrix4f;
typedef tagTMatrix4<double>		TMatrix4d;

// Plane
template <class Type>
struct tagTPlane {
	tagTVector3<Type> pos; 
	tagTVector3<Type> norm; 	
	tagTVector3<Type> ref;//x 방향
	tagTPlane<Type>& operator=(const tagTPlane<Type> &src)
	{		
		pos  = src.pos;
		norm = src.norm;
		ref  = src.ref;
		return *this;
	}	

	template<class Type0>
	void GetPlaneEq(Type0 planeEq[4])
	{	
		planeEq[0] = Type0(norm.vec[0]);
		planeEq[1] = Type0(norm.vec[1]);
		planeEq[2] = Type0(norm.vec[2]);
		planeEq[3] = Type0(-1.f*( norm.vec[0]*pos.vec[0] + norm.vec[1]*pos.vec[1] + norm.vec[2]*pos.vec[2]));
	}

	double GetDistance(const tagTVector3<Type>& tChkPos, const BOOL bSign = FALSE) const
	{
		double dSignedDist =    norm.vec[0] * (tChkPos.vec[0] - pos.vec[0]) +
			norm.vec[1] * (tChkPos.vec[1] - pos.vec[1]) +
			norm.vec[2] * (tChkPos.vec[2] - pos.vec[2]);
		return bSign? dSignedDist: fabs(dSignedDist);
	}
};
typedef tagTPlane<float>		TPlanef;
typedef tagTPlane<double>		TPlaned;

template <class Type>
struct tagTSphere
{
	tagTVector3<Type>	pos;
	Type				radius;

	tagTSphere<Type>& operator=(const tagTSphere<Type> &src)
	{		
		pos  = src.pos;
		radius = src.radius;		
		return *this;
	}
};
typedef tagTSphere<float>		TSpheref;
typedef tagTSphere<double>		TSphered;

typedef struct tagTHCADItem
{
	HCADItem	hItem	: 28;	// HCADItem
	HCADItem	iType	:  4;	// ICADSession.h 에 정의된 _CADITEM_TYPE enum 정보
} THCADItem, *LPTHCADItem;

typedef struct tagTElemSide
{
	TIterator	itrElem;		// Element Data Pool  ( DPoolElem ) Iterator
	int			idx;			// Element Side index ( 0 - 11 : Max 12개 Hexa Edge )

	tagTElemSide() { }
	tagTElemSide( TIterator _itr, int _idx ) : itrElem(_itr), idx(_idx) { }
	bool operator<(const tagTElemSide& other) const
	{
		if(itrElem < other.itrElem) return TRUE;
		if(itrElem > other.itrElem) return FALSE;
		else
		{
			if(idx < other.idx) return TRUE;
			return FALSE;
		}
		return FALSE;
	}
	bool operator==(const tagTElemSide& other) const
	{
		if(itrElem != other.itrElem) return FALSE;
		if(idx != other.idx) return FALSE;
		return TRUE;
	}

	// 	BEGIN_IO_STRUCT(tagTElemSide)
	// 		ADD_IO_VAR_ITER( _ELEMITR,	TIterator,	tagTElemSide, itrElem)
	// 		ADD_IO_VAR_FIXD( _INDEX,	int,		tagTElemSide, idx)
	// 		END_IO_STRUCT(tagTElemSide)

} TElemSide, *LPTElemSide;

template<class Type>
struct tagTItrPair
{
	TIterator	itr;
	Type		tValue;
	tagTItrPair<Type>(const TIterator& srcItr, const Type& srcValue)
	{
		itr = srcItr;
		tValue = srcValue;
	}
	tagTItrPair<Type>& operator=(const tagTItrPair<Type> &src)
	{		
		itr = src.itr;
		tValue = src.tValue;
		return *this;
	}		
	bool operator<(const tagTItrPair& src) const 
	{ 
		return tValue < src.tValue ;
	}
};

typedef tagTItrPair<long>		TItrPairl;
typedef tagTItrPair<float>		TItrPairf;
typedef tagTItrPair<double>		TItrPaird;

template<class Type>
struct tagTMapK
{
	operator unsigned long() { return (i1<<16) + (i2); }
	BOOL operator == (const tagTMapK& src) const { return i1 == src.i1 && i2 == src.i2; }
	Type i1;
	Type i2;
};

typedef tagTMapK<int>		TMapKi;
typedef tagTMapK<long>		TMapKl;
typedef tagTMapK<UINT>		TMapKui;

#pragma pack(pop)