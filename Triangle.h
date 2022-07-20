#pragma once
#include "World.h"


class Triangle
{
public:
	// ���U���g
	HRESULT result;
	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};


	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v�����X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState;
	// �萔�o�b�t�@
	ComPtr <ID3D12Resource> constBuffMaterial;
	

	//3D�I�u�W�F�N�g�̐�
	static const size_t kObjectCount = 50;
	// 3D�I�u�W�F�N�g�̔z��
	Object3d object3ds[kObjectCount];

	// �萔�o�b�t�@�̐���0
	/*ID3D12Resource* constBuffTransform0 = nullptr;
	ConstBufferDataTransform* constMapTransform0 = nullptr;
	// �萔�o�b�t�@�̐���1
	ID3D12Resource* constBuffTransform1 = nullptr;
	ConstBufferDataTransform* constMapTransform1 = nullptr;*/


	//GPU��̃o�b�t�@�ɑΉ��������z������
	Vertex* vertMap = nullptr;
	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ID3D12DescriptorHeap* srvHeap;
	// 
	UINT incrementSize;

	// ���[���h�ϊ��s��
	XMMATRIX matWorld;
	XMMATRIX matWorld1;

	//���W
	XMFLOAT3 scale	 = { 1.0f,1.0f,1.0f };
	XMFLOAT3 position = { 0.0f,0.0f,0.0f };
	XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };
	
	//���W1
	XMFLOAT3 scale1 = { 1.0f,1.0f,1.0f };
	XMFLOAT3 position1 = { 0.0f,0.0f,0.0f };
	XMFLOAT3 rotation1 = { 0.0f,0.0f,0.0f };
	

	// �ˉe�ϊ��s��̌v�Z
	XMMATRIX matProjection;

	// �r���[�ϊ��s��
	XMMATRIX matView;
	XMFLOAT3 eye;	// ���_���W
	XMFLOAT3 target;	// �����_���W
	XMFLOAT3 up;		// ������x�N�g��
	//�J�����̉�]�j
	float angle = 0.0f;

public:

	// ���_�f�[�^
	Vertex vertices[24] ;
	// �C���f�b�N�X�f�[�^
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