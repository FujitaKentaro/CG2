#pragma once
#include <DirectXMath.h>
#include "math/Matrix4.h"

using namespace DirectX;

class ConvertXM
{

public:
	static Matrix4 ConvertMat4toXMMAT( XMMATRIX XMMat);
	static XMMATRIX ConvertXMMATtoMat4(Matrix4 Mat4);
public:
	
	XMMATRIX xmMat;
	Matrix4 mat4;

};

