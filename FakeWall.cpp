#include "FakeWall.h"

void FakeWall::Initialize() 
{ 
	worldTransform_.translation_ = {0.0f, 0.0f, 94.8f};
	worldTransform_.scale_ = {8.0f, 20.0f, 1.0f};
	worldTransform_.Initialize(); 
	model_ = Model::Create();
}

void FakeWall::Update() 
{ 
	worldTransform_.UpdateMatrix(); 
	ImGui::Begin("FakeWall");
	ImGui::DragFloat3("position", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();
}

void FakeWall::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}
