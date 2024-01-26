#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "SafeDelete.h"
#include "Sprite.h"
class TitleScene {
public:
	void Initialize();
	
	void Update();

	void Draw();

private:
	Sprite* sprite_ = nullptr;

};
