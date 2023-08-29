#include "PlayerHP.h"
#include <cassert>
void PlayerHP::Initialize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("HP.png");

	worldTransform_.Initialize();
	worldTransform_.scale_ = {10.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = position;
}

void PlayerHP::Update() { worldTransform_.UpdateMatrix(); }

void PlayerHP::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerHP::OnCollision() { worldTransform_.scale_.x = worldTransform_.scale_.x - 1.0f; }
