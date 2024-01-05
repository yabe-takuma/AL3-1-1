#include "PlayerBullet.h"
#include<cassert>
void PlayerBullet::Initialize(Model* model,Vector3& position, Vector3& velocity) { 
	assert(model);
	model_ = model;
	worldTransform_.translation_ = position;
	worldTransform_.Initialize(); 
	
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

void PlayerBullet::OnCollision() { isDead_ = true; }

Vector3 PlayerBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 PlayerBullet::GetWorldRadius() 
{ 
	Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;
}
