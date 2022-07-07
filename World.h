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

#define DIRECTINPUT_VERSION		0x0800		//DirectInput�̃o�[�W�����w��

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace DirectX;

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