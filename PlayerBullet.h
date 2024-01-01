#pragma once
#include"WorldTransform.h"
#include"Model.h"
class PlayerBullet {
public:
	void Initialize(Model* model,Vector3& position,Vector3&velocity);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void OnCollision();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// ワールドradiusを取得
	Vector3 GetWorldRadius();

	bool IsDead() const { return isDead_; }

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Vector3 velocity_;

	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;

		// デスフラグ
	bool isDead_ = false;

};
