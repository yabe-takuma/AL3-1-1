#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"ImGuiManager.h"
class Item {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void OnCollision();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// ワールドradiusを取得
	Vector3 GetWorldRadius();

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

};
