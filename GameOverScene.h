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
class GameOverScene {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameOverScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameOverScene();

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
	Scene::SceneType NextScene() { return Scene::SceneType::kTitle; }

	bool IsGameScene() { return isGameScene_; }
	Scene::SceneType NextGameScene() { return Scene::SceneType::kGamePlay; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	bool isSceneEnd_ = false;
	bool isGameScene_ = false;

	Sprite* titlesprite_ = nullptr;

	Sprite* Feadsprite_ = nullptr;

	Vector2 pos_;

	Vector4 color_;

	bool isFead_[2] = {false, false};

	XINPUT_STATE joyState;
	XINPUT_STATE prevjoyState;
};
