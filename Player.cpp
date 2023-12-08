#include "Player.h"
#include <cassert>

void Player::Initialize(const std::vector<Model*>& models) {
	
	BaseCharacter::Initialize(models);
	

	InitializeFloatingGimmick();

	SetParent(&worldTransformBody_);

	worldTransformBody_.translation_ = {0.0f, 0.5f, 0.0f};
	worldTransformHead_.translation_ = {0.0f, 1.5f, 0.0f};
	worldTransformL_arm_.translation_ = {-0.5f, 1.3f, 0.0f};
	worldTransformR_arm_.translation_ = {0.5f, 1.3f, 0.0f};

	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() {
	BaseCharacter::Update();
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
			worldTransformBody_.rotation_.y = std::atan2(move2.x, move2.z);
			/*worldTransformHead_.rotation_.y = std::atan2(move2.x, move2.z);
			worldTransformL_arm_.rotation_.y = std::atan2(move2.x, move2.z);
			worldTransformR_arm_.rotation_.y = std::atan2(move2.x, move2.z);*/
		
		}
		//カメラ回転の速さ
		/*const float cameraspeed = 0.1f;
		move2 = Multiply2(move2,MakeRotateYMatrix(cameraspeed));*/

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move2);
		worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, move2);
		/*worldTransformHead_.translation_ = Add(worldTransformHead_.translation_, move2);
		worldTransformL_arm_.translation_ = Add(worldTransformL_arm_.translation_, move2);
		worldTransformR_arm_.translation_ = Add(worldTransformR_arm_.translation_, move2);*/
	}

	// 座標移動(ベクトルの加算)
	//worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	UpdateFloatingGimmick();

	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) { //model_->Draw(worldTransform_, viewProjection); 
	//BaseCharacter::Draw(viewProjection);
	
	//3Dモデルを描画
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);

}

void Player::SetViewProjection(const ViewProjection* viewProjection) {
	viewProjection_ = viewProjection;
}

void Player::InitializeFloatingGimmick() { floatingParameter_ = 0.5f;
	floatingParameterHead_ = 2.0f;


}

void Player::UpdateFloatingGimmick() {
	//浮遊移動のサイクル<frame>
	const uint16_t fream = 70;
	//1フレームでのパラメータ加算値
	const float step = 2.0f * 3.14f / fream;
	//パラメータを1ステップ分加算
	floatingParameter_ += step;
	
	//2πを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * 3.14f);

	//浮遊の振幅<π>
	const float floatingAmplitude = 0.3f;
	//浮遊を座標に反映
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude-0.5f;
	//worldTransformHead_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude+1.0f;
	//worldTransformL_arm_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude+0.8f;
	//worldTransformR_arm_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude+0.8f;

	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * floatingAmplitude;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * floatingAmplitude;
}

void Player::SetParent(const WorldTransform* parent) { 
	worldTransformHead_.parent_ = parent; 
	worldTransformL_arm_.parent_ = parent;
	worldTransformR_arm_.parent_ = parent;
	
}
