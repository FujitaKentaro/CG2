#pragma once
#include "World.h"


class Triangle
{
public:
	// リザルト
	HRESULT result;
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};


	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature;
	// パイプランステートの生成
	ComPtr<ID3D12PipelineState> pipelineState;
	// 定数バッファ
	ComPtr <ID3D12Resource> constBuffMaterial;
	

	//3Dオブジェクトの数
	static const size_t kObjectCount = 50;
	// 3Dオブジェクトの配列
	Object3d object3ds[kObjectCount];

	// 定数バッファの生成0
	/*ID3D12Resource* constBuffTransform0 = nullptr;
	ConstBufferDataTransform* constMapTransform0 = nullptr;
	// 定数バッファの生成1
	ID3D12Resource* constBuffTransform1 = nullptr;
	ConstBufferDataTransform* constMapTransform1 = nullptr;*/


	//GPU上のバッファに対応した仮想メモリ
	Vertex* vertMap = nullptr;
	// 設定を元にSRV用デスクリプタヒープを生成
	ID3D12DescriptorHeap* srvHeap;
	// 
	UINT incrementSize;

	// ワールド変換行列
	XMMATRIX matWorld;
	XMMATRIX matWorld1;

	//座標
	XMFLOAT3 scale	 = { 1.0f,1.0f,1.0f };
	XMFLOAT3 position = { 0.0f,0.0f,0.0f };
	XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };
	
	//座標1
	XMFLOAT3 scale1 = { 1.0f,1.0f,1.0f };
	XMFLOAT3 position1 = { 0.0f,0.0f,0.0f };
	XMFLOAT3 rotation1 = { 0.0f,0.0f,0.0f };
	

	// 射影変換行列の計算
	XMMATRIX matProjection;

	// ビュー変換行列
	XMMATRIX matView;
	XMFLOAT3 eye;	// 視点座標
	XMFLOAT3 target;	// 注視点座標
	XMFLOAT3 up;		// 上方向ベクトル
	//カメラの回転核
	float angle = 0.0f;

public:

	// 頂点データ
	Vertex vertices[24] ;
	// インデックスデータ
	uint16_t indices[36] = {	
		0,1,2,	
		2,1,3,	
	
		6,5,4,
		5,6,7,

		8,9,10,
		10,9,11,

		14,13,12,
		13,14,15,

		16,17,18,
		18,17,19,

		22,21,20,
		21,22,23	
	};

public:	
	
	Triangle(Vertex vertices[]);
	Triangle();
	~Triangle();
	
	void Init(ID3D12Device* device);
	void Update(ID3D12Device* device, BYTE* keys);
	void Draw( ID3D12GraphicsCommandList* commandList);
};