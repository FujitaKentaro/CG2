#include "Vector4.h"

// 零ベクトルとする
Vector4::Vector4()
	:x(0), y(0), z(0),w(0)
{

}

// x成分, y成分, z成分 を指定しての生成
Vector4::Vector4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{

}