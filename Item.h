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

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

};
