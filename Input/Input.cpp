#include "Input.h"
#include<cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

/// <summary>
	/// ������
	/// </summary>
void Input::Initialize(HINSTANCE hInstance, HWND hwnd) {
	HRESULT result;

	// DirectInput�̏�����
	result = DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));
	// �L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));
	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);	//�W���`��
	assert(SUCCEEDED(result));
	//�@�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

/// <summary>
/// �X�V
/// </summary>
void Input::Update() {
	HRESULT result;

	// �O��̃L�[�ۑ�
	memcpy(keysPre, keys, sizeof(keys));

	//�L�[�{�[�h���̎擾�J�n
	result = keyboard->Acquire();
	//�S�L�[�̓��͏�Ԃ��擾����
	result = keyboard->GetDeviceState(sizeof(keys), keys);
}

/// <summary>
/// �L�[�̉������`�F�b�N
/// </summary>
bool Input::PushKey(BYTE keyNumber) {

	// �w��L�[�������Ă����true��Ԃ�
	if (keys[keyNumber]) {
		return true;
	}

	return false;
}

/// <summary>
/// �L�[�̃g���K�[���`�F�b�N
/// </summary>
bool Input::TriggerKey(BYTE keyNumber) {
	// �w��L�[�������Ă����true��Ԃ�
	if (keysPre[keyNumber]==0 &&keys[keyNumber]==1) {
		return true;
	}

	return false;
}