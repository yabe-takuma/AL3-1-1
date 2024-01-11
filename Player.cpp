#include "Player.h"
#include"FakeBullet.h"
#include<cassert>
#include"Item.h"

Player::~Player() {
	for (PlayerBullet* playerbullet : playerbullet_) {
		delete playerbullet;
	}
}

void Player::Initialize(const std::vector<Model*>& models) {
	
	BaseCharacter::Initialize(models);
	
	SetParent(&worldTransformBody_);

	 InitializeFloatingGimmick();

	worldTransform_.translation_ = {6.0f, 0.0f, -70.0f};
	worldTransformBody_.translation_ = {3.0f, 0.5f, -65.0f};
	worldTransformHead_.translation_ = {0.0f, 1.5f, 0.0f};
	worldTransformL_arm_.translation_ = {-1.5f, 1.3f, 0.0f};
	
	worldTransformR_arm_.translation_ = {1.5f, 1.3f, 0.0f};

	worldTransformSord_.rotation_ = {0.0f, 1.6f, 0.0f};

	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	worldTransformSord_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	attack_.bulletcooltime = 0;

		modelbullet_.reset(Model::CreateFromOBJ("PlayerBullet", true));
	pow_ = 1;
	   
	isDead_ = false;
	isClear_ = false;
	sevepow_ = 0;

	behavior_ = Behavior::kRoot;
	
}

void Player::Update()
{

	BaseCharacter::Update();

	if (item_->IsDead_()&&sevepow_==0)
	{
		Pow();
		sevepow_ = 1;
	}

	
	if (fakebullet_->IsDead()) {
		BulletAttack();
		for (PlayerBullet* playerbullet : playerbullet_) {
			playerbullet->Update();
		}
	}
		// デスフラグの立った弾を削除
	playerbullet_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {

			delete bullet;
			return true;
		}
		return false;
	});
	
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

	

	if (isOnCollision_ ==true) {
		timer_++;
	}

	if (timer_ >= 100) {
		timer_ = 0;
		isOnCollision_ = false;
	}
	
	


	if (worldTransformBody_.translation_.x >= -2.5f && worldTransformBody_.translation_.x <= 13 && worldTransformBody_.translation_.z >= 123)
	{
		isClear_ = true;
	}

	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
	worldTransformSord_.UpdateMatrix();

	/*ImGui::Begin("player");
	ImGui::DragFloat3("position", &worldTransformBody_.translation_.x, 0.1f);
	ImGui::DragFloat3("position", &worldTransformHead_.translation_.x, 0.1f);
	ImGui::DragFloat3("position", &worldTransformR_arm_.rotation_.x, 0.01f);
	ImGui::DragFloat3("position", &worldTransformL_arm_.rotation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransformSord_.rotation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransformSord_.rotation_.x, 0.01f);
	ImGui::DragInt("HP", &HP, 1);
	ImGui::DragInt("Pow", &pow_, 1);

	ImGui::End();*/
}

void Player::Draw(ViewProjection& viewProjection)
{ 
// 3Dモデルを描画
	models_[0]->Draw(worldTransformBody_, viewProjection);
	//models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);
	if (behavior_ == Behavior::kAttack) {
		models_[4]->Draw(worldTransformSord_, viewProjection);
	}
	if (fakebullet_->IsDead()) {

		for (PlayerBullet* playerbullet : playerbullet_) {
			playerbullet->Draw(viewProjection);
		}
	}
}

void Player::SetViewProjection(const ViewProjection* viewProjection) {
	viewProjection_ = viewProjection;
}

void Player::BehaviorRootUpdate() 
{
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		speed = 0.2f;
		
		move = {
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

	UpdateFloatingGimmick();

}

void Player::BehaviorAttackUpdate() 
{
	const float kDegreeToRadian = 0.1f;
	attack_.kAnimMaxtime = 20;
	attack_.time++;
	
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B && attack_.time <= attack_.kAnimMaxtime/*&&attack_.weponcooltime>=100*/) {
		isWepon = true;
		isSordAlive_ = true;
		float frame = (float)attack_.time / attack_.kAnimMaxtime;
		float easeInSize = easeInSine(frame * frame);
		//float weaponAngle = 45 * kDegreeToRadian * easeInBack;
		float armAngle = 30 * kDegreeToRadian * easeInSize;

		float frame2 = (float)attack_.time / attack_.kAnimMaxtime;
		float easeInSize2 = easeInSine2(frame2 * frame2);
		// float weaponAngle = 45 * kDegreeToRadian * easeInBack;
		float armAngle2 = 30 * kDegreeToRadian * easeInSize2;

		worldTransformR_arm_.rotation_.x = -1.5f;
		worldTransformR_arm_.rotation_.y = -armAngle;

		worldTransformSord_.rotation_.x = 0.0f;
		worldTransformSord_.rotation_.y = -armAngle2;
	}
	else if (attack_.time >= attack_.kAnimMaxtime) {
		attack_.cooltime++;
		if (attack_.cooltime >= 30) {
			isSordAlive_ = false;
			attack_.time = 0;
			behaviorRequest_ = Behavior::kRoot;
			attack_.cooltime = 0;
		}
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
	worldTransformSord_.parent_ = parent;
}

void Player::Pow() { pow_ = pow_ + 1; }




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
	float PI = 0.975f;
	x = 1 - cos((x * PI) / 2); 
	return x;

}

float Player::easeInSine2(float x) {
	float PI = 3.14f;
	x = -2.0f - cos((x * PI) / 2);
	return x;
}

void Player::BulletAttack()
{
	if (attack_.bulletcooltime <= 10) {
		attack_.bulletcooltime++;
	}
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A&&attack_.bulletcooltime>=10) {
		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		// 速度ベクトルを自機の向きに合わせて回転させる(自キャラのワールド行列はmatWorld)
		velocity = TransformNormal(velocity, worldTransformBody_.matWorld_);

		// 敵の生成
		PlayerBullet* playerbullet = new PlayerBullet();
	

		playerbullet->Initialize(modelbullet_.get(),worldTransformBody_.translation_, velocity);

		velocity = Normalize(velocity);
		velocity = Multiply(kBulletSpeed, velocity);

		playerbullet_.push_back(playerbullet);
		attack_.bulletcooltime = 0;
	}

	
}

void Player::OnCollision() { 
	isDead_ = true;
	//HP = HP - 1;
}

void Player::OnCollision2()
{
	worldTransformBody_.translation_.z = worldTransformBody_.translation_.z - 1.0f;
	speed =  0;
}

Vector3 Player::GetWorldRadius()
{
	Vector3 worldRadius;

	worldRadius.x = worldTransformBody_.scale_.x;
	worldRadius.y = worldTransformBody_.scale_.y;
	worldRadius.z = worldTransformBody_.scale_.z;
	return worldRadius;
}

Vector3 Player::GetSordWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransformSord_.matWorld_.m[3][0];
	worldPos.y = worldTransformSord_.matWorld_.m[3][1];
	worldPos.z = worldTransformSord_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::GetSordWorldRadius()
{
	Vector3 worldRadius;

	worldRadius.x = worldTransformSord_.scale_.x+3.0f;
	worldRadius.y = worldTransformSord_.scale_.y+5.0f;
	worldRadius.z = worldTransformSord_.scale_.z+60.0f;
	return worldRadius;
}

void Player::InitializeFloatingGimmick() {
	floatingParameter_ = 0.5f;
	floatingParameterHead_ = 2.0f;
}

void Player::UpdateFloatingGimmick() {
	// 浮遊移動のサイクル<frame>
	const uint16_t fream = 70;
	// 1フレームでのパラメータ加算値
	const float step = 2.0f * 3.14f / fream;
	// パラメータを1ステップ分加算
	floatingParameter_ += step;

	// 2πを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * 3.14f);

	// 浮遊の振幅<π>
	const float floatingAmplitude = 0.3f;
	// 浮遊を座標に反映
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude - 0.5f;

	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * floatingAmplitude;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * floatingAmplitude;
}