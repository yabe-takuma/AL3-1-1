#pragma once
#include"ViewProjection.h"
#include"WorldTransform.h"
#include"input.h"
    /// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; }

	

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	private:
	ViewProjection viewProjection_;
	//追従対象
	const WorldTransform* target_ = nullptr;

	XINPUT_STATE joyState;

	Input* input_ = nullptr;

	

};
