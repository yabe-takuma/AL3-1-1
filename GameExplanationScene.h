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
class GameExplanationScene {

	struct Easing {
		int32_t time;
		int32_t kAnimMaxtime;
	};

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameExplanationScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameExplanationScene();

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
	Scene::SceneType NextScene() { return Scene::SceneType::kGamePlay; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	bool isSceneEnd_ = false;

	Sprite* titlesprite_ = nullptr;

	Sprite* Feadsprite_=nullptr;

	Vector2 pos_;

	Easing easing_;

	bool isFead_ = false;

	XINPUT_STATE joyState;
	XINPUT_STATE prevjoyState;
};
