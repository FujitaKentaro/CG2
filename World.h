#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <vector>
#include <string>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#include <DirectXTex.h>
#include "math/Affin.h"

#define DIRECTINPUT_VERSION		0x0800		//DirectInputのバージョン指定

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace DirectX;

// 円周率
const float PI = 3.141592f;

// 定数バッファ用データ構造体（マテリアル）
struct ConstBufferDataMaterial {
	XMFLOAT4 color; // 色 (RGBA)
};

// 定数バッファ用データ構造体（ 3D変換行列 ）
struct ConstBufferDataTransform {
	XMMATRIX mat; // 3D変換行列
};

// 頂点用構造体
struct  Vertex
{
	XMFLOAT3 pos;	// xyz座標
	XMFLOAT3 normal;	// 法線ベクトル
	XMFLOAT2 uv; 	// uv座標
};

// 3Dオブジェクト型

struct Object3d {
	// 定数バッファ （行列用）
	ID3D12Resource* constBuffTrnceform = nullptr;
	// 定数バッファマップ （行列用）
	ConstBufferDataTransform* constMapTransform = nullptr;

	// アフィン変換情報
	XMFLOAT3 scale = { 1,1,1 };
	XMFLOAT3 rotation = { 0,0,0 };
	XMFLOAT3 position = { 0,0,0 };

	//ワールド変換行列
	XMMATRIX matWorld ;
	// 親オブジェクトへのポインタ
	Object3d* parent = nullptr;

};

