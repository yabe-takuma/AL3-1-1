#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Player.h"
#include<memory>
#include"Skydome.h"
#include"Ground.h"
#include"DebugCamera.h"
#include"FollowCamera.h"
#include"Enemy.h"
#include"Wall.h"
#include"WeakEnemy.h"
#include<list>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	std::unique_ptr<Model> model_;

	uint32_t textureHandle_ = 0u;

	ViewProjection viewprojection_;

	//自キャラ
	Player* player_ = nullptr;
	

	std::unique_ptr<Model> modelskydome_;

	std::unique_ptr<Skydome> skydome_;

	std::unique_ptr<Ground> ground_;

	std::unique_ptr<Model> modelground_;

	std::unique_ptr<FollowCamera> followcamera_;

	std::unique_ptr<Enemy> enemy_;

	std::unique_ptr<Wall> wall_;
	std::unique_ptr<Model> modelwall_;

   std::list<std::unique_ptr<WeakEnemy>> weakenemys_;

	//デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	// デバッグカメラ有効
	bool isDebugCameraAcctive_ = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
