#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector2.h"


/// <summary>
/// アフィン行列 （角度指定：度数法）
/// </summary>
namespace Affin {

	//円周率
	const float PI = 3.141592654f;
	// 度数法 -> ラジアン変換
	float radConvert(float value);
	// ラジアン -> 度数法変換 
	float degConvert(float value);

	// 単位行列 set
	Matrix4 matUnit();


	// 零行列設定
	Matrix4 matZero();

	// ベクトルと行列の掛け算
	Vector3 VecMat(Vector3 vec, Matrix4 mat);
	Vector3 transform(const Vector3& v, const Matrix4& m);

	// 平行移動
	Matrix4 matTrans(float moveX, float moveY, float moveZ);
	Matrix4 matTrans(Vector3 move);

	// 回転
	Matrix4 matRotateX(float rotationX);
	Matrix4 matRotateY(float rotationY);
	Matrix4 matRotateZ(float rotationZ);
	Matrix4 matRotationZXY(float rotateX, float rotateY, float rotateZ);
	Matrix4 matRotationZXY(Vector3 rotate);
	Matrix4 matRotationXYZ(Vector3 rotate);

	//拡縮
	Matrix4 matScale(float scaleX, float scaleY, float scaleZ);
	Matrix4 matScale(Vector3 scale);

	//拡縮 -> 回転 -> 移動
	Matrix4 matWorld(Vector3 move, Vector3 rotate, Vector3 scale);
}// namespace Affin


