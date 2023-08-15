#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
}

void GameScene::Initialize() {

	

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");

	model_ = Model::Create();
	viewProjection_.Initialize();
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向の表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//// 敵の生成
	//Enemy* enemy_ = new Enemy();

	//// 敵の初期化
	//const float kEnemySpeed = -0.1f;
	//Vector3 velocity_ = {0, 0, kEnemySpeed};

	//Vector3 position = {0, 0, 0};

	//enemy_->Initialize(model_, position, velocity_);
	// 自キャラの生成
	player_ = new Player();
	player_->Initialize(model_, textureHandle_);
	EnemyGeneration();
	
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

}

void GameScene::EnemyGeneration() {
	// 敵の生成
	enemy_ = new Enemy();

	// 敵の初期化
	const float kEnemySpeed = 0.1f;
	Vector3 velocity_ = {0, 0, kEnemySpeed};

	Vector3 position = {0, 0, -10};

	enemy_->Initialize(model_, position, velocity_);


	
}

void GameScene::Update() {
	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraAcctive_ = true;
	}
	if (isDebugCameraAcctive_) {

		 viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		 viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		 // ビュープロジェクション行列の転送
		 viewProjection_.TransferMatrix();
	} else {
		 // ビュープロジェクション行列の更新と転送
		 viewProjection_.UpdateMatrix();
	}
#endif

	

player_->Update();

	if (enemy_ != nullptr) {
	     enemy_->Update();
	 }

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	if (enemy_ != nullptr) {
		 enemy_->Draw(viewProjection_);
	}

	player_->Draw(viewProjection_);

	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
