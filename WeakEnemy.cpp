#include "WeakEnemy.h"

void WeakEnemy::Initialize() 
{
	model_ = Model::Create(); 
	worldTransform_.Initialize();
}

void WeakEnemy::Update() 
{ 
	worldTransform_.UpdateMatrix(); 
}

void WeakEnemy::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}
