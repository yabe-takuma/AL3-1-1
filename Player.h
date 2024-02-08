#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"Input.h"
#include"Xinput.h"
#include"BaseCharacter.h"
#include"ImGuiManager.h"
#include <optional>
#include <cmath>
#include"PlayerBullet.h"
#include<memory>


class FakeBullet;

class Item;

class Player : public BaseCharacter {

	// 振るまい
	enum class Behavior {
		kRoot,   // 通常攻撃
		kAttack, // 攻撃中
	
	};

		// 攻撃モーション
	struct Attack {
		int32_t time;
		int32_t kAnimMaxtime;
		int32_t cooltime;
		int32_t bulletcooltime;
	};

public:

	~Player();

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

	void OnCollision();

	void OnCollision2();

	Vector3 GetWorldPosition();

	float easeInSine(float x);

	float easeInSine2(float x);

	void BulletAttack();

	float easeOutQuad(float x);

	// ワールドradiusを取得
	Vector3 GetWorldRadius();

	Vector3 GetSordWorldPosition();

		// ワールドradiusを取得
	Vector3 GetSordWorldRadius();

	const WorldTransform& GetWorldTransform() { return worldTransformBody_; }

	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return playerbullet_; }

	void InitializeFloatingGimmick();

	void UpdateFloatingGimmick();

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	bool IsSordAlive() const { return isSordAlive_; }

	bool IsOnCollision() const { return isOnCollision_; }

	bool IsClear() const { return isClear_; }

    int32_t GetPow() {return pow_;}

	void Pow();

	void SetFakeBullet(FakeBullet* fakebullet) { fakebullet_ = fakebullet; }

	bool IsDead() const { return isDead_; }

	void SetItem(Item* item) { item_ = item; }

	private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_=nullptr;

	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	WorldTransform worldTransformSord_;

	// 攻撃モーション
	Attack attack_;
	

	// 振るまい
	Behavior behavior_ = Behavior::kRoot;

	static void (Player::*pBehaviorInitializeTable[])();

	static void (Player::*pBehaviorUpdateTable[])();

	// 次の振るまいをリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	bool isWepon = false;

	//キーボード入力
	Input* input_ = nullptr;

	XINPUT_STATE joyState;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	std::list<PlayerBullet*> playerbullet_;
	std::unique_ptr<Model> modelbullet_;

	bool isSordAlive_ = false;

	Vector3 move;

	float speed = 0.3f;

	int32_t HP = 10;

	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	float floatingParameterHead_ = 0.0f;

	bool isOnCollision_ = false;

	int32_t timer_;

	bool isDead_ = false;

	bool isClear_ = false;

	int32_t pow_;

	FakeBullet* fakebullet_ = nullptr;

	Item* item_ = nullptr;

	int32_t sevepow_;

	

};
