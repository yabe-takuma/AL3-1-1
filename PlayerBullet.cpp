#include "PlayerBullet.h"

void PlayerBullet::Initialize(Vector3& position, Vector3& velocity) { 
	worldTransform_.translation_ = position;
	worldTransform_.Initialize(); 
	model_ = Model::Create();
	//model_ = Model::CreateFromOBJ("PlayerBullet", true);
	velocity_ = velocity;
}

void PlayerBullet::Update() 
{ 

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}
