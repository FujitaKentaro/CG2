#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <vector>
#include <string>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <dinput.h>
#include <DirectXTex.h>
#include "math/Affin.h"
#include <wrl.h>

#define DIRECTINPUT_VERSION		0x0800		//DirectInput�̃o�[�W�����w��

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

// �~����
const float PI = 3.141592f;

//�E�B���h�E�T�C�Y
const int window_width = 1280;	//����
const int window_height = 720;	//�c��

// �萔�o�b�t�@�p�f�[�^�\���́i�}�e���A���j
struct ConstBufferDataMaterial {
	XMFLOAT4 color; // �F (RGBA)
};

// �萔�o�b�t�@�p�f�[�^�\���́i 3D�ϊ��s�� �j
struct ConstBufferDataTransform {
	XMMATRIX mat; // 3D�ϊ��s��
};

// ���_�p�\����
struct  Vertex
{
	XMFLOAT3 pos;	// xyz���W
	XMFLOAT3 normal;	// �@���x�N�g��
	XMFLOAT2 uv; 	// uv���W
};

// 3D�I�u�W�F�N�g�^
struct Object3d {
	// �萔�o�b�t�@ �i�s��p�j
	ComPtr <ID3D12Resource> constBuffTrnceform;
	// �萔�o�b�t�@�}�b�v �i�s��p�j
	ConstBufferDataTransform* constMapTransform = nullptr;

	// �A�t�B���ϊ����
	XMFLOAT3 scale = { 1,1,1 };
	XMFLOAT3 rotation = { 0,0,0 };
	XMFLOAT3 position = { 0,0,0 };

	//���[���h�ϊ��s��
	XMMATRIX matWorld ;
	// �e�I�u�W�F�N�g�ւ̃|�C���^
	Object3d* parent = nullptr;

};

