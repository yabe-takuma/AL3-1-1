#include "PlayerBullet.h"
#include "cassert"


void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.png");

	worldTransform_;

	// 因数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	worldTransform_.Initialize();
}

void PlayerBullet::Update() { 
	worldTransform_.UpdateMatrix();



}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
};