#pragma once
#include "Model.h"
#include "WorldTransform.h"
class Wall {
public:
	void Initialize();

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
};
