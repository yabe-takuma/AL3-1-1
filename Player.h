#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"Input.h"
#include"BaseCharacter.h"
#include"ImGuiManager.h"
#include <optional>
#include<random>
class Player : public BaseCharacter {

	//振るまい
	enum class Behavior {
		kRoot,//通常攻撃
		kAttack,//攻撃中
		kJump, //ジャンプ中
	};

	//攻撃モーション
	struct Attack {
		int32_t time;
		int32_t kAnimMaxtime;
		int32_t cooltime;
	};

public:
	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(ViewProjection& viewProjection) override;

	void SetViewProjection(const ViewProjection* viewProjection);
	//浮遊ギミック初期化
	void InitializeFloatingGimmick();
	//浮遊ギミック更新
	void UpdateFloatingGimmick();
	//通常行動更新
	void BehaviorRootUpdate();
	//攻撃行動更新
	void BehaviorAttackUpdate();
	//通常行動初期化
	void BehaviorRootInitialize();
	//攻撃行動初期化
	void BeheviorAttackInitialize();
	//ジャンプ行動初期化
	void BehaviorJumpInitialize();
	//ジャンプ行動更新
	void BehaviorJumpUpdate();

	void CameraSake();

	float EaseInBack(float x);

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

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
	WorldTransform worldTransformHammer_;

	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	float floatingParameterHead_ = 0.0f;
	//攻撃モーション
	Attack attack_;
	//振るまい
	Behavior behavior_ = Behavior::kRoot;

	static void (Player::*pBehaviorInitializeTable[])();

	static void (Player::*pBehaviorUpdateTable[])();



	//次の振るまいをリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	//速度
	Vector3 velocity_ = {};
	
};
