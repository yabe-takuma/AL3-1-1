#pragma once
#include"Model.h"
#include"WorldTransform.h"
class Ground {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

};
