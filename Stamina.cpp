#include "Stamina.h"

void Stamina::Initialize() 
{ 
	worldTransform_.Initialize(); 
	model_ = Model::Create();

	cooltime_ = isCooltime;
}

void Stamina::Update() 
{
	if (worldTransform_.scale_.x >= 0.0f) {
		worldTransform_.scale_.x -= 0.001f;
	}

	if (worldTransform_.scale_.x <= 0.0f)
	{
		cooltime_--;
	}
	if (cooltime_ <= 0)
	{
		worldTransform_.scale_.x = 1.0f;
		cooltime_ = isCooltime;
	}
	worldTransform_.UpdateMatrix(); 

}

void Stamina::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}
