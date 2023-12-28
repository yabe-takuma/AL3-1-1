#pragma once
#include"WorldTransform.h"
#include"Model.h"

class GameScene;

class WeakEnemy {
public:
	void Initialize(Vector3 position);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	GameScene* gameScene_ = nullptr;

};
