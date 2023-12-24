#include "Enemy.h"

void Enemy::Initialize() { 

	worldTransform_.translation_ = {0.0f, 0.0f, 10.0f};

	worldTransform_.Initialize();
	model_ = Model::Create();

}

void Enemy::Update() { 
	
	worldTransform_.UpdateMatrix();

}

void Enemy::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }
