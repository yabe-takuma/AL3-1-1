#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"BaseWall.h"
#include"ImGuiManager.h"

class GameScene;

class Wall : public BaseWall {
public:
	void Initialize(Vector3 position, Vector3 scale);

	void Update() ;

	void Draw(ViewProjection& viewProjection) ;

	void OnCollision();

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

		// ワールド座標を取得
	Vector3 GetWorldPosition();

	// ワールドradiusを取得
	Vector3 GetWorldRadius();

private:
	WorldTransform worldTransform_;
	
	uint32_t textureHandle_;

	Model* model_ = nullptr;

	GameScene* gameScene_ = nullptr;
};
