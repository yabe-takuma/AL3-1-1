#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"ImGuiManager.h"

class GameScene;

class WeakEnemy {
public:
	void Initialize(Vector3 position, Vector3 velocity);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void OnCollision();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// ワールドradiusを取得
	Vector3 GetWorldRadius();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	GameScene* gameScene_ = nullptr;

	bool isspeed = false;

	Vector3 seveposition_;

	float Radius_ = 10.0f; 

	Vector3 velocity_;

};
