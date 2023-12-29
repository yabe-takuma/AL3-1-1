#include "Player.h"
#include<cassert>

void Player::Initialize(const std::vector<Model*>& models) {
	
	BaseCharacter::Initialize(models);
	
	SetParent(&worldTransformBody_);

	worldTransform_.translation_ = {6.0f, 0.0f, -70.0f};
	worldTransformBody_.translation_ = {0.0f, 0.5f, -70.0f};
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

void Player::Update()
{

	BaseCharacter::Update();

	if (behaviorRequest_) {
		// 振るまいを変更する
		behavior_ = behaviorRequest_.value();
		// 各振るまいごとの初期化の実行
		(this->*pBehaviorInitializeTable[static_cast<size_t>(behavior_)])();
		// 振るまいリクエストリセット
		behaviorRequest_ = std::nullopt;
	}
	(this->*pBehaviorUpdateTable[static_cast<size_t>(behavior_)])();
	
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

	

	

	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();

	ImGui::Begin("player");
	ImGui::DragFloat3("position", &worldTransformBody_.translation_.x, 0.1f);
	ImGui::DragFloat3("position", &worldTransformHead_.translation_.x, 0.1f);
	ImGui::DragFloat3("position", &worldTransformR_arm_.translation_.x, 0.1f);
	ImGui::DragFloat3("position", &worldTransformL_arm_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransformL_arm_.rotation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransformR_arm_.rotation_.x, 0.01f);
	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection)
{ 
// 3Dモデルを描画
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);

}

void Player::SetViewProjection(const ViewProjection* viewProjection) {
	viewProjection_ = viewProjection;
}

void Player::BehaviorRootUpdate() 
{
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		const float speed = 0.3f;
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX * SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY * SHRT_MAX * speed};

		// 移動量に速さを反映
		move = Normalize(move);
		move = Multiply(speed, move);
		move = TransformNormal(move, MakeRotateYMatrix(viewProjection_->rotation_.y));
		if (move.x != 0.0f) {

			worldTransformBody_.rotation_.y = std::atan2(move.x, move.z);
		}

		// 座標移動(ベクトルの加算)
		worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, move);
	}

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		behavior_ = Behavior::kAttack;
	}
}

void Player::BehaviorAttackUpdate() 
{
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		worldTransformL_arm_.rotation_.x = -1.5f;
		worldTransformL_arm_.rotation_.y = -0.5f;
	}
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		behaviorRequest_ = Behavior::kRoot;
	}

	}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransformBody_.matWorld_.m[3][0];
	worldPos.y = worldTransformBody_.matWorld_.m[3][1];
	worldPos.z = worldTransformBody_.matWorld_.m[3][2];

	return worldPos;
}

void Player::SetParent(const WorldTransform* parent) {
	worldTransformHead_.parent_ = parent;
	worldTransformL_arm_.parent_ = parent;
	worldTransformR_arm_.parent_ = parent;
	worldTransformHammer_.parent_ = parent;
}

void Player::BehaviorRootInitialize() {

	worldTransformL_arm_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm_.rotation_ = {0.0f, 0.0f, 0.0f};
}

void Player::BeheviorAttackInitialize() { attack_.time = 0; }

void (Player::*Player::pBehaviorInitializeTable[])() = {
    &Player::BehaviorRootInitialize,
    &Player::BeheviorAttackInitialize,
};

void (Player::*Player::pBehaviorUpdateTable[])() = {
    &Player::BehaviorRootUpdate,
    &Player::BehaviorAttackUpdate,
};

float Player::easeInSine(float x)
{ 
	return 1 - Math.cos((x * Math.PI) / 2); 

}