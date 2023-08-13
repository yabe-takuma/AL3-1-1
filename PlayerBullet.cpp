#include "PlayerBullet.h"
#include "cassert"


void PlayerBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.png");

	worldTransform_;

	// 因数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	worldTransform_.Initialize();
	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void PlayerBullet::Update() { 
	
	// 座標を移動させる(1フレーム分の移動量を足し込む)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	worldTransform_.UpdateMatrix();

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
};