#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"ImGuiManager.h"

class Player;

class BreakWall {
public:
	void Initialize();

	void Update();

	void Draw(ViewProjection& viewProjection);

	void OnCollision();

	void SetPlayer(Player* player) { player_ = player; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// ワールドradiusを取得
	Vector3 GetWorldRadius();

	bool IsOnCollision() const { return isOnCollision_; }

	private:
	WorldTransform worldTransform_;

	WorldTransform worldTransformhp_;

	Model* model_ = nullptr;

	Model* modelhp_ = nullptr;

	int32_t hp_;

	bool isOnCollision_ = false;

	int32_t timer_;

	Player* player_ = nullptr;

};
