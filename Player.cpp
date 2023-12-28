#include "Player.h"
#include<cassert>

Player::~Player() { delete sprite2DReticle_; }

void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	// 3Dレティクルのワールドトランスフォーム初期化
	worldTransform3DReticle_.Initialize();

	// レティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("uvChecker.png");

	// スプライト生成
	sprite2DReticle_ =
	    Sprite::Create(textureReticle, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

}

void Player::Update(ViewProjection& viewProjection) {

	// 座標を移動させる(1フレーム分の移動量を足し込む)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	Attack();

	if (input_->IsPressMouse(WM_RBUTTONDOWN == 0))
	{
		isSpeed = true;
	}

	if (isSpeed == true)
	{
		velocity_.z = 0.0f;
	}
	else if (isSpeed == false)
	{
		velocity_.z = 1.0f;
	}

	// 自機のワールド座標から3Dレティクルのワールド座標を計算

	// 自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 50.0f;
	// 自機から3Dレティクルへのオフセット(z+向き)
	Vector3 offset = {0, 0, 1.0f};
	// 自機のワールド行列の回転を反映
	offset = TransformNormal(offset, worldTransform_.matWorld_);

	// ベクトルの長さを整える
	offset = Normalize(offset);
	offset = Multiply(kDistancePlayerTo3DReticle, offset);

	// 3Dレティクルの座標を指定
	worldTransform3DReticle_.translation_ = Add(GetWorldPosition3DReticle(), offset);

	worldTransform3DReticle_.UpdateMatrix();

	//行列を定数バッファに転送
	//worldTransform_.TransferMatrix();

	

	// 3Dレティクルのワールド行列からワールド座標を取得
	Vector3 positionReticle = GetWorldPosition();

	// ビューポート行列
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	//// ビュー行列とプロジェクション行列、ビューポート行列を合成する
	Matrix4x4 matViewProjectionViewport =
	    Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);

	// ワールドからスクリーン座標変換(ここで3Dから2Dになる)
	positionReticle = Transform(positionReticle, matViewProjectionViewport);

	// スプライトのレティクルに座標設定
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));

	

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

	////座標移動(ベクトルの加算)
	//worldTransform_.translation_= Add(worldTransform_.translation_,move);

	ScreenWorldTransformation(viewProjection);

	worldTransform_.UpdateMatrix();

	ImGui::Begin("Window");
	ImGui::DragFloat3("position", &worldTransform3DReticle_.translation_.x, 0.01f);
	ImGui::End();

}

void Player::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	model_->Draw(worldTransform3DReticle_, viewProjection, textureHandle_);
}

void Player::ScreenWorldTransformation(ViewProjection& viewProjection) {
	POINT mousePosition;
	// マウス座標(スクリーン座標)を取得する
	GetCursorPos(&mousePosition);

	// クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	// スプライトのレティクルに座標設定
	sprite2DReticle_->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));

	// ビューポート行列
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	Matrix4x4 matInverseViewport = Inverse(matViewport);
	Matrix4x4 matInverseView = Inverse(viewProjection.matView);
	Matrix4x4 matInverseProjection = Inverse(viewProjection.matProjection);

	// ビュープロジェクションビューポート合成行列
	Matrix4x4 matInverseVPV =
	    Multiply(Multiply(matInverseViewport, matInverseProjection), matInverseView);

	// Matrix4x4 matVPV = Multiply(Multiply(viewProjection.matView, viewProjection.matProjection),
	// matViewport);
	// 合成行列の逆行列を計算する
	// Matrix4x4 matInverseVPV = Inverse(matVPV);

	// スクリーン座標
	Vector3 posNear = Vector3((float)mousePosition.x, 0, 0);
	Vector3 posFar = Vector3((float)mousePosition.x, 1, 1);

	// スクリーン座標系からワールド座標系へ
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	// マウスレイの方向
	Vector3 mouseDirection = Subtract(posFar, posNear);
	mouseDirection = Normalize(mouseDirection);
	// カメラから照準オブジェクトの座標
	const float kDistanceTestobject = 100;

	mouseDirection = Multiply(kDistanceTestobject, mouseDirection);
	
worldTransform3DReticle_.translation_ = Add(posNear, mouseDirection);
	worldTransform3DReticle_.translation_.y = 0.0f;
	worldTransform3DReticle_.UpdateMatrix();

	
}

void Player::Attack() 
{
	if (input_->IsPressMouse(WM_RBUTTONDOWN == 0)) {

		

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		// 速度ベクトルを自機の向きに合わせて回転させる(自キャラのワールド行列はmatWorld)
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		
		
		// 自機から照準オブジェクトへのベクトル
		// 3Dレティクルのワールド座標 - プレイヤーのワールド座標
		velocity = Subtract(GetWorldPosition3DReticle(), GetWorldPosition());
		velocity = Normalize(velocity);
		velocity = Multiply(kBulletSpeed, velocity);
		
		velocity_ = velocity;

		
		
	}
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

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::DrawUI() {  }