#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"Input.h"
#include"Xinput.h"
#include"BaseCharacter.h"
#include"ImGuiManager.h"
class Player : public BaseCharacter {

	// 振るまい
	enum class Behavior {
		kRoot,   // 通常攻撃
		kAttack, // 攻撃中
	};

public:
	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(ViewProjection& viewProjection) override;

	void SetViewProjection(const ViewProjection* viewProjection);

	// 通常行動更新
	void BehaviorRootUpdate();
	// 攻撃行動更新
	void BehaviorAttackUpdate();
	// 通常行動初期化
	void BehaviorRootInitialize();
	// 攻撃行動初期化
	void BeheviorAttackInitialize();

	Vector3 GetWorldPosition();

	const WorldTransform& GetWorldTransform() { return worldTransformBody_; }

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_=nullptr;

	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	WorldTransform worldTransformHammer_;


	//キーボード入力
	Input* input_ = nullptr;

	XINPUT_STATE joyState;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

};
