#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Player.h"
#include<memory>
#include"Skydome.h"
#include"Ground.h"
#include"DebugCamera.h"
#include"FollowCamera.h"
#include"Enemy.h"
#include"Wall.h"
#include"WeakEnemy.h"
#include<list>
#include <sstream>
#include"BreakWall.h"
#include"FakeWall.h"
#include"Item.h"
#include "Scene.h"
#include"FakeBullet.h"
#include"Sprite.h"
#include"Explanation.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

	struct Easing {
		int32_t time;
		int32_t kAnimMaxtime;
	};

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void EnemyGeneration(const Vector3& position,const Vector3& velocity);

	void LoadEnemyPopData();

	void UpdateEnemyPopCommands();

	void CheckAllCollisions();

	void LoadWallPopData();

	void UpdateWallPopCommands();

	void WallGeneration(const Vector3& position, const Vector3& scale);

	void Reset();

	void GameReset();

	void DrawUI();

	void ScoreInitialize();

	float easeOutBounce(float x);

	// 弾リストを取得
	const std::list <std::unique_ptr<WeakEnemy>>& GetWeakEnemys() const { return weakenemys_; }

	bool IsGameClear() { return isGameClear_; }
	Scene::SceneType NextGameScene() { return Scene::SceneType::kGameClear; }

	bool IsGameOver() { return isGameOver_; }
	Scene::SceneType NextGameOverScene() { return Scene::SceneType::kGameOver; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	std::unique_ptr<Model> model_;

	uint32_t textureHandle_ = 0u;

	ViewProjection viewprojection_;

	//自キャラ
	Player* player_ = nullptr;
	

	std::unique_ptr<Model> modelskydome_;

	std::unique_ptr<Skydome> skydome_;

	std::unique_ptr<Ground> ground_;

	std::unique_ptr<Model> modelground_;

	std::unique_ptr<FollowCamera> followcamera_;

	std::unique_ptr<Enemy> enemy_;

	std::list<std::unique_ptr<Wall>> walls_;
	std::unique_ptr<Model> modelwall_;

   std::list<std::unique_ptr<WeakEnemy>> weakenemys_;
	std::unique_ptr<Model> modelweakenemys_;

   std::unique_ptr<BreakWall> breakwall_;

   std::unique_ptr<FakeWall> fakewall_;

   std::unique_ptr<Item> item_;
   std::unique_ptr<Model> modelitem_;

   std::unique_ptr<FakeBullet> fakebullet_;
   std::unique_ptr<Model> modelfakebullet_;

   	// 自キャラモデル
   std::vector<Model*> playerModels;

   Vector3 velocity_;

   // 3Dモデル
   std::unique_ptr<Model> modelFighterBody_;
   std::unique_ptr<Model> modelFighterHead_;
   std::unique_ptr<Model> modelFighterL_arm_;
   std::unique_ptr<Model> modelFighterR_arm_;
   std::unique_ptr<Model> modelsord_;

    // 敵発生コマンド
   std::stringstream enemyPopCommands;

    // 敵発生コマンド
   std::stringstream wallPopCommands;

   Vector3 scale_;

	//デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	// デバッグカメラ有効
	bool isDebugCameraAcctive_ = false;

	bool isGameClear_ = false;
	bool isGameOver_ = false;

	int32_t isoncollision_=0;

	std::unique_ptr<Sprite> uiSprite_;
	std::unique_ptr<Sprite> ui2Sprite_;

	std::unique_ptr<Sprite> scoresprite_[12];
	uint32_t scoretexture_[10];

	std::unique_ptr<Explanation> explanation_;

	uint32_t soundDataHandle_[4] = {0, 0,0,0};

	std::unique_ptr<Sprite> Feadsprite_;

	Vector2 pos_;

	Easing easing_;

	bool isFead_ = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
