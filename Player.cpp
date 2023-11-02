#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() {

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターも移動の速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {

		move.x += kCharacterSpeed;
	};

	// 押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_UP)) {
		move.z += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {

		move.z -= kCharacterSpeed;
	};

	// ゲームパッド状態取得、ゲームパッドが有効の場合if文がを通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.3f;

		// 移動量
		Vector3 move2 = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};

		// 移動量に速さを反映
		move2 = Normalize(move2);
		move2 = Multiply(speed, move2);
		move2 = TransformNormal(move2, MakeRotateYMatrix(viewProjection_->rotation_.y));
		if (move2.x != 0.0f) {

			worldTransform_.rotation_.y = std::atan2(move2.x, move2.z);
			MakeRotateYMatrix(worldTransform_.rotation_.y);
			move2 = Multiply(move2, MakeRotateYMatrix(worldTransform_.rotation_.y));
		}
		//カメラ回転の速さ
		/*const float cameraspeed = 0.1f;
		move2 = Multiply2(move2,MakeRotateYMatrix(cameraspeed));*/

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move2);
	}

	// 座標移動(ベクトルの加算)
	//worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }

void Player::SetViewProjection(const ViewProjection* viewProjection) {
	viewProjection_ = viewProjection;
}
