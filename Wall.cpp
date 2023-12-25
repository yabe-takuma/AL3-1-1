#include "Wall.h"


void Wall::Initialize(const std::vector<Model*>& models) {
	BaseWall::Initialize(models);
	
	worldTransform_.translation_ = {3.0f, 0.0f, 5.0f};
	

	
		worldTransform_.Initialize();
	worldTransform2_.Initialize();
	
}

void Wall::Update() {
	BaseWall::Update();
	
		worldTransform_.UpdateMatrix();
	worldTransform2_.UpdateMatrix();
	
}

void Wall::Draw(ViewProjection& viewProjection) {
	
	models_[0]->Draw(worldTransform_, viewProjection);
	models_[1]->Draw(worldTransform2_, viewProjection);
	/*models_[2]->Draw(worldTransform_, viewProjection);
	models_[3]->Draw(worldTransform_, viewProjection);
	models_[4]->Draw(worldTransform_, viewProjection);
	models_[5]->Draw(worldTransform_, viewProjection);
	models_[6]->Draw(worldTransform_, viewProjection);
	models_[7]->Draw(worldTransform_, viewProjection);
	models_[8]->Draw(worldTransform_, viewProjection);
	models_[9]->Draw(worldTransform_, viewProjection);*/
	
}