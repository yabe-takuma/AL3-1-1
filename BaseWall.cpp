#include "BaseWall.h"

void BaseWall::Initialize(const std::vector<Model*>& models) {
	models_ = models;
	worldTransform_.Initialize();
}

void BaseWall::Update() { worldTransform_.UpdateMatrix(); }

void BaseWall::Draw(ViewProjection& viewProjection) {
	for (Model* model : models_) {
		model->Draw(worldTransform_, viewProjection);
	}
}
