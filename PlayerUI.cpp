#include "PlayerUI.h"
#include <cassert>
void PlayerUI::Initialize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;
	model_ = Model::CreateFromOBJ("Player", true);
	//textureHandle_ = TextureManager::Load("mario.jpg");

	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = position;
}

void PlayerUI::Update() { worldTransform_.UpdateMatrix(); }

void PlayerUI::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

void PlayerUI::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
