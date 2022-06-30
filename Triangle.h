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
	ID3D12RootSignature* rootSignature = nullptr;
	// パイプランステートの生成
	ID3D12PipelineState* pipelineState = nullptr;
	// 定数バッファ
	ID3D12Resource* constBuffMaterial = nullptr;
	ID3D12Resource* constBuffTransform = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;

	//GPU上のバッファに対応した仮想メモリ
	Vertex* vertMap = nullptr;
	// 設定を元にSRV用デスクリプタヒープを生成
	ID3D12DescriptorHeap* srvHeap = nullptr;

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
	Vertex vertices[4] ;
	// インデックスデータ
	unsigned short indices[6]={0,1,2,1,2,3};

public:	
	
	Triangle(Vertex vertices[]);
	Triangle();
	~Triangle();
	
	void Init(ID3D12Device* device);
	void Update(ID3D12Device* device, BYTE* keys);
	void Draw( ID3D12GraphicsCommandList* commandList);
};