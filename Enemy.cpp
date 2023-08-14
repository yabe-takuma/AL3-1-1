#include "Enemy.h"
#include <cassert>
#include "IMGuiManager.h"

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("Enemy.jpg");

	worldTransform_;

	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = {6.0f, 2.0f, 50.0f};
	worldTransform_.Initialize();
	velocity_ = velocity;

}

void Enemy::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity_);
	

	switch (phase_) {
	case Phase::Approach:
	default:
		Approach();
		break;
	case Phase::Leave:
		Leave();
		break;
	}
}

void Enemy::Approach() {
	// 移動(ベクトルを加算)
	Add(worldTransform_.translation_, velocity_);
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	const float kEnemySpeed = 0.1f;
	velocity_ = {kEnemySpeed, -kEnemySpeed, 0};
	// 移動(ベクトルを加算)
	Add(worldTransform_.translation_, velocity_);
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
