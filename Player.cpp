#include "Player.h"
#include <cassert>
#include "IMGuiManager.h"

Player::~Player() { 
for (PlayerBullet* bullet_ : bullets_) {

		delete bullet_;
	}



}

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();


}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		// 速度ベクトルを自機の向きに合わせて回転させる(自キャラのワールド行列はmatWorld)
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾を生成し,初期化
		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::GetWorldRadius() {
	Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;
}

void Player::OnCollision() {}

void Player::Update()
{ 

	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	// 押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	// 移動限界座標
	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 19.4f;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// キャラクター攻撃処理
	Attack();

		// 弾更新
	for (PlayerBullet* bullet : bullets_) {

		bullet->Update();
	}

	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// キャラクターの座標を画面表示する処理
	ImGui::Begin("Debug1");

	float playerPos[] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	// float3スライダー
	ImGui::SliderFloat3("PlayerPos", playerPos, -50.0f, 50.0f);

	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.y = playerPos[1];
	worldTransform_.translation_.z = playerPos[2];

	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection_)
{ 
	model_->Draw(worldTransform_, viewProjection_, textureHandle_); 

	for (PlayerBullet* bullet : bullets_) {

		bullet->Draw(viewProjection_);
	}

}