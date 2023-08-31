#include "LimitTimer.h"
#include <cassert>
void LimitTimer::Initialize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("Timer2.png");

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.5f, 5.0f, 0.1f};
	worldTransform_.translation_ = position;

	TimerInitialize();
}

void LimitTimer::Update() { 
	TimerUpdate();
	if (worldTransform_.scale_.y < 0.0f)
	{
		istimerlimit_ = true;
	}
	worldTransform_.UpdateMatrix(); }

void LimitTimer::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void LimitTimer::TimerInitialize()
{ kFireTimer_ = kFireInterval_; }

void LimitTimer::TimerUpdate()
{
	// タイマーカウントダウン
	kFireTimer_--;
	// 指定時間に達した
	if (kFireTimer_ <= 0) {
		worldTransform_.scale_.y = worldTransform_.scale_.y - 0.5f;
		// タイマーを初期化
		kFireTimer_ = kFireInterval_;
	}
}

void LimitTimer::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
