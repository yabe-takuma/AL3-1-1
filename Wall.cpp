#include "Wall.h"

void Wall::Initialize() {
	worldTransform_.Initialize();
	model_ = Model::Create();
}

void Wall::Update() { worldTransform_.UpdateMatrix(); }

void Wall::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }