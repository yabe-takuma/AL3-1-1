#include "Enemy.h"
#include"Player.h"


void Enemy::Initialize() { 

	worldTransform_.translation_ = {0.0f, 5.0f, 10.0f};

	worldTransform_.Initialize();
	model_ = Model::CreateFromOBJ("Hanter",true);
	
}

void Enemy::Update() { 
	
	
	Vector3 velocity(0, 0, kSpeed_);
	
	GetWorldPosition();
	velocity = Subtract(player_->GetWorldPosition(), GetWorldPosition());

	velocity = Normalize(velocity);
	velocity = Multiply(kSpeed_, velocity);
	
		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
	
	worldTransform_.UpdateMatrix();

	//ImGui::Begin("Enemy");
	//ImGui::DragInt("timer", &timer_, 1);
	//ImGui::End();
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

void Enemy::OnCollision() { isOnCollision_ = true; 
if (isOnCollision_ == true)
{
		timer_++;
	}

 if (timer_ >= 31)
{
		timer_ = 0;
		isOnCollision_ = false;

}

}

Vector3 Enemy::GetWorldRadius() { 
	Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;
}
