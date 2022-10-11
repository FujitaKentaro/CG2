#pragma once
#include <wrl.h>
#include <Windows.h>
#include <dinput.h>

#define DIRECTINPUT_VERSION	0x0800

class Input
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(HINSTANCE hInstance,HWND hwnd);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

public:


	template<class T>using ComPtr= Microsoft::WRL::ComPtr<T>;
private:
	// �L�[�{�[�h�f�o�C�X�̐���
	ComPtr <IDirectInputDevice8> keyboard = nullptr;
};

