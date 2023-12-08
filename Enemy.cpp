#include "Enemy.h"

void Enemy::Initialize(const std::vector<Model*>& models) { 
	BaseCharacter::Initialize(models);

	worldTransformBody_.translation_ = {-10.0f, -1.0f, 15.0f};
	worldTransformL_arm_.translation_ = {-9.0f, 0.0f, 15.0f};
	worldTransformR_arm_.translation_ = {-11.0f, 0.0f, 15.0f};

	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	
	
}

void Enemy::Update() { 
	BaseCharacter::Update();
	Vector3 velocity_ = {0.0f, 0.0f, 0.1f};
	
	const float rotation_ = 0.01f;
	worldTransformBody_.rotation_.y += rotation_;
	worldTransformL_arm_.rotation_.y += rotation_;
	worldTransformR_arm_.rotation_.y += rotation_;

	velocity_ = TransformNormal(velocity_, MakeRotateYMatrix(worldTransformBody_.rotation_.y));

	
	 worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, velocity_);
	worldTransformL_arm_.translation_ = Add(worldTransformL_arm_.translation_, velocity_);
	 worldTransformR_arm_.translation_ = Add(worldTransformR_arm_.translation_, velocity_);
	
	

	worldTransformBody_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();

}

void Enemy::Draw(ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformL_arm_, viewProjection);
	models_[2]->Draw(worldTransformR_arm_, viewProjection);


}





