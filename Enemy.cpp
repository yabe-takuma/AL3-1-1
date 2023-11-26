#include "Enemy.h"

void Enemy::Initialize(const std::vector<Model*>& models) { 
	BaseCharacter::Initialize(models);

	worldTransformBody_.translation_ = {0.0f, -1.0f, 0.0f};
	worldTransformL_arm_.translation_ = {1.0f, 0.0f, 0.0f};
	worldTransformR_arm_.translation_ = {-1.0f, 0.0f, 0.0f};

	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	velocity_[0] = {0.0f, 0.0f, 0.0f};
	velocity_[1] = {0.0f, 0.0f, 0.0f};
	velocity_[2] = {0.0f, 0.0f, 0.0f};
}

void Enemy::Update() { 
	BaseCharacter::Update();
	
	
	//velocity_[0] = TransformNormal(velocity_[0], worldTransformBody_.matWorld_);
	//velocity_[1] = TransformNormal(velocity_[1], worldTransformL_arm_.matWorld_);
	//velocity_[2] = TransformNormal(velocity_[2], worldTransformR_arm_.matWorld_);
	
	
	velocity_[0].x += angularVelocity * deltaTime;
	velocity_[0].z += angularVelocity * deltaTime;

		//worldTransformBody_.rotation_.y = std::atan2(velocity_[0].x, velocity_[0].z);

	worldTransformBody_.translation_.x =0.0f + std::cos(velocity_[0].x) * 10.0f;
	worldTransformBody_.translation_.z =0.0f + std::sin(velocity_[0].x) * 10.0f;



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
