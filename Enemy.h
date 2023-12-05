#pragma once
#include"WorldTransform.h"
#include "BaseCharacter.h"
#include<cmath>

class Enemy : public BaseCharacter {
public:
	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(ViewProjection& viewProjection) override;

	
	private:
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	
	float angularVelocity = 0.14f;
	float angle = 0.0f;
	float deltaTime = 0.1f;

	// カメラのビュープロジェクション
	ViewProjection viewProjection_;

};
