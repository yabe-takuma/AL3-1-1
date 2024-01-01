#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include<memory>

class Player;

class Enemy {
public:
	void Initialize();

	void Update();

	void Draw(ViewProjection& viewProjection);

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	void OnCollision();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Player* player_=nullptr;

};
