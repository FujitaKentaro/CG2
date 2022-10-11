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
	void Initialize(HINSTANCE hInstance, HWND hwnd);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name="keyNumber">キー番号（DIK_0 等）</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);
	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// <param name="keyNumber">キー番号（DIK_0 等）</param>
	/// <returns>トリガーか</returns>
	bool TriggerKey(BYTE keyNumber);

public:


	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	// キーボードデバイスの生成
	ComPtr <IDirectInputDevice8> keyboard = nullptr;
	// DirectInputの初期化
	ComPtr<IDirectInput8> directInput = nullptr;
	
	BYTE keys[256] = {};
	BYTE keysPre[256] = {};
};

