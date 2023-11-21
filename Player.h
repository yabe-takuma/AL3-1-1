#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"Input.h"
#include"BaseCharacter.h"
class Player : public BaseCharacter {
public:
	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(ViewProjection& viewProjection) override;

	void SetViewProjection(const ViewProjection* viewProjection);
	//浮遊ギミック初期化
	void InitializeFloatingGimmick();
	//浮遊ギミック更新
	void UpdateFloatingGimmick();

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

	//3Dモデル
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;

	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	float floatingParameterHead_ = 0.0f;

};
