#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3Dオブジェクト解放
	delete homeOBJ;
	delete player;
	delete reticle;
	delete zango;
	for (int i = 1; i < 5; i++) {
		delete PopPos_[i];
	}

	//3Dモデル解放
	delete model;
	delete model2;
	delete reticleMD;
	delete zangoMD;
	delete eneMD;
	delete floor;

	//オーディオ解放
	audio->Finalize();
	delete audio;

}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, GameScene* gamescene) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(gamescene);


	gamescene_ = gamescene;
	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);
	//ビューの生成
	{
		view = new View();
	}
	//ビューの初期化
	{
		view->Initialize();
	}

	//スプライトの初期化
	{
		sprite->Initialize(spriteCommon);
		position.x = 400.0f;
		position.y = 0.0f;
		sprite->SetPozition(position);
		sprite->SetSize(XMFLOAT2{ 500.0f,281.0f });

		sprite1->Initialize(spriteCommon);
		sprite1->SetPozition(position1);
		sprite1->SetSize(XMFLOAT2{ 200.0f,112.0f });

		sprite2->Initialize(spriteCommon);
		position2.x = 900.0f;
		sprite2->SetPozition(position2);
		sprite2->SetSize(XMFLOAT2{ 300.0f,170.0f });

		titleSP->Initialize(spriteCommon);
		titleSP->SetPozition(titlePOS);
		titleSP->SetSize(XMFLOAT2{ WinApp::window_width,WinApp::window_height });
		endSP->Initialize(spriteCommon);
		endSP->SetPozition(endPOS);
		endSP->SetSize(XMFLOAT2{ WinApp::window_width,WinApp::window_height });

		retSP->Initialize(spriteCommon);
		retPOS = XMFLOAT2{ (WinApp::window_width - 100) / 2,(WinApp::window_height - 100) / 2 };
		retSP->SetPozition(retPOS);
		//retSP->SetSize(XMFLOAT2{ WinApp::window_width / 5,WinApp::window_height / 10 });
	}
	//スプライトの画像指定
	{
		spriteCommon->LoadTexture(0, "mario.jpg");
		sprite->SetTextureIndex(0);
		spriteCommon->LoadTexture(1, "inu.png");
		sprite1->SetTextureIndex(1);
		spriteCommon->LoadTexture(2, "reimu.png");
		sprite2->SetTextureIndex(2);
		spriteCommon->LoadTexture(3, "Title.png");
		titleSP->SetTextureIndex(3);
		spriteCommon->LoadTexture(4, "end.png");
		endSP->SetTextureIndex(4);
		spriteCommon->LoadTexture(5, "2Dret.png");
		retSP->SetTextureIndex(5);
	}
	// OBJからモデルデータを読み込み
	{
		model = Model::LoadFromOBJ("cube");
		model2 = Model::LoadFromOBJ("cube");
		reticleMD = Model::LoadFromOBJ("cube");
		zangoMD = Model::LoadFromOBJ("zango");
		eneMD = Model::LoadFromOBJ("ene");
		floorMD = Model::LoadFromOBJ("floor");
	}
	//3Dオブジェクト生成
	{
		homeOBJ = Object3d::Create();
		player = Object3d::Create();
		reticle = Object3d::Create();
		zango = Object3d::Create();
		floor = Object3d::Create();
		for (int i = 0; i < 5; i++) {
			PopPos_[i] = Object3d::Create();
		}
	}
	// 親子設定
	{
		player->SetParent(homeOBJ);
		for (int i = 1; i < 5; i++) {
			PopPos_[i]->SetParent(PopPos_[0]);
		}
	}
	// オブジェクトにモデルを紐づける
	{
		homeOBJ->SetModel(model);
		player->SetModel(model2);
		reticle->SetModel(reticleMD);
		zango->SetModel(zangoMD);
		floor->SetModel(floorMD);
		for (int i = 0; i < 5; i++) {
			PopPos_[i]->SetModel(reticleMD);
		}
	}
	//3Dオブジェクトの位置を指定
	{
		player->wtf.position = Vector3{ 0,1,15 };
		homeOBJ->wtf.position = Vector3{ 0,1,0 };
		floor->wtf.position = Vector3{ 0,-1,0 };

		PopPos_[1]->wtf.position = Vector3{ 0,0,150 };
		PopPos_[2]->wtf.position = Vector3{ 0,0,-150 };
		PopPos_[3]->wtf.position = Vector3{ 150,0,0 };
		PopPos_[4]->wtf.position = Vector3{ -150,0,0 };
	}
	{
		homeOBJ->wtf.scale = Vector3{ 3,3,3 };
		zango->wtf.scale = (Vector3{ 5, 3.5f, 5 });
	}
	//3Dオブジェクトを一回アップデート
	{


		ai = Vector3{ 0,1,45 };
		view->focalLengs = 90;

		view->eye = { ai.x,ai.y,ai.z };
		view->target = Vector3{ 0,1,80 };


		homeOBJ->Update(view);
		player->Update(view);
		zango->Update(view);
		floor->Update(view);
		for (int i = 0; i < 5; i++) {
			PopPos_[i]->Update(view);
		}

	}


	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("gate.wav");
	audio->LoadWave("0303.wav");


}


void GameScene::Update() {
	srand((unsigned)time(nullptr));
	int popRand = rand() % 4 + 1;

	switch (scene)
	{
	case 0:// title
		if (input->TriggerKey(DIK_SPACE)) {
			scene = 2;
		}
		// カメラ関係
		startCount = 0;
		nowCount = 0;
		elapsedCount = 0;
		elapsedTime = 0;
		maxTime = 50.0f;
		timeRate;
		maxTimeRate;
		cameraState = 0;
		// 敵
		popTime = 0;
		coolTime = 0;
		killCounter;
		popCount = 0;
		wave = 0;
		waitTimer = 250;



		break;

	case 3: // end
		if (input->TriggerKey(DIK_SPACE)) {
			scene = 0;
		}
		break;

	case 1:// info()	

		// カメラのプログラム持ってきただけ
	{
		//// カメラ移動更新処理
		// スタート地点	：start
		// エンド地点		：end
		// 経過時間		：elapsedTime [s]
		// 移動完了の率（経過時間/全体時間） ：timeRate (%)
		nowCount++;

		if (input->TriggerKey(DIK_R)) {
			startCount = nowCount;
			switch (cameraState)
			{
			case 0:
				cameraState = 1;
				break;
			case 2:
				scene = 2;
				// カメラ関係
				startCount = 0;
				nowCount = 0;
				elapsedCount = 0;
				elapsedTime = 0;
				maxTime = 50.0f;
				timeRate;
				maxTimeRate;
				cameraState = 2;
				break;
			}
		}


		elapsedCount = nowCount - startCount;
		elapsedTime = static_cast<float> (elapsedCount) / 1.0f;
		timeRate = min(elapsedTime / maxTime, 1.0f);

		if (cameraState == 1) {
			Vector3 A, B, C, AB, AC, FL, FLst, FLen;
			p0 = Affin::GetWorldTrans(player->wtf.matWorld);
			p1 = Vector3(0, 0, 0);
			p2 = Vector3(0, 150, 0);
			p3 = Vector3(0, 150, 1);
			A = Vector3::lerp(p0, p1, timeRate);
			B = Vector3::lerp(p1, p2, timeRate);
			C = Vector3::lerp(p1, p3, timeRate);
			AB = Vector3::lerp(A, B, timeRate);
			AC = Vector3::lerp(A, C, timeRate - 0.1);
			FLst = Vector3(90, 0, 0);
			FLen = Vector3(20, 0, 1);
			FL = Vector3::lerp(FLst, FLen, timeRate - 0.1);
			view->focalLengs = FL.x;

			view->eye = AB;
			view->target = AC;
			if (timeRate >= 1.0) {
				cameraState = 2;
			}
		}
		if (cameraState == 3) {
			Vector3 A, B, C, AB, AC, FL, FLst, FLen;
			p0 = Vector3(0, 150, 0);
			p1 = Vector3(0, 0, 0);
			p2 = Affin::GetWorldTrans(player->wtf.matWorld);
			p3 = Affin::GetWorldTrans(reticle->wtf.matWorld);
			A = Vector3::lerp(p0, p1, timeRate);
			B = Vector3::lerp(p1, p2, timeRate);
			C = Vector3::lerp(p1, p3, timeRate);
			AB = Vector3::lerp(A, B, timeRate - 0.01);
			AC = Vector3::lerp(A, C, timeRate);
			FLst = Vector3(20, 0, 0);
			FLen = Vector3(90, 0, 1);
			FL = Vector3::lerp(FLst, FLen, timeRate - 0.1);
			view->focalLengs = FL.x;

			view->eye = AB;
			view->target = AC;
			if (timeRate >= 1.0) {
				cameraState = 0;
			}
		}
		if (cameraState == 0) {
			ai = Affin::GetWorldTrans(player->wtf.matWorld);
			view->focalLengs = 90;

			view->eye = { ai.x,ai.y,ai.z };
			view->target = Affin::GetWorldTrans(reticle->wtf.matWorld);
		}
		else if (cameraState == 2) {
			view->focalLengs = 20;

			view->eye = Vector3(0, 150, 0);
			view->target = Affin::GetWorldTrans(player->wtf.matWorld);

		}

	}
	homeOBJ->Update(view);
	player->Update(view);
	zango->Update(view);
	floor->Update(view);
	for (int i = 0; i < 5; i++) {
		PopPos_[i]->Update(view);
	}

	break;



	case 2: // game

		// オブジェクト移動
		if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
		{
			// 現在の座標を取得
			Vector3 rotate = homeOBJ->wtf.rotation;

			// 移動後の座標を計算
			/*if (input->PushKey(DIK_UP)) { rotate.x += 0.5f; }
			else if (input->PushKey(DIK_DOWN)) { rotate.x -= 0.5f; }*/
			if (input->PushKey(DIK_RIGHT)) { rotate.y += 1.0f; }
			else if (input->PushKey(DIK_LEFT)) { rotate.y -= 1.0f; }

			// 座標の変更を反映

			homeOBJ->wtf.rotation = rotate;
		}
		homeOBJ->Update(view);
		player->Update(view);
		zango->Update(view);
		floor->Update(view);
		//敵ポップ

		for (int i = 0; i < 5; i++) {
			PopPos_[i]->Update(view);
		}

		Reticle3D();

		//当たり判定
		{
			Vector3 a = player->wtf.position;
			Vector3 b = homeOBJ->wtf.position;
			float xyz = std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f) + std::pow(a.z - b.z, 2.0f);
			float lenR = std::pow(1.0f + 1.0f, 2.0f);
			if (xyz <= lenR) {
				ischackFlag = 1;
			}
		}
		//当たり判定
		{
			Vector3 a = player->wtf.position;
			Vector3 b = homeOBJ->wtf.position;
			float xyz = std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f) + std::pow(a.z - b.z, 2.0f);
			float lenR = std::pow(1.0f + 1.0f, 2.0f);
			if (xyz <= lenR) {
				ischackFlag = 1;
			}
		}


		// カメラのプログラム持ってきただけ
		{
			//// カメラ移動更新処理
			// スタート地点	：start
			// エンド地点		：end
			// 経過時間		：elapsedTime [s]
			// 移動完了の率（経過時間/全体時間） ：timeRate (%)
			nowCount++;

			if (input->TriggerKey(DIK_R)) {
				startCount = nowCount;
				switch (cameraState)
				{
				case 0:
					cameraState = 1;
					break;
				case 2:
					cameraState = 3;
					break;
				}
			}

			elapsedCount = nowCount - startCount;
			elapsedTime = static_cast<float> (elapsedCount) / 1.0f;
			timeRate = min(elapsedTime / maxTime, 1.0f);

			if (cameraState == 1) {
				Vector3 A, B, C, AB, AC, FL, FLst, FLen;
				p0 = Affin::GetWorldTrans(player->wtf.matWorld);
				p1 = Vector3(0, 0, 0);
				p2 = Vector3(0, 150, 0);
				p3 = Vector3(0, 150, 1);
				A = Vector3::lerp(p0, p1, timeRate);
				B = Vector3::lerp(p1, p2, timeRate);
				C = Vector3::lerp(p1, p3, timeRate);
				AB = Vector3::lerp(A, B, timeRate);
				AC = Vector3::lerp(A, C, timeRate - 0.1);
				FLst = Vector3(90, 0, 0);
				FLen = Vector3(20, 0, 1);
				FL = Vector3::lerp(FLst, FLen, timeRate - 0.1);
				view->focalLengs = FL.x;

				view->eye = AB;
				view->target = AC;
				if (timeRate >= 1.0) {
					cameraState = 2;
				}
			}
			if (cameraState == 3) {
				Vector3 A, B, C, AB, AC, FL, FLst, FLen;
				p0 = Vector3(0, 150, 0);
				p1 = Vector3(0, 0, 0);
				p2 = Affin::GetWorldTrans(player->wtf.matWorld);
				p3 = Affin::GetWorldTrans(reticle->wtf.matWorld);
				A = Vector3::lerp(p0, p1, timeRate);
				B = Vector3::lerp(p1, p2, timeRate);
				C = Vector3::lerp(p1, p3, timeRate);
				AB = Vector3::lerp(A, B, timeRate - 0.01);
				AC = Vector3::lerp(A, C, timeRate);
				FLst = Vector3(20, 0, 0);
				FLen = Vector3(90, 0, 1);
				FL = Vector3::lerp(FLst, FLen, timeRate - 0.1);
				view->focalLengs = FL.x;

				view->eye = AB;
				view->target = AC;
				if (timeRate >= 1.0) {
					cameraState = 0;
				}
			}




			if (cameraState == 0) {
				ai = Affin::GetWorldTrans(player->wtf.matWorld);
				view->focalLengs = 90;

				view->eye = { ai.x,ai.y,ai.z };
				view->target = Affin::GetWorldTrans(reticle->wtf.matWorld);
			}
			else if (cameraState == 2) {
				view->focalLengs = 20;

				view->eye = Vector3(0, 150, 0);
				view->target = Affin::GetWorldTrans(player->wtf.matWorld);

			}
		}


		// リセット
		if (input->PushKey(DIK_R)) {
			ischackFlag = 0;
		}
		//音声再生
		if (soundCheckFlag == 0) {
			//音声再生
			audio->PlayWave("0303.wav");
			soundCheckFlag = 1;
		}
		if (input->TriggerKey(DIK_SPACE)) {

		}

		break;

	}


}

void GameScene::Draw() {


	switch (scene)
	{
	case 0:// title
		titleSP->Draw();
		break;
	case 3:// end
		endSP->Draw();
		break;
	case 1:// 
	case 2: // game
		sprite->Draw();

		if (ischackFlag == 0) {
			sprite1->Draw();
		}
		else {}

		sprite2->Draw();

		//3Dオブジェクト描画前処理
		Object3d::PreDraw(dxCommon->GetCommandList());
		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加できる
		/// <summary>

		//3Dオブジェクトの描画
		homeOBJ->Draw();
		player->Draw();
		//reticle->Draw();
		zango->Draw();
		floor->Draw();

		for (int i = 1; i < _countof(PopPos_); i++) {
			PopPos_[i]->Draw();
		}

		//3Dオブジェクト描画後処理
		Object3d::PostDraw();

		// 前景スプライト

		//retSP->Draw();
		break;
	}


}

void GameScene::Reticle3D() {
	//自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offset = { 0.0f, 0, -1.0f };
	//自機のワールド行列の回転を反映
	offset = Affin::VecMat(offset, player->wtf.matWorld);
	//ベクトルの長さを整える
	//offset.nomalize();
	float len = sqrt(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
	if (len != 0) {
		offset /= len;
	}
	offset *= -100;
	reticle->wtf.position = offset;
	reticle->wtf.scale = Vector3(0.5f, 0.5f, 0.5f);
	reticle->wtf.matWorld = Affin::matScale(reticle->wtf.scale);
	reticle->wtf.matWorld = Affin::matTrans(reticle->wtf.position);

	reticle->Update(view);

}
