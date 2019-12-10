#include "stdafx.h"
#include "MathLib.h"
#include "ExMathLib.h"

CMathLib::CMathLib()
{
	EX_MATH::CExMathLib lib;
	lib.DoubleSq(12);
}


CMathLib::~CMathLib()
{
}
