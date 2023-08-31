#include "PlayerBullet.h"
#include "cassert"


void PlayerBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	
	//modelplayerbullet_ = Model::CreateFromOBJ("Bullet", true);
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("PlayerBullet.png");

	worldTransform_;

	// 因数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
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
	model_->Draw(worldTransform_, viewProjection,textureHandle_);
};

void PlayerBullet::OnCollision() { isDead_ = true; }

Vector3 PlayerBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 PlayerBullet::GetWorldRadius() {
	Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;
}