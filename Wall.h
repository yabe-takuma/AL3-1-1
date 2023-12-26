#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"BaseWall.h"
#include"ImGuiManager.h"
class Wall : public BaseWall {
public:
	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(ViewProjection& viewProjection) override;

private:
	WorldTransform worldTransform_[34];
	
	uint32_t textureHandle_;

	Model* model_ = nullptr;
};
