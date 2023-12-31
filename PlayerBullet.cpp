#include "PlayerBullet.h"

void PlayerBullet::Initialize() 
{ 
	worldTransform_.Initialize(); 
	model_ = Model::CreateFromOBJ("PlayerBullet", true);
}

void PlayerBullet::Update() 
{ 
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}
