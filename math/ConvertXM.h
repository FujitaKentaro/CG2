#pragma once
#include <DirectXMath.h>
#include "math/Matrix4.h"

using namespace DirectX;

class ConvertXM
{

public:
	static Matrix4 ConvertXMMATtoMat4( XMMATRIX XMMat);
	static XMMATRIX ConvertMat4toXMMAT(Matrix4 Mat4);
public:
	
	XMMATRIX xmMat;
	Matrix4 mat4;

};

