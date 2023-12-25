#include "Wall.h"


void Wall::Initialize(const std::vector<Model*>& models) {
	BaseWall::Initialize(models);
	
	worldTransform_.translation_ = {3.0f, 0.0f, 5.0f};
	/*worldTransform_[1].translation_ = {0.0f, 0.0f, 10.0f};
	worldTransform_[2].translation_ = {3.0f, 0.0f, 1.0f};
	worldTransform_[3].translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[4].translation_ = {-20.0f, 0.0f, 5.0f};
	worldTransform_[5].translation_ = {-10.0f, 0.0f, 5.0f};
	worldTransform_[6].translation_ = {10.0f, 0.0f, 5.0f};
	worldTransform_[7].translation_ = {15.0f, 0.0f, 5.0f};
	worldTransform_[8].translation_ = {3.0f, 0.0f, 5.0f};
	worldTransform_[9].translation_ = {3.0f, 0.0f, 5.0f};*/

	//for (int i = 0; i < 10; i++) {
		worldTransform_.Initialize();
	//}
}

void Wall::Update() {
	BaseWall::Update();
	//for (int i = 0; i < 10; i++) {
		worldTransform_.UpdateMatrix();
	//}
}

void Wall::Draw(ViewProjection& viewProjection) {
	for (int i = 0; i < 10; i++) {
		models_[i]->Draw(worldTransform_, viewProjection);
	}
}