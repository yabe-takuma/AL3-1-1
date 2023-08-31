#include "Frame.h"
#include <cassert>
void Frame::Initialize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;
	
	textureHandle_ = TextureManager::Load("frame.png");

	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = position;
}

void Frame::Update() { worldTransform_.UpdateMatrix(); }

void Frame::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


void Frame::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
