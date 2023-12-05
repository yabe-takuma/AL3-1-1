#include "Enemy.h"

void Enemy::Initialize(const std::vector<Model*>& models) { 
	BaseCharacter::Initialize(models);

	worldTransformBody_.translation_ = {0.0f, -1.0f, 5.0f};
	worldTransformL_arm_.translation_ = {1.0f, 0.0f, 0.0f};
	worldTransformR_arm_.translation_ = {-1.0f, 0.0f, 0.0f};

	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	
	
}

void Enemy::Update() { 
	BaseCharacter::Update();
	Vector3 velocity_ = {1.0f, 0.0f, 0.0f};
	const float rotation_ = 0.1f;
	viewProjection_.rotation_.y += rotation_;
	velocity_ = Normalize(velocity_);
	 velocity_ = TransformNormal(velocity_, MakeRotateYMatrix(viewProjection_.rotation_.y));
	/*velocity_ = TransformNormal(velocity_, worldTransformL_arm_.matWorld_);
	 velocity_ = TransformNormal(velocity_, worldTransformR_arm_.matWorld_);*/
	
	
	/*if (velocity_.x != 0.0f) {

		worldTransformBody_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
		worldTransformR_arm_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
		worldTransformL_arm_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	}*/
	
	
	
	 worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, velocity_);
	

	/*worldTransformL_arm_.translation_ = Add(worldTransformL_arm_.translation_, velocity_[1]);
	worldTransformR_arm_.translation_ = Add(worldTransformR_arm_.translation_, velocity_[2]);

	worldTransformBody_.rotation_=Add(worldTransformBody_.rotation_, velocity_[0]);
	worldTransformL_arm_.rotation_ = Add(worldTransformL_arm_.rotation_, velocity_[1]);
	worldTransformR_arm_.rotation_ = Add(worldTransformR_arm_.rotation_, velocity_[2]);*/

	worldTransformBody_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();

}

void Enemy::Draw(ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformL_arm_, viewProjection);
	models_[2]->Draw(worldTransformR_arm_, viewProjection);


}





