#include "EnemyHP.h"
#include<cassert>
void EnemyHP::Initialize(Model* model,const Vector3& position) 
{ 
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("HP.png");

	worldTransform_.Initialize();
	worldTransform_.scale_ = {15.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = position;

}

void EnemyHP::Update() { 
	
	

	
	
	worldTransform_.UpdateMatrix(); }

void EnemyHP::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void EnemyHP::OnCollision()
{ worldTransform_.scale_.x = worldTransform_.scale_.x - 1.0f; }

void EnemyHP::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}