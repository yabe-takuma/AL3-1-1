#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include"Model.h"
class TitleScene {
public:
	void Initialize();
	
	void Update();

	void Draw();

private:
	Sprite* sprite_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
};
