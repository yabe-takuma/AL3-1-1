#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"

#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"

class GameClear {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameClear();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameClear();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	///< summary>
	/// 描画
	/// </summary>
	void Draw();

	void DrawUI();

	void Reset();

	bool IsSceneEnd() { return isSceneEnd_; }
	Scene::SceneType NextScene() { return Scene::SceneType::kGamePlay; }

	bool IsTitleScene() { return isTitleScene_; }
	Scene::SceneType NextTitleScene() { return Scene::SceneType::kTitle; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	bool isSceneEnd_ = false;
	bool isTitleScene_ = false;

	Sprite* titlesprite_ = nullptr;

	XINPUT_STATE joyState;
	XINPUT_STATE prevjoyState;

	Sprite* Feadsprite_ = nullptr;

	Vector2 pos_;

	Vector4 color_;

	bool isFead_[2] = {false,false};
	
	
};
