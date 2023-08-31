#pragma once
#include"Model.h"
#include"WorldTransform.h"
class LimitTimer {
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void TimerInitialize();

	void TimerUpdate();

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	bool IsTimerLimit() const { return istimerlimit_; };

	static const int kFireInterval_ = 60;

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	int32_t kFireTimer_ = 0;

	bool istimerlimit_ = false;
};
