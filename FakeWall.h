#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"ImGuiManager.h"
class FakeWall {
public:
	void Initialize();

	void Update();

	void Draw(ViewProjection& viewProjection);

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

};
