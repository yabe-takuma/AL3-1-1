#include "EnemyHP.h"
#include<cassert>
void EnemyHP::Initialize(Model* model,const Vector3& position) 
{ 
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("HP.png");

	worldTransform_.Initialize();
	worldTransform_.scale_ = {4.95f, 0.5f, 0.1f};
	worldTransform_.translation_ = position;

}

void EnemyHP::Update() { 
	
	if (worldTransform_.scale_.x < 0.1f) {
		isenemylimit_ = true;
	}
	
	
	worldTransform_.UpdateMatrix(); }

void EnemyHP::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void EnemyHP::OnCollision()  { 
	
	
	
	

		worldTransform_.scale_.x = worldTransform_.scale_.x - 0.33f;
	



}

void EnemyHP::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}

