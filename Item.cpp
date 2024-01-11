#include "Item.h"
#include<cassert>
void Item::Initialize(Model* model) 
{ 
	assert(model); 
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {4.6f, 0.0f, 56.8f};
	worldTransform_.rotation_ = {0.0f, 1.0f, 0.0f};
	isDead_ = false;
}

void Item::Update() 
{ 
	worldTransform_.UpdateMatrix(); 
	/*ImGui::Begin("Item");
	ImGui::DragFloat3("position", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();*/
}

void Item::Draw(ViewProjection& viewProjection) 
{ 
	model_->Draw(worldTransform_, viewProjection);

}

void Item::OnCollision() { worldTransform_.scale_.x = 0.0f;
	worldTransform_.scale_.y = 0.0f;
	worldTransform_.scale_.z = 0.0f;
	isDead_ = true;
}

Vector3 Item::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Item::GetWorldRadius() {
	Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;
}
