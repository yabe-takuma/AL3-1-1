#include "RailCamera.h"
#include "ImGuiManager.h"
void RailCamera::Initialize(
    const Vector3& velocity, const WorldTransform& position, const WorldTransform& rotation) {

	// ワールドトランスフォームの初期設定
	worldTransform_ = position;
	worldTransform_ = rotation;
	worldTransform_.translation_ = {0.0f, 0.0f, -100.0f};
	// ビュープロジェクションの初期化
	viewprojection_.Initialize();

	velocity_ = velocity;
	worldTransform_.Initialize();

	viewprojection_.farZ = 1200.0f;
	viewprojection_.Initialize();
}



void RailCamera::Update() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	// worldTransform_.rotation_ = Add(worldTransform_.rotation_, velocity_);

	viewprojection_.matView = Inverse(worldTransform_.matWorld_);
	ImGui::Begin("Camera");
	float CameraTranslation[] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::SliderFloat3("CameraTranslation", CameraTranslation, 50.0f, -20.0f);
	worldTransform_.translation_.x = CameraTranslation[0];
	worldTransform_.translation_.y = CameraTranslation[1];
	worldTransform_.translation_.z = CameraTranslation[2];

	float CameraRotation[] = {
	    worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z};
	ImGui::SliderFloat3("CameraRotation", CameraRotation, 20.0f, -20.0f);
	worldTransform_.rotation_.x = CameraRotation[0];
	worldTransform_.rotation_.y = CameraRotation[1];
	worldTransform_.rotation_.z = CameraRotation[2];
	worldTransform_.UpdateMatrix();
	ImGui::End();
}

WorldTransform RailCamera::GetWorldPosition() {
	// ワールド座標を入れる変数
	WorldTransform worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.translation_.x = worldTransform_.matWorld_.m[3][0];
	worldPos.translation_.y = worldTransform_.matWorld_.m[3][1];
	worldPos.translation_.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

WorldTransform RailCamera::GetWorldRotation() {
	// ワールド座標を入れる変数
	WorldTransform worldRot;
	// ワールド行列の回転成分を取得(ワールド座標)
	worldRot.rotation_.x = worldTransform_.matWorld_.m[2][0];
	worldRot.rotation_.y = worldTransform_.matWorld_.m[2][1];
	worldRot.rotation_.z = worldTransform_.matWorld_.m[2][2];

	return worldRot;
}