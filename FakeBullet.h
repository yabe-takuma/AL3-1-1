#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"ImGuiManager.h"



class FakeBullet {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void OnCollision();

	

	Vector3 GetWorldPosition();

	// ワールドradiusを取得
	Vector3 GetWorldRadius();

	bool IsDead() const { return isDead_; }

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	bool isDead_ = false;

	

};
