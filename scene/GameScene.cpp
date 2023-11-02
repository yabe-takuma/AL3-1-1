#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { }

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	model_.reset(Model::CreateFromOBJ("Player",true));

	textureHandle_ = TextureManager::Load("sample.png");

	viewprojection_.Initialize();

	//自キャラの生成
	player_ = std::make_unique<Player>();
	//自キャラの初期化
	player_->Initialize(model_.get(),textureHandle_);
	//天球の生成
	skydome_ = std::make_unique<Skydome>();
	modelskydome_.reset(Model::CreateFromOBJ("skydome", true));
	skydome_->Initialize(modelskydome_.get());
	//フィールドの生成
	ground_ = std::make_unique<Ground>();
	modelground_.reset(Model::CreateFromOBJ("ground", true));
	ground_->Initialize(modelground_.get());

	followcamera_ = std::make_unique<FollowCamera>();
	followcamera_->Initialize();
	followcamera_->SetTarget(&player_->GetWorldTransform());

	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);

	player_->SetViewProjection(&followcamera_->GetViewProjection());

}

void GameScene::Update() { 
	
	if (player_ != nullptr) {

		player_->Update();
	}
	if (skydome_ != nullptr) {
		skydome_->Update();
	}
	if (ground_ != nullptr) {
		ground_->Update();
	}
	// 追従カメラの更新
	if (followcamera_ != nullptr) {
		followcamera_->Update();
	}
	

	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraAcctive_ = true;
	}
	if (isDebugCameraAcctive_) {

		viewprojection_.matView = debugCamera_->GetViewProjection().matView;
		viewprojection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewprojection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewprojection_.UpdateMatrix();
	}
#endif

	viewprojection_.matProjection = followcamera_->GetViewProjection().matProjection;
	viewprojection_.matView = followcamera_->GetViewProjection().matView;

	viewprojection_.TransferMatrix();

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
	if (player_ != nullptr) {

		player_->Draw(viewprojection_);
	}
	if (skydome_ != nullptr) {
		skydome_->Draw(viewprojection_);
	}
	if (ground_ != nullptr){
	
		ground_->Draw(viewprojection_);
	}

	

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
