#include "Player.h"
#include "IMGuiManager.h"
#include <cassert>

Player::~Player() {
	for (PlayerBullet* bullet_ : bullets_) {

		delete bullet_;
	}
	delete sprite2DReticle_;
}

void Player::Initialize(Model* model, uint32_t textureHandle, const Vector3& Position) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();

	worldTransform_.translation_ = Position;

	// 3Dレティクルのワールドトランスフォーム初期化
	worldTransform3DReticle_.Initialize();

	// SetParent(GetWorldTransform3DReticle())

	// HPInitialize();

	// レティクル用テクスチャ取得
	uint32_t textureReticle= TextureManager::Load("Reticle.png");

	SpritePosition = {worldTransform3DReticle_.translation_.x,worldTransform3DReticle_.translation_.y};

	// スプライト生成
	sprite2DReticle_ =
	    Sprite::Create(textureReticle, SpritePosition, {1.0f,1.0f,1.0f,1.0f}, {0.5f, 0.5f}, false, false);
}

void Player::Update(ViewProjection& viewProjection_) {

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

	// キャラクター攻撃処理
	Attack();

	// 自機のワールド座標から3Dレティクルのワールド座標を計算

	// 自機から3Dレティクルへの距離
	//const float kDistancePlayerTo3DReticle = 50.0f;
	//// 自機から3Dレティクルへのオフセット(z+向き)
	//Vector3 offset = {0, 0, 1.0f};
	//// 自機のワールド行列の回転を反映
	//offset = TransformNormal(offset, worldTransform_.matWorld_);

	//// ベクトルの長さを整える
	//offset = Normalize(offset);
	//offset = Multiply(kDistancePlayerTo3DReticle, offset);

	//// 3Dレティクルの座標を指定
	//worldTransform3DReticle_.translation_ = Add(GetWorldPosition3DReticle(), offset);

	//worldTransform3DReticle_.UpdateMatrix();

	//// 3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算

	//// 3Dレティクルのワールド行列からワールド座標を取得
	//Vector3 positionReticle = GetWorldPosition();

	// ビューポート行列
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	//// ビュー行列とプロジェクション行列、ビューポート行列を合成する
	//Matrix4x4 matViewProjectionViewport =
	//    Multiply(Multiply(viewProjection_.matView,viewProjection_.matProjection), matViewport);

	//// ワールドからスクリーン座標変換(ここで3Dから2Dになる)
	//positionReticle = Transform(positionReticle, matViewProjectionViewport);

	//// スプライトのレティクルに座標設定
	//sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));

	ScreenWorldTransformation(viewProjection_, matViewport);

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

	// ImGui::DragInt("HP", &hp_, 1.0f);
	ImGui::Text("2DReticle:(%f,%f)", &worldTransform3DReticle_.translation_.x, worldTransform_.translation_.y);


	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	for (PlayerBullet* bullet : bullets_) {

		bullet->Draw(viewProjection_);
	}
	// 3Dレティクルを描画
	//model_->Draw(worldTransform3DReticle_, viewProjection_);
}

void Player::DrawUI() { sprite2DReticle_->Draw(); }

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		// 速度ベクトルを自機の向きに合わせて回転させる(自キャラのワールド行列はmatWorld)
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾を生成し,初期化
		PlayerBullet* newBullet = new PlayerBullet();

		// 自機から照準オブジェクトへのベクトル
		// 3Dレティクルのワールド座標 - プレイヤーのワールド座標
		velocity = Subtract(GetWorldPosition3DReticle(), GetWorldPosition());
		velocity = Normalize(velocity);
		velocity = Multiply(kBulletSpeed, velocity);

		newBullet->Initialize(model_, GetWorldPosition(), velocity);

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

Vector3 Player::GetWorldPosition3DReticle() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

	return worldPos;
}

void Player::HPInitialize() { hp_ = HP; }

void Player::OnCollision() {
	/*hp_--;

	if (hp_ <= 0) {
	    isDead_ = true;
	}*/
}

void Player::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}

void Player::ScreenWorldTransformation(ViewProjection& viewprojection_,Matrix4x4& matViewport)
{ POINT mousePosition;
//マウス座標(スクリーン座標)を取得する
	GetCursorPos(&mousePosition);

	// クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	// スプライトのレティクルに座標設定
	sprite2DReticle_->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));


	// ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPV = Multiply(viewprojection_.matView, Multiply(viewprojection_.matProjection, matViewport));
	// 合成行列の逆行列を計算する
	Matrix4x4 matInverseVPV = Inverse(matVPV);
	
	// スクリーン座標
	Vector3 posNear = Vector3((float)mousePosition.x, (float)mousePosition.y, 0);
	Vector3 posFar = Vector3((float)mousePosition.x, (float)mousePosition.y, 1);

	// スクリーン座標系からワールド座標系へ
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	// マウスレイの方向
	Vector3 mouseDirection = Subtract(posFar, posNear);
	mouseDirection = Normalize(mouseDirection);
	// カメラから照準オブジェクトの座標
	const float kDistanceTestobject = 50;
	
	mouseDirection = Multiply(kDistanceTestobject, mouseDirection);

	worldTransform3DReticle_.translation_ = Add(posNear,mouseDirection);
	worldTransform3DReticle_.UpdateMatrix();

	ImGui::Begin("Player");
	
	ImGui::Text("Near:(%.2f,%.2f,%.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%.2f,%.2f,%.2f)", posFar.x, posFar.y, posFar.z);
	ImGui::Text(
	    "3DReticle:(%.2f,%.2f,%.2f)", worldTransform3DReticle_.translation_.x,
	    worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	ImGui::End();
	
}