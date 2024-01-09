#include "BreakWall.h"
#include"Player.h"

void BreakWall::Initialize() 
{ 

	worldTransform_.translation_ = {5.9f, 0.0f, 119.8f};
	worldTransform_.scale_ = {10.0f, 20.0f, 1.0f};

	worldTransformhp_.translation_ = {5.9f, 5.0f, 118.8f};
	worldTransformhp_.scale_ = {10.0f, 1.0f, 1.0f};
		

	worldTransform_.Initialize();
	worldTransformhp_.Initialize();
	model_ = Model::Create();
	modelhp_ = Model::Create();
	hp_ = 100;
	isDead_ = false;

	texture_[0] = TextureManager::Load("ge-ji.png");
	texture_[1] = TextureManager::Load("doa.png");

}

void BreakWall::Update() 
{ 
	worldTransform_.UpdateMatrix(); 
	worldTransformhp_.UpdateMatrix();
	ImGui::Begin("Window");
	ImGui::DragFloat3("position", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragInt("HP", &hp_, 1);
	ImGui::End();

	if (isOnCollision_ == true) {
		timer_++;
	}

	if (timer_ >= 100) {
		timer_ = 0;
		isOnCollision_ = false;
	}

	if (hp_ <= 0)
	{
		isDead_ = true;
	}
	
}

void BreakWall::Draw(ViewProjection& viewProjection) 
{
	if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection, texture_[1]);
	}
	if (hp_ >= 1) {

		modelhp_->Draw(worldTransformhp_, viewProjection, texture_[0]);
	}
}

void BreakWall::OnCollision() { hp_ = hp_ -player_->GetPow();
	worldTransformhp_.scale_.x = worldTransformhp_.scale_.x - 0.1f*player_->GetPow();
	if (timer_ <= 0) {
		isOnCollision_ = true;
	}
}

Vector3 BreakWall::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 BreakWall::GetWorldRadius() {
	Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;
}

