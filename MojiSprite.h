#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"
class MojiSprite {
public:
	void Initialize();

	void Update();

	void DrawUI();

	private:
	Sprite* texturesprite_ = nullptr;



};
