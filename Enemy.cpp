#include "Enemy.h"
#include <cassert>
#include "IMGuiManager.h"
#include "Player.h"
#include"GameScene.h"

 Enemy::~Enemy() {
	/*for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}*/
	 //delete enemyhp_;
 }

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	modelenemy_ = model;
	model_ = model;
	modelenemy_ = Model::CreateFromOBJ("Enemy", true);
	textureHandle_ = TextureManager::Load("Explosion.png");

	worldTransform_;

	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	//worldTransform_.translation_ = {6.0f, 2.0f, 50.0f};

	

	worldTransform_.Initialize();
	velocity_ = velocity;

	

	// 接近フェーズ初期化
	ApproachInitialize();

	HPInitialize();

	ExplorionInitialize();

	//Vector3 position_ = {0.0f, 0.0f, 20.0f};
	//enemyhp_ = new EnemyHP();
	//enemyhp_->Initialize(model_, position_);

}

void Enemy::Update() {
	worldTransform_.UpdateMatrix();
	//worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity_);
	
	

	switch (phase_) {
	case Phase::Approach:
	default:
		Approach();
		break;
	case Phase::Leave:
		Leave();
		break;
	}

	ApproachUpdate();

	//for (EnemyBullet* bullet : bullets_)
	//{
	//	bullet->Update();
	//}

	//// デスフラグの立った弾を削除
	//bullets_.remove_if([](EnemyBullet* bullet) {
	//	if (bullet->IsDead()) {
	//		delete bullet;
	//		return true;
	//	}
	//	return false;
	//});

	if (hp_ <= 0)
	{
		isexplosion_ = true;
		ExplorionUpdate();
	}

	
	
	ImGui::Begin("Enemy");
	ImGui::DragInt("ExplosionTimer", &kExplosionTimer_, 1);

	    ImGui::End();

}

void Enemy::Draw(const ViewProjection& viewProjection) {
	if (hp_ >= 1) {

		modelenemy_->Draw(worldTransform_, viewProjection);
	}
	else
	{
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	}
	/*for (EnemyBullet* bullet : bullets_) {
	    bullet->Draw(viewProjection);
	}*/
	//if (enemyhp_ != nullptr) {

	//	enemyhp_->Draw(viewProjection);
	//}
}

void Enemy::Fire() {
	const float kBulletSpeed = 3.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	GetWorldPosition();
	velocity = Subtract(player_->GetWorldPosition(), GetWorldPosition());

	velocity = Normalize(velocity);
	velocity = Multiply(kBulletSpeed, velocity);

	EnemyBullet* newEnemyBullet = new EnemyBullet();
	newEnemyBullet->Initialize(model_, worldTransform_.translation_, velocity);

	gameScene_->AddEnemyBullet(newEnemyBullet);
}

void Enemy::Approach() {
	// 移動(ベクトルを加算)
	Add(worldTransform_.translation_, velocity_);
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	const float kEnemySpeed = 0.1f;
	velocity_ = {kEnemySpeed, -kEnemySpeed, 0};
	// 移動(ベクトルを加算)
	Add(worldTransform_.translation_, velocity_);
}

void Enemy::ApproachInitialize() {
	// 発射タイマーを初期化
	kFireTimer_ = kFireInterval_;
}

void Enemy::ApproachUpdate() {

	// 発射タイマーカウントダウン
	kFireTimer_--;
	// 指定時間に達した
	if (kFireTimer_ <= 0) {
		// 弾を発射
		Fire();
		// 発射タイマーを初期化
		kFireTimer_ = kFireInterval_;
	}
}

void Enemy::HPInitialize()
{ hp_ = HP_; }

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Enemy::GetWorldRadius() {
	Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;
}

void Enemy::OnCollision() {
	
		hp_--;
	
	
}
void Enemy::ExplorionInitialize()
{ kExplosionTimer_ = kExplosionInterval_; }

void Enemy::ExplorionUpdate()
{ 
	kExplosionTimer_--;

	if (kExplosionTimer_ <= 0)
	{
	isDead_ = true;
	kExplosionTimer_ = kExplosionInterval_;
	}


}
