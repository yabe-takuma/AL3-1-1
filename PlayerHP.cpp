#include "PlayerHP.h"
#include <cassert>
void PlayerHP::Initialize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;
	framemodel_ = model;
	textureHandle_ = TextureManager::Load("PlayerHP.png");
	

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.5f, 5.0f, 0.1f};
	worldTransform_.translation_ = position;

	
}

void PlayerHP::Update() { worldTransform_.UpdateMatrix(); }

void PlayerHP::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	
}

void PlayerHP::OnCollision() { worldTransform_.scale_.y = worldTransform_.scale_.y - 1.0f; }

void PlayerHP::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
