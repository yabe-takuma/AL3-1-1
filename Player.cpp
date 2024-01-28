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
	worldTransformHammer_.translation_ = {0.0f,1.0f,0.0f};

	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	worldTransformHammer_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() {
	BaseCharacter::Update();

	if (behavior_ == Behavior::kRoot)
	{
		havior_ = 0;
	}
	else if (behavior_ == Behavior::kAttack)
	{
		havior_ = 1;
	}
	else if (behavior_ == Behavior::kJump)
	{
		havior_ = 2;
	}

	if (behaviorRequest_) {
	//振るまいを変更する
		behavior_ = behaviorRequest_.value();
		//各振るまいごとの初期化の実行
		(this->*pBehaviorInitializeTable[static_cast<size_t>(behavior_)])();
		//振るまいリクエストリセット
		behaviorRequest_ = std::nullopt;
	}
	(this->*pBehaviorUpdateTable[static_cast<size_t>(behavior_)])();
	//BehaviorRootUpdate();
	
	//BehaviorAttackUpdate();

		worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
	worldTransformHammer_.UpdateMatrix();

	
	 ImGui::Begin("Windows");
	ImGui::DragFloat("L_arm", &worldTransformL_arm_.rotation_.x, 0.01f);
	 ImGui::DragInt("Behavior", &havior_, 1);
	ImGui::End();
	
}

void Player::Draw(ViewProjection& viewProjection) { //model_->Draw(worldTransform_, viewProjection); 
	//BaseCharacter::Draw(viewProjection);
	
	//3Dモデルを描画
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);
	if (behavior_ == Behavior::kAttack) {

		models_[4]->Draw(worldTransformHammer_, viewProjection);
	}
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
	

	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * floatingAmplitude;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * floatingAmplitude;
}

void Player::BehaviorRootUpdate() {
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
		//Vector3 move2 = 
		velocity_={
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};

		// 移動量に速さを反映
		velocity_ = Normalize(velocity_);
		velocity_ = Multiply(speed, velocity_);
		velocity_ = TransformNormal(velocity_, MakeRotateYMatrix(viewProjection_->rotation_.y));
		if (velocity_.x != 0.0f) {

			worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
			worldTransformBody_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
			/*worldTransformHead_.rotation_.y = std::atan2(move2.x, move2.z);
			worldTransformL_arm_.rotation_.y = std::atan2(move2.x, move2.z);
			worldTransformR_arm_.rotation_.y = std::atan2(move2.x, move2.z);*/
		}
		// カメラ回転の速さ
		/*const float cameraspeed = 0.1f;
		move2 = Multiply2(move2,MakeRotateYMatrix(cameraspeed));*/

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
		worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, velocity_);
		/*worldTransformHead_.translation_ = Add(worldTransformHead_.translation_, move2);
		worldTransformL_arm_.translation_ = Add(worldTransformL_arm_.translation_, move2);
		worldTransformR_arm_.translation_ = Add(worldTransformR_arm_.translation_, move2);*/

		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			behavior_ = Behavior::kAttack;
		}
		
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A) {
			behavior_ = Behavior::kJump;
		}
	}
		
	

	// 座標移動(ベクトルの加算)
	// worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	UpdateFloatingGimmick();




}

void Player::BehaviorAttackUpdate() {
	float armPI = 1.57f;
	float weaponPI = 4.71f;
	const float kDegreeToRadian = 0.1f;
	attack_.kAnimMaxtime = 50;
	attack_.time++;
	
	if (attack_.time <= attack_.kAnimMaxtime) {
	
		float frame = (float)attack_.time / attack_.kAnimMaxtime;
		float easeInBack = EaseInBack(frame * frame);
		float weaponAngle = 45 * kDegreeToRadian*easeInBack;
		float armAngle = 45 * kDegreeToRadian * easeInBack;

		worldTransformHammer_.rotation_.x = weaponAngle-weaponPI;
		worldTransformL_arm_.rotation_.x = armAngle - armPI;
		worldTransformR_arm_.rotation_.x = armAngle - armPI;
	} else if (attack_.time >= attack_.kAnimMaxtime) {
		attack_.cooltime++;
		if (attack_.cooltime >= 30) {
			attack_.time = 0;
			behaviorRequest_ = Behavior::kRoot;
			attack_.cooltime = 0;
		}
	}
}

void Player::BehaviorRootInitialize() { 
	
worldTransformL_arm_.rotation_ = {0.0f, 0.0f, 0.0f}; 
worldTransformR_arm_.rotation_ = {0.0f, 0.0f, 0.0f};
}

void Player::BeheviorAttackInitialize() 
{ attack_.time = 0;

}

void Player::BehaviorJumpInitialize() {
worldTransformBody_.translation_.y = 0;
worldTransformL_arm_.rotation_.x = 0;
worldTransformR_arm_.rotation_.x = 0;

// ジャンプ初速
const float kJumpFirstSpeed = 1.0f;
// ジャンプ初速を与える
velocity_.y = kJumpFirstSpeed;
}

void Player::BehaviorJumpUpdate() 
{
	//移動
worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, velocity_);
//重力加速度
const float kGravilyAcceleration = 0.05f;
//加速度ベクトル
Vector3 accelerationVector = {0, -kGravilyAcceleration, 0};
//加速する
Add(velocity_, accelerationVector);
//着地
if (worldTransformBody_.translation_.y <= 0.0f)
{
		worldTransformBody_.translation_.y = 0;
		//ジャンプ終了
		behaviorRequest_ = Behavior::kRoot;
}
}



float Player::EaseInBack(float x) { 
	float radian = 0.005f;
		 float c1 = 3.70158f;
		 float c3 = c1 + radian;

		

		return c3=c3 * x * x * x - c1 * x * x;
	
}

void Player::SetParent(const WorldTransform* parent) { 
	worldTransformHead_.parent_ = parent; 
	worldTransformL_arm_.parent_ = parent;
	worldTransformR_arm_.parent_ = parent;
	worldTransformHammer_.parent_ = parent;
}

void (Player::*Player::pBehaviorInitializeTable[])() = {
    &Player::BehaviorRootInitialize,
    &Player::BeheviorAttackInitialize,
	&Player::BehaviorJumpInitialize,
};

void (Player::*Player::pBehaviorUpdateTable[])() = {
    &Player::BehaviorRootUpdate,
    &Player::BehaviorAttackUpdate,
	&Player::BehaviorJumpUpdate,
};
