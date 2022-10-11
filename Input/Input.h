#pragma once
#include <wrl.h>
#include <Windows.h>
#include <dinput.h>

#define DIRECTINPUT_VERSION	0x0800

class Input
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(HINSTANCE hInstance,HWND hwnd);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

public:


	template<class T>using ComPtr= Microsoft::WRL::ComPtr<T>;
private:
	// キーボードデバイスの生成
	ComPtr <IDirectInputDevice8> keyboard = nullptr;
};

