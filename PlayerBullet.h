#pragma once
#include"WorldTransform.h"
#include"Model.h"
class PlayerBullet {
public:
	void Initialize(Vector3& position,Vector3&velocity);

	void Update();

	void Draw(ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Vector3 velocity_;

		// デスフラグ
	bool isDead_ = false;

};
