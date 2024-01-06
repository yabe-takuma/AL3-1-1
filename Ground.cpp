#include "Ground.h"
#include<cassert>
void Ground::Initialize(Model* model) { 
	
	assert(model);
	model_ = model;

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.rotation_ = {0, 0, 0};
	worldTransform_.scale_ = {100.0f, 100.0f, 300.0f};
	worldTransform_.Initialize();
}

void Ground::Update()
{ worldTransform_.UpdateMatrix(); }

void Ground::Draw(ViewProjection& viewProjection)
{ model_->Draw(worldTransform_, viewProjection); }
