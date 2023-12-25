#include "Wall.h"


void Wall::Initialize(const std::vector<Model*>& models) {
	BaseWall::Initialize(models);
	
	worldTransform_.Initialize();
	
}

void Wall::Update() {
	BaseWall::Update();
	worldTransform_.UpdateMatrix(); 

}

void Wall::Draw(ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransform_, viewProjection);
}