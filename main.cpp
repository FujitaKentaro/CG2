#include "World.h"
#include "Input/Input.h"
#include "base/WinApp.h"
#include "base/DirectXCommon.h"
#include "object/Triangle.h"




//Windousアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#pragma region 基盤システムの初期化
	// ポインタ
	Input* input = nullptr;
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;

	// NEW
	input = new Input;
	winApp = new WinApp;
	dxCommon = new DirectXCommon;


#pragma region WindousAPI初期化処理

	winApp->Intialize();

#pragma endregion WindousAPI初期化処理

	//DirectX初期化処理　ここから

#pragma region DirectX初期化処理

#ifdef _DEBUG

	//デバックレイヤーをオンに
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif // _DEBUG

//#pragma endregion DirectX初期化処理

	dxCommon->Initialize(winApp);


	input->Initialize(winApp);
	//DirectX初期化処理　ここまで
#pragma endregion 基盤システムの初期化

	//描画初期化処理　ここから
#pragma region 描画初期化処理

	//頂点
	Vertex vertex[] = {
		// 前
		{{-5.0f,-5.0f, -5.0f},{}, {0.0f, 1.0f}/* 左下*/},
		{{-5.0f, 5.0f, -5.0f},{}, {0.0f, 0.0f}/* 左上*/},
		{{ 5.0f,-5.0f, -5.0f},{}, {1.0f, 1.0f}/* 右下*/},
		{{ 5.0f, 5.0f, -5.0f},{}, {1.0f, 0.0f}/* 右上*/},
		// 後ろ
		{{-5.0f,-5.0f,  5.0f},{}, {0.0f, 1.0f}/* 左下*/},
		{{-5.0f, 5.0f,  5.0f},{}, {0.0f, 0.0f}/* 左上*/},
		{{ 5.0f,-5.0f,  5.0f},{}, {1.0f, 1.0f}/* 右下*/},
		{{ 5.0f, 5.0f,  5.0f},{}, {1.0f, 0.0f}/* 右上*/},
		// 左
		{{-5.0f,-5.0f, -5.0f},{}, {1.0f, 1.0f}/* 左下*/},
		{{-5.0f,-5.0f,  5.0f},{}, {0.0f, 1.0f}/* 左上*/},
		{{-5.0f, 5.0f, -5.0f},{}, {1.0f, 0.0f}/* 右下*/},
		{{-5.0f, 5.0f,  5.0f},{}, {0.0f, 0.0f}/* 右上*/},
		// 右
		{{ 5.0f,-5.0f, -5.0f},{}, {1.0f, 1.0f}/* 左下*/},
		{{ 5.0f,-5.0f,  5.0f},{}, {0.0f, 1.0f}/* 左上*/},
		{{ 5.0f, 5.0f, -5.0f},{}, {1.0f, 0.0f}/* 右下*/},
		{{ 5.0f, 5.0f,  5.0f},{}, {0.0f, 0.0f}/* 右上*/},
		// 下
		{{-5.0f, 5.0f, -5.0f},{}, {0.0f, 1.0f}/* 左下*/},
		{{-5.0f, 5.0f,  5.0f},{}, {0.0f, 0.0f}/* 左上*/},
		{{ 5.0f, 5.0f, -5.0f},{}, {1.0f, 1.0f}/* 右下*/},
		{{ 5.0f, 5.0f,  5.0f},{}, {1.0f, 0.0f}/* 右上*/},
		// 上
		{{-5.0f,-5.0f, -5.0f},{}, {0.0f, 1.0f}/* 左下*/},
		{{-5.0f,-5.0f,  5.0f},{}, {0.0f, 0.0f}/* 左上*/},
		{{ 5.0f,-5.0f, -5.0f},{}, {1.0f, 1.0f}/* 右下*/},
		{{ 5.0f,-5.0f,  5.0f},{}, {1.0f, 0.0f}/* 右上*/},

	};



	//三角形生成--箱
	Triangle* triangle;

	triangle = new Triangle(vertex);

	triangle->Init(dxCommon->GetDevice());


#pragma endregion 描画初期化処理
	//描画初期化処理　ここまで


	//ゲームループ
	while (true) {

#pragma region ウィンドウメッセージ処理

		//メッセージがある？
		if (winApp->ProcessMessage()) {
			break;
		}
#pragma endregion ウィンドウメッセージ処理

#pragma region キーボード情報の取得

		input->Update();

#pragma endregion キーボード情報の取得

		//DirectX毎フレーム処理　ここから
#pragma region DirectX毎フレーム処理
		// 更新処理




		triangle->Update(dxCommon->GetDevice(), input);

#pragma endregion DirectX毎フレーム処理
		//DirectX毎フレーム処理　ここまで

		//---------------------------------------------------

#pragma region 毎フレーム描画処理
		// 4.描画コマンドここから
		/// 
		///	描画前処理
		/// 
		dxCommon->PreDraw();


		triangle->Draw(dxCommon->GetCommandList());



		/// 
		///	描画後処理
		/// 
		dxCommon->PostDraw();
#pragma endregion 毎フレーム描画処理

	}
	// ウィンドウクラスを登録解除
	winApp->Finalize();

	delete input;
	delete dxCommon;
	delete triangle;
	winApp->Finalize();
	delete winApp;
	


	return 0;
}