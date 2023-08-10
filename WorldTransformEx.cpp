#include "Matrix4x4.h"
#include "Vector3.h"
#include "WorldTransform.h"


void WorldTransform::UpdateMatrix() {
	matWorld_.m;

	// スケール、回転、平行移動を合成して行列を計算する
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	

	TransferMatrix();
}