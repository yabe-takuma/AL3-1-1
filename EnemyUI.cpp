#include "EnemyUI.h"
#include <cassert>
void EnemyUI::Initialize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;
	model_ = Model::CreateFromOBJ("Enemy", true);
	//textureHandle_ = TextureManager::Load("Enemy.jpg");

	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = position;
}

void EnemyUI::Update() { worldTransform_.UpdateMatrix(); }

void EnemyUI::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

void EnemyUI::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
