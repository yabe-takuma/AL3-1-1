#include "WeakEnemy.h"
#include"GameScene.h"

void WeakEnemy::Initialize(Vector3 position, Vector3 velocity) {
	model_ = Model::Create(); 

	worldTransform_.translation_ = position;
	seveposition_ = position;

	velocity_ = velocity;

	worldTransform_.Initialize();
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

	ImGui::Begin("position");
	ImGui::DragFloat3("position", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("move", &velocity_.x, 0.1f);
	ImGui::End();

}

void WeakEnemy::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}

void WeakEnemy::OnCollision() {}
