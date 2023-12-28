#include "WeakEnemy.h"

void WeakEnemy::Initialize(Vector3 position) 
{
	model_ = Model::Create(); 

	worldTransform_.translation_ = position;

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
