#pragma once

#include "math/Matrix4.h"
#include "math/Affin.h"

class Trans
{
public:
	Trans();
	~Trans();
	void Initialize();
public:
	// ローカルスケール
	Vector3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	Vector3 rotation = { 0,0,0 };
	// ローカル座標
	Vector3 position = { 0,0,0 };
	// ローカルワールド変換行列
	Matrix4 matWorld = Affin::matUnit();

};