#include "Wall.h"


void Wall::Initialize(const std::vector<Model*>& models) {
	BaseWall::Initialize(models);
	
	worldTransform_.Initialize();
	model_ = Model::Create();
}

void Wall::Update() { worldTransform_.UpdateMatrix(); }

void Wall::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }