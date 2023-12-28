#include "Enemy.h"
#include"Player.h"


void Enemy::Initialize() { 

	worldTransform_.translation_ = {0.0f, 0.0f, 10.0f};

	worldTransform_.Initialize();
	model_ = Model::Create();
	
}

void Enemy::Update() { 
	
	const float kSpeed = 0.3f;
	Vector3 velocity(0, 0, kSpeed);

	GetWorldPosition();
	velocity = Subtract(player_->GetWorldPosition(), GetWorldPosition());

	velocity = Normalize(velocity);
	velocity = Multiply(kSpeed, velocity);

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);

	worldTransform_.UpdateMatrix();

}

void Enemy::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }

Vector3 Enemy::GetWorldPosition() { 	
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
