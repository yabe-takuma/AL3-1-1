#pragma once
#include"Model.h"
#include"WorldTransform.h"

class EnemyHP {
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void OnCollision();



	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	bool EnemyLimit() const { return isenemylimit_; }

	private:
	WorldTransform worldTransform_;

	Model* model_=nullptr;

	uint32_t textureHandle_ = 0u;

	bool isenemylimit_ = false;


};
