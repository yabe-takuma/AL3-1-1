#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model) {
	assert(model);

	model_ = model;

	worldTransform_;
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {100.0f, 100.0f, 100.0f};
	worldTransform_.Initialize();
}

void Skydome::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Skydome::Draw(ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection);
}
