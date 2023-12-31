#include "Item.h"
#include<cassert>
void Item::Initialize(Model* model) 
{ 
	assert(model); 
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {4.6f, 0.0f, 56.8f};
	worldTransform_.rotation_ = {0.0f, 1.0f, 0.0f};
	
}

void Item::Update() 
{ 
	worldTransform_.UpdateMatrix(); 
	ImGui::Begin("Item");
	ImGui::DragFloat3("position", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();
}

void Item::Draw(ViewProjection& viewProjection) 
{ 
	model_->Draw(worldTransform_, viewProjection);

}
