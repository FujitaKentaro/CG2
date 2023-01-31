#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string.h>
#include "Model.h"


#include "math/Vector3.h"
#include "math/Matrix4.h"
#include "math/Affin.h"

#include "Trans.h"
#include "View.h"

//// �萔�o�b�t�@�p�f�[�^�\����
//struct ViewState
//{
//	XMFLOAT3 eye;
//	XMFLOAT3 target;
//	XMFLOAT3 up;
//
//	XMMATRIX view;       // ���[���h �� �r���[�ϊ��s��
//	XMMATRIX projection; // �r���[ �� �v���W�F�N�V�����ϊ��s��
//};

/// <summary>
/// 3D�I�u�W�F�N�g
/// </summary>
class Object3d
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	/*using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;*/



	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB0
	{
		//XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
	};



private: // �萔
	static const int division = 50;					// ������
	static const float radius;				// ��ʂ̔��a
	static const float prizmHeight;			// ���̍���
	static const int planeCount = division * 2 + division * 2;		// �ʂ̐�
	static const int vertexCount = planeCount * 3;		// ���_��

public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

	/*/// <summary>
	/// ���_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	static const Vector3& GetEye() { return eye; }

	/// <summary>
	/// ���_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	static void SetEye(Vector3 eye);

	/// <summary>
	/// �����_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	static const Vector3& GetTarget() { return target; }

	/// <summary>
	/// �����_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	static void SetTarget(Vector3 target);*/

	/// <summary>
	/// �x�N�g���ɂ��ړ�
	/// </summary>
	/// <param name="move">�ړ���</param>
	//static void CameraMoveVector(Vector3 move);


	/*static const XMFLOAT3& GetEye() { return eye; }

	static void SetEye(XMFLOAT3 eye);

	static const XMFLOAT3& GetTarget() { return target; }

	static void SetTarget(XMFLOAT3 target);*/

	static float FieldOfViewY(float focalLengs, float sensor);


private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;

	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;


	//// �r���[�s��
	//static Matrix4 matView;
	//// �ˉe�s��
	//static Matrix4 matProjection;
	//// ���_���W
	//static Vector3 eye;
	//// �����_���W
	//static Vector3 target;
	//// ������x�N�g��
	//static Vector3 up;

	//static Matrix4 viewProjectionMatrix;
	//static Matrix4 viewMatrixInv;

	// �r���[�s��
	static XMMATRIX matView;
	// �ˉe�s��
	static XMMATRIX matProjection;
	// ���_���W
	static XMFLOAT3 eye;
	// �����_���W
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;

private:// �ÓI�����o�֐�

	/// <summary>
	/// �J����������
	/// </summary>
	/// <param name="window_width">��ʉ���</param>
	/// <param name="window_height">��ʏc��</param>
	static void InitializeCamera(int window_width, int window_height);

	/// <summary>
	/// �O���t�B�b�N�p�C�v���C������
	/// </summary>
	/// <returns>����</returns>
	static void InitializeGraphicsPipeline();

	/// <summary>
	/// �r���[�s����X�V
	/// </summary>
	static void UpdateViewMatrix();

public: // �����o�֐�

	bool Initialize();
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	void Update(View* view);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	Object3d* GetParent() const { return parent; }

	void SetParent(Object3d* parent) { this->parent = parent; }

	//setter
	void SetModel(Model* model) { this->model = model; }

	static void MakePerspectiveL(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix);

	static void MakeLookL(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4& mat);

	static Matrix4 MakeInverse(const Matrix4* mat);



private: // �����o�ϐ�
public:
	ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@

	// �F
	XMFLOAT4 color = { 1,1,1,1 };

	// �e�I�u�W�F�N�g
	Object3d* parent = nullptr;
	//���f��
	Model* model = nullptr;
	Trans wtf;

	static float win_wi, win_hi;
public:
	
	static float focalLengs;

};