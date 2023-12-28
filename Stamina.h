#pragma once
#include"WorldTransform.h"
#include"Model.h"
class Stamina {
public:
	void Initialize();

	void Update();

	void Draw(ViewProjection& viewProjection);

	static const int isCooltime = 120;

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	int32_t cooltime_;

};
