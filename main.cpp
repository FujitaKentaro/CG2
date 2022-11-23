#include "World.h"
#include "Input/Input.h"
#include "base/WinApp.h"
#include "base/DirectXCommon.h"
#include "object/Triangle.h"




//Windous�A�v���ł̃G���g���[�|�C���g�imain�֐��j
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#pragma region ��ՃV�X�e���̏�����
	// �|�C���^
	Input* input = nullptr;
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;

	// NEW
	input = new Input;
	winApp = new WinApp;
	dxCommon = new DirectXCommon;


#pragma region WindousAPI����������

	winApp->Intialize();

#pragma endregion WindousAPI����������

	//DirectX�����������@��������

#pragma region DirectX����������

#ifdef _DEBUG

	//�f�o�b�N���C���[���I����
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif // _DEBUG

//#pragma endregion DirectX����������

	dxCommon->Initialize(winApp);


	input->Initialize(winApp);
	//DirectX�����������@�����܂�
#pragma endregion ��ՃV�X�e���̏�����

	//�`�揉���������@��������
#pragma region �`�揉��������

	//���_
	Vertex vertex[] = {
		// �O
		{{-5.0f,-5.0f, -5.0f},{}, {0.0f, 1.0f}/* ����*/},
		{{-5.0f, 5.0f, -5.0f},{}, {0.0f, 0.0f}/* ����*/},
		{{ 5.0f,-5.0f, -5.0f},{}, {1.0f, 1.0f}/* �E��*/},
		{{ 5.0f, 5.0f, -5.0f},{}, {1.0f, 0.0f}/* �E��*/},
		// ���
		{{-5.0f,-5.0f,  5.0f},{}, {0.0f, 1.0f}/* ����*/},
		{{-5.0f, 5.0f,  5.0f},{}, {0.0f, 0.0f}/* ����*/},
		{{ 5.0f,-5.0f,  5.0f},{}, {1.0f, 1.0f}/* �E��*/},
		{{ 5.0f, 5.0f,  5.0f},{}, {1.0f, 0.0f}/* �E��*/},
		// ��
		{{-5.0f,-5.0f, -5.0f},{}, {1.0f, 1.0f}/* ����*/},
		{{-5.0f,-5.0f,  5.0f},{}, {0.0f, 1.0f}/* ����*/},
		{{-5.0f, 5.0f, -5.0f},{}, {1.0f, 0.0f}/* �E��*/},
		{{-5.0f, 5.0f,  5.0f},{}, {0.0f, 0.0f}/* �E��*/},
		// �E
		{{ 5.0f,-5.0f, -5.0f},{}, {1.0f, 1.0f}/* ����*/},
		{{ 5.0f,-5.0f,  5.0f},{}, {0.0f, 1.0f}/* ����*/},
		{{ 5.0f, 5.0f, -5.0f},{}, {1.0f, 0.0f}/* �E��*/},
		{{ 5.0f, 5.0f,  5.0f},{}, {0.0f, 0.0f}/* �E��*/},
		// ��
		{{-5.0f, 5.0f, -5.0f},{}, {0.0f, 1.0f}/* ����*/},
		{{-5.0f, 5.0f,  5.0f},{}, {0.0f, 0.0f}/* ����*/},
		{{ 5.0f, 5.0f, -5.0f},{}, {1.0f, 1.0f}/* �E��*/},
		{{ 5.0f, 5.0f,  5.0f},{}, {1.0f, 0.0f}/* �E��*/},
		// ��
		{{-5.0f,-5.0f, -5.0f},{}, {0.0f, 1.0f}/* ����*/},
		{{-5.0f,-5.0f,  5.0f},{}, {0.0f, 0.0f}/* ����*/},
		{{ 5.0f,-5.0f, -5.0f},{}, {1.0f, 1.0f}/* �E��*/},
		{{ 5.0f,-5.0f,  5.0f},{}, {1.0f, 0.0f}/* �E��*/},

	};



	//�O�p�`����--��
	Triangle* triangle;

	triangle = new Triangle(vertex);

	triangle->Init(dxCommon->GetDevice());


#pragma endregion �`�揉��������
	//�`�揉���������@�����܂�


	//�Q�[�����[�v
	while (true) {

#pragma region �E�B���h�E���b�Z�[�W����

		//���b�Z�[�W������H
		if (winApp->ProcessMessage()) {
			break;
		}
#pragma endregion �E�B���h�E���b�Z�[�W����

#pragma region �L�[�{�[�h���̎擾

		input->Update();

#pragma endregion �L�[�{�[�h���̎擾

		//DirectX���t���[�������@��������
#pragma region DirectX���t���[������
		// �X�V����




		triangle->Update(dxCommon->GetDevice(), input);

#pragma endregion DirectX���t���[������
		//DirectX���t���[�������@�����܂�

		//---------------------------------------------------

#pragma region ���t���[���`�揈��
		// 4.�`��R�}���h��������
		/// 
		///	�`��O����
		/// 
		dxCommon->PreDraw();


		triangle->Draw(dxCommon->GetCommandList());



		/// 
		///	�`��㏈��
		/// 
		dxCommon->PostDraw();
#pragma endregion ���t���[���`�揈��

	}
	// �E�B���h�E�N���X��o�^����
	winApp->Finalize();

	delete input;
	delete dxCommon;
	delete triangle;
	winApp->Finalize();
	delete winApp;
	


	return 0;
}