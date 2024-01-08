#include "FakeBullet.h"
#include<cassert>
 void FakeBullet::Initialize(Model* model) 
{
	assert(model);
	 worldTransform_.translation_ = {0.0f, 0.0f, 31.0f};
	worldTransform_.Initialize();
	 model_ = model;
 }

void FakeBullet::Update() 
{ 
	worldTransform_.UpdateMatrix(); 
	ImGui::Begin("FakeBullet");
	ImGui::DragFloat3("position", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
}

void FakeBullet::Draw(ViewProjection& viewProjection) 
{
	if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection);
	}
}

void FakeBullet::OnCollision() { isDead_ = true; }

Vector3 FakeBullet::GetWorldPosition() { 
// ワールド座標を入れる変数
	 Vector3 worldPos;
	 // ワールド行列の平行移動成分を取得(ワールド座標)
	 worldPos.x = worldTransform_.matWorld_.m[3][0];
	 worldPos.y = worldTransform_.matWorld_.m[3][1];
	 worldPos.z = worldTransform_.matWorld_.m[3][2];

	 return worldPos;
}

Vector3 FakeBullet::GetWorldRadius() { 
Vector3 worldRadius;

	 worldRadius.x = worldTransform_.scale_.x;
	 worldRadius.y = worldTransform_.scale_.y;
	 worldRadius.z = worldTransform_.scale_.z;
	 return worldRadius;
}


