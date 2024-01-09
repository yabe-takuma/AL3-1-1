#include "WeakEnemy.h"
#include"GameScene.h"
#include<cassert>
void WeakEnemy::Initialize(Vector3 position, Vector3 velocity) {
	
	model_ = Model::CreateFromOBJ("WeakEnemy", true) ;

	worldTransform_.translation_ = position;
	seveposition_ = position;

	velocity_ = velocity;

	worldTransform_.Initialize();

	isDead_ = false;
}

void WeakEnemy::Update() 
{ 

	

	
	 
	

	if (worldTransform_.translation_.x<=seveposition_.x-Radius_)
	{
		isspeed = false;
		
	} 
	if (worldTransform_.translation_.x >= seveposition_.x + Radius_) {
		isspeed = true;
	
	}

	if (isspeed)
	{
		velocity_.x =-0.1f;
	}
	else
	{
		velocity_.x =0.1f;
	}

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	worldTransform_.UpdateMatrix(); 

	/*ImGui::Begin("position");
	ImGui::DragFloat3("position", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("move", &velocity_.x, 0.1f);
	ImGui::End();*/

}

void WeakEnemy::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}

void WeakEnemy::OnCollision() { isDead_ = true; }

Vector3 WeakEnemy::GetWorldPosition() { 
// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;

}

Vector3 WeakEnemy::GetWorldRadius() { 
Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;
}
