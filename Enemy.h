#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include<memory>
#include"ImGuiManager.h"

class Player;

class Enemy {
public:
	void Initialize();

	void Update();

	void Draw(ViewProjection& viewProjection);

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	void OnCollision();

	bool IsOnCollision() const { return isOnCollision_; }

	// ワールドradiusを取得
	Vector3 GetWorldRadius();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Player* player_=nullptr;

	float kSpeed_ = 0.3f;

	bool isOnCollision_ = false;

	int32_t timer_;

};
