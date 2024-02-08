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
#include"ImGuiManager.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene {

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

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

	float easeOutBounce(float x);

	bool IsSceneEnd() { return isSceneEnd_; }
	Scene::SceneType NextScene() { return Scene::SceneType::kGameExplanation; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	bool isSceneEnd_ = false;
	bool isfadeout_ = false;

	float fadeourposX = 640.0f;
	float fadeourposY = -720.0f;

	float velocity = 10.0f;

	Sprite* titlesprite_ = nullptr;
	Sprite* fadeout_ = nullptr;

	XINPUT_STATE joyState;
	XINPUT_STATE prevjoyState;
};
