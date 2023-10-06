#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include"Skydome.h"
#include"RailCamera.h"
#include<list>
#include <sstream>
#include"Scene.h"
#include"EnemyHP.h"
#include"EnemyUI.h"
#include"PlayerHP.h"
#include"PlayerUI.h"
#include"LimitTimer.h"
#include"LImitTimerUI.h"
#include"Frame.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

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

	///< summary>
	/// 衝突判定と応答
	///  </summary>
	void CheckAllCollisions();

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name"enemyBullet">敵弾</param>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void EnemyGeneration(const Vector3& position);

	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { return enemybullets_; }

	// 弾リストを取得
	const std::list<Enemy*>& GetEnemys() const { return enemys_; }

	bool IsSceneEnd() { return isSceneEnd_; }
	Scene::SceneType NextScene() { return Scene::SceneType::kGameOver; }

	bool IsGameClear() { return isGameClear_; }
	Scene::SceneType NextGameScene() { return Scene::SceneType::kGameClear; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	Model* model_ = nullptr;

	ViewProjection viewProjection_;
	Player* player_ = nullptr;
	Model* modelplayer_ = nullptr;
	Enemy* enemy_ = nullptr;

	// 3Dモデル
	Model* modelSkydome_ = nullptr;
	Skydome* skydome_ = nullptr;

	// レールカメラ
	RailCamera* railcamera_ = nullptr;

	// 敵弾
	std::list<EnemyBullet*> enemybullets_;

	// 敵
	 std::list<Enemy*> enemys_;

	 // 敵発生コマンド
	 std::stringstream enemyPopCommands;

	// デバッグカメラ有効
	bool isDebugCameraAcctive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	bool isSceneEnd_ = false;

	EnemyHP* enemyhp_ = nullptr;

	EnemyUI* enemyui_ = nullptr;

	PlayerHP* playerhp_ = nullptr;

	PlayerUI* playerui_ = nullptr;

	LimitTimer* limittimer_ = nullptr;

	LImitTimerUI* limittimerui_ = nullptr;

	Frame* frame_ = nullptr;

	bool isGameClear_ = false;

	/*uint32_t textureHandle_ = 0u;

	Model* model_ = nullptr;*/

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
