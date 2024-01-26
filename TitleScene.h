#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include"Model.h"
#include"Scene.h"
class TitleScene {
public:

	TitleScene();

	~TitleScene();

	void Initialize();
	
	void Update();

	void Draw();

	void DrawUI();

	bool IsSceneEnd() { return isSceneEnd_; }
	Scene::SceneType NextScene() { return Scene::SceneType::kGamePlay; }

private:
	Sprite* titlesprite_[2] = {nullptr,nullptr};
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isSceneEnd_ = false;

	bool isFead_ = false;

	Vector2 pos_;

	Vector2 velocity_;

	Vector4 color_;

	XINPUT_STATE joyState;
	XINPUT_STATE prevjoyState;
};
