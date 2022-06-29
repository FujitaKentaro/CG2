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
	ID3D12RootSignature* rootSignature = nullptr;
	// �p�C�v�����X�e�[�g�̐���
	ID3D12PipelineState* pipelineState = nullptr;
	// �萔�o�b�t�@
	ID3D12Resource* constBuffMaterial = nullptr;
	//ID3D12Resource* constBuffTransform = nullptr;
	//ConstBufferDataTransform* constMapTransform = nullptr;

	//GPU��̃o�b�t�@�ɑΉ��������z������
	Vertex* vertMap = nullptr;
	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ID3D12DescriptorHeap* srvHeap = nullptr;

public:

	// ���_�f�[�^
	Vertex vertices[3] ;
	// �C���f�b�N�X�f�[�^
	unsigned short indices[3]={0,1,2};

public:	
	
	Triangle(Vertex vertices[]);
	Triangle();
	~Triangle();
	
	void Init(ID3D12Device* device);
	void Update(ID3D12Device* device);
	void Draw( ID3D12GraphicsCommandList* commandList);
};