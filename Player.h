#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"Input.h"
class Player {
public:
	void Initialize(Model* model,uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void SetViewProjection(const ViewProjection* viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_=nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//キーボード入力
	Input* input_ = nullptr;

	//ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	//カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

};
