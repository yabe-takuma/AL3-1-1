#include "BreakWall.h"

void BreakWall::Initialize() 
{ 

	worldTransform_.translation_ = {5.9f, 0.0f, 119.8f};
	worldTransform_.scale_ = {10.0f, 20.0f, 1.0f};

	worldTransform_.Initialize();
	model_ = Model::Create();
}

void BreakWall::Update() 
{ 
	worldTransform_.UpdateMatrix(); 

	ImGui::Begin("Window");
	ImGui::DragFloat3("position", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();

}

void BreakWall::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}

void BreakWall::OnCollision() { worldTransform_.scale_.x=worldTransform_.scale_.x - 1.0f; }

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

