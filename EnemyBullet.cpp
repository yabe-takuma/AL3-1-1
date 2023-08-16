#include "EnemyBullet.h"
#include <cassert>
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("Red.png");

	worldTransform_;

	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.Initialize();
	velocity_ = velocity;
}

void EnemyBullet::OnCollision() { isDead_ = true; }

Vector3 EnemyBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 EnemyBullet::GetWorldRadius() {
	Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;
}

void EnemyBullet::Update() {

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}