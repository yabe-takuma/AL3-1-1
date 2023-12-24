#include "Player.h"
#include<cassert>

void Player::Initialize(Model* model,uint32_t textureHandle)
{
	//NULLポインタチェック
	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

}

void Player::Update()
{
	
	////キャラクターの移動ベクトル
	//Vector3 move = {0, 0, 0};

	////キャラクターも移動の速さ
	//const float kCharacterSpeed = 0.2f;

	////押した方向で移動ベクトルを変更(左右)
	//if (input_->PushKey(DIK_LEFT)) {
	//	move.x -= kCharacterSpeed;
	//} else if (input_->PushKey(DIK_RIGHT)) {

	//	move.x += kCharacterSpeed;
	//};

	//// 押した方向で移動ベクトルを変更(上下)
	//if (input_->PushKey(DIK_UP)) {
	//	move.y += kCharacterSpeed;
	//} else if (input_->PushKey(DIK_DOWN)) {

	//	move.y -= kCharacterSpeed;
	//};

	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		const float speed = 0.3f;
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX * SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY * SHRT_MAX * speed};

		// 移動量に速さを反映
		move = Normalize(move);
		move = Multiply(speed, move);
		move = TransformNormal(move, MakeRotateYMatrix(viewProjection_->rotation_.y));
		if (move.x != 0.0f) {

			worldTransform_.rotation_.y = std::atan2(move.x, move.z);
		}

		// 座標移動(ベクトルの加算)
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	}

	

	worldTransform_.UpdateMatrix();

}

void Player::Draw(ViewProjection& viewProjection)
{ model_->Draw(worldTransform_, viewProjection); }

void Player::SetViewProjection(const ViewProjection* viewProjection) {
	viewProjection_ = viewProjection;
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