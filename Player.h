#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"Input.h"
#include"Xinput.h"
#include"BaseCharacter.h"
class Player : public BaseCharacter {
public:
	void Initialize(Model* model,uint32_t textureHandle) override;

	void Update() override;

	void Draw(ViewProjection& viewProjection) override;

	void SetViewProjection(const ViewProjection* viewProjection);

	Vector3 GetWorldPosition();

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

	XINPUT_STATE joyState;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

};
