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

Vector3 Enemy::GetWorldPosition() { 	
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
