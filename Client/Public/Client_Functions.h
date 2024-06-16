#pragma once

#include "Engine_Defines.h"

namespace Client
{
   wstring Convert_StrToWStr(const string& str);
   string Convert_WStrToStr(const wstring& wstr);
   wstring Get_Path(const wstring& wstrFileFullPath);
};

namespace JoMath
{
	_matrix LookTo(_fvector vTargetLook);
	_matrix LookAt(_fvector vSrc, _fvector vDst);

	_vector ToEulerAngle(_fvector vQuat);
}

namespace JoRandom
{
	_int Random_Int(_int _iMin, _int _iMax);
	_float Random_Float(_float _fMin, _float _fMax);
}

