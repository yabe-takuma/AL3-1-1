#include "Matrix4x4.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include <MathFunction.h>


void WorldTransform::UpdateMatrix() {
	matWorld_.m;

	// スケール、回転、平行移動を合成して行列を計算する
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	// 親があれば親のワールド行列に掛ける
	if (parent_) {

		matWorld_ = Multiply(matWorld_, parent_->matWorld_);
	}
    
	TransferMatrix();
}