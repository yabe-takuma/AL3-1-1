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

void BreakWall::OnCollision() {}

