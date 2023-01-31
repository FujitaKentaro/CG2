#pragma once

#include "base/DirectXCommon.h"
#include <DirectXMath.h>
#include "input/Input.h"
#include "object/Object3d.h"
#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"
#include "Model.h"
#include "Audio.h"
#include <string>

#include "math/Matrix4.h"

#include "Trans.h"
#include "View.h"



/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // �ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input, GameScene* gamescene);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();


private: // �����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;


	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	Sprite* sprite = new Sprite();
	XMFLOAT2 position = sprite->GetPosition();

	Sprite* sprite1 = new Sprite();
	XMFLOAT2 position1 = sprite1->GetPosition();

	Sprite* sprite2 = new Sprite();
	XMFLOAT2 position2 = sprite2->GetPosition();

	Sprite* titleSP = new Sprite();
	XMFLOAT2 titlePOS = titleSP->GetPosition();
	Sprite* endSP = new Sprite();
	XMFLOAT2 endPOS = endSP->GetPosition();

	Sprite* retSP = new Sprite();
	XMFLOAT2 retPOS = retSP->GetPosition();

	int ischackFlag = 0;

	Object3d* homeOBJ = nullptr;
	Object3d* player = nullptr;
	Object3d* reticle = nullptr;
	Object3d* zango = nullptr;
	Object3d* floor = nullptr;
	Model* model = nullptr;
	Model* model2 = nullptr;
	Model* reticleMD = nullptr;
	Model* zangoMD = nullptr;
	Model* eneMD = nullptr;
	Model* floorMD = nullptr;


	int soundCheckFlag = 0;

	GameScene* gamescene_ = nullptr;

	// �J�����֌W

	View* view = nullptr;
	// ���Ԍv���ɕK�v�ȃf�[�^
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;
	float elapsedTime = 0;

	// ��ԂŎg���f�[�^
	// start -> end �� 5[��] �Ŋ���������
	Vector3 p0, p1, p2, p3;
	//Vector3 p0, p1, p2, p3;
	float maxTime = 50.0f;
	float timeRate;
	float maxTimeRate;
	int cameraState = 0;

	Vector3 ai;


	float KEyeSpeed = 0.0f;
	float addspeed = 0.0f;

	int scene = 0;


};

