#include "FollowCamera.h"

void FollowCamera::Initialize() {
	viewProjection_.translation_;
	viewProjection_.matProjection;
	viewProjection_.matView;
	viewProjection_.rotation_ = {0.0f, 0.0f, 0.0f};
	viewProjection_.Initialize();
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void FollowCamera::Update() {

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		const float kRotSpeed = 0.1f;

		viewProjection_.rotation_.y += joyState.Gamepad.sThumbRX / SHRT_MAX * kRotSpeed;
	}

	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		offset = TransformNormal(offset, MakeRotateYMatrix(viewProjection_.rotation_.y));

		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}

	

	viewProjection_.UpdateMatrix();
}
