#include "LImitTimerUI.h"
#include <cassert>
void LImitTimerUI::Initialize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("Timer.jpg");

	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = position;
}

void LImitTimerUI::Update() { worldTransform_.UpdateMatrix(); }

void LImitTimerUI::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void LImitTimerUI::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}