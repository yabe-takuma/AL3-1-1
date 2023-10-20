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
	
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	//キャラクターも移動の速さ
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更(左右)
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

	//ゲームパッド状態取得、ゲームパッドが有効の場合if文がを通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	//速さ
		const float speed = 0.5f;
		
		//移動量
		Vector3 move2 = {(float)joyState.Gamepad.sThumbLX, 0.0f,(float)joyState.Gamepad.sThumbLY};
		//移動量に速さを反映
		move2 = Multiply(speed, Normalize(Division(move2,SHRT_MAX)));

		//移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move2);
	}

	//座標移動(ベクトルの加算)
	worldTransform_.translation_= Add(worldTransform_.translation_,move);

	worldTransform_.UpdateMatrix();

}

void Player::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
